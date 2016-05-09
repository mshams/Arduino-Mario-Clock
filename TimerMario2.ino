#include "NokiaFa5110.h"
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include "Util.h"
#include <avr/pgmspace.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>
#include <Narcoleptic.h>


const byte PIN_MENU = 8, PIN_UP = 12, PIN_DOWN = 13;
const byte PIN_TEMP = A0, PIN_TONE = 10, PIN_LED1 = A1, PIN_LED2 = A2, PIN_LED3 = A3, PIN_LED4 = 2;
const byte PIN_LCD1=3, PIN_LCD2=4, PIN_LCD3=5, PIN_LCD4=6, PIN_LCD5=7, PIN_LCD6=9;
const byte APP_MAIN=0, APP_SETTIME=1, APP_SETDATE=2, APP_SETALARM=3, APP_MENU=4, APP_ALARM=5, APP_INTRO=6, APP_NONE=7;
const byte EEPROM_ID = 0x99;
const int EEP_ID_ADDR = 0, EEP_ALARM1_ADDR = 1, EEP_ALARM2_ADDR = 3;

const String preNon = "+  ";
const String preSel = "+ >";
const String preTitle = "+++++MENU+++++";
const String preBottom = "++++++++++++++";
const String preMiddle = "+            +";

byte appState = APP_INTRO;
byte button = 0, selectedMenu = APP_MENU, setPointer=0;
int chour, cminute, cyear, cmonth, cday, cahour=6, caminute=10, ctemp, otemp;
boolean changed = true;
OneWire temp(PIN_TEMP);
DallasTemperature sensors(&temp);

NokiaFa5110 lcd = NokiaFa5110(PIN_LCD1, PIN_LCD2, PIN_LCD3, PIN_LCD4, PIN_LCD5, PIN_LCD6);
tmElements_t tm;


void setup(void)
{
  Serial.begin(9600);
  Serial.println("START");
  
  pinMode(PIN_MENU, INPUT);
  pinMode(PIN_UP, INPUT);
  pinMode(PIN_DOWN, INPUT);  

  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
  //lcd.LcdClear();
  ////lcd.WriteString("START",25,2);

  analogReference(INTERNAL);
  randomSeed(analogRead(0));
  //sensors.begin();
  

  /*
  if( EEPROM.read(EEP_ID_ADDR) == EEPROM_ID){
    cahour = word(EEPROM.read(EEP_ALARM1_ADDR), EEPROM.read(EEP_ALARM1_ADDR+1));
    caminute = word(EEPROM.read(EEP_ALARM2_ADDR), EEPROM.read(EEP_ALARM2_ADDR+1));    
  }
  else
  {
    // here if the ID is not found, so write the default data
    EEPROM.write(EEP_ID_ADDR, EEPROM_ID);
    EEPROM.write(EEP_ALARM1_ADDR, highByte(cahour));
    EEPROM.write(EEP_ALARM1_ADDR+1, lowByte(cahour));
    EEPROM.write(EEP_ALARM2_ADDR, highByte(caminute));
    EEPROM.write(EEP_ALARM2_ADDR+1, lowByte(caminute));
  }
  */

}

