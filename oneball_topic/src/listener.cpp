#include "ros/ros.h"
#include "gazebo_msgs/ModelStates.h"

void chatterCallback(const gazebo_msgs::ModelStates::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s] position [%f, %f, %f]", 
  	msg->name[1].c_str(), 
  	msg->pose[1].position.x, 
  	msg->pose[1].position.y, 
  	msg->pose[1].position.z);
}
// %EndTag(CALLBACK)%

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");
  ros::NodeHandle n;


  ros::Subscriber sub = n.subscribe("/gazebo/model_states", 1000, chatterCallback);

  ros::spin();

  return 0;
}
