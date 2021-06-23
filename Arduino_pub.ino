
#include <Wire.h>
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <ros.h>
#include <std_msgs/Float32.h>

// Instantiate ROSSerial 
ros::NodeHandle nh; 
std_msgs::Float32 flt_msg;
ros::Publisher chatter ("heatSensor", &flt_msg);
float message = 0.0f;

GridEYE grideye;

void setup() {

  
  // Use I2C as input
  Wire.begin();
  grideye.begin(DEFAULT_ADDRESS, Wire);
  // ROSSerial as output
  nh.initNode();
  nh.advertise(chatter);
}

void loop() {
  // Placeholder for however input is taken.
  short int tot = 0;
  for(unsigned short int i = 0; i < 64; i++){
    tot += grideye.getPixelTemperature((char)i);
  }
  // Currently assuming that float32 is needed.
  message = (float)tot / 64.0f;

  // Publish results
  flt_msg.data = message;
  chatter.publish(&flt_msg);
  nh.spinOnce();
  // Send output once a second.
  delay(1000);
  
}
