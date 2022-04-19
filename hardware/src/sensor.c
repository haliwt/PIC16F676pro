#include "../../hardware/inc/sensor.h"

static unsigned int  Charging_VoltageValue(void);
void SENSOR_Init(void)
{

	ANSELbits.ANS0 = 1; //analog I/O
	ANSELbits.ANS1 = 0 ; //digital I/O GPIO
	ANSELbits.ANS2 = 0;


    TRISAbits.TRISA0 = 1 ; //as input  GPIO --
	TRISAbits.TRISA1 = 1 ; //as input  GPIO
	TRISAbits.TRISA2 = 1 ; //as input  GPIO
	TRISAbits.TRISA5 = 1 ; //as input GPIO
}

uint8_t Top_Position(void)
{
	//TRISAbits.TRISA2 = 1 ; 
   if(TOP_POS_RA2_GetValue()==1){ //reach top position

   	  return 1;
   } 
   else{

   	return 0;
   }

}
uint8_t Bottom_Position(void)
{
	
	if(BOTTOM_POS_RA1_GetValue()==1){
       return 1;
	}
	else{

		return 0;
	}

}

uint8_t Clamp_Hand(void)
{
	
   if(CLAMPHAND_RA5_GetValue()==1){ //clamp hand
    	return 0;
    }
    else{
    	return 1;
    }

  

}

uint8_t Do_Charge(void)
{
	ANSELbits.ANS0 = 1; //analog I/O
	  TRISAbits.TRISA0 = 1 ; //as input  GPIO --
  if(Charging_VoltageValue()  > 150  ){ //charing 0.9V =184
      return 0;
  }
  else{ //dont't charging state

  	return 1;
  }
}

/**************************************************************************
 *
 *    Function Name: void Voltage_Test(void)
 *    Function: ADC 
 * 
 * 
**************************************************************************/
static unsigned int Charging_VoltageValue(void)
{
         unsigned int  cTemp;

         //DelayXms(10);
		ADCON0=0B10000001;      //选择ＡＮ0 通道
                                //转换结果右对齐
                                //选择ＶＤＤ作为参考电压
         __delay_ms(2);
         ADCON0bits.GO_DONE = 1;           //启动ＡＤ转换
         while(ADCON0bits.GO_DONE == 1);   //等待转换完成
         cTemp  = ADRESH;       //读取ＡＤ转换结果高位
         cTemp &= 0x03;
         cTemp <<= 8;           //
         cTemp += ADRESL;       //读取ＡＤ转换低８位并加上高位
         return(cTemp);         //返回ＡＤ转换结果    
 }
