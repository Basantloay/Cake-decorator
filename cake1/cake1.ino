/**************************The reference materials *****************************
 
i used function idea from these sites and added some little modifications
functions servoPulse() and servoPulseV() taken from
//https://forum.arduino.cc/index.php?topic=407596.0
funcrion checkKeypadPressed taken from
//http://anilarduino.blogspot.com/2015/05/interfacing-keypad-with-arduino.html

*********************************************************************************/

// EGG VALVE: servo motor ===> pin A5
// VANILLIA VALVE: servo motor ===> pin A4
// SUGAR VALVE: servo motor ===> pin A3
// FLOUR VALVE: servo motor ===> pin A2
// MIXER: stepper motor==> pin A1,A0
// HEATER: led===>pin 0
//PRODUCTIN LINE:stepper motor==> pin 1,2
//yellow led ==>pin 3
//Red led ==> pin 4
//key pad ==> 5,6 Rows
//        ==> 7,8 Columns 
//STAND : stepper motor==> pin 9,10
//ARM : servo motor ==> pin 11
////////////Making the cake\\\\\\\\\\\\\\\

#define l1 1
#define l2 2
#define s1 9
#define s2 10
#define led 0
#define arm 11
#define yellow 3
#define red 4
int positionv=1;
char pins[6] = {A5,A4,A3,A2,A1,A0};
bool flag=true;
unsigned long  prev = 0, current=0 ;
int angle;
int pwm;
char key;
const int row[2] = {5,6}; 
const int col[2] = {8,7}; 
const char keypad[2][2] = {{'1','2'},{'3','4'}};               
  
