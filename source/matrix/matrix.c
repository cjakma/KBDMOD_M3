#define KEYBD_EXTERN
#include "global.h"
#include "timer.h"
#include "keymap.h"
#include "print.h"
#include "led.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <util/delay.h>     /* for _delay_ms() */

#include "hwport.h"
#include "usbdrv.h"
#include "matrix.h"
#include "usbmain.h"
#include "hwaddress.h"
#include "macro.h"

#include "ps2main.h"

#define STANDBY_LOOP    130000  // scan matix entry is 2.2msec @ 12Mh x-tal : 5min
uint32_t scankeycntms = 0;
	
// 17*8 bit matrix
uint32_t MATRIX[MAX_COL];
uint32_t curMATRIX[MAX_COL];
int8_t debounceMATRIX[MAX_COL][MAX_ROW];
uint8_t svkeyidx[MAX_COL][MAX_ROW];

uint8_t matrixFN[MAX_LAYER];           // (col << 4 | row)
uint8_t layer = 0;
uint8_t kbdsleepmode = 0;
uint8_t ledPortBackup = 0;
uint16_t macrokeypushedcnt;
uint16_t ledkeypushedcnt;
uint16_t macroresetcnt;
uint16_t winkeylockcnt;
uint16_t keylockcnt;
uint8_t keylock = 0;
#define SWAP_TIMER  0x400
#define KEYLOCK_TIMER  0x600
#define KEYLOCK_COUNTER_START 0x8000

uint8_t swapCtrlCaps = 0x80;
uint8_t swapAltGui =  0x80;
uint16_t cntLcaps = 0;
uint16_t cntLctrl = 0;
uint16_t cntLAlt = 0;
uint16_t cntLGui = 0;

uint8_t isLED3000 = 0;

int8_t isFNpushed = 0;
extern int8_t usbmode;


static void swap_load(void)
{
    swapAltGui = eeprom_read_byte(EEPADDR_SWAPALTGUI);
    if(swapAltGui != 1)
        swapAltGui = 0;     
    swapCtrlCaps = eeprom_read_byte(EEPADDR_SWAPCTRLCAPS);
    if(swapCtrlCaps != 1)
        swapCtrlCaps = 0; 
}

static uint8_t findFNkey(void)
{
    uint8_t col, row;
    uint8_t keyidx;
    uint8_t i;
    for(i = 0; i < MAX_LAYER; i++)
    {
        matrixFN[i] = 0x00;
    	for(col=0;col<MAX_COL;col++)
    	{
    		for(row=0;row<MAX_ROW;row++)
            {
               keyidx = pgm_read_byte(keymap[i]+(col*MAX_ROW)+row);
    			if(keyidx == K_FN)
    			{
                    matrixFN[i] = col << 5 | row;
    			}
    		}
        }
        if (matrixFN[i] == 0x00)
        {
            matrixFN[i] = matrixFN[0];  // default FN position
        }
        
    }
    return 0;
}


void keymap_init(void) 
{
	int16_t i, j, keyidx;
#if 1
	// set zero for every flags
	for(i=0;i<MAX_KEY;i++)
		KFLA[i]=0;
#endif
    keyidx = 0x6000;
    for (i = 0; i < 8; i++)
    {
        keymap[i] = keyidx;
        keyidx += 0x100;
    }
        
	// set flags
	for(i=0;(keyidx=pgm_read_byte((uint16_t)(&keycode_set2_special[i])))!=K_NONE;i++)
		KFLA[keyidx] |= KFLA_SPECIAL;
    
	for(i=0;(keyidx=pgm_read_byte((uint16_t)(&keycode_set2_makeonly[i])))!=K_NONE;i++)
		KFLA[keyidx] |= KFLA_MAKEONLY;
    
	for(i=0;(keyidx=pgm_read_byte((uint16_t)(&keycode_set2_make_break[i])))!=K_NONE;i++)
		KFLA[keyidx] |= KFLA_MAKE_BREAK;
	for(i=0;(keyidx=pgm_read_byte((uint16_t)(&keycode_set2_extend[i])))!=K_NONE;i++)
		KFLA[keyidx] |= KFLA_EXTEND;
	for(i=0;(keyidx=pgm_read_byte((uint16_t)(&keycode_set2_proc_shift[i])))!=K_NONE;i++)
		KFLA[keyidx] |= KFLA_PROC_SHIFT;




	for(i=0;i<MAX_ROW;i++)
		MATRIX[i]=0;


    findFNkey();

	for(i=0;i<MAX_COL;i++)
	{
        for(j=0;j<MAX_ROW;j++)
        {
            debounceMATRIX[i][j] = -1;
        }
        curMATRIX[i] = 0;
	}
   layer = eeprom_read_byte(EEPADDR_KEYLAYER);
    if (layer >= MAX_LAYER)
        layer = 0;

   swap_load();
}


