#include "../../hardware/inc/sensor.h"


void SENSOR_Init(void)
{

	ANSELbits.ANS0 = 0;  //digital I/O GPIO
	ANSELbits.ANS1 = 0 ;
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

uint8_t Do_Charge(void)
{

  if(DOCHARGE_RA0_GetValue()==1){ //don't charging 
      return 1;
  }
  else{ //charging state

  	return 0;
  }



}
uint8_t Clamp_Hand(void)
{
	
	if(CLAMPHAND_RA5_GetValue()==1){ //clamp hand
    	return 1;
    }
    else{
    	return 0;
    }

    return 0;

}