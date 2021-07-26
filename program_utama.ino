#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "RTClib.h"
#include <Wire.h>
RTC_DS3231 rtc;

int automanual = 1;   // mode auto manual
int weather;          // pembacaan LDR cuaca

int lcd_page = 0;
unsigned long lastmillis;

// Tulisan yang akan ditampilkan pada LCD
String sky_condition;
String kondisi_sistem;
String indikator_1;
String indikator_2;
String indikator_3;
String indikator_4;
String indikator_5;
//int indikator_rusak = 0;

// Output LED
int led_1 = 15;
int led_2 = 4;
int led_3 = 16;
int led_4 = 17;
int led_5 = 5;
int led_6 = 18;

// Pembacaan data dari Blynk
int pinvalue_1 = 1;
int pinvalue_2 = 1;
int pinvalue_3 = 1;
int pinvalue_4 = 1;
int pinvalue_5 = 1;

// Input LDR
int cuaca = 33;
int ldr_1 = 13;
int ldr_2 = 14;
int ldr_3 = 27;
int ldr_4 = 26;
int ldr_5 = 25;


// aut, wifi and password blynk
//char auth[] = "1--MAVCO2kZQOTqaHurIvhs0ZORgWMCh";
char auth[] = "PylwfEoWVPVOCACyt0MbavazHWYbCxzd";
char ssid[] = "NasiPadang";
char pass[] = "123456";

// virtual data LCD dari blynk
WidgetLCD lcd_1(V10);
WidgetLCD lcd_2(V11);

void setup()
{
  // Debug console
  Serial.begin(9600);
  lastmillis = millis();

  Wire.begin();
  rtc.begin();
//  rtc.adjust(DateTime(__DATE__, __TIME__));
  
  // inisiasi output
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_5, OUTPUT);
  pinMode(led_6, OUTPUT);

  // Relay bersifat low active yaitu ketika relay diberi sinyal LOW maka relay akan langsung aktif.
  // Oleh karena itu, saat sistem baru dijalankan, semua relay di buat standby HIGH sehingga relay mati.
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, HIGH);
  digitalWrite(led_3, HIGH);
  digitalWrite(led_4, HIGH);
  digitalWrite(led_5, HIGH);
  digitalWrite(led_6, HIGH);

  //inisiasi input
  pinMode(cuaca, INPUT);
  pinMode(ldr_1, INPUT);
  pinMode(ldr_2, INPUT);
  pinMode(ldr_3, INPUT);
  pinMode(ldr_4, INPUT);
  pinMode(ldr_5, INPUT);
  
  Blynk.begin(auth, ssid, pass);
}

// membaca virtual data button dari blynk
BLYNK_WRITE(V0){
   pinvalue_1 =  param.asInt();
}
BLYNK_WRITE(V1){
   pinvalue_2 =  param.asInt();
}
BLYNK_WRITE(V2){
   pinvalue_3 =  param.asInt();
}
BLYNK_WRITE(V3){
   pinvalue_4 =  param.asInt();
}
BLYNK_WRITE(V4){
   pinvalue_5 =  param.asInt();
}
BLYNK_WRITE(V5){
   automanual =  param.asInt();
}

