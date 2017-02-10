#include "phidgets_api/ik.h"

namespace phidgets {

IK::IK():
  Phidget(),
  ik_handle_(0)
{
  // create the handle
  CPhidgetInterfaceKit_create(&ik_handle_);

  // pass handle to base class
  Phidget::init((CPhidgetHandle)ik_handle_);

  // register base class callbacks
  Phidget::registerHandlers();
  
  // register ik data callback
  CPhidgetInterfaceKit_set_OnSensorChange_Handler(ik_handle_, SensorHandler, this);

}


int IK::SensorHandler(CPhidgetInterfaceKitHandle ik, void *userptr, int index, int sensorValue)
{
  ((IK*)userptr)->sensorHandler(index, sensorValue);
  return 0;
}

void IK::sensorHandler(int index, int sensorValue)
{
  printf("index: %d, value: %d\n", index, sensorValue);
}

} // namespace phidgets
