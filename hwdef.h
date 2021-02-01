#define int8 char
#define int8_t char
#define int16 short
#define uint8_t unsigned int8
#define uint16_t unsigned int16
//------------------------------------------------------------------------------
//#FUSES RC
//dgv#FUSES INTRC                    //Internal RC Osc
//#FUSES NOPLLEN                //No pll enable
#FUSES NOMCLR
//dgv#FUSES WDT2048                //Watch Dog Timer uses Postscale
//#FUSES WDT1
//#FUSES NOWDT                  //No Watch Dog Timer
//#FUSES INTRC_IO               //Internal RC Osc
//dgv#FUSES BORV22                   //Brownout reset at 2.2V
//#FUSES NOBROWNOUT
//dgv#FUSES NOPBADEN                 //PORTB pins are configured as digital I/O on RESET
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
//#FUSES NOXINST                //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES PUT                      //Power Up Timer
//#FUSES NOPUT                  //No Power Up Timer 
#FUSES PROTECT
//#FUSES CPB
#FUSES NOCPD
//dgv#FUSES PBADEN
//dgv#PRIORITY  INT_EXT, INT_TIMER1, INT_TIMER3, INT_RDA, INT_AD
//------------------------------------------------------------------------------
#DEVICE ADC=10
//------------------------------------------------------------------------------
#byte WPUB =   0xF7C
#byte IOCB  =  0xF7D

struct{
    unsigned char ANS0:1;
    unsigned char ANS1:1;
    unsigned char ANS2:1;
    unsigned char ANS3:1;
    unsigned char ANS4:1;
    unsigned char ANS5:1;
    unsigned char ANS6:1;
    unsigned char ANS7:1;
}ANSEL;
#locate ANSEL  = 0xF7E
struct{
    unsigned char ANS8:1;
    unsigned char ANS9:1;
    unsigned char ANS10:1;
    unsigned char ANS11:1;
}ANSELH;
#locate ANSELH = 0xF7F 

#byte PORTA =  0xF80
#byte PORTB =  0xF81
#byte PORTC =  0xF82
#byte PORTD =  0xF83
#byte PORTE =  0xF84

#bit  PA3 =    PORTA.3
#bit  PA5 =    PORTA.5
#bit  PA6 =    PORTA.6

#bit  PB6 =    PORTB.6
#bit  PB7 =    PORTB.7

#bit  PC0 =    PORTC.0
#bit  PC1 =    PORTC.1
#bit  PC2 =    PORTC.2

#byte OSCTUNE= 0xF9B

#byte PIR1 =  0xF9E
#byte PIR2 =  0xFA1

#byte TRISC =  0xF94

#byte TRISB =  0xF93
struct{
    unsigned char RB0:1;
    unsigned char RB1:1;
    unsigned char RB2:1;
    unsigned char RB3:1;
    unsigned char RB4:1;
    unsigned char RB5:1;
    unsigned char RB6:1;
    unsigned char RB7:1;
}trisb_bits;
#locate trisb_bits =  0xF93

#byte TRISA =  0xF92
struct{
    unsigned char RA0:1;
    unsigned char RA1:1;
    unsigned char RA2:1;
    unsigned char RA3:1;
    unsigned char RA4:1;
    unsigned char RA5:1;
    unsigned char RA6:1;
    unsigned char RA7:1;
}trisa_bits;
#locate trisa_bits =  0xF92

#byte LATA =  0xF89
#byte LATB =  0xF8A
#byte LATC =  0xF8B
#byte LATD =  0xF8C
#byte LATE =  0xF8D

#bit  RCIF  =  PIR1.5
#bit  ADIF  =  PIR1.6

#bit  TMR3IF  =  PIR2.1

#byte TXSTA =  0xFAC
#bit  TRMT  =  TXSTA.1

#byte TMR3L =  0xFB2
#byte TMR3H =  0xFB3

struct{
    unsigned char ADCS:3;
    unsigned char ACQT:3;
    unsigned char ADCON2_6:1;
    unsigned char ADFM:1;
}ADCON2;
#locate ADCON2 = 0xFC0
struct{
    unsigned char ADCON1_0:1;
    unsigned char ADCON1_1:1;
    unsigned char ADCON1_2:1;
    unsigned char ADCON1_3:1;
    unsigned char VCFG0:1;
    unsigned char VCFG1:1;
    unsigned char ADCON1_6:1;
    unsigned char ADCON1_7:1;
}ADCON1;
#locate ADCON1 = 0xFC1
struct{
    unsigned char ADON:1;
    unsigned char GO:1;
    unsigned char CHS:4;
    unsigned char ADCON0_6:1;
    unsigned char ADCON0_7:1;
}ADCON0;
#locate ADCON0 = 0xFC2
#byte ADRESL = 0xFC3
#byte ADRESH = 0xFC4
#byte SSPBUF = 0xFC9
#byte T2CON = 0xFCA
#byte PR2 =   0xFCB
#byte TMR2 =  0xFCC

