#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"

ros::NodeHandle  nh;

Servo servo;  //UP DOWN
Servo servo1; //LEFT RIGHT

void servo_cb( const std_msgs::Float32MultiArray& cmd_msg){
  servo.write(cmd_msg.data[0]); //set servo angle, should be from 0-180  
  servo1.write(cmd_msg.data[1]);
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}


ros::Subscriber<std_msgs::Float32MultiArray> sub("servo", servo_cb);

void setup(){
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
  
  servo.attach(5); //UP DOWN
  servo1.attach(6); ////LEFT RIGHT
}

void loop(){
  nh.spinOnce();
  delay(0.01);
}
