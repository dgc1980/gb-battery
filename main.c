/*******************************************************************
* BATTERY TEST                                                     *
*******************************************************************/

#include <gb/gb.h>
#include <stdio.h>
#include <gb/drawing.h>


// hUGETracker
#include "hUGEDriver.h"
extern const hUGESong_t jester;


// 
UBYTE rtc_s;
UBYTE rtc_m;
UBYTE rtc_h;
UBYTE rtc_dh;
UBYTE rtc_dl;

// memory locations to store RTC data for results
char *saved = (char *)0xa000;
int *sd = (int *)0xa001;
int *sh = (int *)0xa002;
int *sm = (int *)0xa003;
int *ss = (int *)0xa004;


void get_day(void)
{
  UBYTE data;

  data = *(UBYTE *)0x6000;
  if( data & 0x1 ) {
    *(UBYTE *)0x6000 = 0;
  }
  *(UBYTE *)0x6000 = 1;
  data = *(UBYTE *)0x6000;
#if 0
  while( data != 0x3 ) {
    data = *(UBYTE *)0x6000;
  }
#else
  delay( 4UL );
#endif

  SWITCH_RAM_MBC1(0x0B);
  rtc_dl = *(UBYTE *)0xA000;
  SWITCH_RAM_MBC1(0x0C);
  rtc_dh = *(UBYTE *)0xA000;
  SWITCH_RAM_MBC1(0);
}

void get_time(void)
{
  SWITCH_RAM_MBC1(0x08);
  rtc_s = *(UBYTE *)0xA000;
  SWITCH_RAM_MBC1(0x09);
  rtc_m = *(UBYTE *)0xA000;
  SWITCH_RAM_MBC1(0x0A);
  rtc_h = *(UBYTE *)0xA000;
  SWITCH_RAM_MBC1(0);
}


/*--------------------------------------------------------------------------*
 | main program                                                             |
 *--------------------------------------------------------------------------*/
void main(void)
{
  DISPLAY_ON;
  enable_interrupts();

  ENABLE_RAM_MBC1;

  //Enable Sound Registers
  NR52_REG = 0x80;
  NR50_REG = 0x77;
  NR51_REG = 0xFF;

  //load music track
  hUGE_init(&jester); 


  gotogxy(3,0);
  gprintf("GB Battery Test");
  gotogxy(5,17);
  gprintf("by dgc1980");
  gotogxy(4,16);
  gprintf("version 0.3");



  // is there already save data from previous test?
  if (saved[0] == 's') {

    gotogxy(3,3);
    gprintf("Previous Result");

    // print saved RTC values   
    gotogxy(4,5);
    gprintf("Days   : %d  ", sd[0]);
    gotogxy(4,6);
    gprintf("Hours  : %d  ", sh[0]);
    gotogxy(4,7);
    gprintf("Minutes: %d  ", sm[0]);
    gotogxy(4,8);
    gprintf("Seconds: %d  ", ss[0]);
    gotogxy(0,10);
    gprintf("Press A to Start New Test");

    // loop until A is pressed
    while(1) {
      if( joypad() & J_A ) {
        break;
      }
    }
  }

  // load RTC data
  get_day();
  get_time();

  //save current RTC values
  int s_rtc_dl = rtc_dl;
  int s_rtc_h = rtc_h;
  int s_rtc_m = rtc_m;
  int s_rtc_s = rtc_s;

  int n_rtc_dl;
  int n_rtc_h;
  int n_rtc_m;
  int n_rtc_s;
  int p_rtc_s = 0;

  gotogxy(3,0);
  gprintf("GB Battery Test");

  gotogxy(3,3);
  gprintf("               ");
  gotogxy(0,10);
  gprintf("                         ");

  saved[0] = 'n'; 

  while(1) {
    // load RTC data
    get_day();
    get_time();

    
    // calculate current RTC values against the above saved offsets
    n_rtc_s = rtc_s - s_rtc_s;
    n_rtc_m = rtc_m - s_rtc_m;
    n_rtc_h = rtc_h - s_rtc_h;
    n_rtc_dl = rtc_dl - s_rtc_dl;

    // fix the offsets when they go negative due to changed values
    if ( n_rtc_s < 0 ) {
        n_rtc_s += 60;
        n_rtc_m -= 1;
    }
    if ( n_rtc_m < 0 ) {
        n_rtc_m += 60;
        n_rtc_h -= 1;
    }
    if ( n_rtc_h < 0 ) {
        n_rtc_h += 24;
        n_rtc_dl -= 1;
    }
    if ( n_rtc_dl < 0 ) {
        n_rtc_dl += 128;
    }


    // check if previous second does not match the current second
    if ( n_rtc_s != p_rtc_s ) {
      // save values to SRAM/FRAM every 10 seconds
      if ( n_rtc_s == 0 || n_rtc_s == 10 || n_rtc_s == 20 || n_rtc_s == 30 || n_rtc_s == 40 || n_rtc_s == 50 ) {
        sd[0] = n_rtc_dl;
        sh[0] = n_rtc_h;
        sm[0] = n_rtc_m;
        ss[0] = n_rtc_s;
        saved[0] = 's'; 
      }
      p_rtc_s = n_rtc_s;
    }

    //play music track
    hUGE_dosound();

    // print current RTC values   
    gotogxy(4,5);
    gprintf("Days   : %d  ", n_rtc_dl);
    gotogxy(4,6);
    gprintf("Hours  : %d  ", n_rtc_h);
    gotogxy(4,7);
    gprintf("Minutes: %d  ", n_rtc_m);
    gotogxy(4,8);
    gprintf("Seconds: %d  ", n_rtc_s);

  }

}
