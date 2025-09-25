#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
#define panel_relay 3
#define battery_relay 4
#define load_relay 5
#define v1_read A0
#define v2_read A1
#define v3_read A2
#define enA 9
#define in1 6
#define in2 7
#define enB 10
#define in3 8
#define in4 11

float voltage1;
float voltage2;
float voltage3;
const int pwmOutputA = 45;
const int pwmOutputB = 45;

const float VCC = 5.0;
const float factor = 4.78;  

unsigned long startTime = 0;


LiquidCrystal_I2C lcd(0x27, 16, 4); //SDA - A4, SCL - A5

void setup() {
      Serial.begin(9600);
      lcd.begin();
      pinMode(panel_relay,OUTPUT);
      pinMode(battery_relay,OUTPUT);
      pinMode(load_relay,OUTPUT);
      pinMode(v1_read,INPUT);
      pinMode(v2_read,INPUT);
      pinMode(v3_read,INPUT);
      pinMode(enA,OUTPUT);
      pinMode(in1,OUTPUT);
      pinMode(in2,OUTPUT);
      pinMode(enB,OUTPUT);
      pinMode(in3,OUTPUT);
      pinMode(in4,OUTPUT);

      lcd.clear();
      //lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("Enter a number:");

      while (Serial.available() == 0) {
      }
      
      //Serial.println("Low Voltage Disconnect");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Experiment No.1:");
      lcd.setCursor(0,1);
      lcd.print("Low Voltage");
      lcd.setCursor(0,2);
      lcd.print("Disconnect");
      

      digitalWrite(panel_relay,LOW);
      digitalWrite(battery_relay,HIGH);
      digitalWrite(load_relay,HIGH);
      
      //Serial.println("Steadily lower the battery DC voltage");
      delay(4500);
      //voltage3 = (analogRead(v3_read)/1024.0)*(VCC*factor);
      
      startTime = millis();
      while ((millis()-startTime)<=3000){
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(enB, pwmOutputB);
        //delay(2500);
        //digitalWrite(in3, LOW);
        //digitalWrite(in4, LOW);
        
        voltage3 = (analogRead(v3_read)/1024.0)*(VCC*factor);
        //Serial.print("Voltage at load terminals: ");
        Serial.print(voltage3,3);
        Serial.print(",");
        
        
        voltage2 = (analogRead(v2_read)/1024.0)*(VCC*factor)-1.4;    // read the current sensor value (0 - 1023) 
        //Serial.print("Voltage at battery terminals: ");
        Serial.print(voltage2,3);
        Serial.print(",");

         voltage1 = (analogRead(v1_read)/1024.0)*(VCC*factor);
         Serial.println(voltage1,3);
        
         
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("V_panel: ");
         lcd.print(voltage1);
         lcd.print("V");
         lcd.setCursor(0,1);
         lcd.print("V_battery:");
         lcd.print(voltage2);
         lcd.print("V");
         lcd.setCursor(0,2);
         lcd.print("V_load: ");
         lcd.print(voltage3);
         lcd.print("V");
         //delay(1000);
      }
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      
      float LVD = voltage2 ;
      //Serial.print("LVD is ");
      //Serial.print(LVD);
      //Serial.println("V");
      //Serial.println("       ");
      //Serial.println("       ");
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LVD = ");
      lcd.print(LVD);
      lcd.print("V");
      
      digitalWrite(panel_relay,LOW);
      digitalWrite(battery_relay,LOW);
      digitalWrite(load_relay,LOW);
      delay(10000);

      //Serial.println("Test for load disconnect");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Experiment No.2:");
      lcd.setCursor(0,1);
      lcd.print("Test for");
      lcd.setCursor(0,2);
      lcd.print("Load Disconnect");
      
      digitalWrite(panel_relay,HIGH);
      digitalWrite(battery_relay,HIGH);
      digitalWrite(load_relay,HIGH);
      delay(1000);
      //Serial.println("Steadily increase the panel DC voltage");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Slowly increase");
      lcd.setCursor(0,1);
      lcd.print("Panel Voltage");
      delay(1000);

      startTime = millis();
      while((millis()-startTime)<=4000){
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enB, pwmOutputB);
      //delay(5000);
      voltage3 = (analogRead(v3_read)/1024.0)*(VCC*factor);
        //Serial.print("Voltage at load terminals: ");
        Serial.print(voltage3,3);
        Serial.print(",");
        
        
        voltage2 = (analogRead(v2_read)/1024.0)*(VCC*factor);    // read the current sensor value (0 - 1023) 
        //Serial.print("Voltage at battery terminals: ");
        Serial.print(voltage2,3);
        Serial.print(",");

         voltage1 = (analogRead(v1_read)/1024.0)*(VCC*factor);
         Serial.println(voltage1,3);
        
         
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("V_panel: ");
         lcd.print(voltage1);
         lcd.print("V");
         lcd.setCursor(0,1);
         lcd.print("V_battery:");
         lcd.print(voltage2);
         lcd.print("V");
         lcd.setCursor(0,2);