uint8_t macrokeystring[3][30] = {
                                {K_H, K_E, K_L, K_L, K_O, K_H, K_E, K_L, K_L, K_O,K_H, K_E, K_L, K_L, K_O,K_H, K_E, K_L, K_L, K_O,K_H, K_E, K_L, K_L, K_O, K_NONE},
                                {K_RCTRL, K_V, K_RCTRL, K_C, K_P, K_NONE},
                                {K_LSHIFT, K_H, K_LSHIFT, K_I, K_G, K_H, K_LSHIFT, K_1, K_LSHIFT, K_NONE}
                             };


uint8_t processPushedFNkeys(uint8_t keyidx)
{
    uint8_t retVal = 0;
    uint8_t key;
    
    if(keyidx >= K_LED0 && keyidx <= K_LED3)
    {
        retVal = 1;
    }else if(keyidx >= K_LFX && keyidx <= K_LARR)
    {
        retVal = 1;
    }else if(keyidx >= K_L0 && keyidx <= K_L6)
    {
        layer = keyidx - K_L0;
        
        key = pgm_read_byte(keymap[layer]+(5*MAX_ROW)+15);
        isLED3000 = (key == K_LEFT)? 1 : 0;
        
        eeprom_write_byte(EEPADDR_KEYLAYER, layer);
        led_mode_init();
        retVal = 1;
    }else if(keyidx >= K_M01 && keyidx <= K_M52)
    {
        retVal = 1;
    }else if(keyidx == K_RESET)
    {
        extern int portInit(void);
        portInit();
        Reset_AVR();
    }else if(keyidx == K_MRESET)
    {
        retVal = 1;
    }else if(keyidx == K_KEYLOCK)
    {
         keylock ^= 0x02;
         retVal = 1;
    }else if(keyidx == K_WINKEYLOCK)
    {
         keylock ^= 0x01;
         retVal = 1;
    }
    return retVal;
}

uint8_t processReleasedFNkeys(uint8_t keyidx)
{
    uint8_t retVal = 0;
    uint8_t ledblock;
        
    if(keyidx >= K_LED0 && keyidx <= K_LED3)
    {
        ledmodeIndex = keyidx-K_LED0;
        for (ledblock = LED_PIN_ESC; ledblock < LED_PIN_VESEL; ledblock++)
        {
            led_mode_change(ledblock, ledmode[ledmodeIndex][ledblock]);
        }
        led_mode_save();
        retVal = 1;
    }else if(keyidx >= K_LFX && keyidx <= K_LARR)
    {
        retVal = 1;
    }else if(keyidx >= K_M01 && keyidx <= K_M52)
    {
        if(usbmode)
             playMacroUSB(keyidx);
         else
             playMacroPS2(keyidx);
         retVal = 1;
    }else if(keyidx == K_RESET)
    {
        Reset_AVR();
    }else if(keyidx == K_MRESET)
    {
        retVal = 1;
    }
    return retVal;
}



