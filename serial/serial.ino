#include <string.h> 
#include <Servo.h>

 Servo cube;
void setup() {
  Serial.begin( 9600 );     // シリアル通信を初期化する。通信速度は9600bps
  cube.attach(6);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  //  Serial.println( "Hello Arduino!" );   // 最初に1回だけメッセージを表示する
}

void loop(){
 String input;
 if (Serial.available() > 0){
 // シリアルポートより1文字読み込む
 input = Serial.readStringUntil('\n');
 int angle = input.toInt();
 // 受け取った文字を送信
  Serial.print(angle);
  Serial.write("\n");
  cube.detach();
  if(angle>=0&&angle<180){
    cube.attach(6);
    cube.write(angle);
    //delay(500);
    //digitalWrite(13, HIGH);
    delay(50);
    //digitalWrite(13, LOW);
    cube.detach();
    
    }
  else if(angle == 200){
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
      }
 }
}
