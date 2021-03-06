#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

void clear_bt_serial(){
  while(mySerial.available()){
    Serial.write(mySerial.read());
  }
}

// Note: it seems that you cannot communicate with the device when it is connected! This is pretty odd
void setup() {
  delay(5000);
  Serial.begin(115200);
  Serial.println("Starting");
  // Set baud to 9600 regardless of previous setting
  mySerial.begin(115200); delay(50);
  mySerial.println(); delay(50);
  mySerial.println(); delay(50);
  mySerial.println("BC:BR=06"); delay(100); 
  
  mySerial.begin(19200); delay(50);
  mySerial.println(); delay(50);
  mySerial.println(); delay(50);
  mySerial.println("BC:BR=06"); delay(100);
  
  mySerial.begin(9600);
  mySerial.println(); delay(50);
  mySerial.println(); delay(50);
  // Make sure the UI is activated
  mySerial.println("BC:UI=01");
  delay(50); clear_bt_serial();
  
  Serial.print("NM::");
  mySerial.println("BC:NM");
  delay(50); clear_bt_serial();
   
  Serial.print("BR::");
  mySerial.println("BC:BR");
  delay(50); clear_bt_serial();
  
  mySerial.println("BC:NM=AirBeam_99");
  delay(50); clear_bt_serial();
  //                      ATPowerOn, ACPaired,ATLinkLost,  Interval, DiscMode,  DiskTimeout
  mySerial.println("BC:FT=00,00,00,01,03,0000");  // It will never try to autoconnect and will always be in discoverable mode.
  delay(50); clear_bt_serial();
  
  mySerial.println("BC:BR=08"); // 19200 baud
  
  mySerial.begin(19200); delay(50);
  mySerial.println(); delay(50);
  mySerial.println(); delay(50);
  
  mySerial.println("BC:NM");
  Serial.println("NM::");
  clear_bt_serial();
  //mySerial.println("BC:BR=0C"); // 115200 baud
  Serial.println("Done");
}

// 50;InsertSensorPackageName;DHT22-RH;Humidity;RH;percent;%;0;25;50;75;100\n
void loop(){
  char c;
  if(mySerial.available()){
    Serial.write(mySerial.read());
  }

  if(Serial.available()){
    c = Serial.read();
    mySerial.write(c);
    //Serial.print("w: x");
    //Serial.println(c, HEX);
  }
}

