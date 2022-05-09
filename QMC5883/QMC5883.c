/*
 * QMC5883.c
 *
 *  Created on: 2020. 5. 22.
 *      Author: bbb
 */

#include "QMC5883.h"

I2C_HandleTypeDef hi2c1;

int previousDegree;

float Atan2(float y, float x)
{
#define MY_FLT_EPSILON 1.192092896e-07F
  const float scale = 0.017453292f;
  const float atan2_p1 = 57.283627f;
  const float atan2_p3 = -18.667446f;
  const float atan2_p5 = 8.9140005f;
  const float atan2_p7 = -2.5397246f;

  float ax = (x>0)?x:-x;
  float ay = (y>0)?y:-y;
  float a,c,c2;
  if(ax >= ay)
  {
    c = ay/(ax+MY_FLT_EPSILON);
    c2=c*c;
    a=(((atan2_p7*c2+atan2_p5)*c2+atan2_p3)*c2+atan2_p1)*c;
  }
  else
  {
    c = ax/(ay+MY_FLT_EPSILON);
    c2 = c*c;
    a=90.0-(((atan2_p7*c2+atan2_p5)*c2+atan2_p3)*c2+atan2_p1)*c;
  }
  if(x<0) a=180.0-a;
  if(y<0) a=360-a;

  return (float)(a*scale);
}

void QMC5883_WriteReg(uint8_t Reg,uint8_t val)
{
  uint8_t buff[2] = {Reg,val};
  HAL_I2C_Master_Transmit(&hi2c1,QMC5883_ADDR,buff,2,3000);
}

void QMC5883_init(){
  QMC5883_WriteReg(0x0B,0x01);
  //Define Set/Reset period
  QMC5883_setMode(Mode_Continuous,ODR_200Hz,RNG_8G,OSR_512);
  /*
  Define
  OSR = 512
  Full Scale Range = 8G(Gauss)
  ODR = 200HZ
  set continuous measurement mode
  */
}

void QMC5883_setMode(uint8_t mode,uint8_t odr,uint8_t rng,uint8_t osr)
{
  QMC5883_WriteReg(0x09,mode|odr|rng|osr);
}


void QMC5883_softReset()
{
  QMC5883_WriteReg(0x0A,0x80);
}

uint8_t QMC5883L_Read_Reg(uint8_t reg)
{
  uint8_t Buffer[1];
  HAL_I2C_Mem_Read(&hi2c1,QMC5883_ADDR,reg,1,Buffer,1,10);
  return Buffer[0];
}

void QMC5883L_Read_Data(int16_t *MagX,int16_t *MagY,int16_t *MagZ) // (-32768 / +32767)
{
  *MagX=((int16_t)QMC5883L_Read_Reg(0x00) | (((int16_t)QMC5883L_Read_Reg(0x01))<<8));
  *MagY=((int16_t)QMC5883L_Read_Reg(0x02) | (((int16_t)QMC5883L_Read_Reg(0x03))<<8));
  *MagZ=((int16_t)QMC5883L_Read_Reg(0x04) | (((int16_t)QMC5883L_Read_Reg(0x05))<<8));
}


float QMC5883_getHeading(uint8_t up,int16_t x,int16_t y,int16_t z) {
  if(up == 'x') return Atan2((float)z,(float)y);
  else if(up == 'y') return Atan2((float)x, (float)z);
  else if(up == 'z') return Atan2((float)y, (float)x);
  else return 0.0;
}

void QMC5883_read_angle(int *degrees)
{
  static int previousDegree;

  int16_t campaX,campaY,campaZ;
  //QMC5883_read(&campaX,&campaY,&campaZ);
  QMC5883L_Read_Data(&campaX,&campaY,&campaZ);

 float heading = QMC5883_getHeading('z',campaX,campaY,campaZ);
 float declinationAngle = (-8.0 + (20.0 / 60.0)) / (180.0 / 3.1415); //for Seoul
   heading += declinationAngle;

   if (heading < 0)
    {
      heading += 2 * 3.1415;
    }

    if (heading > 2 * 3.1415)
    {
      heading -= 2 * 3.1415;
    }

    // Convert to degrees
      float headingDegrees = heading * 180/3.1415;

      // Fix HMC5883L issue with angles
      float fixedHeadingDegrees;

//      if (headingDegrees >= 1 && headingDegrees < 240)
//      {
//        //fixedHeadingDegrees = map(headingDegrees, 0, 239, 0, 179);
//        headingDegrees *= 180.0/240.0;
//        //if(headingDegrees < 0) headingDegrees = 0;
//        if(headingDegrees > 180) headingDegrees = 180;
//      }
//      else if (headingDegrees >= 240)
//      {
//        //fixedHeadingDegrees = map(headingDegrees, 240, 360, 180, 360);
//        headingDegrees *= (float)(180-360)/(240-360);
//        if(headingDegrees >= 360) headingDegrees -= 180;
//      }
//////////////// if you need calibration , uncomment this parts //////////////////////////
      fixedHeadingDegrees = headingDegrees;

      // Smooth angles rotation for +/- 3deg
      //int smoothHeadingDegrees = round(fixedHeadingDegrees);
      int smoothHeadingDegrees = (int)fixedHeadingDegrees;

      if (smoothHeadingDegrees < (previousDegree + 3) && smoothHeadingDegrees > (previousDegree - 3))
      {
        smoothHeadingDegrees = previousDegree;
      }

      previousDegree = smoothHeadingDegrees;

      *degrees = (int) smoothHeadingDegrees;
      *degrees = 360 - *degrees + 90;
      if(*degrees >= 360) *degrees -= 360;
}
