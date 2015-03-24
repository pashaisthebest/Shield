/* 
 SHIELD Controller v2 Frimware
 
 Аналоговые PIN:
 А0 — напряжение от аккумулятора №1
 А1 — напряжение от аккумулятора №2
 А2 — напряжение от аккумулятора №3
 А3 — напряжение от аккумулятора №4
 
 Входные напряжения этих пинов надо будет подбирать по результатам испытаний, когда будет скетч готов, ориентировочно:
 3.5V — зарядка 0%
 4.0V — зарядка 100%
 
 Общая зарядка аккумуляторов будет считаться как среднее арифметическое 4-х значений. 
 Контроль каждого аккумулятора нам необходим т.к. они разряжаются неравномерно.
 А4 — сигнал "подключена зарядка" если зарядка подключена приходит напряжение 4V.
 
 Цифровые PIN:
 10 — управление логотипом
 12 — управление нагревом
 */

#include <SoftwareSerial.h>
#include <DallasTemperature.h>
#include <OneWire.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 12

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

SoftwareSerial mySerial(0, 1);

const int CHANGING_HEAT_LEVEL = 101;
int whatWereDoingByte = 255;
int valueByte = 255;

int logo = 9;
int heat = 10;
int charge = A2; // Индикатор зарядки SHIELD от внешней сети
int incomingbyte = 0;

float battery0 = 0;
float battery1 = 0;
float battery2 = 0;
float battery3 = 0;
float batteriesAreCharging = 0;

float batteryAverage = 0;
int batteryLevel = 0;
float charging = 0;

const float battery0coeff = 0.00746003898635;
const float battery1coeff = 0.00372434017595;
const float battery2coeff = 0.00374389051808;
const float battery3coeff = 0.00587635239567;

int batteryAverageOverTime = 0;
const float BATTERY_MINIMUM_V = 3.5;

const int writeChargeValueOnceInLoops = 100;
int batteryLevelsOverTimeSum = 0;
int batteryCounter = 0;

int currentShieldHeatValue = 0;

void setup() {

//  pinMode(10, OUTPUT);
//  digitalWrite(10, HIGH);
    
  Serial.begin(115200);  
  mySerial.begin(115200);

  pinMode(logo, OUTPUT);
  pinMode(heat, OUTPUT);
  pinMode(charge, OUTPUT);
  digitalWrite(logo, LOW);
  digitalWrite(heat, LOW);
  digitalWrite(charge, LOW);

//  Serial.println("SHEILD IS HERE"); 


  Serial.println("Dallas Temperature IC Control Library Demo");
  // Start up the library
  sensors.begin();
}

