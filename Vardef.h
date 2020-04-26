//==================================================================EEPROM
#define CTRINIe	0X00
#define STSe	0X01
//-----------------
#define SPEEDe2	0X03
//-----------------
#define EExteH	0X04
#define EExteL	0X05
//-----------------
#define DefWay	0X06
#define IDBASEe	0X07
//-----------------
#define RED2Do	0X08
#define PTTOUTe	0X09
//-----------------
#define RED0Di	10
#define RED1Di	11
#define RED2Di	12
//-----------------
#define RR0TO	13
#define RR1TO	14
#define RR2TO	15
//=================
#define TRISAe	16
#define TRISBe	17
#define TRISCe	18
#define TRISDe	19
#define TRISEe	20
//-----------------
#define PORTAe	21
#define PORTBe	22
#define PORTCe	23
#define PORTDe	24
#define PORTEe	25
//-----------------
#define MASKAe	26
#define MASKBe	27
#define MASKCe	28
#define MASKDe	29
#define MASKEe	30
//-----------------
#define IDOe	31
//-----------------
#define LSR0	36
//-----------------
#define LSR1	44
//-----------------
#define LSR2	52
//=-·-=-·-=-·-=-·-=-·-=
#define DEvente	60
#define AddEvDc	61
#define SEvente	62
#define AddEvSeg1	63
#define SEvente2	64
#define AddEvSeg2	65
#define MEvente	66
#define AddEvMin1	67
#define MEvente2	68
#define AddEvMin2	69
#define HEvente	70
#define AddEvHs 	71
//-----------------
#define FLAGSev	72
//-----------------
#define BUFFEv	73
//-----------------
#define ANA0Hi	74
#define ANA1Hi	75
#define ANA2Hi	76
#define ANA3Hi	77
#define ANA4Hi	78
#define ANA5Hi	79
#define ANA6Hi	80
#define ANA7Hi	81
#define ANA0Lo	82
#define ANA1Lo	83
#define ANA2Lo	84
#define ANA3Lo	85
#define ANA4Lo	86
#define ANA5Lo	87
#define ANA6Lo	88
#define ANA7Lo	89
//-----------------
#define Ana0EvHi	90
#define Ana1EvHi	91
#define Ana2EvHi	92
#define Ana3EvHi	93
#define Ana4EvHi	94
#define Ana5EvHi	95
#define Ana6EvHi	96
#define Ana7EvHi	97
//-----------------
#define Ana0EvMe	98
#define Ana1EvMe	99
#define Ana2EvMe	100
#define Ana3EvMe	101
#define Ana4EvMe	102
#define Ana5EvMe	103
#define Ana6EvMe	104
#define Ana7EvMe	105
//-----------------
#define Ana0EvLo	106
#define Ana1EvLo	107
#define Ana2EvLo	108
#define Ana3EvLo	109
#define Ana4EvLo	110
#define Ana5EvLo	111
#define Ana6EvLo	112
#define Ana7EvLo	113
//-----------------
#define Bit0EvHi	114
#define Bit0EvLo	115
#define Bit1EvHi	116
#define Bit1EvLo	117
#define Bit2EvHi	118
#define Bit2EvLo	119
#define Bit3EvHi	120
#define Bit3EvLo	121
#define Bit4EvHi	122
#define Bit4EvLo	123
#define Bit5EvHi	124
#define Bit5EvLo	125
#define Bit6EvHi	126
#define Bit6EvLo	127
#define Bit7EvHi	128
#define Bit7EvLo	129
#define Bit8EvHi	130
#define Bit8EvLo	131
//-----------------
#define Bit9EvHi	132
#define Bit9EvLo	133
#define BitAEvHi	134
#define BitAEvLo	135
#define BitBEvHi	136
#define BitBEvLo	137
#define BitCEvHi	138
#define BitCEvLo	139
#define BitDEvHi	140
#define BitDEvLo	141
//-----------------
#define LsEventos	142
//--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=
#DEFINE	PKDV	STS,0	//(PDZ)	FLAG DE PAQUETE VALIDO
#DEFINE	UIDV	STS,1	//(PDZ)	FLAG DE ID VALIDO
#DEFINE	ErTo	STS,2	//
#DEFINE	STSf3	STS,3	//
#DEFINE	BUFFULLf	STS,4	//
#DEFINE	ACKSTATs	STS,5	//
#DEFINE	STSf6	STS,6	//
#DEFINE	BTTX	STS,7	//BIT TX FSK
//--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=0X6F
#DEFINE	SYSen	STSr,0	//(SYS)		ESTE FLAG INDICA SI EL SYSTEME ESTA HABILITADO O NO!	
#DEFINE	RS0en	STSr,1	//(Com DGV)	ENABLE PORT RS232(0)9600
#DEFINE	RS1en	STSr,2	//(Com H/W)	ENABLE PORT RS232(1)38400
#DEFINE	RS2en	STSr,3	//(Com FSK)	ENABLE PORT RS232(2)1200
#DEFINE	DIGEVen	STSr,4	//()
#DEFINE	ANAEVen	STSr,5	//()
#DEFINE	TIMEVen	STSr,6	//()
#DEFINE	Repe	STSr,7	//(Repetidora)	Permite retransmitir por el mismo medio
//========================================================================
#DEFINE	ANA0	PORTA,0	//(I/0)(AD)0
#DEFINE	ANA1	PORTA,1	//(I/0)(AD)0
#DEFINE	ANA2	PORTA,2	//(I/0)(AD)0
#DEFINE	ANA3	PORTA,3	//(I/0)(AD)0
#DEFINE	Tx0	PORTA,4	//(TX RS232(0))
#DEFINE	Rx0	PORTA,4	//(RX RS232(0))
#DEFINE	ANA4	PORTA,5	//(I/O)(AD)0
//--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=
#DEFINE	RB0	PORTB,0	//(I/O)
#DEFINE	RB1	PORTB,1	//(I/O)
#DEFINE	RB2	PORTB,2	//(I/O)
#DEFINE	RB3	PORTB,3	//(I/O)
#DEFINE	RB4	PORTB,4	//(I/O)
#DEFINE	RB5	PORTB,5	//(I/O)
#DEFINE	RB6	PORTB,6	//(I/O)(ICSPc)1
#DEFINE	RB7	PORTB,7	//(I/O)(ICSPd)1
//--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=
#DEFINE	BUSY	PORTC,0	//1(BUSY)
#DEFINE	Rx2	PORTC,1	//1(RX RS232(2))(PWM2)0
#DEFINE	Tx2	PORTC,2	//0(TX RS232(2))(PWM1)0
#DEFINE	I2Cc	PORTC,3	//1(I2Cc)1
#DEFINE	I2Cd	PORTC,4	//1(I2Cd)1
#DEFINE	PTT	PORTC,5	//1(PTT)
#DEFINE	Tx1	PORTC,6	//0(TX RS232(1))
#DEFINE	Rx1	PORTC,7	//1(RX RS232(1))
//--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=
#DEFINE	LED1	PORTD,0	//
#DEFINE	LED2	PORTD,1	//
#DEFINE	RD2	PORTD,2	//(I/O)
#DEFINE	RD3	PORTD,3	//(I/O)
#DEFINE	RD4	PORTD,4	//(I/O)
#DEFINE	RD5	PORTD,5	//(I/O)
#DEFINE	RD6	PORTD,6	//(I/O)
#DEFINE	RD7	PORTD,7	//(I/O)
//--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=
#DEFINE	ANA5	PORTE,0	//
#DEFINE	ANA6	PORTE,1	//
#DEFINE	ANA7	PORTE,2	//
//==================================================================
