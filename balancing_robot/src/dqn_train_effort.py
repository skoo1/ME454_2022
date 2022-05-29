import rospy
import math
import numpy as np
import time

from std_srvs.srv import Empty
from gazebo_msgs.msg import LinkStates
from std_msgs.msg import Float64


pubLeftWheelEffort  = rospy.Publisher('/two_wheel_robot/left_wheel_effort_controller/command', Float64, queue_size=1)
pubRightWheelEffort = rospy.Publisher('/two_wheel_robot/right_wheel_effort_controller/command', Float64, queue_size=1)

reset_world = rospy.ServiceProxy('/gazebo/reset_world', Empty)
unpause = rospy.ServiceProxy('/gazebo/unpause_physics', Empty)
pause = rospy.ServiceProxy('/gazebo/pause_physics', Empty)

rospy.init_node('cartpole_control_script')
rate = rospy.Rate(120)


####### DQN from minimalRL ########
import collections
import random

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

#Hyperparameters
learning_rate = 0.001
gamma         = 0.98
buffer_limit  = 50000
batch_size    = 32

class ReplayBuffer():
    def __init__(self):
        self.buffer = collections.deque(maxlen=buffer_limit)
    
    def put(self, transition):
        self.buffer.append(transition)
    
    def sample(self, n):
        mini_batch = random.sample(self.buffer, n)
        s_lst, a_lst, r_lst, s_prime_lst, done_mask_lst = [], [], [], [], []
        
        for transition in mini_batch:
            s, a, r, s_prime, done_mask = transition
            s_lst.append(s)
            a_lst.append([a])
            r_lst.append([r])
            s_prime_lst.append(s_prime)
            done_mask_lst.append([done_mask])

        return torch.tensor(s_lst, dtype=torch.float), torch.tensor(a_lst), \
               torch.tensor(r_lst), torch.tensor(s_prime_lst, dtype=torch.float), \
               torch.tensor(done_mask_lst)
    
    def size(self):
        return len(self.buffer)

class Qnet(nn.Module):
    def __init__(self):
        super(Qnet, self).__init__()
        self.fc1 = nn.Linear(4, 128)
        self.fc2 = nn.Linear(128, 128)
        self.fc3 = nn.Linear(128, 2)

    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x
      
    def sample_action(self, obs, epsilon):
        out = self.forward(obs)
        coin = random.random()
        if coin < epsilon:
            return random.randint(0,1)
        else : 
            return out.argmax().item()
            
def train(q, q_target, memory, optimizer):
    for i in range(10):
        s,a,r,s_prime,done_mask = memory.sample(batch_size)

        q_out = q(s)
        q_a = q_out.gather(1,a)
        max_q_prime = q_target(s_prime).max(1)[0].unsqueeze(1)
        target = r + gamma * max_q_prime * done_mask
        loss = F.smooth_l1_loss(q_a, target)
        
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

####### END of DQN from minimalRL ########


class RobotState(object):
    def __init__(self):
        self.body_x = 0.0
        self.body_x_dot = 0.0
        self.body_theta = 0.0
        self.body_theta_dot = 0.0
        self.robot_state = [self.body_x, self.body_x_dot, self.body_theta, self.body_theta_dot]
        
        self.data = None

        self.theta_threshold = 0.21
        self.x_threshold = 1.0

        self.current_effort = 0.0
        self.done = False


robot_state = RobotState()

def set_robot_state():
    robot_state.robot_state = [robot_state.body_x, robot_state.body_x_dot, robot_state.body_theta, robot_state.body_theta_dot]


def reset():
    rospy.wait_for_service('/gazebo/reset_world')
    try:
        reset_world()
    except (rospy.ServiceException) as e:
        print ('reset_world failed!')

    rospy.wait_for_service('/gazebo/pause_physics')
    try:
        pause()
    except (rospy.ServiceException) as e:
        print ('rospause failed!')

    set_robot_state()
    robot_state.current_effort = 0
    robot_state.done = False
    # print ('called reset()')


