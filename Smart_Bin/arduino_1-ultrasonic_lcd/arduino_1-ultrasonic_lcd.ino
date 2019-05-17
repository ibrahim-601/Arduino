

#include <LiquidCrystal.h>//library for lcd display
 #include <Servo.h>// library for servo motor
#define trigger 6 // user define I/O of ultasound sensor
#define echo 7
Servo servoMain; // Define our Servo
LiquidCrystal lcd(12,11,5,4,3,2); // define LCD for interfacing


float time=0.00,distance=0.00; // define float  value for calculation


void setup()
{


  
    lcd.begin(16,2);// define col and row number
    Serial.begin(9600);// define boud rate to data communication
    servoMain.attach(9); //  define servo motor drive I/O

    
 
       pinMode(8, INPUT);// red full bsket AND SMS
       pinMode(10,OUTPUT);// define output
  
       pinMode(trigger,OUTPUT);// 6
       pinMode(echo,INPUT);// 7
       
       
 
 lcd.setCursor(0,0);// define CR in statement
 lcd.print(" Welcome");
 lcd.setCursor(0,1);
 lcd.print("Farzana Morsheda");
 delay(2000);//
 lcd.clear();// statement to clear display all CR


 

 
}
 
void loop()
{

   lcd.clear();
  lcd.setCursor(0,0);
   lcd.print("Smart Bin");
  lcd.setCursor(0,1);
  lcd.print("Ready to collect");


 
 digitalWrite(trigger,LOW);// pulse generation
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 time=pulseIn(echo,HIGH);// statement to take signal from ultrasound
 distance=time*340/20000; // convert coming pulse into distance
 //Serial.println(distance);
 

  
   if (distance<=19)
   {

     lcd.clear();
     
     lcd.setCursor(0,0);
   lcd.print("Smart Bin");
  lcd.setCursor(0,1);
  lcd.print("Taking ..");
  
  
   servoMain.write(160); // basket open Turn clockwise Servo for 90-180 degrees
   delay(8000); 
   
   
     servoMain.write(55);   // Turn Servo clockwise Left to 180-90 degrees
 
   
     lcd.clear();
     lcd.setCursor(0,0);
      lcd.print("Smart Bin");
    lcd.setCursor(0,1);
    lcd.print("closing....");
      delay(2000);

    lcd.clear();
  lcd.setCursor(0,0);
   lcd.print("Smart Bin");
  lcd.setCursor(0,1);
  lcd.print("Ready to collect");  
  
   
   }


int sms=digitalRead(8);
if(sms==LOW)// active low IR sensor

{
digitalWrite(10,HIGH);
delay(300);
    digitalWrite(10,LOW);
    delay(300);
    digitalWrite(10,HIGH);
    //delay(300);  
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print("Smart Bin");
    //lcd.setCursor(0,1);
    //lcd.print("sms sending....");

      
}

else
{
  
  digitalWrite(10,LOW);
  
  }




}



