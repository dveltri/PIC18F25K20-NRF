#include <16F1829.h>
#device ADC=8  
               
//#FUSES WDT      
#FUSES NOBROWNOUT           	//No brownout reset
#FUSES NOLVP                	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O  


#use delay(internal=32MHz)
#use FIXED_IO( A_outputs=PIN_A5 )                                               

#define TX1    PIN_B7
#define RX1    PIN_B5

                                                                                                                       
#use rs232(baud=115200,parity=N,stop=1,xmit=TX1,rcv=RX1,ERRORS,bits=8,stream=lnk1)

#define led	PIN_A5              
#define PIN_servo	PIN_C2

#define PIN_motor1	PIN_C4 
#define PIN_motor1b	PIN_C6
#define PIN_motor2	PIN_C5     
#define PIN_motor2b	PIN_C3

#define int8_t int8              
#define int16_t int16                                                 
#define uint8_t	unsigned int8
#define uint16_t unsigned int16

#define LOGf(x,y) fprintf(lnk1,x,y)                  
#define LOG(x) fputs (x, lnk1)
#define LOGchr(x) fputc(x, lnk1)

struct{
    unsigned char ANSA0:1;
    unsigned char ANSA1:1;
    unsigned char ANSA2:1;
    unsigned char ANSELA_3:1;
    unsigned char ANSA4:1;
}ANSELA;
#locate ANSELA  = 0x18C

struct{
    unsigned char ADPREF:2;
    unsigned char ADNREF:1;
    unsigned char ADCON1_3:1;
    unsigned char ADCS:3;
    unsigned char ADFM:1;
}ADCON1;
#locate ADCON1 = 0x09E

