#ifndef __KEY_H_
#define __KEY_H_
#include "../../main.h"



#define KEY1_RC2_GetValue()           PORTCbits.RC2



#define		_KEY_ALL_OFF				0X1F

//normal times be pressed key
#define		_KEY_TRG_1_WK_UP     			0x01  //WK_UP
#define		_KEY_TRG_2_KEY_1     			0x02  //??????--???
#define		_KEY_TRG_3_TIMER     			0x04   //????
#define		_KEY_TRG_4_FILTER     			0x08
// combination of buttons 
#define		_KEY_TRG_5_WINDTI   			0x11   //?????
#define		_KEY_TRG_6_WINDTI   			0x12   //?????
#define		_KEY_TRG_7_WINDTI   			0x14   //?????
#define		_KEY_TRG_8_WINDTI   			0x18   //?????

//long times be pressed
#define		_KEY_CONT_1_WK_UP     	     0x81    //??????--???
#define		_KEY_CONT_2_KEY_1    		 0x82    //??????--???
#define		_KEY_CONT_3_TIMER     	     0x84    //?????? ?????
#define		_KEY_CONT_4_FILTER     	     0x88    //??? --?????
#define		_KEY_CONT_5_WINDTI     		 0x89




#define		_KEY_CONT_1     	    0x81    //?????
#define		_KEY_CONT_2     		0x82
#define		_KEY_CONT_3     		0x84
#define		_KEY_CONT_4     	    0x88

#define		_KEY_COM_1    		    0x91
#define		_KEY_COM_2    		    0x92
#define		_KEY_COM_3    		    0x94
#define		_KEY_COM_4    		    0x98

typedef  struct  _state_
{
 unsigned char          read;
 unsigned char         buffer;
 unsigned char        value;
 unsigned char        off_time;
 unsigned long        on_time;

 enum{
  start  = 0,
  first  = 1,
  second = 2,
  cont   = 3,
  end    = 4,
  finish = 5,
 }state;
}key_types;

key_types key;

typedef struct _CMD{
   unsigned char gWait;
   unsigned char gCmd;
   unsigned char gCmd_Power;
   unsigned char gCmd_KeyState;
   unsigned char gCmd_KeyNum;
   unsigned char topPos;
   unsigned char bottomPos;
   unsigned char handPos;
   unsigned char gDoKey ;
   unsigned char gmotor_upStep;
   unsigned char gkeyValue;
   unsigned char gTimer_100ms;
   
}CMD_T;

CMD_T cmd_t;

enum runCmd{
    
  PowerOff = 0x0c,
  PowerOn = 0x01,
  MotorUp = 0x02,
  MotorDown = 0x03,
  Charging  = 0x04,
  MotorLocked = 0x05,
  MotorStop  = 0x06,
  DoCharge   =0x07,
  Top_Pos    =0x08,
  Bottom_Pos = 0x09,
  ClampHand  = 0x0A,
  TempStop  = 0x0B,
  Nothing = 0xff
          

};

unsigned char gDoCharging;
unsigned char dochargingFlag;
void KEY_Init(void);
unsigned char  KEY_Scan(void);


void CheckMode(unsigned char keyvalue);
void RunCommand(void);

void MotorRun_Up_TempStop_Detection(void);

void PowerOff_Fun(void);

#endif 
