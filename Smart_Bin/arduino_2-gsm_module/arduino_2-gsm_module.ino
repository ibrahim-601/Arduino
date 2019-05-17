#include <Sim800l.h>

#include<SoftwareSerial.h>


SoftwareSerial gsm(10,11);
Sim800l Sim8001;

char num[15]="+8801521489042";
char text[10]="sms";
int a=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Sim8001.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(a==0)
    {
      delay(1000);
      Sim8001.sendSms(num,text);
      delay(1000);
      a=1;
    }
}
