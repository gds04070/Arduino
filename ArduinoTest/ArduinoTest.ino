#include <SoftwareSerial.h>
//보내기 버튼을 눌렀을떄 LED깜빡
int Tx = 2;
int Rx = 3;
byte buffer[1024];
int bufferPosition;
boolean temp = 0;

SoftwareSerial btSerial(Tx, Rx);

void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  bufferPosition = 0;

  Serial.begin(9600);
  btSerial.begin(9600);
  Serial.println("Start");

}

void loop() {
  // put your main code here, to run repeatedly:
  if(btSerial.available()){
      //수신받은 데이터 저장
      byte data = btSerial.read();
      //수신된 데이터 시리얼 모니터로 출력
      Serial.write(data);
      //수신받은 데이터를 버퍼에 저장
      buffer[bufferPosition++] = data;
    

    if(data = 'F'){
      //LED가 꺼있을 경우 LED를 킨다
      if(temp == 0){
        digitalWrite(6, HIGH);
        temp = 1;
        }else{ //LED가 켜져 있을 경우 LED를 끈다
          digitalWrite(6,LOW);
          temp = 0;
          }
      } 
      //문자열 종료 표시
      if(data == '\n'){
         buffer[bufferPosition] = '\0';
         bufferPosition = 0;
        }
  }

  if(Serial.available()){
    btSerial.write(Serial.read());
    }
  
}
