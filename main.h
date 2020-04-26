#define int8 char
#define int16 short
#define uint8 unsigned char
#define uint16 unsigned short

//------------------------------------------------------------------------------
//#FUSES RC
#FUSES INTRC                    //Internal RC Osc
//#FUSES NOPLLEN                //No pll enable
#FUSES NOMCLR
#FUSES WDT2048                  //Watch Dog Timer uses Postscale
#FUSES WDT
//#FUSES NOWDT                  //No Watch Dog Timer
//#FUSES INTRC_IO               //Internal RC Osc
#FUSES BORV22                   //Brownout reset at 2.2V
//#FUSES NOBROWNOUT
#FUSES NOPBADEN                 //PORTB pins are configured as digital I/O on RESET
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
//#FUSES NOXINST                //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES PUT                      //Power Up Timer
//#FUSES NOPUT                  //No Power Up Timer 
#FUSES PROTECT
//#FUSES CPB
#FUSES NOCPD
#FUSES PBADEN
#PRIORITY  INT_EXT, INT_TIMER1, INT_TIMER3, INT_RDA, INT_AD
//------------------------------------------------------------------------------
#byte WPUB =   0xF7C
#byte IOCB  =  0xF7D

#byte ANSEL  = 0xF7E
#byte ANSELH = 0xF7F 

#byte PORTA =  0xF80
#byte PORTB =  0xF81
#byte PORTC =  0xF82
#byte PORTD =  0xF83
#byte PORTE =  0xF84

#bit  PA3 =    PORTA.3
#bit  PA5 =    PORTA.5
#bit  PA6 =    PORTA.6
#bit  PC0 =    PORTC.0
#bit  PC1 =    PORTC.1
#bit  PC2 =    PORTC.2

#byte OSCTUNE= 0xF9B

#byte PIR1 =  0xF9E

#byte TRISC =  0xF94
#byte TRISB =  0xF93
#byte TRISA =  0xF92

#byte LATA =  0xF89
#byte LATB =  0xF8A
#byte LATC =  0xF8B
#byte LATD =  0xF8C
#byte LATE =  0xF8D

#bit  RCIF  =  PIR1.5

#byte TXSTA =  0xFAC
#bit  TRMT  =  TXSTA.1

#byte TMR3L =  0xFB2
#byte TMR3H =  0xFB3

#byte SSPBUF = 0xFC9
#byte T2CON = 0xFCA
#byte PR2 =   0xFCB
#byte TMR2 =  0xFCC

#byte OSCCON = 0xFD3

#byte TMR0L =  0xFD6
#byte TMR0H =  0xFD7
#byte STATUS = 0xFD8

#byte BSR =    0xFE0

#byte INTCON = 0xFF2
#byte INTCON2 = 0xFF1
#byte INTCON3 = 0xFF0

#bit  T2CKPS0  =T2CON.0
#bit  T2CKPS1  =T2CON.1
#bit  TMR20N   =T2CON.2
#bit  T2OUTPS0 =T2CON.3
#bit  T2OUTPS1 =T2CON.4
#bit  T2OUTPS2 =T2CON.5
#bit  T2OUTPS3 =T2CON.6

#bit  GIE =    INTCON.7
#bit  PEIE =   INTCON.6
#bit  TMR0IE = INTCON.5
#bit  INT0IE = INTCON.4
#bit  RBIE =   INTCON.3
#bit  TMR0IF = INTCON.2
#bit  INT0IF = INTCON.1
#bit  RBIF =   INTCON.0

#bit  RBPU     = INTCON2.7
#bit  INTEDG0  = INTCON2.6
#bit  INTEDG1  = INTCON2.5
#bit  INTEDG2  = INTCON2.4
#bit  TMR0IP   = INTCON2.2
#bit  RBIP     = INTCON2.0

#bit  Z  =     STATUS.2
#bit  STATUS_Carry =  STATUS.0

#define Version "base.v1805"
//------------------------------------------------------------------------------
//---Port A
#define GPIO00  PIN_A0
#define GPIO01  PIN_A1
#define GPIO02  PIN_A2
#define GPIO03  PIN_A3
#define GPIO04  PIN_A4
#define GPIO05  PIN_A5
#define GPIO06  PIN_A6
#define GPIO07  PIN_A7

//---Port B
#define GPIO08  PIN_B0
#define GPIO09  PIN_B1
#define GPIO10  PIN_B2
#define GPIO11  PIN_B3
#define GPIO12  PIN_B4
#define GPIO13  PIN_B5
#define ADD2    PIN_B6
#define PGC     PIN_B6
#define ADD1    PIN_B7
#define PGD     PIN_B7

//---Port C
#define LEDC    PIN_C0
#define GPIO14  PIN_C1
#define LED1    PIN_C2
#define GPIO15  PIN_C3
#define LED2    PIN_C4
#define LED3    PIN_C5
#define TX1     PIN_C6
#define RX1     PIN_C7

