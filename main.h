//------------------------------------------------------------------------------
#define delay delay_ms
#define LOGf(x,y) fprintf(lnk2,x,y)
#define LOG(x) fputs (x, lnk2)
#define LOGchr(x) fputc(x, lnk2)
//------------------------------------------------------------------------------
#define IOs_Pins     12
//--------------------
#define IOs_Count    (IOs_Pins)
#define Svr_Count    4
#define Tmrs_Count   6
#define Events_Count 9
//------------------------------------------------------------------------------ types of io
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
   unsigned char Samples;
   unsigned char Value;
   unsigned char LValue;
   unsigned char Flags;
   unsigned char HigLvl; //cota H
   unsigned char LowLvl; //cota L
   unsigned char HigEvt;
   unsigned char MidEvt;
   unsigned char LowEvt;
   unsigned int16 LstChg;
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
//------------------------------------------------------------------------------idex task
#define Hw_Tmrs         0
#define Hw_Read_INP     1
#define Hw_Procc_INP    2
//#define Hw_Blind1       3
//#define Hw_Blind2       4
#define Hw_ADC          3
typedef struct
{
   TS_IOs IOs[IOs_Count];
   TS_Tmrs Tmrs[Tmrs_Count];
   TS_Srv_Stk Srv[Svr_Count];
   uint8_t Events[Events_Count];
   //-----------------------
   uint8_t AdChl;       //chanel of ADC
   uint16_t packet_count;
   uint16_t battery;
   uint16_t hr_gnd;
   uint16_t luz_am;
   uint16_t luz_uv;
//   int8 diff;               //
}TS_DGV_OS;

extern TS_DGV_OS iGP;
extern DgvSck iSck;
extern TS_PDGV *pdgv;

int8 InstTask(unsigned char Task);
void SetOutput(unsigned char Out,unsigned char value);
unsigned int16 GetInputs(void);
void UpdtInputV(unsigned char io,unsigned char val);
void UpdtInput(unsigned char io,unsigned char val);
void sensors(void);

//#define IDhw (0x10+(input(ADD2)<<2)+(input(ADD1)<<1)+(input(ADD0)<<0)^7)
#define IDhw (0x10|((ADRESH>>5)&7));

#if((PCB&6)==6)
#define ToggleLed(x)    //output_toggle(x)
#define ToggleColor(x)  //output_bit(x,input_state(LEDC));output_toggle(LEDC);
#define SetGreen(x)     //output_low(LEDC);output_high(x);
#define SetRed(x)       //output_high(LEDC);output_low(x);
#define SetOff(x)       //input(x)
#define SetHi(x)        //output_high(x)
#define SetLo(x)        //output_low(x)
#else
#define ToggleLed(x)    output_toggle(x)
#define ToggleColor(x)  output_bit(x,input_state(LEDC));output_toggle(LEDC);
#define SetGreen(x)     output_low(LEDC);output_high(x);
#define SetRed(x)       output_high(LEDC);output_low(x);
#define SetOff(x)       input(x)
#define SetHi(x)        output_high(x)
#define SetLo(x)        output_low(x)
#endif
#define GetRTC()        get_timer0()
#define GetRTC32(x)     {x=Htim0;x<<=16;x|=get_timer0();}
#define Xms *62 //esto es la relacion de ticks y ms de get_timer0

