#include "phidgets_ik/ik_ros_i.h"

namespace phidgets {

IKRosI::IKRosI(ros::NodeHandle nh, ros::NodeHandle nh_private):
  IK(),
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
}

void IKRosI::sensorHandler(int index, int sensorValue)
{
  // do nothing - just refer to base class callbalck, which prints the values
  IK::sensorHandler(index, sensorValue);
}

} // namespace phidgets

