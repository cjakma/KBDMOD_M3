#include <stdio.h>
#include "keymap.h"

#define MAX_COL     6
#define MAX_ROW     19

#define MAX_LAYER   8
#define MAXHEXLINE 32	/* the maximum number of bytes to put in one line */


// Total 132 keys + one none
    

unsigned char keymap_code[MAX_LAYER][MAX_COL][MAX_ROW] =  {
	{
		// LAYER 0 : Syryan
		// ROW0         ROW1    ROW2     ROW3      ROW4 	ROW5	ROW6     ROW7     ROW8      ROW9     ROW10    ROW11   ROW12          ROW13           ROW14    ROW15                        ROW16  ROW17 ROW18
		{K_F2,      K_F3,   K_F8,   K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE,     K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL0
		{K_ESC,     K_1,    K_2,    K_3,    K_4,    K_5,    K_6,    K_7,    K_8,    K_9,    K_0,    K_MINUS,K_EQUAL,    K_BKSP,     K_SCRLCK,K_NONE,            K_NONE,K_NONE,K_NONE}, // COL1
		{K_TAB,     K_Q,    K_W,    K_E,    K_R,    K_T,    K_Y,    K_U,    K_I,    K_O,    K_P,    K_RBR,  K_LBR,      K_BKSLASH,  K_DEL, K_NONE,              K_NONE,K_NONE,K_NONE}, // COL2
		{K_CAPS,    K_A,    K_S,    K_D,    K_F,    K_G,    K_H,    K_J,    K_K,    K_L,    K_COLON,K_QUOTE,K_ENTER,    K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL3
		{K_LSHIFT,  K_Z,    K_X,    K_C,    K_V,    K_B,    K_N,    K_M,    K_COMMA,K_DOT,  K_SLASH,K_NONE, K_RSHIFT,   K_INSERT,   K_UP,   K_NONE,             K_NONE,K_NONE,K_NONE}, // COL4
		{K_LCTRL,   K_NONE, K_LALT, K_SPACE,K_FN,   K_B,    K_NONE, K_NONE, K_SPACE,K_RALT, K_NONE, K_NONE, K_NONE,     K_LEFT,     K_DOWN, K_RIGHT,            K_NONE,K_NONE,K_NONE}  // COL5
	},
	{
		// LAYER 0 : leeku
		// ROW0     ROW1        ROW2     ROW3      ROW4 	ROW5	ROW6     ROW7     ROW8      ROW9     ROW10    ROW11   ROW12          ROW13           ROW14    ROW15                        ROW16  ROW17 ROW18
		{K_ESC,     K_M15,  K_LGUI, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE,     K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL0
		{K_HASH,    K_1,    K_2,    K_3,    K_4,    K_5,    K_6,    K_7,    K_8,    K_9,    K_0,    K_MINUS,K_EQUAL,    K_BKSP,     K_DEL,  K_NONE,             K_NONE,K_NONE,K_NONE}, // COL1
		{K_TAB,     K_Q,    K_W,    K_E,    K_R,    K_T,    K_Y,    K_U,    K_I,    K_O,    K_P,    K_RBR,  K_LBR,      K_BKSLASH,  K_PRNSCR,K_NONE,            K_NONE,K_NONE,K_NONE}, // COL2
		{K_CAPS,    K_A,    K_S,    K_D,    K_F,    K_G,    K_H,    K_J,    K_K,    K_L,    K_COLON,K_QUOTE,K_ENTER,    K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL3
		{K_LSHIFT,  K_Z,    K_X,    K_C,    K_V,    K_B,    K_N,    K_M,    K_COMMA,K_DOT,  K_SLASH,K_NONE, K_RSHIFT,   K_NONE,     K_UP,   K_NONE,             K_NONE,K_NONE,K_NONE}, // COL4
		{K_LCTRL,   K_NONE, K_LALT, K_SPACE,K_FN,   K_B,    K_NONE, K_NONE, K_SPACE,K_RALT, K_NONE, K_NONE, K_NONE,    K_LEFT,     K_DOWN, K_RIGHT,            K_NONE,K_NONE,K_NONE}  // COL5


	},
	{
		// LAYER 0 : normal
		// ROW0     ROW1        ROW2     ROW3      ROW4 	ROW5	ROW6     ROW7     ROW8      ROW9     ROW10    ROW11   ROW12          ROW13           ROW14    ROW15                        ROW16  ROW17 ROW18
		{K_ESC,     K_M15,  K_M16,   K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE,     K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL0
		{K_HASH,    K_1,    K_2,    K_3,    K_4,    K_5,    K_6,    K_7,    K_8,    K_9,    K_0,    K_MINUS,K_EQUAL,    K_BKSP,     K_DEL,  K_NONE,             K_NONE,K_NONE,K_NONE}, // COL1
		{K_TAB,     K_Q,    K_W,    K_E,    K_R,    K_T,    K_Y,    K_U,    K_I,    K_O,    K_P,    K_RBR,  K_LBR,      K_BKSLASH,  K_PGUP, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL2
		{K_CAPS,    K_A,    K_S,    K_D,    K_F,    K_G,    K_H,    K_J,    K_K,    K_L,    K_COLON,K_QUOTE,K_ENTER,    K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL3
		{K_LSHIFT,  K_Z,    K_X,    K_C,    K_V,    K_B,    K_N,    K_M,    K_COMMA,K_DOT,  K_SLASH,K_NONE, K_RSHIFT,   K_NONE,     K_UP,   K_NONE,             K_NONE,K_NONE,K_NONE}, // COL4
		{K_LCTRL,   K_NONE, K_LALT, K_SPACE,K_FN,   K_B,    K_NONE, K_NONE, K_SPACE,K_RALT, K_NONE, K_NONE, K_NONE,     K_LEFT,     K_DOWN, K_RIGHT,            K_NONE,K_NONE,K_NONE}  // COL5

	},
	{
		// LAYER 0 : normal
		// ROW0     ROW1        ROW2     ROW3      ROW4 	ROW5	ROW6     ROW7     ROW8      ROW9     ROW10    ROW11   ROW12          ROW13           ROW14    ROW15                        ROW16  ROW17 ROW18
		{K_ESC,     K_FN,   K_F1,   K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE,     K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL0
		{K_HASH,    K_1,    K_2,    K_3,    K_4,    K_5,    K_6,    K_7,    K_8,    K_9,    K_0,    K_MINUS,K_EQUAL,    K_BKSP,     K_DEL,  K_NONE,             K_NONE,K_NONE,K_NONE}, // COL1
		{K_TAB,     K_Q,    K_W,    K_E,    K_R,    K_T,    K_Y,    K_U,    K_I,    K_O,    K_P,    K_RBR,  K_LBR,      K_BKSLASH,  K_PGUP, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL2
		{K_CAPS,    K_A,    K_S,    K_D,    K_F,    K_G,    K_H,    K_J,    K_K,    K_L,    K_COLON,K_QUOTE,K_ENTER,    K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL3
		{K_LSHIFT,  K_Z,    K_X,    K_C,    K_V,    K_B,    K_N,    K_M,    K_COMMA,K_DOT,  K_SLASH,K_NONE, K_RSHIFT,   K_NONE,     K_UP,   K_NONE,             K_NONE,K_NONE,K_NONE}, // COL4
		{K_LCTRL,   K_NONE, K_LALT, K_SPACE,K_NONE, K_B,    K_NONE, K_NONE, K_SPACE,K_RALT, K_NONE, K_NONE, K_NONE,     K_LEFT,     K_DOWN, K_RIGHT,            K_NONE,K_NONE,K_NONE}  // COL5

	},
	{	
        // LAYER 4 : normal
		// ROW0        ROW1            ROW2     ROW3     ROW4 	ROW5	ROW6     ROW7     ROW8             ROW9     ROW10          ROW11           ROW12          ROW13           ROW14          ROW15           ROW16          ROW17
		{ K_NEXT_TRK,
            K_FN,
            K_STOP,
            K_PLAY,
            K_MUTE,
            K_BASS_BST,
            K_LOUDNESS,
            K_VOL_UP,
            K_VOL_DOWN,
            K_BASS_UP,
            K_BASS_DN,
            K_TRE_UP,
            K_TRE_DN,
            K_MEDIA_SEL,
            K_MAIL,
            K_CALC,
            K_MYCOM,
            K_WWW_SEARCH,
            }, // COL0
        		{K_WWW_HOME,
            K_WWW_BACK,
            K_WWW_FORWARD,
            K_WWW_STOP,
            K_WWW_REFRESH,
            K_WWW_FAVORITE,
            K_EJECT,
            K_SCREENSAVE,
            K_REC,
        	K_REWIND,
        	K_MINIMIZE,

            K_System,
            K_POWER,
            K_SLEEP,
            K_WAKE,K_WAKE,K_VOL_UP,K_NONE, K_NONE},  // COL1
		{K_TAB,   K_Q,      K_W,  K_E,  K_R,  K_T,  K_Y,  K_U,  K_I,      K_O,  K_P,      K_LBR,    K_RBR,    K_BKSLASH,K_NONE,   K_DEL,    K_END,    K_PGDN, K_NONE},  // COL2
		{K_CAPS,  K_A,      K_S,  K_D,  K_F,  K_G,  K_H,  K_J,  K_K,      K_L,  K_COLON,  K_QUOTE,  K_ENTER,  K_NONE,   K_NONE,   K_NONE,   K_NONE,   K_NONE, K_NONE},  // COL3
		{K_LSHIFT,K_Z,      K_X,  K_C,  K_V,  K_B,  K_N,  K_M,  K_COMMA,  K_DOT,K_SLASH,  K_NONE,   K_RSHIFT, K_NONE,   K_NONE,   K_NONE,   K_UP,     K_NONE, K_NONE},  // COL4
		{K_LCTRL, K_LGUI,   K_LALT,K_NONE,K_NONE,K_NONE,K_SPACE,K_NONE,K_NONE,K_RALT,K_RGUI,K_APPS,K_RCTRL,K_NONE,K_NONE,         K_LEFT,   K_DOWN,   K_RIGHT, K_NONE}  // COL5

	},
	{
		// LAYER 0 : normal
		// ROW0     ROW1        ROW2     ROW3      ROW4 	ROW5	ROW6     ROW7     ROW8      ROW9     ROW10    ROW11   ROW12          ROW13           ROW14    ROW15                        ROW16  ROW17 ROW18
		{K_ESC,     K_FN,   K_F1,   K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE,     K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL0
		{K_HASH,    K_1,    K_2,    K_3,    K_4,    K_5,    K_6,    K_7,    K_8,    K_9,    K_0,    K_MINUS,K_EQUAL,    K_BKSP,     K_DEL,  K_NONE,             K_NONE,K_NONE,K_NONE}, // COL1
		{K_TAB,     K_Q,    K_W,    K_E,    K_R,    K_T,    K_Y,    K_U,    K_I,    K_O,    K_P,    K_RBR,  K_LBR,      K_BKSLASH,  K_PGUP, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL2
		{K_CAPS,    K_A,    K_S,    K_D,    K_F,    K_G,    K_H,    K_J,    K_K,    K_L,    K_COLON,K_QUOTE,K_ENTER,    K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL3
		{K_LSHIFT,  K_Z,    K_X,    K_C,    K_V,    K_B,    K_N,    K_M,    K_COMMA,K_DOT,  K_SLASH,K_NONE, K_RSHIFT,   K_NONE,     K_UP,   K_NONE,             K_NONE,K_NONE,K_NONE}, // COL4
		{K_LCTRL,   K_NONE, K_LALT, K_SPACE,K_NONE, K_B,    K_NONE, K_NONE, K_SPACE,K_RALT, K_NONE, K_NONE, K_NONE,     K_LEFT,     K_DOWN, K_RIGHT,            K_NONE,K_NONE,K_NONE}  // COL5

	},
	{
         // LAYER 6: LED
        // ROW0     ROW1        ROW2     ROW3      ROW4 	ROW5	ROW6     ROW7     ROW8      ROW9     ROW10    ROW11   ROW12          ROW13           ROW14    ROW15                        ROW16  ROW17 ROW18
		{K_LFX,   K_LFX,    K_LFX,  K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE,     K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL0
        {K_LFULL, K_LFULL,  K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,    K_LFULL,    K_LFULL,K_NONE,             K_NONE,K_NONE,K_NONE}, // COL1
        {K_LFULL, K_LFULL,  K_LASD, K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,    K_LFULL,    K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL2
        {K_LFULL, K_LASD,   K_LASD, K_LASD, K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,    K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL3
        {K_LFULL, K_LFULL,  K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,    K_NONE,     K_LASD, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL4
        {K_LFULL, K_LFULL,  K_LFULL,K_LFULL,K_FN,   K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,K_LFULL,    K_LASD,     K_LASD, K_LASD,             K_NONE,K_NONE,K_NONE}  // COL5

     },
        

	{	
		// LAYER  FN
        // ROW0    ROW1         ROW2     ROW3      ROW4 	ROW5	ROW6     ROW7     ROW8      ROW9     ROW10    ROW11   ROW12          ROW13           ROW14    ROW15                        ROW16  ROW17 ROW18
		{K_L0,    K_L1,     K_L2,   K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE, K_NONE,     K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE}, // COL0
		{K_HASH,  K_F1,     K_F2,   K_F3,	K_F4,	K_F5,   K_F6,   K_F7,   K_F8,   K_F9,   K_F10,	K_F11,  K_F12,      K_RESET,     K_PRNSCR,K_NONE,            K_NONE,K_NONE,K_NONE},  // COL1
		{K_TAB,   K_M01,    K_M02,  K_M03,  K_M04,  K_M05,  K_M06,  K_M07,  K_M08,  K_M09,  K_M10,  K_RBR,  K_LBR,      K_MRESET,  K_DEL,  K_NONE,             K_NONE,K_NONE,K_NONE},  // COL2
		{K_CAPS,  K_M11,    K_M12,  K_M13,  K_M14,  K_PGUP, K_HOME, K_M17,  K_M18,  K_M19,  K_COLON,K_QUOTE,K_ENTER,    K_NONE,     K_NONE, K_NONE,             K_NONE,K_NONE,K_NONE},  // COL3
		{K_LSHIFT,K_M20,    K_M21,  K_M22,  K_M23,  K_PGDN, K_M25,  K_M26,  K_COMMA,K_DOT,  K_SLASH,K_NONE, K_RSHIFT,   K_INSERT,   K_UP,   K_NONE,             K_NONE,K_NONE,K_NONE},  // COL4
        {K_LCTRL, K_NONE,   K_LALT, K_SPACE,K_FN,   K_END,  K_NONE, K_NONE, K_SPACE,K_RALT, K_NONE, K_NONE, K_NONE,     K_LED0,     K_LED1, K_LED2,             K_NONE,K_NONE,K_NONE}  // COL5

	}
	
 };

typedef enum
{
    LED_EFFECT_FADING          = 0,
    LED_EFFECT_FADING_PUSH_ON  = 1,
    LED_EFFECT_PUSHED_LEVEL    = 2,
    LED_EFFECT_PUSH_ON         = 3,
    LED_EFFECT_PUSH_OFF        = 4,
    LED_EFFECT_ALWAYS          = 5,
    LED_EFFECT_BASECAPS        = 6,
    LED_EFFECT_OFF             = 7,
    LED_EFFECT_NONE
}LED_MODE;

#define LEDMODE_ADDRESS 0x6800
unsigned char  ledmode[5][11] ={ 
                    {LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, 
                    LED_EFFECT_ALWAYS, LED_EFFECT_BASECAPS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, 
                    LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS},

                    {LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, 
                    LED_EFFECT_FADING, LED_EFFECT_BASECAPS, LED_EFFECT_FADING, LED_EFFECT_FADING, 
                    LED_EFFECT_FADING, LED_EFFECT_FADING, LED_EFFECT_FADING},

                    {LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, 
                    LED_EFFECT_PUSHED_LEVEL, LED_EFFECT_BASECAPS, LED_EFFECT_PUSHED_LEVEL, LED_EFFECT_PUSHED_LEVEL, 
                    LED_EFFECT_PUSHED_LEVEL, LED_EFFECT_PUSHED_LEVEL, LED_EFFECT_PUSHED_LEVEL},

                    {LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, LED_EFFECT_ALWAYS, 
                    LED_EFFECT_ALWAYS, LED_EFFECT_BASECAPS, LED_EFFECT_PUSHED_LEVEL, LED_EFFECT_PUSHED_LEVEL, 
                    LED_EFFECT_PUSHED_LEVEL, LED_EFFECT_PUSHED_LEVEL, LED_EFFECT_PUSHED_LEVEL},

                    {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, 
                    LED_EFFECT_FADING, LED_EFFECT_BASECAPS, LED_EFFECT_OFF, LED_EFFECT_OFF, 
                    LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF}
};


#define TEXT_ADDRESS 0x6900
const char *macrostart = "MACRO record mode@";
const char *macroend = "@record done@";
const char *macroresetstart = "MACRO erase";
const char *macroresetdone = "done@";



int keymAddress[MAX_LAYER] = {
    0x6000, // FACTORY DEFAULT
    0x6100,
    0x6200,
    0x6300,
    0x6400,
    0x6500,
    0x6600, // LED LAYER
    0x6700, // FN LAYER
    };
    

int addressExtended = 0;
void insertExtSegAddr(FILE *fp)
{
   fprintf(fp,":020000021000EC\n");
}      

void revertExtSegAddr(FILE *fp)
{
   fprintf(fp,":020000020000FC\n");
}
int buffer2Hex(FILE *fp, int address, int length, unsigned char *buffer)
{
   unsigned char checksum = 0;
   int j;
   char cnt;   

   cnt = length;

   while (length > 0)
   {
      
      if (!addressExtended && (address >= 0x10000))
      {
         insertExtSegAddr(fp);
         addressExtended = 1;
      }else if (addressExtended && (address < 0x10000))
      {
         revertExtSegAddr(fp);
         addressExtended = 0;
      }

      length = length - 0x10;

      cnt = length >= 0 ? 0x10 : length + 0x10;

      fprintf(fp,":%02X", cnt);
      checksum += cnt;
      fprintf(fp,"%04X", (unsigned short)address);
      checksum += ((address >> 8) & 0xFF);
      checksum += address & 0xFF;
      fprintf(fp,"00");
      checksum += 0x00;

      for(j = 0; j < cnt; j++)
      {
         fprintf(fp,"%02X", *buffer);
         checksum += *buffer;
         buffer++;
      }
      checksum = ~(checksum & 0xFF) + 1;
      fprintf(fp,"%02X\n", checksum & 0xFF);
      address += 0x10;
      checksum = 0;
   }
   return 0;
}

 unsigned char hello[] = "hello world";

int main(int argc, char *argv[])
{
   
   int layer;
   int address;
   unsigned char *keymap;
   
   FILE *fp = fopen("keymap.hex", "w");

   for (layer = 0; layer < MAX_LAYER ; layer++)
   {
      address = keymAddress[layer];
      keymap = &(keymap_code[layer][0][0]);
      
      buffer2Hex(fp, address, MAX_COL * MAX_ROW, keymap);
   }

   keymap = &(ledmode[0][0]);

   buffer2Hex(fp, LEDMODE_ADDRESS, 256, keymap);


   address = TEXT_ADDRESS;
   keymap = (unsigned char *)macrostart;
   buffer2Hex(fp, address, 20, keymap);

   address += 0x20;
   keymap = (unsigned char *)macroend;
   buffer2Hex(fp, address, 20, keymap);

   address += 0x20;
   keymap = (unsigned char *)macroresetstart;
   buffer2Hex(fp, address, 20, keymap);

   address += 0x20;
   keymap = (unsigned char *)macroresetdone;
   buffer2Hex(fp, address, 20, keymap);


   
   fclose(fp);
   return 0;
}

