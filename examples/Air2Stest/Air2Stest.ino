#include <Arduino.h>
#include <Wire.h>
#include "bq40z50.h"

// #define BQ40Z50_ADDR 0x0B

// Main Loop

void setup() {
  Serial.begin(115200);         // 启动串行通信
  bq40z50_Init();              // 初始化I2C总线
}

void loop() {
//   uint8_t dataReceived;         // 用于存储接收到的数据
//   Wire.beginTransmission(SLAVE_ADDR);  // 开始与从设备的I2C通信
//   Wire.write(0x01);             // 发送数据请求
//   Wire.endTransmission();       // 结束传输

//   Wire.requestFrom(SLAVE_ADDR, 1);  // 请求从设备发送1字节数据
//   if (Wire.available()) {       // 检查是否收到数据
//     dataReceived = Wire.read(); // 读取数据
//     Serial.print("Received data: ");
//     Serial.println(dataReceived);  // 在串行监视器上打印接收到的数据
//   }


  Serial.println("电池温度: " + String(bq40z50_read_temp() * 0.1) + " °C");
  Serial.println("电池组电压: " + String(bq40z50_read_voltage()) + " mV");
  Serial.println("电池电流: " + String(bq40z50_read_current()) + " mA");
  Serial.println("电池电量: " + String(bq40z50_read_capacity()) + " %");
  Serial.println("剩余容量: " + String(bq40z50_read_Remaining_Capacity()) + " mAh");
  Serial.println("剩余放电时间: " + String(bq40z50_read_RunTimeToEmpty()) + " min");
  Serial.println("平均放电时间: " + String(bq40z50_read_AverageTimeToEmpty()) + " min");
  Serial.println("剩余充电时间: " + String(bq40z50_read_AverageTimeToFull()) + " min");
  Serial.println("支持的充电电流: " + String(bq40z50_read_ChargingCurrent()) + " mA");
  Serial.println("支持的充电电压: " + String(bq40z50_read_ChargingVoltage()) + " mV");
  Serial.println("电池循环次数: " + String(bq40z50_read_CycleCount()));
  Serial.println("电池健康值: " + String(bq40z50_read_RelativeStateOfCharge()) + " %");
  delay(5000);  // 等待1秒
}