void servoPulse (char servo, int angle)
{
  pwm = angle * 9 + 500;
  digitalWrite(servo, HIGH);
  delayMicroseconds(pwm); 
  digitalWrite(servo, LOW);
  delay(50); 
}
void servoPulseV (char servo, int angle)
{
  pwm = angle * 9 + 500;
  digitalWrite(servo, HIGH);
  delayMicroseconds(pwm); 
  digitalWrite(servo, LOW);
  delay(5); 
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
   servoPulseV(pins[1], angle);  }
   prev=millis();
   int flag1=true;
  //one revolution === 8
  for (int i = 0; i < rotations*8; i++) {
    current= millis();
    if (flag1&&(unsigned long)(current - prev) >= 100) {
     // for (angle = 180; angle >= 0; angle -= 60)  {
      // servoPulseV(pins[1], angle);  }
      servoPulseV(pins[1], 0);
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
   delay(50);
moveMixer(5,6);
moveMixerV(4,7);
delay(50);
//open sugar valve
for (angle = 0; angle <= 180; angle += 60)  {
   servoPulse(pins[2], angle);  }
   delay(200);
 for (angle = 180; angle >= 0; angle -= 60)  {
   servoPulse(pins[2], angle);  }
   delay(50);
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
 
 bool checkKeypadPressed(char & key1)
{
  for(int i = 0;i < 2;i++)
  {
    digitalWrite(row[0],HIGH);
    digitalWrite(row[1],HIGH);
    digitalWrite(row[i],LOW);
    
    for(int j = 0;j<2;j++)
    {
      int col_state = digitalRead(col[j]);
      if(col_state == LOW)
      {
        key1=keypad[i][j];
        return true;
      }
    }
  }
  delay(30);
 return false; 
}
 void decor1(){
  //0 disk 
  
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  for (angle = 36; angle <= 72; angle += 12)  {
  servoPulse(arm, angle);  }
  //1 disk 
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  for (angle = 72; angle <= 108; angle += 12)  {
   servoPulse(arm, angle);  }
  //2 disk
  for (int i = 0; i < 8; i++) {
    digitalWrite(yellow,1);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  digitalWrite(yellow,0);
   for (angle = 108; angle <= 144; angle += 12)  {
   servoPulse(arm, angle);  }
  //3 disk
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  for (angle = 144; angle <= 180; angle += 12)  {
   servoPulse(arm, angle);  }
   // 4 disk
for (int i = 0; i < 8; i++) {
    digitalWrite(red,1);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
   digitalWrite(red,0);
   
 for (angle = 180; angle >= 0; angle -= 60)  {
   servoPulse(arm, angle);  }
}

void decor2(){
  //0 disk 
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  for (angle = 36; angle <= 72; angle += 12)  {
   servoPulse(arm, angle);  }
  //1 disk 
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  for (angle = 72; angle <= 108; angle += 12)  {
   servoPulse(arm, angle);  }
  //2 disk
  for (int i = 0; i < 8; i++) {
    if(i%2==0)
      digitalWrite(yellow,1);
     else
      digitalWrite(yellow,0);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  digitalWrite(yellow,0);
   for (angle = 108; angle <= 144; angle += 12)  {
   servoPulse(arm, angle);  }
  //3 disk
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  for (angle = 144; angle <= 180; angle += 12)  {
   servoPulse(arm, angle);  }
   // 4 disk
for (int i = 0; i < 8; i++) {
    if(i%2==0)
      digitalWrite(red,1);
    else
     digitalWrite(red,0); 
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
   digitalWrite(red,0);
   
 for (angle = 180; angle >= 0; angle -= 60)  {
   servoPulse(arm, angle);  }
}

void decor3(){
  //0 disk 
  for (int i = 0; i < 8; i++) {
    digitalWrite(yellow,1);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  digitalWrite(yellow,0);
  for (angle = 36; angle <= 72; angle += 12)  {
  servoPulse(arm, angle);  }
  //1 disk 
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  for (angle = 72; angle <= 108; angle += 12)  {
   servoPulse(arm, angle);  }
  //2 disk
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
   for (angle = 108; angle <= 144; angle += 12)  {
   servoPulse(arm, angle);  }
  //3 disk
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  for (angle = 144; angle <= 180; angle += 12)  {
   servoPulse(arm, angle);  }
   // 4 disk
for (int i = 0; i < 8; i++) {
    digitalWrite(red,1);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(red,0);
    delay(100);
    digitalWrite(red,1);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
     digitalWrite(red,0);
     delay(100);
  }
   digitalWrite(red,0);
   
 for (angle = 180; angle >= 0; angle -= 60)  {
   servoPulse(arm, angle);  }
}

void decor4(){
  //0 disk 
  for (int i = 0; i < 8; i++) {
    digitalWrite(red,1);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  digitalWrite(red,0);
  for (angle = 36; angle <= 72; angle += 12)  {
  servoPulse(arm, angle);  }
  //1 disk 
  for (int i = 0; i < 8; i++) {
     digitalWrite(red,1);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
   digitalWrite(red,0);
  for (angle = 72; angle <= 108; angle += 12)  {
   servoPulse(arm, angle);  }
  //2 disk
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
   for (angle = 108; angle <= 144; angle += 12)  {
   servoPulse(arm, angle);  }
  //3 disk
  for (int i = 0; i < 8; i++) {
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
  }
  for (angle = 144; angle <= 180; angle += 12)  {
   servoPulse(arm, angle);  }
   // 4 disk
for (int i = 0; i < 8; i++) {
    digitalWrite(red,1);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    delay(100);
    digitalWrite(red,0);
    delay(100);
    digitalWrite(yellow,1);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    delay(100);
     digitalWrite(yellow,0);
     delay(100);
  }
   digitalWrite(red,0);
    digitalWrite(yellow,0);
 for (angle = 180; angle >= 0; angle -= 60)  {
   servoPulse(arm, angle);  }
}
void decorateCake(){
  switch(key){
      case '1':
        decor1();
        break;
        case '2':
        decor2();
        break;
        case '3':
        decor3();
        break;
        case '4':
        decor4();
        break;
      default:
           break;
    }
key=0;
}

void cakeIntegration()
{
  bool answr1=checkKeypadPressed(key);
  if(answr1)
  {
    makeCake();
    bakeCake();
    decorateCake();
  }

    
}
void setup() {
  /*for(int i=0;i<4;i++)
 digitalWrite(pins[i],0);
 delay(15);*/
 //for(int i=0;i<4;i++)
// digitalWrite(pins[i],1);
  pinMode(LED_BUILTIN,OUTPUT);
 for(int i=0;i<6;i++)
 {
 pinMode(pins[i],OUTPUT);
 if(i!=4 && i!=5)
 {
 digitalWrite(pins[i],1);
 digitalWrite(pins[i],0);
 }
 }
for(int i=0;i<5;i++)
 pinMode(i,OUTPUT);
 for(int i = 0; i<2; i++)
  {
    pinMode(col[i],INPUT_PULLUP);
    pinMode(row[i],OUTPUT); 
    digitalWrite(row[i],HIGH);
  }
for(int i=9;i<12;i++)
 pinMode(i,OUTPUT);
digitalWrite(arm,1);
digitalWrite(arm,0); 
  
}

void loop() {
  cakeIntegration();
} 
