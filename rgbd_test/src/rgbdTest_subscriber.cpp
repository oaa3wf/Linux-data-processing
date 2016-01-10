#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Vector3.h"
#include "ros/time.h"
#include "sensor_msgs/image_encodings.h"
#include <sensor_msgs/CameraInfo.h>


#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
	std::ofstream ofs;
	//double nseconds =(double) (msg->header).stamp.nsec;
	//double seconds = (double) (msg->header).stamp.sec;
	//double theTime = seconds + (nseconds*10e-9);
	string message;
	//sprintf((char *)message.c_str(),"%f,%f,%f,%f,%f\n",(msg->header).stamp.toSec(),0.0,0.0,0.0,3.0);
	//ofs.open("/home/sastrygrp/Documents/code/sensor_check.csv", std::ofstream::out | std::ofstream::app);
	//ofs.write(message.c_str(),strlen(message.c_str()));
	//ofs.close();
	try
	{ 
		cv:imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
		cv::waitKey(30);
		cout<< msg->encoding <<endl;
	 	
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
	}
}

void depth_image_callback(const sensor_msgs::ImageConstPtr& msg)
{
	std::ofstream ofs;
	//double nseconds =(double) (msg->header).stamp.nsec;
	//double seconds = (double) (msg->header).stamp.sec;
	//double theTime = seconds + (nseconds*10e-9);
	string message;
	//sprintf((char *)message.c_str(),"%f,%f,%f,%f,%f\n",(msg->header).stamp.toSec(),0.0,0.0,0.0,3.0);
	//ofs.open("/home/sastrygrp/Documents/code/sensor_check.csv", std::ofstream::out | std::ofstream::app);
	//ofs.write(message.c_str(),strlen(message.c_str()));
	//ofs.close();
	try
	{ 
		
		cv:imshow("view", 0.20*(cv_bridge::toCvShare(msg, "32FC1")->image));
		cv::waitKey(30);
		cout<< msg->encoding <<endl;
	 	
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("Could not convert from '%s' to '8UC1'.", msg->encoding.c_str());
	}
}

void image_info_callback(const sensor_msgs::CameraInfoConstPtr& msg)
{
	//std::ofstream ofs;
	double nseconds =(double) (msg->header).stamp.nsec;
	double seconds = (double) (msg->header).stamp.sec;
	double theTime = seconds + (nseconds*10e-9);
	string message;
	//sprintf((char *)message.c_str(),"%f,%f,%f,%f,%f\n",(msg->header).stamp.toSec(),0.0,0.0,0.0,3.0);
	//ofs.open("/home/sastrygrp/Documents/code/sensor_check.csv", std::ofstream::out | std::ofstream::app);
	//ofs.write(message.c_str(),strlen(message.c_str()));
	//ofs.close();
	std::cout<< "got image info header at time:" << seconds << ":" << nseconds <<std::endl;
	
	
}

void depth_image_info_callback(const sensor_msgs::CameraInfoConstPtr& msg)
{
	//std::ofstream ofs;
	double nseconds =(double) (msg->header).stamp.nsec;
	double seconds = (double) (msg->header).stamp.sec;
	double theTime = seconds + (nseconds*10e-9);
	string message;
	//sprintf((char *)message.c_str(),"%f,%f,%f,%f,%f\n",(msg->header).stamp.toSec(),0.0,0.0,0.0,3.0);
	//ofs.open("/home/sastrygrp/Documents/code/sensor_check.csv", std::ofstream::out | std::ofstream::app);
	//ofs.write(message.c_str(),strlen(message.c_str()));
	//ofs.close();
	std::cout<< "got depth image info header at time:" << seconds << ":" << nseconds << std::endl;
	
	
}



int main (int argc, char **argv)
{
	ros::init(argc, argv, "sensor_subscriber");
	ros::NodeHandle nh;
	cv::namedWindow("view");
	cv::startWindowThread();
	//ros::Subscriber image_sub = nh.subscribe("/camera/rgb/image_color", 100, imageCallback);
	//ros::Subscriber image_info_sub = nh.subscribe("/camera/rgb/camera_info", 100, image_info_callback);
	ros::Subscriber depth_image_sub = nh.subscribe("/camera/depth/image", 100, depth_image_callback);
	//ros::Subscriber depth_image_info_sub = nh.subscribe("/camera/depth/camera_info", 100, depth_image_info_callback);
	//ros::Subscriber gyr_sub = nh.subscribe("sensor_msgs/gyr", 10000, gyrCallback);
	//ros::Subscriber acc_sub = nh.subscribe("sensor_msgs/acc", 10000, accCallback);
	//ros::Subscriber imu_sub = nh.subscribe("sensor_msgs/Imu", 10000, accCallback);		
	ros::spin();
	cv::destroyWindow("view");

}



