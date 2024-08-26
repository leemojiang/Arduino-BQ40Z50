// MyHeader.h
#ifndef BQ40Z50_H
#define BQ40Z50_H
#include <Arduino.h>
#include <Wire.h>

#define BQ40Z50_ADDR 0x0B //电池地址	


extern uint8_t bq40z50_state_flag;		//状态标志位

void bq40z50_Init(void);		//初始化

uint16_t bq40z50_read_temp(void);		//读取电池温度 单位0.1℃

uint16_t bq40z50_read_voltage(void);		//读取电池组电压	单位：mv

int16_t bq40z50_read_current(void);		//读取电池电流	单位：ma

uint8_t bq40z50_read_capacity(void);		//读取电池电量	单位：%

uint16_t bq40z50_read_Remaining_Capacity(void);		//读取电池剩余容量	单位：mah
	
uint16_t bq40z50_read_RunTimeToEmpty(void);		//读取剩余放电时间 单位：min

uint16_t bq40z50_read_AverageTimeToEmpty(void);		//平均放电时间 单位：min

uint16_t bq40z50_read_AverageTimeToFull(void);		//读取剩余充电时间 单位：min

uint16_t bq40z50_read_ChargingCurrent(void);		//获取电池支持的充电电流

uint16_t bq40z50_read_ChargingVoltage(void);		//获取电池支持的充电电压

uint16_t bq40z50_read_CycleCount(void);		//读取电池循环次数

uint8_t bq40z50_read_RelativeStateOfCharge(void);		//读取电池健康值	单位：%

#endif