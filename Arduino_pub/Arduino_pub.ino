
#include <Wire.h>
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <ros.h>
#include <std_msgs/Float32.h>

// Instantiate ROSSerial 
ros::NodeHandle nh; 
std_msgs::Float32 flt_msg;
ros::Publisher chatter ("heatSensor", &flt_msg);
float message = 0.0f;

// To receive input from heat sensor
GridEYE grideye;

long pub_timer;

void setup() {
  // Use I2C as input
  Wire.begin();
  grideye.begin(DEFAULT_ADDRESS, Wire);
  // ROSSerial as output
  nh.initNode();
  nh.advertise(chatter);
}

void loop() {
  // We want to run spinOnce every frame, so we need to use a timer variable instead of delay
  if (millis() > pub_timer){
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
    pub_timer() = millis() + 1000; // publish every second
  }
  nh.spinOnce(); 
  
}