#byte TMR0L =  0xFD6
#byte TMR0H =  0xFD7
//#byte STATUS = 0xFD8

#byte OSIDGV = 0xFD3

#byte BSR =    0xFE0

#byte INTCON = 0xFF2
#byte INTCON2 = 0xFF1
#byte INTCON3 = 0xFF0


/*#bit  ADON    =ADCON0.0
#bit  ADGO    =ADCON0.1
#bit  CHS0    =ADCON0.2
#bit  CHS1    =ADCON0.3
#bit  CHS2    =ADCON0.4
#bit  CHS3    =ADCON0.5

#bit  ADCS0    =ADCON2.0
#bit  ADCS1    =ADCON2.1
#bit  ADCS2    =ADCON2.2
#bit  ACQT0    =ADCON2.3
#bit  ACQT1    =ADCON2.4
#bit  ACQT2    =ADCON2.5
#bit  ADFM     =ADCON2.7*/

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

//#bit  Z  =     STATUS.2
//#bit  STATUS_Carry =  STATUS.0

#define Version "base.v1904"
//------------------------------------------------------------------------------
//---Port A
#define GPIO00 PIN_A0
#define GPIO01 PIN_A1
#define GPIO02 PIN_A2
#define GPIO03 PIN_A3
#define GPIO04 PIN_A4
#define GPIO05 PIN_A5
#define GPIO06 PIN_A6
#define LEDC   PIN_A7

//---Port B
#define GPIO07 PIN_B0
#define GPIO08 PIN_B1
#define GPIO09 PIN_B2
#define GPIO10 PIN_B3
#define GPIO11 PIN_B4
#define GPIO12 PIN_B5
#define PGC    PIN_B6
#define RX2    PIN_B6
#define PGD    PIN_B7
#define TX2    PIN_B7

//---Port C
#define GPIO13 PIN_C0
#define GPIO14 PIN_C1
#define GPIO15 PIN_C2
#if((PCB&1)==1)
#define LED3   PIN_C3
#define LED2   PIN_C4
#define LED1   PIN_C5
#endif
#if((PCB&2)==2)
#define LED2   PIN_C3
#define LED1   PIN_C4
#define LED3   PIN_C5
#endif
#define TX1    PIN_C6
#define RX1    PIN_C7

//---Port D
//#define PD0  PIN_D0
//#define PD1  PIN_D1
//#define PD2  PIN_D2
//#define PD3  PIN_D3
//#define PD4  PIN_D4
//#define PD5  PIN_D5
//#define PD6  PIN_D6
//#define PD7  PIN_D7

//---Port E
//define PE0   PIN_E0
//define PE1   PIN_E1
//define PE2   PIN_E2
#define MCLR   PIN_E3
#define ADD0   PIN_E3
//define PE4   PIN_E4
//define PE5   PIN_E5
//define PE6   PIN_E6
//define PE7   PIN_E7
//------------------------------------------------------------------------------
#define RF24_CS   PIN_B0
#define RF24_CE   PIN_C3
#define RF24_IRQ  PIN_C4
#define SPI_MOSI  PIN_C6
#define SPI_MISO  PIN_C7
#define SPI_CLK   PIN_A7
//------------------------------------------------------------------------------
//#DEVICE ICD=TRUE
#use delay(internal=16M)
//#use delay(internal=64M)
#if((PCB&6)==6)
//, ENABLE=RF24_CE, ENABLE_ACTIVE=1
//dgv#use spi(MASTER, FORCE_SW, DO=SPI_MOSI, DI=SPI_MISO, CLK=SPI_CLK, mode=0, baud=100000, BITS=8, MSB_FIRST, SAMPLE_RISE, stream=RF24_SPI)
#define lnk1 RF24_SPI
#else
#use rs232(baud=115200,parity=N,stop=1,xmit=TX1,rcv=RX1,ERRORS,bits=8,stream=lnk1)
#endif
#use rs232(baud=115200,parity=N,stop=1,xmit=TX2,rcv=RX2,ERRORS,bits=8,force_sw,stream=lnk2) 

struct{

    unsigned char SCS0:1;

    unsigned char SCS1:1;

    unsigned char IOFS:1;

    unsigned char OSTS:1;

    unsigned char IRCF0:1;

    unsigned char IRCF1:1;

    unsigned char IRCF2:1;

    unsigned char IDLEN:1;

}OSCCON;

#locate OSCCON =  0xFD3

//#use FAST_IO(A)
//#use FAST_IO(B)
//#use FAST_IO(C)
//#use FAST_IO(D)
//#use FAST_IO(E)

