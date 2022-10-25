#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

#define SS_PIN 10
#define RST_PIN 9
#define red 8
#define green 6
int relay=3;
const int buto = 7; 
byte readCard[4];
int k=0;
String tagID = "";
MFRC522 mfrc522(SS_PIN, RST_PIN);

boolean getID();
int buttonState = 0;
void setup() {
pinMode(red, OUTPUT); 
pinMode(green, OUTPUT);
pinMode(relay,OUTPUT);
pinMode(buto, INPUT);;
digitalWrite(relay,HIGH);
digitalWrite(red,LOW);
digitalWrite(green,LOW);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Card based");
  lcd.setCursor(5, 1);
  lcd.print("door lock");
  delay(3000);
  Serial.begin(9600);
}

void loop() {
 Serial.begin(115200);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Place Your Card");    

  if (getID()){
        Serial.println((String)"?card="+tagID);
        while(k==0){
          if (Serial.available() > 0) {
            //kwakira data zivuye kuri node mcu na server
          DynamicJsonBuffer jsonBuffer;
          JsonObject& root = jsonBuffer.parseObject(Serial.readStringUntil('\n'));
          if (root["cstatus"]) {
          int cstatus = root["cstatus"];
          if(cstatus==1){
            noaccess();
            } else{
              opendoor();
              }
          }
          }
              }
    
    }
}
void(* resetFunc) (void) = 0;
boolean getID(){
  if(!mfrc522.PICC_IsNewCardPresent()){
    return false;
    }
  if(!mfrc522.PICC_ReadCardSerial()){
    return false;
    }
    tagID = "";
    for (uint8_t i = 0; i < 4; i++){
      tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      tagID.toUpperCase();
      mfrc522.PICC_HaltA();
      return true;
  }
void noaccess(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your are not");
  lcd.setCursor(0, 1);
  lcd.print("allowed");
  digitalWrite(red,HIGH);
  digitalWrite(green,LOW);
  delay(3000);
  resetFunc();
  }
void opendoor(){
  digitalWrite(relay,LOW);
  digitalWrite(green,HIGH);
  delay(2000);
  resetFunc();
  }
