#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
int lcdColumns = 16;
int lcdRows = 2;

const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define SS_PIN 10
#define RST_PIN 9
#define red 8
#define green 7
int relay=3;
const int buto = 6; 
byte readCard[4];
int k=0;
String tagID = "",data = "";
MFRC522 mfrc522(SS_PIN, RST_PIN);

boolean getID();
int buttonState = 0;
void setup() {
lcd.begin(16, 2);
pinMode(red, OUTPUT); 
pinMode(green, OUTPUT);
pinMode(relay,OUTPUT);
pinMode(buto, INPUT);;
digitalWrite(relay,HIGH);
digitalWrite(red,LOW);
digitalWrite(green,LOW);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.setCursor(0, 0);
  lcd.print("Card based");
  lcd.setCursor(0, 1);
  lcd.print("door lock");
  delay(3000);
  Serial.begin(9600);
}

void loop() {
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Place Your Card");    

  if (getID()){
         if (tagID == "13CAD1E"){
          Serial.println((String)"card1="+tagID);
          } else if (tagID == "41FCFE45"){//
            Serial.println((String)"card2="+tagID);
          } else if (tagID == "5135A45"){
            Serial.println((String)"card3="+tagID);
          } else if (tagID == "B38204B"){//
            Serial.println((String)"card4="+tagID);
          }
        while(k==0){
          if (Serial.available() > 0) {
            //kwakira data zivuye kuri node mcu na server
          data = Serial.readStringUntil('\n');
          Serial.println(data);
          StaticJsonDocument<96> root;
          DeserializationError error = deserializeJson(root, data);
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
  delay(4000);
  resetFunc();
  }
void opendoor(){
  digitalWrite(relay,LOW);
  digitalWrite(green,HIGH);
  delay(5000);
  resetFunc();
  }
