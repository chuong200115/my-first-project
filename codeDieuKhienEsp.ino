#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "djnAN27kGxB8WPyTCtyDZRRt9AT32u7M"; 
char ssid[] = "NgocTuan";                           
char pass[] = "01977161";


BlynkTimer timer;
void setup()
{
   Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);  
   timer.setInterval(1000L, blinkLedWidget);
   pinMode(D0, OUTPUT);  
   digitalWrite(D0,LOW);
   pinMode(D1, OUTPUT); 
   digitalWrite(D1,LOW);
   pinMode(D2, OUTPUT); 
   digitalWrite(D2,LOW);
   pinMode(D3, OUTPUT); 
   digitalWrite(D3,LOW);
   pinMode(D4, OUTPUT); 
   digitalWrite(D4,LOW);
   pinMode(D5, OUTPUT);    
   digitalWrite(D5,LOW);                             
}

WidgetLED led1(V1);


// V7 LED Widget is blinking
void blinkLedWidget()
{
if (led1.getValue()) {
led1.off();
} 
else{
  led1.on();
}
}

BLYNK_WRITE(V0)                     
{
   int pinValue = param.asInt();       
   
   if (pinValue == 1) {
   digitalWrite(D0, HIGH);         
   }   
   else {
   digitalWrite(D0, LOW);        
   }
}
BLYNK_WRITE(V2)                     
{
   int pinValue = param.asInt();       
   
   if (pinValue == 1) {
   digitalWrite(D1, HIGH);         
   }   
   else {
   digitalWrite(D1, LOW);        
   }
}
BLYNK_WRITE(V3)                     
{
   int pinValue = param.asInt();       
   
   if (pinValue == 1) {
   digitalWrite(D2, HIGH);         
   }   
   else {
   digitalWrite(D2, LOW);        
   }
}
BLYNK_WRITE(V4)                     
{
   int pinValue = param.asInt();       
   
   if (pinValue == 1) {
   digitalWrite(D3, HIGH);         
   }   
   else {
   digitalWrite(D3, LOW);        
   }
}
BLYNK_WRITE(V5)                     
{
   int pinValue = param.asInt();       
   
   if (pinValue == 1) {
   digitalWrite(D4, HIGH);         
   }   
   else {
   digitalWrite(D4, LOW);        
   }
}
BLYNK_WRITE(V6)                     
{
   int pinValue = param.asInt();       
   
   if (pinValue == 1) {
   digitalWrite(D5, HIGH);         
   }   
   else {
   digitalWrite(D5, LOW);        
   }
}
void loop()
{
   Blynk.run(); 
   timer.run();                  
}