uint8_t getLayer(uint8_t FNcolrow)
{
    uint8_t col;
    uint8_t row;
    uint8_t cur;
    
    col = (FNcolrow >> 5) & 0x0f;
    row = FNcolrow & 0x1f;
	
#ifdef KBDMOD_M3
    DDRC  = BV(col) | 0xC0;        //  only target col bit is output and others are input
    PORTC &= ~BV(col);       //  only target col bit is LOW and other are pull-up
#else
    DDRA  = BV(col);        //  only target col bit is output and others are input
    PORTA = ~BV(col);       //  only target col bit is LOW and other are pull-up
#endif

	
	_delay_us(10);
#ifdef KBDMOD_M3
    if(row<8){
		cur = ~PINA & BV(row);
    }else{
		cur = ~PINB & BV(row);
    }
#endif

#ifdef KBDMOD_M5
	if(row<2)	{				// for 0..7, PORTA 0 -> 7
		cur = ~PING & BV(row);
	}
	else if(row>=3 && row<10) {	// for 8..15, PORTC 7 -> 0
		cur = ~PINC & BV(row-2);
	}else if(row >= 10 && row<18){
	    cur = ~PINF & BV(row-10);
	}
#endif
#ifdef KBDMOD_M7
   if(row < 8)   {           // for 0..7, PORTA 0 -> 7
      cur = ~PINC & BV(row);
   }
   else if(row < 16) {   // for 8..15, PORTC 7 -> 0
      cur = ~PINF & BV(row-8);
   }else{
      cur = ~PING & BV(row-16);
   }  
#endif
    if(cur)
    {
      isFNpushed = DEBOUNCE_MAX*2;
      return 7;        // FN layer or beyondFN layer
    }
    else
    {
      if(isFNpushed)
      {
         return 7;        // FN layer or beyondFN layer
      }else
      {
         return layer;                   // Normal layer
      }
    }
}


uint8_t scanmatrix(void)
{
   uint8_t col;
   uint8_t vPinC, vPinF, vPinG;

   uint8_t matrixState = 0;
   uint8_t ledblock;

    if (scankeycntms++ >= STANDBY_LOOP)
        scankeycntms = STANDBY_LOOP;
    
    if (scankeycntms == STANDBY_LOOP && kbdsleepmode == 0)   // 5min
    {
        kbdsleepmode = 1;
        ledmodeIndex = 4;       // hidden OFF index

        for (ledblock = LED_PIN_PRT; ledblock < LED_PIN_VESEL; ledblock++)
        {
            led_mode_change(ledblock, ledmode[ledmodeIndex][ledblock]);
        }
    }
    

	// scan matrix 
	for(col=0; col<MAX_COL; col++)
	{
      // Col -> set only one port as input and all others as output low
#ifdef KBDMOD_M3
        DDRC  = BV(col) | 0xC0;        //  only target col bit is output and others are input
        PORTC &= ~BV(col);       //  only target col bit is LOW and other are pull-up
#else
        DDRA  = BV(col);        //  only target col bit is output and others are input
        PORTA = ~BV(col);       //  only target col bit is LOW and other are pull-up
#endif
      _delay_us(10);
#ifdef KBDMOD_M3
      vPinC = ~PINA;
      vPinF = ~PINB;
      vPinG = 0;
      curMATRIX[col] = (uint32_t)(vPinG & 0x07) << 16 | (uint32_t)vPinF << 8 | (uint32_t)vPinC;
#endif
      
#ifdef KBDMOD_M5
      vPinG = ~PING;
      vPinC = ~PINC;
      vPinF = ~PINF;
      curMATRIX[col] = (uint32_t)(vPinG & 0x03) << 16 | (uint32_t)vPinC << 8 | (uint32_t)vPinF;
#endif
#ifdef KBDMOD_M7
      vPinG = ~PING;
      vPinC = ~PINC;
      vPinF = ~PINF;
      curMATRIX[col] = (uint32_t)(vPinG & 0x07) << 16 | (uint32_t)vPinF << 8 | (uint32_t)vPinC;
#endif
      if(curMATRIX[col])
      {
         matrixState |= SCAN_DIRTY;
         
         scankeycntms = 0;
         if (kbdsleepmode == 1)
         {
             led_mode_init();
             led_3lockupdate(LEDstate);
             kbdsleepmode = 0;
         }
      }
 	}

    
    return matrixState;
}

