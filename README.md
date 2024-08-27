# Arduino-BQ40Z50
BQ40Z50 lib for Arduino (Tested on esp32)

Read data from battery management chip bq40z50 using esp32, test on DJI Air2S battery.
## Usage
The bq40z50 is connected using I2C. The DJI Air2S battery pins definations from right to left are  - - - - SMBD(SDA) SMDC(SCL) + + + +. Pin 5 and 6 should be connected to esp32 default SDA(GPIO21) and SCL(GPIO22).  

![Pins Connection](/extras/connection.JPG "Pins Connection")

And there is the acquired data print with serial:
![](/extras/screenshot.png "Result")


## Reference
Based on https://www.bilibili.com/video/BV1VP4y1B71w
