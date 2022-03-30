#include "ros/ros.h"			// ROS basic header file
#include "ros_tutorials_topic/MsgTutorial.h"	// MsgTutorial message file header(Auto-generated after build)

int main(int argc, char **argv)                 	// Node main function
{
  ros::init(argc, argv, "topic_publisher");     	// Node name initialization
  ros::NodeHandle nh;			// Node handle declaration for communication with ROS system

// Publisher declaration, using MsgTutorial message file from ros_tutorials_topic package
// Create the publisher ros_tutorial_pub. The topic name is "ros_tutorial_msg"
// set the publisher queue size to 100
  ros::Publisher ros_tutorial_pub = nh.advertise<ros_tutorials_topic::MsgTutorial>("ros_tutorial_msg", 100);

// Set the loop period. & Quot; 10 & quot; refers to 10 Hz and repeats at 0.1 second intervals
  ros::Rate loop_rate(10);

// Declare msg message in MsgTutorial message file format
  ros_tutorials_topic::MsgTutorial msg;	

// Declare variable to be used in message
  int count = 0;                           
    while (ros::ok())
  {
    msg.stamp = ros::Time::now();	// Put the current time in the msg's substamp message
    msg.data  = count; 		// Put the value of the variable count in the lower data message of msg

    ROS_INFO("send msg = %d", msg.stamp.sec);  	// Display the stamp.sec message
    ROS_INFO("send msg = %d", msg.stamp.nsec); 	// Display the stamp.nsec message
    ROS_INFO("send msg = %d", msg.data);        		// Display  data message

    ros_tutorial_pub.publish(msg);			// Publish message

    loop_rate.sleep();				//  Go to sleep according to the loop cycle defined above

    ++count;					//  Increment count variable by 1
  }

  return 0;
}

