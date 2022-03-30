#include "ros/ros.h"
#include "gazebo_msgs/ModelStates.h"

void chatterCallback(const gazebo_msgs::ModelStates::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s] \n position [%f, %f, %f] \n orientation [%f, %f, %f] \n linear velocity [%f, %f, %f] \n angular velocity [%f, %f, %f]", 
  	msg->name[2].c_str(), 
  	msg->pose[2].position.x, 
  	msg->pose[2].position.y, 
  	msg->pose[2].position.z, 
  	msg->pose[2].orientation.x, 
  	msg->pose[2].orientation.y, 
  	msg->pose[2].orientation.z, 
  	msg->twist[2].linear.x, 
  	msg->twist[2].linear.y, 
  	msg->twist[2].linear.z, 
  	msg->twist[2].angular.x, 
  	msg->twist[2].angular.y, 
  	msg->twist[2].angular.z
  	);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "kinematics_listener");
  ros::NodeHandle n;


  ros::Subscriber sub = n.subscribe("/gazebo/link_states", 1000, chatterCallback);

  ros::spin();

  return 0;
}
