#include "bq40z50.h"

uint8_t bq40z50_state_flag;		//状态标志位
/*
bq40z50_state_flag = 0  正常
bq40z50_state_flag = 1  通讯连接错误
bq40z50_state_flag = 2  通讯校验错误
*/

uint8_t bq40z50_word_buf[6];

void bq40z50_Init(void)		//初始化
{
	Wire.begin();   
}

uint8_t calculate_crc8(uint8_t InitialValue, uint8_t *message ,uint8_t len)		//CRC-8校验 X8+X2+X+1
{
	uint8_t i, crc = InitialValue;		/* 计算的初始crc值 */
	
	while(len--)
	{
		crc ^= (*message++);
		for(i = 0;i < 8;i++)
		{
			if(crc & 0x80)
			{
				crc = (crc << 1) ^ 0x07;		//多项式 POLY
			}
			else crc <<= 1;
		}
	}
	return crc;
}

int read_word(uint8_t memory_addr)    //读取一个字节
{   
    bq40z50_word_buf[0] = 0x16;
    bq40z50_word_buf[1] = memory_addr;
    bq40z50_word_buf[2] = 0x16 + 1;
    bq40z50_word_buf[3] = bq40z50_word_buf[4] = bq40z50_word_buf[5] = 0;

    Wire.beginTransmission(BQ40Z50_ADDR);
    Wire.write(memory_addr);
    if (Wire.endTransmission(false) == 0) { // false keeps the connection active
        Wire.requestFrom(BQ40Z50_ADDR, 3); // 请求3字节数据
        if (Wire.available() == 3) {
            bq40z50_word_buf[3] = Wire.read();
            bq40z50_word_buf[4] = Wire.read();
            bq40z50_word_buf[5] = Wire.read();

            if (calculate_crc8(0, bq40z50_word_buf, 5) == bq40z50_word_buf[5]) {
                bq40z50_state_flag = 0; // 通讯校验成功
            } else {
                bq40z50_state_flag = 2; // 通讯校验错误
            }
        } else {
            bq40z50_state_flag = 1; // 通讯连接错误
        }
    } else {
        bq40z50_state_flag = 1; // 通讯连接错误
    }

    return bq40z50_state_flag;
}

uint16_t bq40z50_read_temp(void)		//读取电池温度 单位0.1℃
{
	int flag = read_word(0x08);
	if(flag == 0)		//通讯连接正确
	{
		return (uint16_t)(bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3]) - 2731.5;
	}
	else return 0;	//通讯连接错误
}


uint16_t bq40z50_read_voltage(void)		//读取电池组电压	单位：mv
{
	read_word(0x09);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


int16_t bq40z50_read_current(void)		//读取电池电流	单位：ma
{
	read_word(0x0A);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


uint8_t bq40z50_read_capacity(void)		//读取电池电量	单位：%
{
	read_word(0x0D);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


uint16_t bq40z50_read_Remaining_Capacity(void)		//读取电池剩余容量	单位：mah
{
	read_word(0x0F);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


uint16_t bq40z50_read_FullChargeCapacity(void)		//读取电池充满电的容量 单位：mah
{
	read_word(0x10);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


//读取根据当前放电速率预测的剩余放电时间 单位：min
//return 65535 = 电池未放电
uint16_t bq40z50_read_RunTimeToEmpty(void)
{
	read_word(0x11);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


//读取根据当前平均放电速率预测的剩余放电时间 单位：min
//return 65535 = 电池未放电
uint16_t bq40z50_read_AverageTimeToEmpty(void)
{
	read_word(0x12);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


//读取根据当前充电速率预测平均到满的时间 单位：min
//return 65535 = 电池未充电
uint16_t bq40z50_read_AverageTimeToFull(void)
{
	read_word(0x13);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


uint16_t bq40z50_read_ChargingCurrent(void)		//获取电池支持的充电电流
{
	read_word(0x14);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


uint16_t bq40z50_read_ChargingVoltage(void)		//获取电池支持的充电电压
{
	read_word(0x15);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


uint16_t bq40z50_read_CycleCount(void)		//读取电池循环次数
{
	read_word(0x17);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


uint8_t bq40z50_read_RelativeStateOfCharge(void)		//读取电池健康值	单位：%
{
	read_word(0x4F);
	if(bq40z50_state_flag == 0)		//通讯连接正确
	{
		return bq40z50_word_buf[4]<<8 | bq40z50_word_buf[3];
	}
	else return 0;	//通讯连接错误
}