void loop() {
  
  
  
  //  Serial.print("battery counter = "); 
  //  Serial.println(batteryCounter); 

//  delay(100);


  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
//  Serial.print("Requesting temperatures...");
//  sensors.requestTemperatures(); // Send the command to get temperatures
//  Serial.println("DONE");
//  
//  Serial.print("Temperature for the device 1 (index 0) is: ");
//  Serial.println(sensors.getTempCByIndex(0));  


  /* BATTERIES 
   
   BATTERY 0 VOLTAGE
   513,00  3,827  0.00746003898635
   
   BATTERY 1 VOLTAGE
   1023.00  3.810  0.00372434017595
   
   BATTERY 2 VOLTAGE
   1023.00  3.830  0.00374389051808
   
   BATTERY 3 VOLTAGE 
   647.00  3,802   0.00587635239567
   
   */

//  battery0 = analogRead(A0) * battery0coeff;
//  battery1 = analogRead(A1) * battery1coeff;
//  battery2 = analogRead(A2) * battery2coeff;
//  battery3 = analogRead(A3) * battery3coeff;
//
//  batteryAverage = (battery0 + battery1 + battery2 + battery3) / 4;
//  batteryLevel = (batteryAverage - BATTERY_MINIMUM_V) * 2 * 100;

//  if (batteryCounter >= writeChargeValueOnceInLoops) {
    //    Serial.print("BATTERIES CHARGE PERCENT = ");
    //    Serial.println(batteryLevelsOverTimeSum/writeChargeValueOnceInLoops);

//    byte batteryCommandByte = 102;
//    byte valueByte = batteryLevelsOverTimeSum/writeChargeValueOnceInLoops;
//    valueByte = (valueByte>100) ? 100 : valueByte;
//    Serial.println(batteryCommandByte);
//    Serial.println(valueByte);    
//
//    batteryLevelsOverTimeSum = 0; 
//    batteryCounter = 0; 


    //    if (battery0 <= 3.5)  {
    //      digitalWrite(heat, LOW);
    //      digitalWrite(logo, LOW);
    //      Serial.println("SHIELD IS TURNED OFF, BATTERY 0 VOLTAGE <= 1.75V");
    //    } 
    //    else if (battery1 <= 3.5) {
    //      digitalWrite(heat, LOW);
    //      digitalWrite(logo, LOW);
    //      Serial.println("SHIELD IS TURNED OFF, BATTERY 1 VOLTAGE <= 1.75V");
    //    } 
    //    else if (battery2 <= 3.5) {
    //      digitalWrite(heat, LOW);
    //      digitalWrite(logo, LOW);
    //      Serial.println("SHIELD IS TURNED OFF, BATTERY 2 VOLTAGE <= 1.75V");
    //    } 
    //    else if (battery3 <= 3.5) {
    //      digitalWrite(heat, LOW);
    //      digitalWrite(logo, LOW);
    //      Serial.println("SHIELD IS TURNED OFF, BATTERY 3 VOLTAGE <= 1.75V");
    //    }

//  }
//  else if (batteryCounter == 50) {
//
//    batteriesAreCharging = analogRead(A6);
//    
//
//      byte batteryCommandByte = 103;
//      byte valueByte;
//
//      if (batteriesAreCharging > 0) {
//        valueByte = 1;
//      }
//      else {
//        valueByte = 0;
//      }
//      
//      Serial.println(batteryCommandByte);
//      Serial.println(valueByte);    
//  }

//  batteryLevelsOverTimeSum += batteryLevel;
//  batteryCounter++;


  //  Serial.print("BATTERY 0 VOLTAGE = ");
  //  Serial.println(battery0);
  //  Serial.print("BATTERY 1 VOLTAGE = ");
  //  Serial.println(battery1);
  //  Serial.print("BATTERY 2 VOLTAGE = ");
  //  Serial.println(battery2);
  //  Serial.print("BATTERY 3 VOLTAGE = ");
  //  Serial.println(battery3);

  // Если напряжение на какой-либо из батарей падает до 1.75V мы отключаем SHIELD


  // BLE 
  if(mySerial.available() == 2) {

    // int currentMessagePointer = 0;
    // int whatWereDoingByte = 0;
    // int valueByte = 0;
    int availableCount = mySerial.available();
//    for (int i=0; i<availableCount; i++) {
//      incomingbyte = mySerial.read();
//      Serial.println(incomingbyte);
//    }

    char incomingBytes[availableCount];
    mySerial.readBytes(incomingBytes, availableCount);
    
    for (int i=0; i<availableCount; i++) {
      Serial.println((int)incomingBytes[i]);
    }
    

//    if (incomingbyte == CHANGING_HEAT_LEVEL) { // what were doing byte
//      whatWereDoingByte = incomingbyte;
//      valueByte = 255; // drop value
//    }
//    else if (incomingbyte >= 0 && incomingbyte <= 100 && whatWereDoingByte!=255) { // value byte, making sure that action byte is present
//      valueByte = incomingbyte;
//    }
//    else {
//      valueByte = 255;        
//      whatWereDoingByte = 255;
//    }
//
//    if (whatWereDoingByte != 255 && valueByte !=255) {
//
//      // decide on what to do with the incoming data
//      if (whatWereDoingByte == CHANGING_HEAT_LEVEL) {
//        setHeatVelueToShield(valueByte);
//      }
//
//      valueByte = 255;        
//      whatWereDoingByte = 255;
//    }
  } 
}

void setHeatVelueToShield( int value ) {

  if (value == 0) { // гасим все
    digitalWrite(logo, LOW);
    digitalWrite(heat, LOW);
    //    Serial.println("SHIELD IS SWITCHING OFF");
  }
  else {
  
    int finalValue = map(value, 0, 100, 40, 255);
    analogWrite(heat, finalValue);
    analogWrite(logo, finalValue);
  }
  
//  if (currentShieldHeatValue == 0 && value!=0) {
    // turning on
//    digitalWrite(logo, HIGH);
//    digitalWrite(heat, HIGH);
    
    //    Serial.println("SHIELD IS SWITCHING ON");
//  }



    currentShieldHeatValue = value;
  
  
//  analogWrite(heat, 100);
  
  //  Serial.print("SETTING VALUE TO SHIELD: ");
  //  Serial.println(currentShieldHeatValue);

  // here is the place to put the code that physically controls shield
}


