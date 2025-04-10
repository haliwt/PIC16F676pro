#ifndef __KEY_H_
#define __KEY_H_
#include "../../main.h"



#define KEY1_RC2_GetValue()           PORTCbits.RC2

#define		_KEY_ALL_OFF				0X1F

#define   MODE_KEY                     1

typedef enum{
    stop,
    up,
	down,
	null_up_state,
	null_down_state,
	null_top_pos,
	null_bottom_pos,
	null_state
}up_down_state;


#if MODE_KEY

 typedef enum KEY_STATE{
  start  = 0,
  first  = 1,
  second = 2,
  cont   = 3,
  end    = 4,
  finish = 5,
 }state;

typedef  struct  _state_
{
 unsigned char          read;
 unsigned char         buffer;
 unsigned char        value;
 unsigned char        off_time;
 unsigned long        on_time;
  unsigned char       state;


}key_types;

key_types key;

#endif 


typedef struct _CMD{

   unsigned char gCmd;
   unsigned char gCmd_Power;
   unsigned char direction_flag;
   unsigned char clamphandPos;
   unsigned char gmotor_thefirst_run_flag;
   
}CMD_T;

CMD_T cmd_t;

enum runCmd{

  PowerOff = 0,
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
  

};

unsigned char gDoCharging;
unsigned char dochargingFlag;
void KEY_Init(void);
unsigned char  KEY_Scan(void);


void CheckMode(unsigned char keyvalue);
void RunCommand(void);





#endif 
