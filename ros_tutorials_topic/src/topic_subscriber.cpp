#include "ros/ros.h" 			// ROS basic header file
#include "ros_tutorials_topic/MsgTutorial.h" 	// MsgTutorial  message file header (Auto-generated after build)
// A message callback function, named ros_tutorial_msg below
// This is a function that works when a message is received
// The input message is supposed to receive the MsgTutorial message from the ros_tutorials_topic package
void msgCallback(const ros_tutorials_topic::MsgTutorial::ConstPtr& msg)
{
  ROS_INFO("recieve msg = %d", msg->stamp.sec); 	// Disaplay stamp.sec message
  ROS_INFO("recieve msg = %d", msg->stamp.nsec); 	// Disaplay stamp.nsec message
  ROS_INFO("recieve msg = %d", msg->data); 		// Disaplay data message
}
int main(int argc, char **argv)		// Node main function
{
  ros::init(argc, argv, "topic_subscriber");	// Initialize the node name

  ros::NodeHandle nh;                                   	// Declare a node handle to communicate with the ROS system

// Subscriber declaration, using MsgTutorial message file from ros_tutorials_topic package
// Create subscriber ros_tutorial_sub. The topic name is "ros_tutorial_msg"
// Set the subscriber queue size to 100
  ros::Subscriber ros_tutorial_sub = nh.subscribe("ros_tutorial_msg", 100, msgCallback);

// callback function will be waiting for message to be received,
// Execute callback function when message is received
  ros::spin();

  return 0;
}


