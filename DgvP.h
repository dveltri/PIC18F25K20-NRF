#define ParmRxTOut  (2Xms)
#define ParmTxTOut  (5Xms)
#define Lnk_Count 1
//------------------------------------------------------------------------------
#define Osi2         0
//#define Osi2_Start   1
#define Osi2_Ctrl    2
#define Osi2_IdS     3
#define Osi2_IdT     4
#define Osi2_SockS   5
#define Osi2_SockT   6
#define Osi2_Len     7
#define Osi2_Datos   8
#define Osi3         10
#define Osi3_Chk_Crc 11
#define Osi3_Chk_ID  12
#define Osi2_Len2    13
#define Procces      20
//------------------------------------------------------------------------------
#define pdgv_Preambulo  0x7E
#define pdgv_Ver        0x01
#define pdgv_TCP        0x00
#define pdgv_UDP        0x10
#define pdgv_None       0x00
#define pdgv_Chs        0x04
#define pdgv_Sum        0x08
#define pdgv_Crc        0x0C
//----------------------
#define CmpCtr    0
#define CmpIdS    1
#define CmpIdT    2
#define CmpSkS    3
#define CmpSkT    4
#define CmpLen    5
#define CmpDat    6
#define MaxLen    127
#define LINKS     4
//------------------------------------------------------------------------------
#define CMD_RESET       0
#define CMD_CHG_ID      1
#define CMD_PING        2
#define CMD_WEE         3
#define CMD_REE         4
#define CMD_WRAM        5
#define CMD_RRAM        6
#define CMD_SBIT_RAM    7
#define CMD_CBIT_RAM    8
#define CMD_XBIT_RAM    9
#define CMD_INC_RAM     10
#define CMD_DEC_RAM     11
#define CMD_SBIT_EE     12
#define CMD_CBIT_EE     13
#define CMD_XBIT_EE     14
#define CMD_INC_EE      15
#define CMD_DEC_EE      16
//------------------------
#define CMD_SEND_Tsk    17
#define CMD_IF_EQ_RAM   18
#define CMD_IF_MA_RAM   19
//------------------------
#define CMD_CPY_R2R     22
#define CMD_CPY_R2E     23
#define CMD_CPY_E2R     24
#define CMD_CPY_E2E     25
#define CMD_IF_EQ_EE    26
#define CMD_IF_MA_EE    27
//------------------------
#define CMD_Dom_OmOff   64
#define CMD_Bind_Stps   65
//------------------------
#define CMD_CONFIRM_TCP 82
#define CMD_Err_Trg_Fnc 83 //El Target no tiene el comando/funcion implementado
#define CMD_RUN_Sch     252
#define CMD_RUN_RgTSK   253
#define CMD_RUN_2TSK    254
//------------------------------------------------------------------------------
typedef struct
{
   unsigned char Ctrl;
   unsigned char IdS;
   unsigned char IdT;
   unsigned char SckS;
   unsigned char SckT;
   unsigned char Len;
   unsigned char Data[256];
}DgvPk;
//------------------------------------------------------------------------------
typedef struct
{
   unsigned char TmpBf[5];
   unsigned char RxSts;
   unsigned int16 RxTOut;
   unsigned char TxSts;
   unsigned int16 TxTOut;
   unsigned char *RxPtr;
   unsigned char *RxLst;
   DgvPk *TxPk;
   DgvPk *RxPk;
}DgvSck;
//------------------------------------------------------------------------------
typedef struct
{
  DgvSck Sck[Lnk_Count];
  unsigned char ID[8];
  unsigned int16 LTRx;
}TS_PDGV;
//------------------------------------------------------------------------------
         void Mk_Response(DgvSck *Sck);
         void InitDgvP(void);
unsigned char IFIDLIST(unsigned char IDT);
unsigned char CalChs(unsigned char* ptr);
         int8 InstTask(unsigned char Task);
//------------------------------------------------------------------------------
         void Pdgv_Osi2(char Data,unsigned char ori);
unsigned char Pdgv_Osi3(DgvSck *Sck);
         void Pdgv_Osi4(DgvSck *Sck);
         void Pdgv_Osi5(DgvSck *Sck);
         void Pdgv_AddCrc(DgvSck *Sck);
         void Pdgv_TxPk(DgvSck *Sck);
         void Pdgv_TxStsMch(DgvSck *Sck,unsigned char ori);
//------------------------------------------------------------------------------
#if((PCB&6)==6)
#define DgvTxBy(x)
#define DgvTxFlush()
#define DgvRxByNoLock(x)
#define DgvRxByLock()
#else
#define DgvTxBy(x)    fputc(x,lnk1);rchr=fgetc(lnk1);if(x!=rchr){SetRed(LED2);}tchr=x
#define DgvTxFlush()
#define DgvRxByNoLock(x)   while(kbhit(lnk1)!=0)x=fgetc(lnk1)
#define DgvRxByLock()   fgetc(lnk1)
#endif

