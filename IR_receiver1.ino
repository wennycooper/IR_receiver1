#include <Timer.h>
#include <IRremote.h>

int RECV_PIN = 2; // 使用數位腳位2接收紅外線訊號
IRrecv irrecv(RECV_PIN); // 初始化紅外線訊號輸入
decode_results results; // 儲存訊號的結構
Timer tcb;

unsigned int count0 = 0;
unsigned int count1 = 0;

void writeToSerial(){
  Serial.print(count1);
  Serial.print(" ; "); 
  Serial.println(count0); 
  count0 = 0;
  count1 = 0;
}

void setup() {
  Serial.begin(115200);
  irrecv.blink13(true); // 設為true的話，當收到訊號時，腳位13的LED便會閃爍
  irrecv.enableIRIn(); // 啟動接收
  tcb.every(1000, writeToSerial); // 每經過1000毫秒，就會呼叫writeToSerial
}

void loop() {
  tcb.update();
  if (irrecv.decode(&results)) { // 接收紅外線訊號並解碼
//    Serial.print("results value is "); // 輸出解碼後的資料
//    Serial.print(results.value, HEX);
//    Serial.print(", bits is ");
//    Serial.print(results.bits);
//    Serial.print(", decode_type is ");
//    Serial.println(results.decode_type);
    if (results.value == 0x77E14050) 
      count0++;
    if (results.value == 0x405077E1) 
      count1++;

    irrecv.resume(); // 準備接收下一個訊號
  }





  
}
