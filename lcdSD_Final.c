#include <rxduino.h>
#include <Liquidcrystal.h>
#include <sdmmc.h>
SDMMC mySD;
LiquidCrystal lcd (0, 1,2, 3, 4,5); //Rs,EN,D4,D5,D6,D7
#define led 8
#define lcdled 9
#define soils 6
int count=0;
int ldr =0;
float temp=0.0;
float solar=0.0;
float battery=0.0;
int soil=0;
void scanSensors()
{
ldr=analogRead(5);
temp=analogRead(4);
temp*=0.488;
solar=analogRead(0);
solar*=0.0384;
battery=analogRead(1);
battery*=0.0201;
digitalWrite(soils,1);
delay(1000);
soil=analogRead(2);
delay(1000);
digitalWrite(soils,0);
}
void disp()
{
scanSensors();
lcd.clear();
lcd.print ("Light intensity");
if (ldr>550)
{
digitalWrite(9,1);
}
else
{
digitalWrite(9,0);
}
lcd.setCursor(0,1);
lcd.print(ldr);
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temperature");
lcd.setCursor(0,1);
lcd.print(temp);
delay(2000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Solar Panel V");
lcd.setCursor(0,1);
lcd.print(solar);
delay(2000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Battery V");
lcd.setCursor(0,1);
lcd.print(battery);
delay(2000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Soil Moisture");
lcd.setCursor(0,1);
lcd.print(soil);
delay(2000);

digitalWrite(8,1);
delay(100);
digitalWrite(8,0);
delay(100);
}
void writeSD()
{
digitalWrite (PIN_LED2, 1);
File myFile = mySD.open ("t_write.txt", FILE_WRITE);
    if (myFile == false)
    {
        lcd.clear();
        lcd.print("Access Failed");
        digitalWrite (PIN_LED3, 1);
        while (1) {
                   }
    }

    // Write
    //Serial.println ("Success to access MMC");
    //digitalWrite(PIN_LED2,1);
 
   myFile.print(ldr);
   myFile.print(',');
   myFile.print(temp);
   myFile.print(',');
   myFile.print(solar);
   myFile.print(',');
   myFile.print(battery);
   myFile.print(',');
   myFile.print(soil);
   myFile.println ();
   myFile.close ();
   delay(500);
   digitalWrite(PIN_LED2,0);
}
void setup()
{       lcd.begin (16,2);
        pinMode(PIN_LED0,OUTPUT);
        pinMode(PIN_LED1,OUTPUT);
        pinMode(PIN_LED2,OUTPUT);
        pinMode(PIN_LED3,OUTPUT);
        pinMode(6,OUTPUT);
        pinMode(7,OUTPUT);
        pinMode(8,OUTPUT);
        pinMode(9,OUTPUT);   
        digitalWrite(7, 0);
        digitalWrite(9, 0);
        digitalWrite(6, 0);
        digitalWrite(8, 0);
        lcd.print("  CloudY v3.4  ");
        
        // start the Ethernet connection and the server:
       
        mySD.begin ();
        //pinMode ( PIN_SW ,INPUT );
        delay(500);
        digitalWrite(PIN_LED0, 1);                            
}
void loop()
{
disp();
count++;
if(count==5)
{
writeSD();
count=0;
}
}