//---Port D
//#define GPIOxx  PIN_D0
//#define GPIOxx  PIN_D1
//#define GPIOxx  PIN_D2
//#define GPIOxx  PIN_D3
//#define GPIOxx  PIN_D4
//#define GPIOxx  PIN_D5
//#define GPIOxx  PIN_D6
//#define GPIOxx  PIN_D7

//---Port E
//define GPIOxx   PIN_E0
//define GPIOxx   PIN_E1
//define GPIOxx   PIN_E2
#define MCLR   PIN_E3
#define ADD0   PIN_E3
//define GPIOxx   PIN_E4
//define GPIOxx   PIN_E5
//define GPIOxx   PIN_E6
//define GPIOxx   PIN_E7
//------------------------------------------------------------------------------
#DEVICE ADC=8
//#use delay(internal=16M)
#use delay(internal=64M)

#use rs232(baud=115200,parity=N,stop=1,xmit=TX1,rcv=RX1,ERRORS,bits=8,stream=lnk1)
//#use rs232(baud=38400,parity=N,stop=1,xmit=TX2,rcv=RX2,bits=8,force_sw,stream=lnk2) 

//#use FAST_IO(A)
#use FAST_IO(B)
//#use FAST_IO(C)
//#use FAST_IO(D)
#use FAST_IO(E)
//------------------------------------------------------------------------------
#define delay delay_ms
//#define LOG(x) fputs(x,lnk2)
//#define LOGchr(x) fputc(x,lnk2)
//#define LOGf(x,y) fprintf(lnk2,x,y)
//------------------------------------------------------------------------------
#define IOs_Pins     12
#define IOs_Count    (IOs_Pins)
#define Svr_Count    4
#define Tmrs_Count   6
#define Events_Count 9
//------------------------------------------------------------------------------idex task
#define Hw_Read_INP     0
#define Hw_Procc_INP    1
#define Hw_Tmrs         2
#define Hw_ADC          3
//------------------------------------------------------------------------------ typos de io
#define IO_Flg_Typ_Msk  0x07
#define IO_Flg_Typ_Out  0x00  // Salida On Off
#define IO_Flg_Typ_OutA 0x01  // Salida Analoga
#define IO_Flg_Typ_OutF 0x02  // Salida PWM
#define IO_Flg_Typ_OutD 0x03  // Salida Trk Diming

#define IO_Flg_Typ_In   0x04  // Input On Off
#define IO_Flg_Typ_InAC 0x05  // Analoga Acotada
#define IO_Flg_Typ_InAV 0x06  // Analoga Variacion
#define IO_Flg_Typ_InD  0x07  // Input Domotica short Press Long Press

#define IO_Flg_Sts      0x08  // Flag de status
#define IO_Flg_W        0x10  // 
#define IO_Flg_X        0x20
#define IO_Flg_Neg      0x40  // Invertido
#define IO_Flg_LSts     0x80
//-------------------estructura de conf io en eeprom----------------------------
typedef struct
{
   unsigned char IO_0_Flg;
   unsigned char IO_0_Hi;
   unsigned char IO_0_Lo;
   unsigned char IO_0_Hi_Ev;
   unsigned char IO_0_Me_Ev;
   unsigned char IO_0_Lo_Ev;
}TS_IOs_A_EE;
//--------------------estructura de io en ram-------------------------------------
typedef struct
{
  unsigned char Value;
  unsigned char Flags;
  unsigned char HigLvl; //cota H
  unsigned char LowLvl; //cota L
  unsigned char HigEvt;
  unsigned char MidEvt;
  unsigned char LowEvt;
  unsigned char LstVal;
}TS_IOs;
//------------------------------------------------------------------------------
typedef struct
{
  unsigned int16 ConstTime;
  unsigned int16 LastTime;
}TS_Srv_Stk;
//------------------------------------------------------------------------------
typedef struct
{
  unsigned char TmpCount1;
  unsigned char TmpCount2;
  unsigned char Prescale;
  unsigned char OverFlowEv;
  //unsigned char Iteraciones;
}TS_Tmrs;
//------------------------------------------------------------------------------
typedef struct
{
   TS_IOs IOs[IOs_Count];
   TS_Tmrs Tmrs[Tmrs_Count];
   TS_Srv_Stk Srv[Svr_Count];
   uint8 Events[Events_Count];
   //-----------------------
   uint8 AdChl;     //chanel of ADC
//   int8 diff;               //
}TS_DGV_OS;

extern TS_DGV_OS iGP;
extern DgvSck iSck;
extern TS_PDGV *pdgv;

int8 InstTask(unsigned char Task);
unsigned short GetInputs(void);
void SetOutput(unsigned char Out,unsigned char value);
#define ToggleLed(x)    output_toggle(x)
#define ToggleColor(x)  output_bit(x,input_state(LEDC));output_toggle(LEDC);
#define SetGreen(x)     output_low(LEDC);output_high(x);
#define SetRed(x)       output_high(LEDC);output_low(x);
#define SetOff(x)       input(x)
#define GetRTC()        get_timer0()
#define Xms *62 //esto es la relacion de ticks y ms de get_timer0