void loop(void)
{
  switch(appState){
  case  APP_INTRO:
    //lcd.Light(1);
    //lcd.PrintPic(Logo, 504);
    PlayTheme();
    //delay(3000);
    MarioAnim();

    appState = APP_MAIN;
    break;

  case  APP_MAIN:
    if (! changed) break;
    //lcd.LcdClear();
    //lcd.Light(0);
    //lcd.WriteString("    " + TimeString(),0,0);
    //lcd.WriteString("  "   + DateString(), 0,2);
    //lcd.WriteString("  "   + GetTemp() + " |" + AlarmString(), 0,4);
    changed = false;
    //delay(1000);
    //appState = APP_MENU;
    break;

  case  APP_MENU:
    if (! changed) break;
    //lcd.LcdClear();
    //lcd.Light(1);
    //lcd.WriteString(preTitle, 0,0);
    //lcd.WriteString((selectedMenu == APP_SETTIME?  preSel : preNon) + "Set Time  +", 0,1);
    //lcd.WriteString((selectedMenu == APP_SETDATE?  preSel : preNon) + "Set Date  +", 0,2);
    //lcd.WriteString((selectedMenu == APP_SETALARM? preSel : preNon) + "Set Alarm +", 0,3);
    //lcd.WriteString((selectedMenu == APP_MENU?  preSel : preNon) + "Back      +", 0,4);
    //lcd.WriteString(preBottom,0,5);
    changed = false;
    delay(500);
    //appState = APP_NONE;
    break;

  case  APP_SETTIME:
    if (! changed) break;
    //lcd.LcdClear();
    //lcd.WriteString(preTitle, 0,0);
    //lcd.WriteString(preMiddle, 0,1);
    //lcd.WriteString("+    " + Format(chour) + ":" + Format(cminute) + "   +", 0,2);
    //lcd.WriteString(StrPointer(setPointer), 0,3);
    //lcd.WriteString(preMiddle, 0,4);
    //lcd.WriteString(preBottom,0,5);
    changed = false;
    delay(500);
    //appState = APP_MAIN;
    break;

  case  APP_SETDATE:
    if (! changed) break;
    //lcd.LcdClear();
    //lcd.WriteString(preTitle, 0,0);
    //lcd.WriteString(preMiddle, 0,1);
    //lcd.WriteString("+ " + String(cyear) + "/" + Format(cmonth) + "/" + Format(cday) + " +", 0,2);
    //lcd.WriteString(StrPointer(setPointer), 0,3);
    //lcd.WriteString(preMiddle, 0,4);
    //lcd.WriteString(preBottom,0,5);
    changed = false;
    delay(500);
    //appState = APP_MAIN;
    break;

  case  APP_SETALARM:
    if (! changed) break;
    //lcd.LcdClear();
    //lcd.WriteString(preTitle, 0,0);
    //lcd.WriteString(preMiddle, 0,1);
    //lcd.WriteString("+    " + AlarmString() + "   +", 0,2);
    //lcd.WriteString(StrPointer(setPointer), 0,3);
    //lcd.WriteString(preMiddle, 0,4);
    //lcd.WriteString(preBottom,0,5);
    changed = false;
    delay(500);
    //appState = APP_MAIN;
    break;

  case  APP_ALARM:
    //lcd.LcdClear();
    MarioAnim();
    changed = true;
    // appState = APP_MAIN;
    break; 
  }

  /*
  Serial.println(TimeString());
   Serial.print(cyear);
   Serial.print(cmonth);
   Serial.println(cday);
   Serial.print(chour);
   Serial.println(cminute);
   Serial.print(cahour);
   Serial.println(caminute);
   
   Serial.print(year);
   Serial.print(month);
   Serial.println(day);
   Serial.print(hour);
   Serial.println(minut);
   */
  Serial.println(123);


  //CheckButtons();
  //GetTemp();
  //TimeString();
  //DateString();  
  //delay(100);

  //Narcoleptic.delay(100);
}

String GetTemp(void){    
  //ctemp = int(floor(analogRead(PIN_TEMP) / 9.31));
  //sensors.requestTemperatures();
  //ctemp = int(floor(sensors.getTempCByIndex(0)));

  if (otemp != ctemp){
    otemp = ctemp; 
    changed = true;
    //lcd.WriteString(String(ctemp), 2,4);
  }

  return "~" + String(ctemp);
}

String TimeString(void){
  RTC.read(tm);
  if(cminute != tm.Minute){
    chour = tm.Hour;
    cminute = tm.Minute;
    changed = true;
  }

  //Check for alarm time
  if (chour == cahour && cminute == caminute && tm.Second == 0) appState = APP_ALARM;

  return Format(chour) + ":" + Format(cminute);
}

String AlarmString(void){  
  return Format(cahour) + ":" + Format(caminute);
}

String DateString(void){
  RTC.read(tm);  
  cyear = tmYearToCalendar(tm.Year);
  cmonth = tm.Month;
  cday = tm.Day;
  return String(cyear) + "/" + Format(cmonth) + "/" + Format(cday);  
}

String Format(int n){
  return (n>9 ? String(n): "0" + String(n));
}

