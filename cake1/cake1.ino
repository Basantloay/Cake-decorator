//https://forum.arduino.cc/index.php?topic=407596.0

////////////Making the cake\\\\\\\\\\\\\\\

// EGG VALVE: servo motor ===> pin A5
// VANILLIA VALVE: servo motor ===> pin A4
// SUGAR VALVE: servo motor ===> pin A3
// FLOUR VALVE: servo motor ===> pin A2
// MIXER: stepper motor==> pin A1,A0
// HEATER: led===>pin 0
//PRODUCTIN LINE:stepper motor==> pin 1,2
#define l1 1
#define l2 2
#define led 0
int positionv=1;
char pins[6] = {A5,A4,A3,A2,A1,A0};
bool flag=true;
unsigned long  prev = 0, current=0 ;
int angle;
int pwm;

void servoPulse (char servo, int angle)
{
  pwm = angle * 9 + 500;
  digitalWrite(servo, HIGH);
  delayMicroseconds(pwm); //First delay
  digitalWrite(servo, LOW);
  delay(50); //Second delay
}
void moveMixer(int rotations,int d)
{
  //one revolution === 8
  for (int i = 0; i < rotations*8; i++) {
    digitalWrite(pins[4], HIGH);
    digitalWrite(pins[5], LOW);
    delay(d);
    digitalWrite(pins[4], LOW);
    digitalWrite(pins[5], HIGH);
    delay(d);
  }
}

void moveMixerV(int rotations,int d)
{
   for (angle = 0; angle <= 180; angle += 60)  {
   servoPulse(pins[1], angle);  }
   prev=millis();
   int flag1=true;
  //one revolution === 8
  for (int i = 0; i < rotations*8; i++) {
    current= millis();
    if (flag1&&(unsigned long)(current - prev) >= 100) {
      for (angle = 180; angle >= 0; angle -= 60)  {
       servoPulse(pins[1], angle);  }
       flag1=false;
    }
    digitalWrite(pins[4], HIGH);
    digitalWrite(pins[5], LOW);
    delay(d);
    digitalWrite(pins[4], LOW);
    digitalWrite(pins[5], HIGH);
    delay(d);
    
  }
}

void makeCake()
{
 //for(int i=0;i<4;i++)
 //digitalWrite(pins[i],0);
// delay(15);
 //for(int i=0;i<4;i++)
// digitalWrite(pins[i],1);

 //open egg valve
  for (angle = 0; angle <= 180; angle += 60)  {
   servoPulse(pins[0], angle);  }
   delay(500);
 for (angle = 180; angle >= 0; angle -= 60)  {
   servoPulse(pins[0], angle);  }
moveMixer(5,6);
moveMixerV(4,6);
//open sugar valve
for (angle = 0; angle <= 180; angle += 60)  {
   servoPulse(pins[2], angle);  }
   delay(200);
 for (angle = 180; angle >= 0; angle -= 60)  {
   servoPulse(pins[2], angle);  }
 moveMixer(10,6); 
 for(int i=0;i<3;i++)
 {
  //open flour valve
  for (angle = 0; angle <= 180; angle += 60)  {
   servoPulse(pins[3], angle);  }
   delay(100);
 for (angle = 180; angle >= 0; angle -= 60)  {
   servoPulse(pins[3], angle);  }
 moveMixer(4,12); 
 }
  }

///////////////Baking the cake\\\\\\\\\\\\\\\\\\

void moveLine(int rotations,int d)
{
  //one revolution === 8
  for (int i = 0; i < rotations*8; i++) {
    digitalWrite(l1, HIGH);
    digitalWrite(l2, LOW);
    delay(d);
    digitalWrite(l1, LOW);
    digitalWrite(l2, HIGH);
    delay(d);
  }
}

 void bakeCake()
 {
  moveLine(1,80);
  digitalWrite(led,1);
  delay(1000);
  digitalWrite(led,0);
   moveLine(1,80);
  delay(1000); 
 }

 ///////////////////////Decorate cake\\\\\\\\\\\\\\
 
 /* currentMillis = millis();
    if ((unsigned long)(currentMillis - previousMillis) >= interval) {
      ledState = !ledState; // "toggles" the state
      digitalWrite(ledPin, ledState); // sets the LED based on ledState
      previousMillis = millis();
    }
  */
/* for(int i=0;i<180;i++)
 {
  digitalWrite(pins[0],i);
  delay(15);
 }
  delay(500);
 for(int i=180;i>0;i--)
 {
  digitalWrite(pins[0],i);
  delay(15);
 }*/
// movePulse(pins[0]);
  //delay(500);
  
void setup() {
 for(int i=0;i<6;i++)
 pinMode(pins[i],OUTPUT);
for(int i=0;i<3;i++)
 pinMode(i,OUTPUT);

}

void loop() {
  if(flag)
    //makeCake();
   bakeCake(); 
   flag=false;
  delay(3000);

} 
