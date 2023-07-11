#include <Servo.h>
Servo myservo;

#define slot1 3
#define slot2 2
#define trigPin 6
#define t2 7
#define slot3 4
#define slot4 5

long duration;
int distance;

int S1 = 0, S2 = 0, S3=0, S4 = 0;
int flag1 = 0, flag2 = 0;
int slot = 4, total = 0;
int d1, d2, dis1, dis2;

int x, pos = 0;

void Read_Sensor(){
  S1 = 0, S2 = 0, S3=0, S4=0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  d1 = pulseIn(slot3, HIGH);
  
  digitalWrite(t2, LOW);
  delayMicroseconds(2);
  digitalWrite(t2, HIGH);
  delayMicroseconds(10);
  digitalWrite(t2, LOW);
  d2 = pulseIn(slot4, HIGH);
  dis1 = d1*0.034/2;
  dis2 = d2*0.034/2;
  

  if(digitalRead(slot1) == 0){S1 = 1;}
  if(digitalRead(slot2) == 0){S2 = 1;}
  if(dis1 <=20){S3 = 1;}
  if(dis2 <=20){S4 = 1;}
  
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  pinMode(13, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(t2, OUTPUT);
  pinMode(slot3, INPUT);
  pinMode(slot4, INPUT);
  pinMode(slot1, INPUT);
  pinMode(slot2, INPUT);
  myservo.attach(9);
  myservo.write(0);

  Read_Sensor();
  total = S1+S2;
  slot = slot-total;
}

void loop() {
  while (!Serial.available());
  x = Serial.readString().toInt();
  if(x == 1){
    digitalWrite(13, HIGH);
    Read_Sensor();
    if(S1 == 1){Serial.println("S1: Fill ");}
    else{Serial.println("S1: Empty");}

    if(S2 == 1){Serial.println("S2: Fill ");}
    else{Serial.println("S2: Empty");}

    if(S3 == 1){Serial.println("S3: Fill ");}
    else{Serial.println("S3: Empty");}

    if(S4 == 1){Serial.println("S4: Fill ");}
    else{Serial.println("S4: Empty");}

    if(S1 == 0 || S2 == 0 || S3 == 0 || S4 == 0){
      for(pos = 0; pos<=90; pos+=1){
        myservo.write(pos);
        delay(15);
      }
      delay(3000);
      for(pos = 90; pos>=0; pos-=1){
        myservo.write(pos);
        delay(15);
      }
      Serial.println("Ok");
    }else{
      Serial.println("No Slots Available");
    }
    
    x=0;
  }
  digitalWrite(13, LOW);
}
