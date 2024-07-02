#include <Arduino.h>
#include <Keypad.h>
// put function declarations here:
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {9, 10, 11}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
      Serial.begin(9600);
      pinMode(2,OUTPUT);  
      pinMode(4,INPUT);  
      pinMode(A0,OUTPUT);//led for wrong password 
      pinMode(A1,OUTPUT);//motor pins
      pinMode(A2,OUTPUT);
      pinMode(A3,OUTPUT);
      
}
static int i=0;
static int tries=0;
String pass;
static int r;
static int distance;
static int duration;

void loop() {
   char h=kpd.getKey();
   if(h){
  
     pass=pass+h;
     i++;

   }

   if (i==3)
   {
      /* code */
   if (pass=="123")
   {
   Serial.print('h');
      pass="";
      i=0;
         
         digitalWrite(A0,LOW);//led
         digitalWrite(A1,HIGH);
         digitalWrite(A2,HIGH);
         digitalWrite(A3,LOW);
         delay(3000);

      r=0;
      
         digitalWrite(A1,LOW);
         digitalWrite(A2,LOW);
         digitalWrite(A3,LOW);
         delay(3000);


   ////////// ultrasonic ///////// check
   while(1)
   {
      /* code */
      
   digitalWrite(2, LOW);
   delayMicroseconds(2);
   digitalWrite(2, HIGH);
   delayMicroseconds(10);
   digitalWrite(2, LOW);

   duration = pulseIn(4, HIGH);
   distance = (duration*.0343)/2;
   if ((distance>=40)&(r==0))
   {
      /* code */
         digitalWrite(A1,HIGH);
         digitalWrite(A2,LOW);
         digitalWrite(A3,HIGH);
         delay(3000);
         digitalWrite(A1,LOW);
         digitalWrite(A2,LOW);
         digitalWrite(A3,LOW);
         r=r+1;
         break;
   }else{
         digitalWrite(A1,LOW);
         digitalWrite(A2,LOW);
         digitalWrite(A3,LOW);
         delay(3000);
   }
   }
   

   }else{
      if (tries==2)
      {
         Serial.println("z");
         pass="";
         i=0;
         tries=0;
         
      }
      else{
         
      pass="";
      i=0;
      tries++;
      digitalWrite(A0,HIGH);

      }
      
   
   
      
   }
   }    

}

