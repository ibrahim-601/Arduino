#include<LiquidCrystal.h>
//rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#include <SoftwareSerial.h>
// pin #2 is IN from sensor (yellow wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial fingerPrint(2, 3);

#include <Adafruit_Fingerprint.h>
uint8_t id;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);

#define enroll A0
#define del A1
#define up A2
#define down A3
#define openLight 6
#define closeLight 7
#define unlock 5

void setup()
{
  
  pinMode(enroll, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(del, INPUT_PULLUP);
  pinMode(openLight, OUTPUT);
  pinMode(closeLight, OUTPUT);
  pinMode(unlock, OUTPUT); 
  lcd.begin(16, 2);
  lcd.print("   Biometric ");
  lcd.setCursor(0, 1);
  lcd.print("Security System");
  delay(1000);
  lcd.clear();
  finger.begin(57600);
  Serial.begin(9600);
  lcd.clear();
  lcd.print(" Finding Module ");
  lcd.setCursor(0, 1);
  delay(1000);
  if (finger.verifyPassword())
  {
    Serial.println("Found fingerprint sensor!");
    lcd.clear();
    lcd.print("  Module Found ");
    delay(1000);
  }
  else
  {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.clear();
    lcd.print("Module Not Found");
    lcd.setCursor(0, 1);
    lcd.print("Check Connections");
    while (1);
  }
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("  Press Match ");
  lcd.setCursor(0, 1);
  lcd.print("To Start System");
  Serial.println("to start system");
  digitalWrite(closeLight, HIGH);
  if (digitalRead(up) == 0 || digitalRead(down) == 0)
  {
    for (int i = 0; i < 25; i++)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Place Finger");
      Serial.println("Place finger");
      lcd.setCursor(0, 1);
      lcd.print("To unlock.");
      delay(500);
      int result = getFingerprintIDez();
      if (result >= 0)
      {
        digitalWrite(openLight, HIGH);
        digitalWrite(closeLight, LOW);
        lcd.clear();
        lcd.print(" Allowed ");
        Serial.println("allowed");
        lcd.setCursor(0, 1);
        lcd.print(" Gate Opened ");
        Serial.println("gate opened");
        digitalWrite(unlock, HIGH);
        delay(250);
        digitalWrite(unlock, LOW);
        delay(1250);
        digitalWrite(closeLight, HIGH);
        digitalWrite(openLight, LOW);
        lcd.setCursor(0, 1);
        lcd.print(" Gate Closed ");
        Serial.println("gate closed");
        return;
      }
    }
  }
  checkKeys();
  delay(500);
}

void checkKeys()
{
  if (digitalRead(enroll) == 0)
  {
    lcd.clear();
    lcd.print("Please Wait");
    Serial.println("Please Wait");
    delay(1000);
    while (digitalRead(enroll) == 0);
    Enroll();
  }

  else if (digitalRead(del) == 0)
  {
    lcd.clear();
    lcd.print("Please Wait");
    Serial.println("Please Wait");
    delay(1000);
    delet();
  }
}

void Enroll()
{
  int count = 0;
  lcd.clear();
  lcd.print("Enroll Finger ");
  Serial.println("Enroll Finger ");
  lcd.setCursor(0, 1);
  lcd.print("Location:");
  Serial.println("Location:");
  while (1)
  {
    lcd.setCursor(9, 1);
    lcd.print(count);
    Serial.println(count);
    if (digitalRead(up) == 0)
    {
      count++;
      if (count > 25)
        count = 0;
      delay(500);
    }

    else if (digitalRead(down) == 0)
    {
      count--;
      if (count < 0)
        count = 25;
      delay(500);
    }
    else if (digitalRead(del) == 0)
    {
      id = count;
      getFingerprintEnroll();
      return;
    }

    else if (digitalRead(enroll) == 0)
    {
      return;
    }
  }
}

void delet()
{
  int count = 0;
  lcd.clear();
  lcd.print("Delete Finger ");
  Serial.println("Delete Finger ");
  lcd.setCursor(0, 1);
  lcd.print("Location:");
  Serial.println("Location:");
  while (1)
  {
    lcd.setCursor(9, 1);
    lcd.print(count);
    Serial.println(count);
    if (digitalRead(up) == 0)
    {
      count++;
      if (count > 25)
        count = 0;
      delay(500);
    }

    else if (digitalRead(down) == 0)
    {
      count--;
      if (count < 0)
        count = 25;
      delay(500);
    }
    else if (digitalRead(del) == 0)
    {
      id = count;
      deleteFingerprint(id);
      return;
    }

    else if (digitalRead(enroll) == 0)
    {
      return;
    }
  }
}

uint8_t getFingerprintEnroll()
{
  int p = -1;
  lcd.clear();
  lcd.print("Finger ID:");
  Serial.println("Finger ID:");
  lcd.print(id);
  lcd.setCursor(0, 1);
  lcd.print("Place Finger");
  Serial.println("Place Finger");
  delay(1000);
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        lcd.clear();
        lcd.print("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println("No Finger");
        lcd.clear();
        lcd.print("No Finger");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        lcd.clear();
        lcd.print("Comm Error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        lcd.clear();
        lcd.print("Imaging Error");
        break;
      default:
        Serial.println("Unknown error");
        lcd.clear();
        lcd.print("Unknown Error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      lcd.clear();
      lcd.print("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      lcd.clear();
      lcd.print("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      lcd.clear();
      lcd.print("Comm Error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Feature Not Found");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      lcd.clear();
      lcd.print("Feature Not Found");
      return p;
    default:
      Serial.println("Unknown error");
      lcd.clear();
      lcd.print("Unknown Error");
      return p;
  }

  Serial.println("Remove finger");
  lcd.clear();
  lcd.print(" Remove Finger ");
  delay(1000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID ");
  Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  lcd.clear();
  lcd.print(" Place Finger ");
  lcd.setCursor(0, 1);
  lcd.print(" Again ");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        return 0;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  Serial.print("Creating model for #"); Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    lcd.clear();
    lcd.print("Stored!");
    delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  }
  else {
    Serial.println("Unknown error");
    return p;
  }
}

int getFingerprintIDez()
{
  uint8_t p = finger.getImage();

  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
  {
    lcd.clear();
    lcd.print("Finger Not Found");
    lcd.setCursor(0, 1);
    lcd.print("Try Later");
    delay(1000);
    return -1;
  }
  // found a match!
  Serial.print("Found ID #");
  Serial.print(finger.fingerID);
  return finger.fingerID;
}

uint8_t deleteFingerprint(uint8_t id)
{
  uint8_t p = -1;
  lcd.clear();
  lcd.print("Please wait");
  p = finger.deleteModel(id);
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Deleted!");
    lcd.clear();
    lcd.print("Figer Deleted");
    lcd.setCursor(0, 1);
    lcd.print("Successfully");
    delay(1000);
  }

  else
  {
    Serial.print("Something Wrong");
    lcd.clear();
    lcd.print("Something Wrong");
    lcd.setCursor(0, 1);
    lcd.print("Try Again Later");
    delay(1000);
    return p;
  }
}
