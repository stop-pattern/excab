#include <Arduino.h>

constexpr unsigned long baudrate = 9600;    // ボーレート
constexpr unsigned int framelen = 22;         // フレーム長

// シリアル受信フォーマット
// D,SCCC,SSS,MMM,BBB,AAAN
// 0123456789012345678901
// ----------
// D: ドア状態
// SCCC: 符号付き電流3桁
// SSS: 速度3桁
// MMM: MR圧3桁
// BBB: BP圧3桁
// AAA: SAP圧3桁
// N: フッタ

bool door = 0;
int current = 0;
int spd = 0;
int mr = 0;
int bp = 0;
int sap = 0;

void setup() {
    Serial.begin(baudrate);
    while (!Serial);
}

void loop() {
    // シリアル読み込み
    if (Serial.available()) {
        String str = Serial.readStringUntil('N');
        if (str.length() >= framelen) {
            str = str.substring(str.length() - framelen);
            
            door = str.substring(0, 1).toInt();
            current = str.substring(3, 3).toInt();
            if (str.charAt(2) == '-') current *= -1;
            spd = str.substring(7, 3).toInt();
            mr = str.substring(11, 3).toInt();
            bp = str.substring(15, 3).toInt();
            sap = str.substring(19, 3).toInt();
        }
    }

    // loop待機
    delay(1);
}
