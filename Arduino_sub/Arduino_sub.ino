#include <ros.h>
#include <std_msgs/Float32.h>
void messageReceive (const mstd_msgs::Float32& message){
  // Insert code to display heat
}

// Instaantiate ROSSerial
ros::NodeHandle nh;
ros::Subscriber<std_msgs::Float32> sub("heatSensor", &messageReceive);

long sub_timer = 0;

void setup() {
  // ROSSerial as input
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
   nh.spinOnce();
}
