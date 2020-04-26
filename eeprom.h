void write_eeprom(unsigned char address, unsigned char data);
unsigned char read_eeprom(unsigned char address);

//==================================================================EEPROM
#define CTRINIe          0x00
#define STSe             0x01
#define Kdgv_Ctrl        0x02
#define Kdgv_IdS         0x03
#define IDOe             0x04
#define IDOeI            0x05
#define IDOeG1           0x06
#define IDOeG2           0x07
#define IDOeG3           0x08
#define IDOeG4           0x09
#define IDOeG5           0x0A
#define IDOeBC           0x0B
#define LNK_0_Speed      0x0C
#define LNK_0_MAT        0x0D  //cantidad de re transmiciones
#define LNK_0_TO         0x0E  //time out wait response
#define Start_Ev         0x0F
//-----------------------Error Codes
#define Er_TimOut        0x10
#define Er_Ctrl          0x11
#define Er_Len           0x12
#define Er_Rx_Mlc        0x13
#define Er_CRC           0x14
#define Er_WDT           0x15
#define Er_NoEvtFree     0x16
#define Er_Colision      0x17
//-----------------------Free 
#define In_typ_sate      0x18
#define In_typ_sateH     0x19
#define In_Neg           0x1A
#define In_NegH          0x1B
#define FreeEE04         0x1C
#define FreeEE05         0x1D
#define FreeEE06         0x1E
#define FreeEE07         0x1F
#define FreeEE08         0x20
#define FreeEE09         0x21
#define FreeEE0A         0x22
#define FreeEE0B         0x23
#define FreeEE0C         0x24
#define FreeEE0D         0x25
#define FreeEE0E         0x26
#define FreeEE0F         0x27
//-----------------------InEv
#define IO_00_Hold_Ev    0x28
#define IO_00_Tap_Ev     0x29
#define IO_01_Hold_Ev    0x2A
#define IO_01_Tap_Ev     0x2B
#define IO_02_Hold_Ev    0x2C
#define IO_02_Tap_Ev     0x2D
#define IO_03_Hold_Ev    0x2E
#define IO_03_Tap_Ev     0x2F
#define IO_04_Hold_Ev    0x30
#define IO_04_Tap_Ev     0x31
#define IO_05_Hold_Ev    0x32
#define IO_05_Tap_Ev     0x33
#define IO_06_Hold_Ev    0x34
#define IO_06_Tap_Ev     0x35
#define IO_07_Hold_Ev    0x36
#define IO_07_Tap_Ev     0x37
#define IO_08_Hold_Ev    0x38
#define IO_08_Tap_Ev     0x39
#define IO_09_Hold_Ev    0x3A
#define IO_09_Tap_Ev     0x3B
#define IO_0A_Hold_Ev    0x3C
#define IO_0A_Tap_Ev     0x3D
#define IO_0B_Hold_Ev    0x3E
#define IO_0B_Tap_Ev     0x3F
//--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=
#define TIMER1_Ps        0x40
#define TIMER1_Ev        0x41
#define TIMER2_Ps        0x42
#define TIMER2_Ev        0x43
#define TIMER3_Ps        0x45
#define TIMER3_Ev        0x46
#define TIMER4_Ps        0x47
#define TIMER4_Ev        0x48
#define TIMER5_Ps        0x49
#define TIMER5_Ev        0x4A
#define TIMER6_Ps        0x4B
#define TIMER6_Ev        0x4C
//--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=
//#define Win1Time       0x49
//#define Win1Lvl        0x4A
//#define Win2Lvl        0x4B
//#define Win2Time       0x4C
#define Win1Time         0x4D
#define Win1Lvl          0x4E
#define Win2Time         0x4F
#define Win2Lvl          0x50
//#define In_Neg         0x51
//--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=
#define LsEventos        0x52
#define Task58           0x52
#define Task57           0x55
#define Task56           0x58
#define Task55           0x5B
#define Task54           0x5E
#define Task53           0x61
#define Task52           0x64
//_,-,_,-,_,-,_,-,_,-,_,-,_,-,_,-,_,-,_,-,_,-,_,-,_,-,_,-,_//
#define Task1            0xFD
#define Task1d1          0xFE
#define Task1d2          0xFF
//==================================================================

