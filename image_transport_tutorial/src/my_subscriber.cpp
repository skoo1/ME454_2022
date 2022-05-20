#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

/////////////////////////////
// 원본 이미지를 수신하는 노드 ///
////////////////////////////

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
  	cv::Mat img_raw;
  	cv::Mat img_small;

  	img_raw = cv_bridge::toCvShare(msg, "bgr8")->image;

  	cv::resize(img_raw, img_small, cv::Size(1920/4, 1080/4));

    cv::imshow("view", img_small);
    cv::waitKey(1);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "my_subscriber");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera/rgb/image_raw", 1, imageCallback);
  ros::spin();

}
