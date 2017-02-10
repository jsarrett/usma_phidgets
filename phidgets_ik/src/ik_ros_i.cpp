#include "phidgets_ik/ik_ros_i.h"
#include <stdio.h>

namespace phidgets {

IKRosI::IKRosI(ros::NodeHandle nh, ros::NodeHandle nh_private):
  IK(),
  n_in(0),
  n_out(0),
  n_sensors(0),
  nh_(nh),
  nh_private_(nh_private)
{
  ROS_INFO ("Starting Phidgets IK");

  initDevice();
}

void IKRosI::initDevice()
{
  ROS_INFO("Opening device");
  open(-1);

  ROS_INFO("Waiting for IK to be attached...");
  int result = waitForAttachment(10000);
  if(result)
  {
    const char *err;
    CPhidget_getErrorDescription(result, &err);
    ROS_FATAL("Problem waiting for IK attachment: %s", err);
  }

  CPhidgetInterfaceKit_getInputCount(ik_handle_, &n_in);
  CPhidgetInterfaceKit_getOutputCount(ik_handle_, &n_out);
  CPhidgetInterfaceKit_getSensorCount(ik_handle_, &n_sensors);
  ROS_INFO("%d inputs, %d outputs, %d sensors", n_in, n_out, n_sensors);
  for (int i = 0; i < n_in; i++) {
    char topicname[] = "input00";
    snprintf(topicname, sizeof(topicname), "input%02d", i);
    in_pubs_.push_back(nh_.advertise<std_msgs::Bool>(topicname, 1));
  }
  for (int i = 0; i < n_sensors; i++) {
    char topicname[] = "sensor00";
    snprintf(topicname, sizeof(topicname), "sensor%02d", i);
    sensor_pubs_.push_back(nh_.advertise<std_msgs::Float32>(topicname, 1));
  }
}

void IKRosI::sensorHandler(int index, int sensorValue)
{
  // do nothing - just refer to base class callbalck, which prints the values
  IK::sensorHandler(index, sensorValue);
  //get rawsensorvalue and divide by 4096, which according to the documentation for both the IK888 and IK222 are the maximum senosr value
  int rawval = 0;
  CPhidgetInterfaceKit_getSensorRawValue(ik_handle_, index, &rawval);
  std_msgs::Float32 msg;
  msg.data = float(rawval)/4095.0f;
  if ((sensor_pubs_.size() > index) && (sensor_pubs_[index])) {
    sensor_pubs_[index].publish(msg);
  }
}

void IKRosI::inputHandler(int index, int inputValue)
{
  // do nothing - just refer to base class callbalck, which prints the values
  IK::inputHandler(index, inputValue);
  std_msgs::Bool msg;
  msg.data = inputValue != 0;
  if ((in_pubs_.size() > index) && (in_pubs_[index])) {
    in_pubs_[index].publish(msg);
  }
}


} // namespace phidgets