def take_action(action):
    rospy.wait_for_service('/gazebo/unpause_physics')
    try:
        unpause()
    except (rospy.ServiceException) as e:
        print ('/gazebo/pause_physics service call failed')

    if action == 1:
        robot_state.current_effort = robot_state.current_effort + 0.01
    else:
        robot_state.current_effort = robot_state.current_effort - 0.01

    pubLeftWheelEffort.publish(robot_state.current_effort)
    pubRightWheelEffort.publish(robot_state.current_effort)
    
    if robot_state.data == None:
        while robot_state.data is None:
            try:
                robot_state.data = rospy.wait_for_message('/gazebo/link_states', LinkStates, timeout=5)
            except:
                print ('Error getting /gazebo/link_states data.')

    robot_state.data = None

    set_robot_state()

    if robot_state.body_x < -robot_state.x_threshold or robot_state.body_x > robot_state.x_threshold \
            or robot_state.body_theta > robot_state.theta_threshold \
            or robot_state.body_theta < -robot_state.theta_threshold:
       
        robot_state.done = True
        reward = -10

    else:
        robot_state.done = False
        reward = 1

    return reward, robot_state.done


def euler_from_quaternion(x, y, z, w):
        t0 = +2.0 * (w * x + y * z)
        t1 = +1.0 - 2.0 * (x * x + y * y)
        roll_x = math.atan2(t0, t1)
     
        t2 = +2.0 * (w * y - z * x)
        t2 = +1.0 if t2 > +1.0 else t2
        t2 = -1.0 if t2 < -1.0 else t2
        pitch_y = math.asin(t2)
     
        t3 = +2.0 * (w * z + x * y)
        t4 = +1.0 - 2.0 * (y * y + z * z)
        yaw_z = math.atan2(t3, t4)
     
        return roll_x, pitch_y, yaw_z # in radians
    

def callbackLinkStates(data):
    robot_state.body_x = data.pose[2].position.x
    robot_state.body_x_dot = data.twist[2].linear.x
    
    quat_x = data.pose[2].orientation.x
    quat_y = data.pose[2].orientation.y
    quat_z = data.pose[2].orientation.z
    quat_w = data.pose[2].orientation.w
    roll_x, pitch_y, yaw_z = euler_from_quaternion(quat_x, quat_y, quat_z, quat_w)
    robot_state.body_theta = pitch_y # in radian
    robot_state.body_theta_dot = data.twist[2].angular.y  # in radian per second

    set_robot_state()
    # print ('DATA :'), data


def listener():
    print ('listener')
    rospy.Subscriber("/gazebo/link_states", LinkStates, callbackLinkStates) 


def main():
    listener()

    q = Qnet()
    q_target = Qnet()
    q_target.load_state_dict(q.state_dict())
    memory = ReplayBuffer()

    print_interval = 20
    score = 0.0  
    optimizer = optim.Adam(q.parameters(), lr=learning_rate)

    for n_epi in range(10000):
        epsilon = max(0.01, 0.08 - 0.01*(n_epi/200)) #Linear annealing from 8% to 1%
        reset()
        s = np.asarray(robot_state.robot_state)
        done = False

        while not done:
            a = q.sample_action(torch.from_numpy(s).float(), epsilon)      
            r, done = take_action(a)
            # print("a: %d, r: %d, robot_state: %.3f, %.3f, %.3f, %.3f" % (a, r, robot_state.body_x, robot_state.body_x_dot, robot_state.body_theta, robot_state.body_theta_dot))
            time.sleep(0.05)
            s_prime = np.asarray(robot_state.robot_state)

            done_mask = 0.0 if done else 1.0
            memory.put((s,a,r/100.0,s_prime, done_mask))
            s = s_prime

            score += r
            if done:
                break
            
        if memory.size() > 2000:
            train(q, q_target, memory, optimizer)

        if n_epi%print_interval == 0 and n_epi != 0:
            q_target.load_state_dict(q.state_dict())
            print("n_episode :{}, score : {:.1f}, n_buffer : {}, eps : {:.1f}%".format(
                n_epi, score/print_interval, memory.size(), epsilon*100))
            score = 0.0


if __name__ == '__main__':
    main()
