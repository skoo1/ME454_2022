#include "ros/ros.h"
#include "gazebo_msgs/ModelStates.h"
#include "std_msgs/Float32.h"

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    pub_potential_ = n_.advertise<std_msgs::Float32>("/gazebo_energy_tutorial/potential", 1);
    pub_kinetic_ = n_.advertise<std_msgs::Float32>("/gazebo_energy_tutorial/kinetic", 1);
    pub_mechanical_ = n_.advertise<std_msgs::Float32>("/gazebo_energy_tutorial/mechanical", 1);
    sub_ = n_.subscribe("/gazebo/link_states", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const gazebo_msgs::ModelStates::ConstPtr& msg)
  {
    std_msgs::Float32 output_kinetic, output_potential, output_mechanical;
    output_potential.data = 9.81 * msg->pose[1].position.z;
    pub_potential_.publish(output_potential);
    output_kinetic.data = 0.5 * msg->twist[1].linear.z * msg->twist[1].linear.z;
    pub_kinetic_.publish(output_kinetic);
    output_mechanical.data = 9.81 * msg->pose[1].position.z + 0.5 * msg->twist[1].linear.z * msg->twist[1].linear.z;
    pub_mechanical_.publish(output_mechanical);
  }

private: //private으로 NodeHandle과 publisher, subscriber를 선언한다.
  ros::NodeHandle n_; 

  ros::Publisher pub_potential_;
  ros::Publisher pub_kinetic_;
  ros::Publisher pub_mechanical_;
  ros::Subscriber sub_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gazebo_energy_tutorial");
  SubscribeAndPublish SAPObject; //클래스 객체 선을 하게 되면 모든게 된다.
  ros::spin();
  return 0;
}

// void chatterCallback(const gazebo_msgs::ModelStates::ConstPtr& msg)
// {
//   ROS_INFO("I heard: [%s] \n position [%f, %f, %f] \n orientation [%f, %f, %f] \n linear velocity [%f, %f, %f] \n angular velocity [%f, %f, %f]", 
//   	msg->name[2].c_str(), 
//   	msg->pose[2].position.x, 
//   	msg->pose[2].position.y, 
//   	msg->pose[2].position.z, 
//   	msg->pose[2].orientation.x, 
//   	msg->pose[2].orientation.y, 
//   	msg->pose[2].orientation.z, 
//   	msg->twist[2].linear.x, 
//   	msg->twist[2].linear.y, 
//   	msg->twist[2].linear.z, 
//   	msg->twist[2].angular.x, 
//   	msg->twist[2].angular.y, 
//   	msg->twist[2].angular.z
//   	);
// }

// int main(int argc, char **argv)
// {

//   ros::init(argc, argv, "kinematics_listener");
//   ros::NodeHandle n;


//   ros::Subscriber sub = n.subscribe("/gazebo/link_states", 1000, chatterCallback);

//   ros::spin();

//   return 0;
// }