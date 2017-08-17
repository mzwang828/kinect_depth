#include <iostream>

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>

#include <opencv2/highgui/highgui.hpp>


void depthcb(const sensor_msgs::ImageConstPtr& msg)
{

        cv_bridge::CvImageConstPtr depth_img_cv;
        cv::Mat depth_mat;

        // Get the ROS image to openCV
        depth_img_cv = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_16UC1);
        // Convert the uints to floats
        depth_img_cv->image.convertTo(depth_mat, CV_32F, 0.001);

        float depth = depth_img_cv->image.at<short int>(150,200);

        ROS_INFO("Depth: %f", depth);
        ROS_INFO("Height: %d", msg->height);
        ROS_INFO("Width: %d", msg->width);


}

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "depth");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("camera/depth_registered/image_raw", 10, depthcb);


    ros::spin();

    return 0;
}
