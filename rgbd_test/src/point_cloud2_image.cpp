#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/CameraInfo.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Vector3.h"
#include "ros/time.h"
#include "sensor_msgs/image_encodings.h"

#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <sstream>
#include <iostream>
#include <string>
#include <fstream>


/**
 * Gets next sensor reading from file given that the file follows a prespecified standard
 *
 * The prespecified standard is that the file is a csv, and each line is of the form 
 * timestamp,value,value,value,(int)sensor_type. Value can be set to zero when N/A
 * e.g. for cameras 
 *
 * @param file				pointer to csv file with readings
 * @return            an array[5] that stores the current line being read or NULL
 */

double* get_next_reading(std::ifstream* file){

	std::string value;
	int count = 1;

	double* sensor_reading; 
	if((*file).good()){
		sensor_reading = new double[3];
		while((*file).good() && count<4){
			
			
			if(count <=3 ){			
				std::getline ( *file, value, '\n' ); //read string until next comma			
			}	
			
			sensor_reading[count-1] = (double)atof(value.c_str());	
			count++;
		}
	
	}
	else{		
		return NULL;
	}
	//std::cout<<"got here"<<std::endl;
	return sensor_reading;
}

double* camera_transform(double* img_coords){

	double* pix_coords = new double[3];
	
	double fx = 257.760000;	
	double fy = 257.479000;
	
	double cx = 324.060000;
	double cy = 243.954000;

	double x = img_coords[0];
	double y = img_coords[1];
	
	pix_coords[0] = fx*x + cx;
	pix_coords[1] = fy*y + cy;
	pix_coords[2]	= 1;

	return pix_coords;


}


int main(int argc, char **argv)
{
	cv::Mat myImage(640,480,CV_8UC1);
	myImage = cv::Scalar(5);
	std::ofstream myfile;
	std::vector<cv::Point2f> points;
 	myfile.open ("/home/ee125/Documents/code/slam-data/stairs_set/DepthMap/example.csv", std::ofstream::out | std::ofstream::trunc);
	

	std::ifstream sensor_file("/home/ee125/Documents/code/slam-data/stairs_set/PointClouds/depthFile_12.csv");
	
	
	int continue1 = 1;
	
	while(continue1 == 1){
		double* sensor_float;
		sensor_float = get_next_reading(&sensor_file);
	
		if(sensor_float != NULL){
			double image_coords[2] = {sensor_float[0]/sensor_float[2], sensor_float[1]/sensor_float[2]};

			double r2 = image_coords[0]*image_coords[0] + image_coords[1]*image_coords[1];
			double r4 = r2*r2;
			double r6 = r2*r6;

			double k1 = 0.920523;
			double k2 = 0.0;
			double k3 = 0.0;

			image_coords[0] *= 1.0 + k1*r2 + k2*r4 + k3*r6;
			image_coords[1] *= 1.0 + k1*r2 + k2*r4 + k3*r6;


			// Map to pixel space.
			double* pixel_coords;
			pixel_coords = camera_transform(image_coords);
			
			if(myfile.is_open()){
				myfile << pixel_coords[0] << "," << pixel_coords[1]<< "," << sensor_float[2] << std::endl;
			}
			
			delete[] pixel_coords;
			
	
		}	

		else{

			std::cout<<"End of file reached"<<std::endl;
			myfile.close();
			continue1 = 0;
		}

		delete[] sensor_float;
	
	}

	return 0;
}