void swap_save(void)
{
   eeprom_write_byte(EEPADDR_SWAPALTGUI, swapAltGui);
   eeprom_write_byte(EEPADDR_SWAPCTRLCAPS, swapCtrlCaps);
}

uint8_t cntKey(uint8_t keyidx, uint8_t clearmask)
{
    switch (keyidx)
    {
        case K_CAPS:
            if (clearmask == 0)
            {
                swapCtrlCaps |= 0x80;
                cntLcaps = 0;
            }
            if (cntLcaps++ >= SWAP_TIMER)
                cntLcaps = SWAP_TIMER;
            break;
        case K_LCTRL:
            if (clearmask == 0)
            {
                swapCtrlCaps |= 0x80;
                cntLctrl = 0;
            }
            if (cntLctrl++ >= SWAP_TIMER)
                cntLctrl = SWAP_TIMER;
            break;
        case K_LALT:
            if (clearmask == 0)
            {
                swapAltGui |= 0x80;
                cntLAlt = 0;
            }
            if (cntLAlt++ >= SWAP_TIMER)
                cntLAlt = SWAP_TIMER;
            break;
        case K_LGUI:
            if (clearmask == 0)
            {
                swapAltGui |= 0x80;
                cntLGui = 0;
            }
            if (cntLGui++ >= SWAP_TIMER)
                cntLGui = SWAP_TIMER;
            break;
    }
    if((cntLcaps == SWAP_TIMER) && (cntLctrl == SWAP_TIMER) && (swapCtrlCaps & 0x80))
    {
        swapCtrlCaps ^= 1;
        swapCtrlCaps &= 0x7F;
        swap_save();
    }
    if((cntLGui == SWAP_TIMER) && (cntLAlt == SWAP_TIMER) && (swapAltGui & 0x80))
    {
        swapAltGui ^= 1;
        swapAltGui &= 0x7F;
        swap_save();
    }
    if(keyidx >= K_M01 && keyidx <= K_M48)
    {
         if(clearmask == 0x0000)
        {
            macrokeypushedcnt = 0;
        }
        if (macrokeypushedcnt++ == SWAP_TIMER)
        {
            recordMacro(keyidx);
            macrokeypushedcnt = 0;
        }
        
    }else if (keyidx >= K_LED0 && keyidx <= K_LED3)
    {
        if(clearmask == 0x0000)
        {
            ledkeypushedcnt = 0;
        }
        if (ledkeypushedcnt++ == SWAP_TIMER)
        {
            recordLED(keyidx);
            ledkeypushedcnt = 0;
        }
        
    }else if (keyidx == K_MRESET)
    {
         if(clearmask == 0x0000)
        {
            macroresetcnt = 0;
        }
        if(macroresetcnt++ == SWAP_TIMER)
        {
            resetMacro();
        }
    }
    return 0;
}


uint8_t swap_key(uint8_t keyidx)
{
    if(keylock & 0x02)
    {
      keyidx = K_NONE;
      return keyidx;
    }
    if(swapCtrlCaps & 0x01)
    {
        if(keyidx == K_CAPS)
        {
            keyidx = K_LCTRL;
        }
        else if(keyidx == K_LCTRL)
        {
            keyidx = K_CAPS;
        }
    }
    if(swapAltGui & 0x01)
    {
        if(keyidx == K_LALT)
        {
            keyidx = K_LGUI;
        }
        else if(keyidx == K_LGUI)
        {
            keyidx = K_LALT;
        }
    }
    if (keylock & 0x01)
    {
      if ((keyidx == K_LGUI) || (keyidx == K_RGUI))
         keyidx = K_NONE;
    }
    return keyidx;
}

