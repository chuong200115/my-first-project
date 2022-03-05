#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int trig1 = 8;
const int echo1 = 7;
const int trig2 = A5;
const int echo2 = A4;
const int relay = 13;   // chân máy bơm

int moc_tren = 900;  // Thay đổi theo thực tế
int moc_duoi = 100;  // Thay đổi theo thực tế
bool relay_status = 0;  
unsigned long milli, milli2;

int count = 0;
int alarm_flag = 0;
int sec_default = 10;
boolean start = false; //mac dinh chua dem
int btnPIN[7] = {53,51,49,47,45,43,41};
int btn[7];

int hour = 0;
int minute = 0;
int sec = sec_default;

//...............................................
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
 lcd.setCursor(0, 0);
 lcd.print("Distance:");
 lcd.setCursor(13, 0);
 lcd.print(" cm");
 pinMode(trig1, OUTPUT);
 pinMode(echo1, INPUT);
 pinMode(trig2, OUTPUT);
 pinMode(echo2, INPUT);
 pinMode(relay,OUTPUT);


  for (int i = 0; i < 7; i++)        pinMode(btnPIN[i], INPUT_PULLUP);
  for (int i = 0; i < 7; i++) btn[i] = 0;
  milli = milli2 = millis(); 
  
  lcd.setCursor(0, 1);
  lcd.print("Time:");

}
//...............................................
void loop()
{
 unsigned long duration1;
 unsigned long duration2;
 int distance1;
 int distance2;

// do cao binh chua 
 digitalWrite(trig1, 0);
 delayMicroseconds(2);
 digitalWrite(trig1, 1);
 delayMicroseconds(5);
 digitalWrite(trig1, 0);
 duration1 = pulseIn(echo1, HIGH);
 distance1 = int(duration1 / 2 / 29.412);

// do cao nguon nuoc
 digitalWrite(trig2, 0);
 delayMicroseconds(2);
 digitalWrite(trig2, 1);
 delayMicroseconds(5);
 digitalWrite(trig2, 0);
 duration2 = pulseIn(echo2, HIGH);
 distance2 = int(duration2 / 2 / 29.412);

// man hinh lcd dong 1
 lcd.setCursor(10, 0);
 lcd.print(distance1);
 if (distance1 < 10) {
   lcd.setCursor(11, 0);
   lcd.print("  ");
 }
 else if (distance1 < 100) {
   lcd.setCursor(12, 0);
   lcd.print(' ');
 }
 if (distance1 > moc_tren && distance2 <10 && relay_status == 0)
   {
    
     digitalWrite (relay, HIGH);
    
   }
   else if (distance2 > 100 && distance1 > moc_tren)
   {
     digitalWrite (relay, LOW);
     relay_status = 1;
   }
  else if (relay_status == 1 && distance1 > moc_tren)
   {
   
    if ( sec > 0 && (millis() - milli) > 1000) //dem nguoc 
    {
        milli = millis();
        sec -= 1;
    }
    if(sec == 0)  
    {
    digitalWrite(relay,HIGH);
    relay_status =0;
    sec= sec_default;
    }
   
   }
  
 else if (distance1 < moc_duoi)
   {
     digitalWrite (relay,LOW);
   
   }

  hour = sec/3600;
  minute = (sec%3600)/60;
  int sec1 = sec%3600%60;

  // man hinh lcd dong 2
    lcd.setCursor(6, 1);
    lcd.print(hour);
    lcd.print("h");
    lcd.setCursor(9, 1);
    lcd.print(minute);
    lcd.print("m");
    lcd.setCursor(12, 1);
    lcd.print(sec1);
    lcd.print("s");
    
// hen gio
  if (millis() - milli2 > 300) //Cứ sau mỗi 300 mili giây là đọc tất cả giá trị button
  { 
    
     for (int i = 0; i < 7; i++)      btn[i] = digitalRead(btnPIN[i]);
     
     
     if (!btn[2]) // cong 1 tieng
     {
        sec = min(99*3600-1, sec + 3600);
     }
     
     else if (!btn[3]) // cong 1 phut
     {
        sec = min(60*60-1, sec + 60);
     }
     
     else if (!btn[4]) // tru 1 tieng
     {
        sec = max(0, sec - 3600);
     }
     
     else if (!btn[5]) // tru 1 phut
     {
        sec = max(0, sec - 60);
     }
     
     milli2 = millis(); 
  }
}
