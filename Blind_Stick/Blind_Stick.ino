#include <GSMSim.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <MPU6050.h>
#include <TinyGPS++.h>
#include <Ultrasonic.h>

#define RX 10
#define TX 11
#define BAUD 9600
#define vibrate 8

GSMSim gsm(RX, TX);
MPU6050 mpu;
TinyGPSPlus gps;
Ultrasonic ultrasonic ( 6 , 7 );

String phone_no = "+8801903622122";
String freeFallMessage = "Sorry to inform you that your loved one may be in trouble. The location is: ";
String callRejectMessage = "The location of your loved one is: ";
boolean freefallDetected = false;
float distance = 0.0;
int counter=0;

void setup() {
  
  Serial.begin(BAUD);
  Serial1.begin(BAUD);
  gsm.start(BAUD);
  delay(500);
  
  pinMode(13,OUTPUT);
  pinMode(vibrate, OUTPUT);

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G))
  {
    delay(250);
    break;
  }
  mpu.setAccelPowerOnDelay(MPU6050_DELAY_3MS);
  mpu.setIntFreeFallEnabled(true);
  mpu.setIntZeroMotionEnabled(false);
  mpu.setIntMotionEnabled(false);
  mpu.setDHPFMode(MPU6050_DHPF_5HZ);
  mpu.setFreeFallDetectionThreshold(17);
  mpu.setFreeFallDetectionDuration(2);
  
  
}

void loop() {
  
  String number = gsm.readCallerID();
  if(number.length()==14)
  {
//    Serial.println(number);
    delay(500); 
    gsm.callHangoff();
    _rejectCallRoutine(number);
  }
//  Serial.println();
  delay(1500);

  
//  Serial.print("loop");
  Activites act = mpu.readActivites();
  if(act.isFreeFall)
  {
    _freeFallRoutine();
    delay(500);
  }

  distance = ultrasonic.read(INC);
  _ultrasonicRoutine(distance);

  counter+=1;
  
  if(counter>150)
  {
    _gpsLocation();
    counter = 0;
  }
//_getLocation();
//  _freeFallRoutine();
//  _rejectCallRoutine();

}

void _freeFallRoutine()
{
  String link = _getLocation();
  String message = freeFallMessage;
  message.concat(link);
//  Serial.println(message);
  _sendSMS(phone_no, message);
}

void _rejectCallRoutine(String number)
{
  String link = _getLocation();
  String message = callRejectMessage;
  message.concat(link);
//  Serial.println(message);
  _sendSMS(number, message);
}

void _ultrasonicRoutine(int sensorDistance)
{
  if ( sensorDistance < 19 )
 {
  digitalWrite(vibrate, HIGH);
 }
 else
 {
  digitalWrite(vibrate, LOW);
 }
}

String _getLocation()
{
  bool a = true;
  String loc = "";
  while(a)
  {
    loc = _gpsLocation();
    if(loc.length()>12)
      a = false;
  }
  String link = "https://www.google.com/maps/search/?api=1&query=";
  link.concat(loc);
  Serial.println(link);
  return link;
}

String _gpsLocation()
{
  String loc = "";
  while(Serial1.available() > 0)
  {
    if (gps.encode(Serial1.read()))
    {
      if (gps.location.isValid())
      {
        String latt = String(gps.location.lat(),6);
        String longi = String(gps.location.lng(),6);
        loc.concat(latt);
        loc.concat(",");
        loc.concat(longi);
//        Serial.println(loc);
        return loc;
      }
    }
  }
}

void _sendSMS(String number, String message)
{
  char smsText[message.length()+2];
  message.toCharArray(smsText, message.length()+1);
  char phoneNo[number.length()+2];
  number.toCharArray(phoneNo, number.length()+1);
  Serial.println(number);
  Serial.println(message);
  gsm.smsTextMode(true);
  gsm.smsSend(phoneNo, smsText);
  delay(500);
}
