#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(2,3);
 
#include <String.h>

 
 
void setup()
{
  gprsSerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
 
  delay(1000);
}
 
void loop()
{
      float h = analogRead(A0);
      float t = analogRead(A0); 
      delay(100);   
         
      Serial.print("Analog value =");
      Serial.println(t);
      
   
  if (gprsSerial.available())
    Serial.write(gprsSerial.read());
 
  gprsSerial.println("AT");
  delay(50);
 
  gprsSerial.println("AT+CPIN?");
  delay(50);
 
  gprsSerial.println("AT+CREG?");
  delay(50);
 
  gprsSerial.println("AT+CGATT?");
  delay(50);
 
  gprsSerial.println("AT+CIPSHUT");
  delay(100);
 
  gprsSerial.println("AT+CIPSTATUS");
  delay(250);
 
  gprsSerial.println("AT+CIPMUX=0");
  delay(250);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"internet\"");//start task and setting the APN,
  delay(250);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(250);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(250);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
  delay(250);
 
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(250);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(250);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=I7HHP47YNWI8PSM8&field1=0" ;//+ String(t) +"&field2="+String(h)
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  
  delay(250);
  ShowSerialData();
 
  gprsSerial.println((char)26);//sending
  delay(1000);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 
void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(1000); 
  
}
