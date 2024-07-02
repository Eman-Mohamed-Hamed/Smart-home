#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);  // rx ,tx
LiquidCrystal_I2C lcd(0x27,16,2);

DHT_Unified dht(12, DHT11);

void setup() {


  BT.begin(9600);
  Serial.begin(9600);

  pinMode(2,OUTPUT); //buzzer
  pinMode(3,OUTPUT);// LDR led 

  pinMode(8,OUTPUT); // fan 
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);

  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A7,INPUT); //analog pin

  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
    
  dht.begin();
  delay(1000);

}

void mode1(){
  float l=analogRead(A7);

  BT.println(l);
  if (l>=500)
  {
    digitalWrite(3,HIGH);
    lcd.clear();
    lcd.print("It is dark now");
    delay(500);
  }
  else{

    digitalWrite(3,LOW);

    lcd.clear();
    lcd.print("thre is light");

    delay(500);
  }

  delay(500);
}

static float temp=0.00;

void mode3(){

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    BT.println(F("Error reading temperature!"));
  }
  else {
    temp=float(event.temperature);
    BT.println("Temperature: "+String(event.temperature)+"°C");

    lcd.setCursor(1,0);
    lcd.clear();
    lcd.print("Temp: "+String(event.temperature)+" C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {

    BT.print(F("Humidity: "));
    BT.print(event.relative_humidity);
    BT.println(F("%"));

    lcd.setCursor(1,1);
    lcd.print("Hum: "+String(event.relative_humidity)+"%");

  }
  delay(2000);
}

static char m;
void loop() {
  BT.println("select mode for  Arduino");
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("select mode !");
  delay(1000);
  lcd.clear();
     

  if(BT.available() > 0 ){
    
    char mode= BT.read();

    if (mode=='1')
    {
      BT.println("Mode 1");

      lcd.clear();
      lcd.print("mode 1");
      delay(500);
      lcd.clear();
      
      while (1)
      {
        mode1();
        if (BT.read()=='b')
        {
          BT.println("end"); 
          break;
        }
        if (Serial.available())
        {
          m=Serial.read();
      
          if (m=='z')
          {
              tone(2,100);
              delay(2000);
            
          }else{
            noTone(2);
          }   
        }
      }
        
      

    }
    else if (mode=='2')
    {
      BT.println("mode2");
      lcd.clear();
      lcd.print("mode 2");
      delay(500);
      lcd.clear();

      while (1)
      {
        if(BT.available() > 0 ){

        char led=BT.read();

        if (led=='r')
        {
          digitalWrite(A2,HIGH);
        
          BT.println("red led is on");

          lcd.clear();
          lcd.print("red is on ");
        }
        if (led=='y')
        {
              digitalWrite(A1,HIGH);
          
              BT.println("yellow led is on");

              lcd.clear();
              lcd.print("yellow is on ");
        }
        if (led=='g')
        {
            digitalWrite(A0,HIGH);
          
            BT.println("  green led is on");

            lcd.clear();
            lcd.print("green is on ");
        }
        if (led=='b')
        {
          BT.println("End");
                        
          lcd.clear();
          lcd.print("End of mode");
          delay(500);
                        
          break;
        }
        if(led=='f'){

            digitalWrite(A0,LOW);
            digitalWrite(A1,LOW);
            digitalWrite(A2,LOW);
            BT.println("All leds are off ");

            lcd.clear();
            lcd.print("All is off");
            

        }     
        if(led=='o'){

            digitalWrite(A0,HIGH);
            digitalWrite(A1,HIGH);
            digitalWrite(A2,HIGH);
            BT.println("All leds are on ");

            lcd.clear();
            lcd.print("All is on");
            

        }       
        if (!(led=='r' || led=='g' || led=='y' || led=='b' || led=='f' || led=='o'))
        {
          BT.println("wrong choice ");

              lcd.clear();
            lcd.print("wrong choice ");
        }

        }
        if (Serial.available())
        {
          m=Serial.read();
          
          if (m=='z')
          {
            /* code */
              tone(2,100);
              delay(2000);
            
          }else{
            noTone(2);
          }   
        }
      }
           
             
    }
    else if (mode=='3')
    {
      BT.println("mode3");

      lcd.clear();
      lcd.print("mode 3");
      delay(500);
      lcd.clear();

      while (1)
      {
        mode3();

        if (temp>20.0)
        {
        digitalWrite(8,HIGH); //enable
        digitalWrite(6,HIGH); 
        digitalWrite(7,LOW);
        delay(3000);
        Serial.print("fan is on ");
        }else
        {
          digitalWrite(8,LOW);
          digitalWrite(6,LOW);
          digitalWrite(7,LOW);
          Serial.print("fan is off ");
          delay(3000);
        }
           
        if (BT.read()=='b')
        {
          BT.println("End");
          break;
                
        }
        if (Serial.available())
        {
          m=Serial.read();
            
          if (m=='z')
          {
            tone(2,100);
            delay(2000);
            
          }else{
            noTone(2);
          }   
        }
      }
        
    }
        
    else 
    {
      BT.println("wrong mode");

      lcd.clear();
      lcd.print("wrong mode ");
      delay(500);
      lcd.clear();

    }
  }

  if (Serial.available())
  {
    m=Serial.read();
      
    if (m=='z')
    {
      
        tone(2,100);
        delay(2000);
      
    }else{
      noTone(2);
    }
  }

   }

