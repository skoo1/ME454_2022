#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "string.h"
#include <cmath>
#include <sensor_msgs/LaserScan.h>
#include "std_msgs/Float32.h"
#include <vector>
#include <algorithm>

#include <fstream>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

using namespace std;
ros::Publisher pub;
pcl::PointCloud<pcl::PointXYZ>::Ptr new_cloud (new::pcl::PointCloud<pcl::PointXYZ>);

// Global variable

void lidar_cb(sensor_msgs::LaserScan msg){

    // angle in radian
    float angle_min = msg.angle_min;
    float angle_max = msg.angle_max;
    float angle_increment = msg.angle_increment;
    std::vector<float> range = msg.ranges;

    // size of range vector
    int len = range.size();
    float angle_temp;

    /// 1. LaserScan msg to PCL::PointXYZ

    // initializae pointcloud
	pcl::ExtractIndices<pcl::PointXYZ> extract;
	pcl::PointIndices::Ptr inf_points(new pcl::PointIndices());


    new_cloud->is_dense = false;
	new_cloud->width = len;
	new_cloud->height = 1;
	new_cloud->points.resize(len);

	// fill the pointcloud
    for(int i = 0; i < len; i++){
        angle_temp = angle_min + i*angle_increment;
        if (std::isinf(range[i])==false){

           	new_cloud->points[i].x = range[i]*cos(angle_temp);
            new_cloud->points[i].y = range[i]*sin(angle_temp);
            new_cloud->points[i].z = 0;
        }
        else{
        	// indices of infinite distance points
        	inf_points->indices.push_back(i);
        }
    }

    // Remove infinite distance points from new_cloud
    extract.setInputCloud(new_cloud);
  	extract.setIndices(inf_points);
  	extract.setNegative(true);
  	extract.filter(*new_cloud);
    // new_cloud
    new_cloud->header.frame_id = msg.header.frame_id;
    pub.publish(new_cloud);
}

int main(int argc, char **argv){

    ros::init(argc, argv, "lidar_homework_node");
    ros::NodeHandle nh;

    ros::Subscriber sub_lidar = nh.subscribe("/scan", 1, lidar_cb);
    std::string topic = nh.resolveName("point_cloud");
    uint32_t queue_size = 1;
    pub = nh.advertise<pcl::PointCloud<pcl::PointXYZRGB>> (topic, queue_size);
    ros::Rate loop_rate(5);

    pcl::visualization::PCLVisualizer viewer ("ICP demo");
    // Create two vertically separated viewports
    // int v1 (0);
    // int v2 (1);
    // viewer.createViewPort (0.0, 0.0, 0.5, 1.0, v1);
    // viewer.createViewPort (0.5, 0.0, 1.0, 1.0, v2);

    // The color we will be using
    float bckgr_gray_level = 0.0;  // Black
    float txt_gray_lvl = 1.0 - bckgr_gray_level;

    // Original point cloud is white
//     pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_in_color_h (new_cloud, (int) 0 , (int) 0 , (int) 255 );
//     viewer.addPointCloud (new_cloud, cloud_in_color_h, "cloud_in_v1");
//     viewer.setCameraPosition (-3.68332, 2.94092, 5.71266, 0.289847, 0.921947, -0.256907, 0);
//     viewer.setSize (1280, 1024);  // Visualiser window size
    
    while(ros::ok()){
        ros::spinOnce();
        viewer.spinOnce ();
        loop_rate.sleep();
    }

    // txtFile.close();
    return 0;
}
