#include <SoftwareSerial.h>
//블루투스
int Tx = 2;
int Rx = 3;

//LED
int LED = 6;

//포토인터럽터핀
int pIPin = 7;

//시간 계산
unsigned long duration;
unsigned long before = 0;
unsigned long period = 0;
int n = 0; //횟수
unsigned long sum = 0; //평균을 위한 합
unsigned long average = 0; //10회당 평균

//버퍼
byte buffer[1024];
int bufferPosition;
boolean temp = 0;

SoftwareSerial btSerial(Tx, Rx);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(pIPin, INPUT);
  bufferPosition = 0;

  Serial.begin(9600);

  //블루투스 시작
  btSerial.begin(9600);

  //포토인터럽터
  do{
    duration = pulseIn(pIPin, LOW); //첫번째 포토인터럽터 통과 감지
    if(duration>0){
      before = millis(); //그 시간을 이전 시간으로 기억
      }
    }while(duration == 0);//반복 조건
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(btSerial.available()){
      byte data = btSerial.read();
      Serial.write(data);
      buffer[bufferPosition++] = data;

    if(data = 'F'){
      if(temp == 0){
        digitalWrite(6, HIGH);
        temp = 1;
        }else{ 
          digitalWrite(6,LOW);
          temp = 0;
          }
      } 
      if(data == '\n'){
         buffer[bufferPosition] = '\0';
         bufferPosition = 0;
        }
  }

   calculateDuration();
   
  
}

//주기계산
void calculateDuration(){
  duration = pulseIn(pIPin, LOW);
  if(duration>0){
    period = (millis() - before) * 2; //주기는 (현재 시간-이전 시간)*2
    n = n+1; //n : 측정 횟수(카운터)
    sum = sum + period;
    Serial.print(n);
    Serial.print(" : ");
    Serial.println(period);
    
    if(n >= 10){
      average = sum / 10;
      Serial.println(average);
      btSerial.println(average); //안드로이드로 보냄
      n = 0;
      sum = 0;
      }
      
    before = millis();
    }
    delay(5);
  }
