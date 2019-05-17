char state;
int vspeed=255, lspeed=200;              // Default speed, from 0 to 255

int motorA1=10, motorA2=9, motorB1=8, motorB2=7, motorAp=11, motorBp=6, blstate=2;

void setup() {
                         
  pinMode(motorA1, OUTPUT);     // Set pins as outputs:
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(motorAp, OUTPUT);
  pinMode(motorBp, OUTPUT);
  pinMode(blstate, INPUT);
  Serial.begin(9600);   // Initialize serial communication at 9600 bits per second:
}

void loop() {

  //Stop if bluetooth is disconnected
  if(digitalRead(blstate)==0)
  {
    digitalWrite(motorA1, LOW);   digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);   digitalWrite(motorB2, LOW);
  }
   
  //Save income data to variable 'state'
  if(Serial.available() > 0){    
    state = Serial.read(); 
  }
  
  //If state is equal with letter 'F', car will go forward!
  if (state == 'F') {
    Serial.write(state);
    digitalWrite(motorA1, LOW);   digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);   digitalWrite(motorB2, HIGH);
    analogWrite(motorAp, vspeed); analogWrite(motorBp, vspeed);
  }
  /***********************Backward****************************/
  //If state is equal with letter 'B', car will go backward
  else if (state == 'B') {
    Serial.write(state);
    digitalWrite(motorA1, HIGH);  digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);  digitalWrite(motorB2, LOW);
    analogWrite(motorAp, vspeed); analogWrite(motorBp, vspeed);
  }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
  else if (state == 'R') {
    Serial.write(state);
    digitalWrite(motorA1, LOW);   digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);   digitalWrite(motorB2, LOW);
    analogWrite(motorAp, vspeed); analogWrite(motorBp, vspeed);
  }      
  /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn Left
  else if (state == 'L') {
    Serial.write(state);
    digitalWrite(motorA1, LOW);   digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);   digitalWrite(motorB2, HIGH);
    analogWrite(motorAp, vspeed); analogWrite(motorBp, vspeed);
  }      
  /***************************Stop*****************************/
  //If state is equal with letter 'S', wheels will stop
  else if (state == 'S') {
    Serial.write(state);
    digitalWrite(motorA1, LOW);   digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);   digitalWrite(motorB2, LOW);
    analogWrite(motorAp, vspeed); analogWrite(motorBp, vspeed);
  }  
  /***************************Forward Right*****************************/
  //If state is equal with letter 'I', Forward Right
  else if (state == 'I') {
    Serial.write(state);
    digitalWrite(motorA1, LOW);   digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);   digitalWrite(motorB2, HIGH);
    analogWrite(motorAp, vspeed); analogWrite(motorBp, lspeed);
  } 
  /***************************Forward Left*****************************/
  //If state is equal with letter 'G', Forward Left
  else if (state == 'G') {
    Serial.write(state);
    digitalWrite(motorA1, LOW);   digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);   digitalWrite(motorB2, HIGH);
    analogWrite(motorAp, lspeed); analogWrite(motorBp, vspeed);
  } 
  /***************************Back Right*****************************/
  //If state is equal with letter 'J', Back Right
  else if (state == 'J') {
    Serial.write(state);
    digitalWrite(motorA1, HIGH);   digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);   digitalWrite(motorB2, LOW);
    analogWrite(motorAp, vspeed); analogWrite(motorBp, lspeed);
  } 
  /***************************Back Left*****************************/
  //If state is equal with letter 'H', Back Left
  else if (state == 'H') {
    Serial.write(state);
    digitalWrite(motorA1, HIGH);   digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);   digitalWrite(motorB2, LOW);
    analogWrite(motorAp, lspeed); analogWrite(motorBp, vspeed);
  } 

}
