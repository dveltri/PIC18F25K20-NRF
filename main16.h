#include <16F1829.h>
#device ADC=10
               
#FUSES WDT
#FUSES NOBROWNOUT           	//No brownout reset
#FUSES NOLVP                	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O  

#define TX1	PIN_B7 //PIN_C4                           
#define RX1	PIN_B5 //PIN_C5                              
#define battery	PIN_A2
#define led	PIN_A5             
#define DHT11_DATA_PIN PIN_C1  
                                                     
#use FIXED_IO( A_outputs=PIN_A0 )
#use FIXED_IO( A_outputs=PIN_A5 )
#use delay(internal=32MHz)
#use rs232(baud=115200, parity=N, stop=1, xmit=TX1, rcv=RX1, ERRORS, bits=8, stream=lnk1) //, rcv=RX1, FORCE_SW

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

