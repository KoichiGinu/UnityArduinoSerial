// 設定定義
#define AIA    5    // モータAのA側ピン
#define AIB    6    // モータAのB側ピン
#define BIA   10    // モータBのA側ピン
#define BIB   11    // モータBのB側ピン

float MotorSpeed = 0;
int MotorMode = 0;

void ReceiveFromUnity();
void Motor();
void SendToUnity();

void setup() {
  // ポート設定
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
}

void loop() {
  //Unityから文字を受け取り，モータ信号処理を行い，Unityに文字を送信する流れ
  ReceiveFromUnity();
  Motor();
  SendToUnity();
}



void ReceiveFromUnity()
{
  if ( Serial.available() ) {
    char mode = Serial.read();

    //Unityから送られてきた文字によって動作を変える
    switch (mode) {
      case '0' :
        MotorSpeed = 255;
        break;
      case '1' :
        MotorSpeed = 0;
        break;

      case 'A' :
        MotorMode = 0;
        break;
      case 'B' :
        MotorMode = 1;
        break;
      case 'C' :
        MotorMode = 2;
        break;
      case 'D' :
        MotorMode = 3;
        break;
    }

  }
}

void Motor() {
  if (MotorMode == 0) {
    // 両側正回転
    analogWrite(AIA, MotorSpeed);
    analogWrite(AIB, 0);
    analogWrite(BIA, MotorSpeed);
    analogWrite(BIB, 0);
  }
  else if (MotorMode == 1) {
    // 両側逆回転
    analogWrite(AIA, 0);
    analogWrite(AIB, MotorSpeed);
    analogWrite(BIA, 0);
    analogWrite(BIB, MotorSpeed);
  }
  else if (MotorMode == 2) {
    // 方側正回転
    analogWrite(AIA, MotorSpeed);
    analogWrite(AIB, 0);
    analogWrite(BIA, 0);
    analogWrite(BIB, 0);
  }
  else {
    // 方側スロースピードの正回転
    analogWrite(AIA, 0);
    analogWrite(AIB, 0);
    analogWrite(BIA, MotorSpeed);
    analogWrite(BIB, 0);
  }
}

void SendToUnity() {
  //シリアル送信
  Serial.print(MotorSpeed);
  Serial.print(",");
  Serial.print(MotorMode);
  Serial.println("");
}
