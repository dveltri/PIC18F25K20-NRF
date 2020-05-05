#ROM int8 getenv("EEPROM_ADDRESS") ={
0xFF,
0xFF,
0x14,
254,
7,
1,
0x80,
0x81,
0x82,
0x83,
0x84,
255,//broadcast
11, //speed
63,
63,
0}

#ROM int8 (getenv("EEPROM_ADDRESS")+IO_02_Hold_Ev) ={
0,0,
0,0,
0,0,
0,0,
0,0,
0,0,
0,0,
0,0,
255,255,255}   //Out_Led_Neg,In_Neg,In_typ_sate

#ROM int8 (getenv("EEPROM_ADDRESS")+TIMER1_Ps) ={
1,0,
4,0,
6,0,
8,0,
10,Task52,
12,0}//Task53

#ROM int8 (getenv("EEPROM_ADDRESS")+Win1Time) ={
0,0,0,0}

#ROM int8 (getenv("EEPROM_ADDRESS")+LsEventos) ={
CMD_RUN_2TSK,196,255,//Task58
CMD_SEND_Tsk,1,Task58,//Task57
CMD_WRAM,128,127,
CMD_WRAM,128,0,
CMD_Dom_OmOff,128,255,
CMD_XBIT_RAM,0,1,
CMD_PING,0,0}