// return : key modified
uint8_t scankey(void)
{
	int8_t col, row;
	uint32_t prev, cur;
    uint8_t prevBit, curBit;
	uint8_t keyidx;
	uint8_t matrixState = 0;
	uint8_t retVal = 0;
    int8_t i;
    long keyaddr;

    matrixState = scanmatrix();

   if (matrixState == 0 && isFNpushed > 0)
   {
      isFNpushed--;
   }

   if(!kbdsleepmode)
   {
      led_PRTIndicater(keylock);
      led_ESCIndicater(layer);
   }
   //static int pushedLevel_prev = 0;

    /* LED Blinker */
    led_blink(matrixState);

    /* LED Fader */
    led_fader();

    clearReportBuffer();
   
	uint8_t t_layer = getLayer(matrixFN[layer]);

	// debounce cleared => compare last matrix and current matrix
	for(col = 0; col < MAX_COL; col++)
	{

        prev = MATRIX[col];
        cur  = curMATRIX[col];
        MATRIX[col] = curMATRIX[col];
		for(i = 0; i < MAX_ROW; i++)
		{
            prevBit = (uint8_t)(prev & 0x01);
            curBit = (uint8_t)(cur & 0x01);
            prev >>= 1;
            cur >>= 1;

#ifdef KBDMOD_M5
            if (i < 8)
            {
                row = 10+i;
            }else if (i < 16)
            {
                row = -6+i;
            }else if (i < 18)
            {
                row = -16+i;
            }else
            {
                continue;
            }
#else // KBDMOD_M7
            row = i;
#endif
            //keyaddr = 0x6000; //keymap[t_layer];
//            keymap[t_layer] = 0X6000;
//            keyaddr = keymap[t_layer];
//            keyaddr += col*MAX_ROW;
//            keyaddr += row;

 //           keyidx = pgm_read_byte(keyaddr); //keymap[t_layer]+(col*MAX_ROW)+row);
            keyidx = pgm_read_byte(keymap[t_layer]+(col*MAX_ROW)+row);

            if (keyidx == K_NONE)
                continue;

            if(curBit && !(keylock & 0x02))
               cntKey(keyidx, 0xFF);
            
            if (!prevBit && curBit)   //pushed
            {
                led_pushed_level_cal();          /* LED_EFFECT_PUSHED_LEVEL calculate */        
                if (processPushedFNkeys(keyidx))
                    continue;
            }else if (prevBit && !curBit)  //released
            {
                cntKey(keyidx, 0x0000);
                if (processReleasedFNkeys(keyidx))
                    continue;
            }

            keyidx = swap_key(keyidx);

            if ((K_L0 <= keyidx && keyidx <= K_L6) || (K_LED0 <= keyidx && keyidx <= K_FN) || (K_M01 <= keyidx) || (keyidx == K_NONE))
               continue;
            
            if(usbmode)
            {
                if(curBit)
                {
                    if(debounceMATRIX[col][row]++ >= DEBOUNCE_MAX)
                    {
                        retVal = buildHIDreports(keyidx);
                        debounceMATRIX[col][row] = DEBOUNCE_MAX*2;
                    }
                }else
                {
                    if(debounceMATRIX[col][row]-- >= DEBOUNCE_MAX)
                    {
                        retVal = buildHIDreports(keyidx);
                    }else
                    {
                        debounceMATRIX[col][row] = 0;
                    }
                }
            }else
            {
                if (!prevBit && curBit)   //pushed
                {
                    debounceMATRIX[col][row] = 0;    //triger

                }else if (prevBit && !curBit)  //released
                {
                    debounceMATRIX[col][row] = 0;    //triger
    			   }
                
                if(debounceMATRIX[col][row] >= 0)
                {                
                   if(debounceMATRIX[col][row]++ >= DEBOUNCE_MAX)
                   {
                        if(curBit)
                        {
                            putKey(keyidx, 1);
                            svkeyidx[col][row] = keyidx;
                        }else
                        {
                            if (keyidx <= K_M01)  // ignore FN keys
                              putKey(svkeyidx[col][row], 0);
                        }
                                               
                        debounceMATRIX[col][row] = -1;
                   }
  
                }
 		    }
		}
	}
 
    retVal |= 0x05;
	return retVal;
}