byte CheckButtons(){
  if (digitalRead(PIN_MENU)== HIGH){
    button = PIN_MENU;
    changed = true;

    if (appState == APP_MAIN){
      appState = APP_MENU;
    }
    else if (appState == APP_ALARM){      
      appState = APP_MAIN;
    }
    else if (appState == APP_MENU && selectedMenu == APP_MENU){
      //on back menu
      appState = APP_MAIN;    
      //selectedMenu = APP_SETTIME;
    }
    else if (appState == APP_SETTIME || appState == APP_SETALARM){
      //move pointer in set menus
      if (setPointer < 3){
        setPointer += 1;
      }
      else{
        setPointer = 0;

        //save datetime
        if (appState == APP_SETTIME) WriteDateTime(chour, cminute, cyear, cmonth, cday);
        appState = APP_MAIN;
        selectedMenu = APP_MENU;
      }
    }
    else if (appState == APP_SETDATE){
      //move pointer in set menus
      if (setPointer < 7){
        setPointer += 1;
      }
      else{
        setPointer = 0;

        //save datetime
        WriteDateTime(chour, cminute, cyear, cmonth, cday);
        appState = APP_MAIN;
        selectedMenu = APP_MENU;
      }
    }    
    else if (appState == APP_MENU && (selectedMenu >= APP_SETTIME && selectedMenu <= APP_SETALARM)){
      //select menu item
      appState = selectedMenu;
    }    
  }
  else if (digitalRead(PIN_UP)== HIGH){
    button = PIN_UP;
    changed = true;

    if (appState == APP_MAIN){
      //lcd.Light(1);
    }
    else if (appState == APP_MENU){
      //on menu go up
      selectedMenu -= 1;
      if (selectedMenu < APP_SETTIME) selectedMenu = APP_MENU;
    }
    else if (appState == APP_ALARM){      
      appState = APP_MAIN;
    }
    else if (appState == APP_SETTIME && selectedMenu == APP_SETTIME){
      //in set menus
      SetTime(setPointer, 1);   
    }
    else if (appState == APP_SETDATE && selectedMenu == APP_SETDATE){
      //in set menus
      SetDate(setPointer, 1);   
    }
    else if (appState == APP_SETALARM && selectedMenu == APP_SETALARM){
      //in set menus
      SetAlarm(setPointer, 1);   
    }

  }
  else if (digitalRead(PIN_DOWN)== HIGH){
    button = PIN_DOWN;
    changed = true;

    if (appState == APP_MAIN){
      //lcd.Light(0);
    }
    else if (appState == APP_MENU){
      //on menu go up
      selectedMenu = (selectedMenu + 1) % (APP_MENU + 1);
      if (selectedMenu == 0) selectedMenu = APP_SETTIME;      
    }
    else if (appState == APP_ALARM){      
      appState = APP_MAIN;
    }
    else if (appState == APP_SETTIME && selectedMenu == APP_SETTIME){
      //in set menus
      SetTime(setPointer, -1);   
    }
    else if (appState == APP_SETDATE && selectedMenu == APP_SETDATE){
      //in set menus
      SetDate(setPointer, -1);   
    }
    else if (appState == APP_SETALARM && selectedMenu == APP_SETALARM){
      //in set menus
      SetAlarm(setPointer, -1);   
    }
  } 
  else{
    button = 0;
  }

  return button;
}


void SetTime(byte pointer, int val){
  if (pointer<2){
    chour += (pointer == 0? val*10 : val);
    if (chour > 24) chour=24;
    if (chour < 0) chour=0;
  }  
  else if (pointer>1){
    cminute += (pointer == 2? val*10 : val);
    if (cminute > 60) cminute=60;
    if (cminute < 0) cminute=0;
  }
}

void SetDate(byte pointer, int val){
  if (pointer<4){
    if (pointer == 0){
      val *= 1000;
    }
    else if (pointer == 1){
      val *= 100;
    }
    else if (pointer == 2){
      val *= 10;
    }
    cyear += val;
    if (cyear > 4000) cyear=2000;
    if (cyear < 1) cyear=2000;
  }  
  else if (pointer>3 && pointer <6){
    cmonth += (pointer == 4? val*10 : val);
    if (cmonth > 12) cmonth=12;
    if (cmonth < 1) cmonth=1;
  }
  else if (pointer>5){
    cday += (pointer == 6? val*10 : val);
    if (cday > 31) cday=31;
    if (cday < 1) cday=1;
  }
}

void SetAlarm(byte pointer, int val){
  if (pointer<2){
    cahour += (pointer == 0? val*10 : val);
    if (cahour > 24) cahour=24;
    if (cahour < 0) cahour=0;
  }  
  else if (pointer>1){
    caminute += (pointer == 2? val*10 : val);
    if (caminute > 60) caminute=60;
    if (caminute < 0) caminute=0;
  }
  //Serial.println(val);
  //Serial.println(AlarmString());
}

String StrPointer(byte pointer){
  String temp = preMiddle;
  byte point = pointer + (appState == APP_SETDATE ? 2:5);
  if ((appState == APP_SETTIME || appState == APP_SETALARM) && pointer >1) point +=1;
  if (appState == APP_SETDATE && pointer >3) point +=1;
  if (appState == APP_SETDATE && pointer >5) point +=1;
  temp.setCharAt(point, '^');
  return temp; 
}

boolean WriteDateTime(int hour, int minut, int year, int month, int day){  
  tm.Year = CalendarYrToTm(year);
  tm.Month = month;
  tm.Day = day;
  tm.Hour = hour;
  tm.Minute = minut;
  return RTC.write(tm);
}

