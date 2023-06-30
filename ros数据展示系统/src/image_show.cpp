/*
 * OpenCV Example using ROS and CPP
 */

// Include the ROS library
#include <ros/ros.h>



#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
// Include CvBridge, Image Transport, Image msg
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

// 窗口名称
static const std::string OPENCV_WINDOW = "Color Image window";

// Topics 彩色图片的话题
static const std::string IMAGE_TOPIC = "/camera/color/image_raw";
// 深度图片话题
static const std::string DEPTH_IMAGE_TOPIC = "/camera/depth/image_rect_raw";
// 彩色图片回调函数
void image_cb(const sensor_msgs::ImageConstPtr& msg)
{
  std_msgs::Header msg_header = msg->header;
  std::string frame_id = msg_header.frame_id.c_str();
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  cv::imshow(OPENCV_WINDOW, cv_ptr->image);
  cv::waitKey(3);
}

// 深度图片回调函数
void depth_image_cb(const sensor_msgs::ImageConstPtr& msg)
{
  std_msgs::Header msg_header = msg->header;
  std::string frame_id = msg_header.frame_id.c_str();
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_16UC1);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  
  cv::imshow("DEPTH IMAGE SHOW", cv_ptr->image);
  cv::waitKey(3);
}
int main(int argc, char** argv)
{
  //初始化节点
  ros::init(argc, argv, "image_show");
  ros::NodeHandle nh;
  // 创建订阅者 订阅 image
  ros::Subscriber sub = nh.subscribe(IMAGE_TOPIC, 1, image_cb);
  ros::Subscriber depth_sub = nh.subscribe(DEPTH_IMAGE_TOPIC, 1, depth_image_cb);
  
  // ros 循环
  ros::spin();

  
  return 0;
}