void LCD()
{ 
  // Void LCD berfungsi sebagai pengatur tulisan yang akan ditampilkan pada LCD

  ////////////////////////TULISAN LCD 1///////////////////////////////////////
  if(lcd_page == 0){
  /////////////////////LAMPU 1//////////////////////
    if(digitalRead(led_1) == 0 && digitalRead(ldr_1) == 0){
      indikator_1 = "LAMPU 1 NYALA";
    }
    else if(digitalRead(led_1) == 1 && digitalRead(ldr_1) == 1){
      indikator_1 = "LAMPU 1 MATI ";
    }
    else {
      indikator_1 = "LAMPU 1 RUSAK";
//      indikator_rusak = 1;
    }
  ///////////////////LAMPU 2////////////////////////
    if(digitalRead(led_2) == 0 && digitalRead(ldr_2) == 0){
      indikator_2 = "LAMPU 2 NYALA";
    }
    else if(digitalRead(led_2) == 1 && digitalRead(ldr_2) == 1){
      indikator_2 = "LAMPU 2 MATI ";
    }
    else {
      indikator_2 = "LAMPU 2 RUSAK";
//      indikator_rusak = 1;
    }
    //////////////////////////////////////////////////
    lcd_1.print(0, 0, indikator_1);
    lcd_1.print(0, 1, indikator_2);
    
    if((millis() - lastmillis) >= 3000){
      lastmillis = millis();
      lcd_page = 1;
      lcd_1.clear();
    }
  }
  else if(lcd_page == 1){
  ////////////////////LAMPU 3/////////////////////////
    if(digitalRead(led_3) == 0 && digitalRead(ldr_3) == 0){
      indikator_3 = "LAMPU 3 NYALA";
    }
    else if(digitalRead(led_3) == 1 && digitalRead(ldr_3) == 1){
      indikator_3 = "LAMPU 3 MATI ";
    }
    else {
      indikator_3 = "LAMPU 3 RUSAK";
//      indikator_rusak = 1;
    }
  //////////////////////LAMPU 4//////////////////////
    if(digitalRead(led_4) == 0 && digitalRead(ldr_4) == 0){
      indikator_4 = "LAMPU 4 NYALA";
    }
    else if(digitalRead(led_4) == 1 && digitalRead(ldr_4) == 1){
      indikator_4 = "LAMPU 4 MATI ";
    }
    else {
      indikator_4 = "LAMPU 4 RUSAK";
//      indikator_rusak = 1;
    }
   ////////////////////////////////////////////////////// 
    lcd_1.print(0, 0, indikator_3);
    lcd_1.print(0, 1, indikator_4);
   
    if((millis() - lastmillis) >= 3000){
      lastmillis = millis();
      lcd_page = 2;
      lcd_1.clear();
    }
  }
  else{
  ///////////////////////LAMPU 5/////////////////////
    if(digitalRead(led_5) == 0 && digitalRead(ldr_5) == 0){
      indikator_5 = "LAMPU 5 NYALA";
    }
    else if(digitalRead(led_5) == 1 && digitalRead(ldr_5) == 1){
      indikator_5 = "LAMPU 5 MATI ";
    }
    else {
      indikator_5 = "LAMPU 5 RUSAK";
//      indikator_rusak = 1;
    }
    //////////////////////////////////////////////////
    lcd_1.print(0, 0, indikator_5);
    
    if((millis() - lastmillis) >= 3000){
      lastmillis = millis();
      lcd_page = 0;
      lcd_1.clear();
    }
  }
  //////////////////TULISAN LCD 2 (CUACA)/////////////////////
  
  if(weather == 0){
    sky_condition = "LANGIT TERANG";
  }
  else{
    sky_condition = "LANGIT GELAP ";
  }
  ///////////TULISAN LCD 2 (KONDISI SISTEM)//////////////
  if (((digitalRead(led_1) == 0 && digitalRead(ldr_1) == 0) || (digitalRead(led_1) == 1 && digitalRead(ldr_1) == 1)) &&
      ((digitalRead(led_2) == 0 && digitalRead(ldr_2) == 0) || (digitalRead(led_2) == 1 && digitalRead(ldr_2) == 1)) &&
      ((digitalRead(led_3) == 0 && digitalRead(ldr_3) == 0) || (digitalRead(led_3) == 1 && digitalRead(ldr_3) == 1)) &&
      ((digitalRead(led_4) == 0 && digitalRead(ldr_4) == 0) || (digitalRead(led_4) == 1 && digitalRead(ldr_4) == 1)) &&
      ((digitalRead(led_5) == 0 && digitalRead(ldr_5) == 0) || (digitalRead(led_5) == 1 && digitalRead(ldr_5) == 1))){
    kondisi_sistem = "SISTEM NORMAL ";
  }
  else{
    kondisi_sistem = "ADA LAMPU MATI";
  }
  /////////////TULISAN LCD 2//////////////////
  lcd_2.print(0, 0, sky_condition);
  lcd_2.print(0, 1, kondisi_sistem);
}

void output(){
  // Sistem Auto dan Manual dikendalikan pada fungsi ini
  DateTime now = rtc.now();
  Serial.println(now.hour());
//  Serial.println(now.minute());
  
  // SISTEM MODE MANUAL 
  if (automanual == 1){
     digitalWrite(led_1, pinvalue_1);
     digitalWrite(led_2, pinvalue_2);
     digitalWrite(led_3, pinvalue_3);
     digitalWrite(led_4, pinvalue_4);
     digitalWrite(led_5, pinvalue_5);
    }

  // SISTEM MODE OTOMATIS
  else{  
    if (weather == 1 || now.hour()>= 18 || now.hour() <= 6){
     digitalWrite(led_1, LOW);
     digitalWrite(led_2, LOW);
     digitalWrite(led_3, LOW);
     digitalWrite(led_4, LOW);
     digitalWrite(led_5, LOW);
    }
    else{
     digitalWrite(led_1, HIGH);
     digitalWrite(led_2, HIGH);
     digitalWrite(led_3, HIGH);
     digitalWrite(led_4, HIGH);
     digitalWrite(led_5, HIGH);
    }
  }
}

void loop()
{
  weather = digitalRead(cuaca); // membaca cuaca dari sensor ldr
  Blynk.run(); // menjalankan blynk
  output(); //menjalankan fungsi output untuk memberikan signal pada digital output
  LCD(); // menjalankan library LCD
}