void MarioAnim(void){
  LedsOff();
  //lcd.Light(0);
  //lcd.PrintPic(Image1, 504);
  delay(500);
  //lcd.PrintPic(Image2, 504);
  tone(PIN_TONE,560,80);
  LedOn(0, 1);
  LedOn(3, 1);
  delay(100);
  //lcd.PrintPic(Image3, 504);
  //lcd.Light(1);
  tone(PIN_TONE,860,50);
  LedOn(1, 1);
  LedOn(2, 1);  
  delay(170);
  //lcd.PrintPic(Image2, 504);
  //lcd.Light(0);
  tone(PIN_TONE,700,100);
  LedOn(0, 0);
  LedOn(3, 0);  
  delay(130);
  //lcd.PrintPic(Image1, 504);
  tone(PIN_TONE,500,100);
  LedOn(1, 0);
  LedOn(2, 0);  
  delay(150);
  //lcd.PrintPic(Image2, 504);
  tone(PIN_TONE,560,80); 
  LedOn(0, 1);
  LedOn(3, 1);  
  delay(100);
  //lcd.PrintPic(Image3, 504);
  //lcd.Light(1);
  tone(PIN_TONE,860,50);
  LedOn(1, 1);
  LedOn(2, 1);    
  delay(170);
  //lcd.PrintPic(Image2, 504);
  //lcd.Light(0);
  tone(PIN_TONE,700,100);
  LedOn(0, 0);
  LedOn(3, 0);    
  delay(130);
  //lcd.PrintPic(Image1, 504);
  tone(PIN_TONE,500,100);
  LedOn(1, 0);
  LedOn(2, 0);    
  delay(150);
  LedsOff();
}

void PlayTheme(void){
  LedsOnRandom();
  tone(PIN_TONE,660,100);
  delay(80+75);
  tone(PIN_TONE,660,100);
  delay(80+150);
  tone(PIN_TONE,660,100);
  delay(80+150);
  LedsOnRandom();
  tone(PIN_TONE,510,100);
  delay(80+50);
  tone(PIN_TONE,660,100);
  delay(80+150);
  tone(PIN_TONE,770,100);
  LedsOnRandom();
  delay(80+275);
  tone(PIN_TONE,380,100);
  delay(80+287);
  tone(PIN_TONE,510,100);
  delay(80+225);
  tone(PIN_TONE,380,100);
  LedsOnRandom();
  delay(80+200);
  tone(PIN_TONE,320,100);
  delay(80+250);
  tone(PIN_TONE,440,100);
  delay(80+150);
  tone(PIN_TONE,480,80);
  LedsOnRandom();
  delay(80+165);
  tone(PIN_TONE,450,100);
  delay(80+75);
  tone(PIN_TONE,430,100);
  delay(80+150);
  tone(PIN_TONE,380,100);
  LedsOnRandom();
  delay(80+100);
  tone(PIN_TONE,660,80);
  delay(80+100);
  tone(PIN_TONE,760,50);
  delay(80+75);
  tone(PIN_TONE,860,100);
  LedsOnRandom();
  delay(80+150);
  tone(PIN_TONE,700,80);
  delay(80+75);
  tone(PIN_TONE,760,50);
  delay(80+175);
  tone(PIN_TONE,660,80);
  LedsOnRandom();
  delay(80+150);
  tone(PIN_TONE,520,80);
  delay(80+75);
  tone(PIN_TONE,580,80);
  delay(80+75);
  tone(PIN_TONE,480,80);
  LedsOnRandom();
  delay(80+175);  
  tone(PIN_TONE,510,100);
  delay(80+275);
  noTone(PIN_TONE);
}

void LedsOff(void){
  digitalWrite(PIN_LED1, LOW); 
  digitalWrite(PIN_LED2, LOW); 
  digitalWrite(PIN_LED3, LOW); 
  digitalWrite(PIN_LED4, LOW); 
}

void LedsOnRandom(void){
  digitalWrite(PIN_LED1, random(0, 10)<5 ? HIGH : LOW); 
  digitalWrite(PIN_LED2, random(0, 10)<5 ? HIGH : LOW); 
  digitalWrite(PIN_LED3, random(0, 10)<5 ? HIGH : LOW); 
  digitalWrite(PIN_LED4, random(0, 10)<5 ? HIGH : LOW); 
}

void LedOn(byte led, byte state){
  const byte leds[4] = {
    PIN_LED1, PIN_LED2, PIN_LED3, PIN_LED4    };
  digitalWrite(leds[led], state);
}















