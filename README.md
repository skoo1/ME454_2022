# ME454 Dynamics System Programming
### Department of Mechanical Engineering, KAIST, South Korea  
#### Lecturer : Prof. Seungbum Koo (skoo at kaist.ac.kr)  
#### TA : Jeongseok Oh (dhwjdtjr0 at kaist.ac.kr) and Beomsu Shin (sbs0323 at kaist.ac.kr)  
### The packages are tested in WSL Ubuntu 20.04 with ROS Noetic
## Packages for TA sessions  

### Installation
```
>> sudo apt update
>> sudo apt install ros-noetic-ros-control ros-noetic-ros-controllers
>> cd ~/catkin_ws/src
# remove all files in ~/catkin_ws/src before executing the following command
# note the dot "." at the end of the command
>> git clone https://github.com/skoo1/ME454_2022.git .
>> cd ~/catkin_ws
>> catkin_make
>> source ~/catkin_ws/devel/setup.bash
```
See the document (README.MD) in each weekly tutorial

### Week 2. oneball_urdf  
Loading a sphere and throwing it using a service call  
We can see that the dynamics works in Gazebo  

### Week 3. cylinder_collision  
Loading two cylinders and push one of it to collide with the other  
We can see the collision and friction works in Gazebo  

### Week 4. billiard and bowling  
Loading minigames with ball and pin objects and fences  
We can see more sophiscated collision works even with meshed objects
  
### Week 5. pendulum
Loading vertical and horizon pendulums to see their swing motions  
We can apply apply torque to a joint of pendulums
  
### Week 6-1. oneball_topic
with oneball_urdf node, we can see ball's position with subscriber node
  
### Week 6-2. oneball_topic, mass_and_inertia
Loading box for translation and rotation to see their simple physics.  
We can apply apply force and torque to box  

### Week 9.

### Week 10.

### Week 11. balancing_robot

### Week 12. balancing_robot

### Week 13. balancing_robot

### Week 14. balancing_robot and cartpole_control
The cartpole exampled can be trained with a reinforcement learning algorithm
