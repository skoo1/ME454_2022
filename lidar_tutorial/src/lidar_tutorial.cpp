#include <ros/ros.h>
#include "string.h"
#include <cmath>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <vector>
#include <algorithm>
#include <opencv2/highgui.hpp>
#include <opencv2/plot.hpp>

using namespace cv;

std_msgs::Float32 msg_minDist;

void lidar_cb(sensor_msgs::LaserScan msg){

    // angle in radian
    float angle_min = msg.angle_min;
    float angle_max = msg.angle_max;
    float angle_increment = msg.angle_increment;
    std::vector<float> range = msg.ranges;

    int len = range.size();
    float angle[len];
    float angle_temp;

    Mat plot_result;
    Ptr<plot::Plot2d> plot_xy;
    Mat x(Size(1, len), CV_64F, Scalar(0));
    Mat y(Size(1, len), CV_64F, Scalar(0));

    for(int i = 0; i < len-1; i++){
        angle_temp = angle_min + i*angle_increment;
        angle[i] = angle_temp;
        if (std::isinf(range[i])==false && range[i]*sin(angle_temp)!= -0.000000 ){
            x.at<double>(i) = range[i]*cos(angle_temp);
            y.at<double>(i) = -range[i]*sin(angle_temp);
        }
    }

    plot_xy = plot::Plot2d::create(x,y);

    plot_xy->setMaxX(5);
    plot_xy->setMinX(-5);
    plot_xy->setMaxY(5);
    plot_xy->setMinY(-5);
    plot_xy->setPlotSize(720,720);
    plot_xy->setNeedPlotLine(false);
    plot_xy->render(plot_result);

    imshow("plot", plot_result);
    waitKey(1);

    float min_range = *min_element(range.begin(), range.end());
    msg_minDist.data = min_range;

    //minDist일때의 각도 추가

    plot_result.release();
    x.release();
    y.release();
    range.clear();
}

int main(int argc, char **argv){

    ros::init(argc, argv, "lidar_tutorial_node");
    ros::NodeHandle nh;

    ros::Subscriber sub_lidar = nh.subscribe("/scan", 1, lidar_cb);
    ros::Publisher pub_lidar_tutorial = nh.advertise<std_msgs::Float32>("/minDist",1);

    ros::Rate loop_rate(5);

    while(ros::ok()){
        ros::spinOnce();
        pub_lidar_tutorial.publish(msg_minDist);
        loop_rate.sleep();
    }
    return 0;
}
