#define MemSysPtr (unsigned char)&iGP
#define MaxMemSys sizeof(iGP)

void InitDgvP(void)
{
   unsigned char tmp0=0;
   pdgv=dgvMalloc(sizeof(TS_PDGV));
   memset((void *)pdgv,0,sizeof(TS_PDGV));
   tmp0=read_eeprom(CTRINIe);
   write_eeprom(CTRINIe,(tmp0+1));
   delay_ms(5);
   for(tmp0=0;tmp0<8;tmp0++)
   {
      pdgv->ID[tmp0]=read_eeprom(IDOe+tmp0);
   }
   //pdgv->ID[1]=IDhw;
   tmp0=pdgv->ID[1];
   while(tmp0--)
   {
      restart_wdt();
      delay_ms(250);
      ToggleLed(LED1);
   }
   SetOff(LED1);
}

unsigned char IFIDLIST(unsigned char IDT)
{
   unsigned char tmp0=1;
   while(tmp0<=pdgv->ID[0])
   {
      if(IDT==pdgv->ID[tmp0])
         return tmp0;
      tmp0++;
   }
   return 0;
}

unsigned char CalChs(unsigned char* ptr)
{
   unsigned char CHS=0;
   unsigned char max=CmpLen;
   ptr+=CmpLen;
   max+=*ptr;
   ptr-=CmpLen;
   while(max--)
   {
      CHS^=*ptr;
      ptr++;
   }
   return CHS;
}

void Mk_Response(DgvSck *Sck)
{
   Sck->TxPk->Ctrl=0;//(Sck->RxPk->Ctrl&0x1F);
   Sck->TxPk->IdS=Sck->RxPk->IdT;
   Sck->TxPk->IdT=Sck->RxPk->IdS;
   Sck->TxPk->SckT=Sck->RxPk->SckS;
   Sck->TxPk->SckS=Sck->RxPk->SckT;
}

void Pdgv_AddCrc(DgvSck *Sck)
{
   Sck->TxTOut=0;
   if((Sck->TxPk->Ctrl&pdgv_UDP)==0)
      Sck->TxSts=4;
   else
      Sck->TxSts=1;
   if((Sck->TxPk->Ctrl&pdgv_Chs)==0)
   {
      Sck->TxPk->Ctrl|=pdgv_Chs;
      Sck->TxPk->Data[Sck->TxPk->Len]=0;
      Sck->TxPk->Len++;
      Sck->TxPk->Data[Sck->TxPk->Len-1]=CalChs((unsigned char*)Sck->TxPk);
   }
}

void Pdgv_TxPk(DgvSck *Sck)
{
   unsigned char* ptr;
   unsigned char lnk=0;
   unsigned char max;
   unsigned char tchr;
   unsigned char rchr;
   unsigned char y=0;
   if(Sck->TxPk==0)
      return;
   DgvRxByNoLock(lnk);
   ptr=(unsigned char*)Sck->TxPk;
   //disable_interrupts(GLOBAL);
   SetGreen(LED2);
   DgvTxBy(0x7E);
   DgvTxBy(Sck->TxPk->Ctrl);
   DgvTxBy(Sck->TxPk->IdS);
   DgvTxBy(Sck->TxPk->IdT);
   DgvTxBy(Sck->TxPk->SckS);
   DgvTxBy(Sck->TxPk->SckT);
   DgvTxBy(Sck->TxPk->Len);
   max=Sck->TxPk->Len;
   ptr=&Sck->TxPk->Data[0];
   while(max--)
   {
      DgvTxBy(*ptr);
      ptr++;
   }
   DgvTxFlush();
   SetOff(LED2);
   //enable_interrupts(GLOBAL); 
}

void Pdgv_TxStsMch(DgvSck *Sck,unsigned char ori)
{
   if(Sck->TxPk!=0)
   {
      if((Sck->TxTOut!=0) && (TimeDiff(Sck->TxTOut) < ParmTxTOut))
      {
      }
      else
      {
         Pdgv_TxPk(Sck);
         if(Sck->TxSts!=0)
            Sck->TxSts--;
         if(Sck->TxSts==0)
         {
            dgvFree((unsigned char*)Sck->TxPk);
            Sck->TxPk=0;
            Sck->TxTOut=0;
         }
      }
   }
}

void Pdgv_Osi2(char Data,unsigned char ori)
{
   DgvSck *Sck;
   if(ori>=Lnk_Count)
      return;
    //disable_interrupts(GLOBAL); 
    pdgv->LTRx=GetRtc();
    Sck=&pdgv->Sck[ori];
   if(Sck->RxSts>=Osi3)
   {
      //enable_interrupts(GLOBAL); 
      return;
   }
   //---------------------------------------------------------------------------
   switch(Sck->RxSts)
   {
      case Osi2:
         SetOff(LED2);
         if(Data!=pdgv_Preambulo)
            break;
         Sck->RxTOut=GetRtc();
         Sck->RxSts=Osi2_Ctrl;
         SetGreen(LED2);
      break;
      case Osi2_Ctrl:
         if((0XEB&Data)!=0)
         {
            Sck->RxSts=Osi2;
            Sck->RxTOut=0;
            SetOff(LED2);
            Error(Er_Ctrl);
            break;
         }
         Sck->TmpBf[CmpCtr]=Data;
         Sck->RxSts=Osi2_IdS;
      break;
      case Osi2_IdS:
         Sck->TmpBf[CmpIdS]=Data;
         Sck->RxSts=Osi2_IdT;
      break;
      case Osi2_IdT:
         Sck->TmpBf[CmpIdT]=Data;
         Sck->RxSts=Osi2_SockS;
      break;
      case Osi2_SockS:
         Sck->TmpBf[CmpSkS]=Data;
         Sck->RxSts=Osi2_SockT;
      break;
      case Osi2_SockT:
         Sck->TmpBf[CmpSkT]=Data;
         Sck->RxSts=Osi2_Len;
      break;
      case Osi2_Len:
         if(Data-1>MaxLen)
         {
            Sck->RxSts=Osi2;
            Sck->RxTOut=0;
            SetOff(LED2);
            Error(Er_Len);
            break;
         }
         Sck->RxPk=dgvMalloc(CmpLen+Data+2);
         if(Sck->RxPk==0)
         {
            Sck->RxSts=Osi2;
            Sck->RxTOut=0;
            SetOff(LED2);
            Error(Er_Rx_Mlc);
            break;
         }
         memcpy(Sck->RxPk,Sck->TmpBf,CmpLen);
         Sck->RxPtr=(unsigned char*)Sck->RxPk;
         Sck->RxPtr+=CmpLen;
         Sck->RxPk->Len=Data;
         Sck->RxLst=Sck->RxPtr;
         Sck->RxLst+=Data;
         Sck->RxPtr++;
         Sck->RxSts=Osi2_Datos;
      break;
      case Osi2_Datos:
         *Sck->RxPtr=Data;
         Sck->RxPtr++;
         if(Sck->RxPtr>Sck->RxLst)
         {
            Sck->RxSts=Osi3;
         }
      break;
   }
   //enable_interrupts(GLOBAL);
   return;
}

unsigned char Pdgv_Osi3(DgvSck *Sck)
{
   unsigned char CHS=0;
   CHS=*Sck->RxLst;
   if(CHS!=CalChs((unsigned char*)Sck->RxPk))
   {
      Sck->RxSts=Osi2;
      Sck->RxTOut=0;
      Error(Er_CRC);
      return 0;
   }
   else
   {
      Sck->RxPk->Len--;
   }
   if(Sck->RxPk->IdT==255)
   {
      Sck->RxPk->IdT=pdgv->ID[1];
      Sck->RxPk->Ctrl|=(128|pdgv_UDP);
      return 1;
   }
   CHS=IFIDLIST(Sck->RxPk->IdT);
   if(CHS!=0)
   {
      if(CHS>1)
      {
         Sck->RxPk->IdT=pdgv->ID[1];
         Sck->RxPk->Ctrl|=(128|pdgv_UDP);
      }
      return 1;
   }
   else
   {
      Sck->RxSts=Osi2;
      Sck->RxTOut=0;
      return 0;
   }
}

void Pdgv_Osi4(DgvSck *Sck)
{
   if((Sck->RxPk->Ctrl&pdgv_UDP)!=0)
      return;
   if(Sck->TxPk!=0)
      return;
   //-----------------------------------
   Sck->TxPk=dgvMalloc(7);
   if(Sck->TxPk==0)
      return;
   Mk_Response(Sck);
   Sck->TxPk->Ctrl=(pdgv_UDP);
   Sck->TxPk->SckT='R';
   Sck->TxPk->Len=0;
   Pdgv_AddCrc(Sck);
   delay_ms(2);
   Pdgv_TxPk(Sck);
   dgvFree((unsigned char*)Sck->TxPk);
   Sck->TxPk=0;
   Sck->TxTOut=0;
   //-----------------------------------
}

void Pdgv_Osi5(DgvSck *Sck)
{
   unsigned char cmd=0;
   unsigned char Len=0;
   unsigned char Tmp0=0;
   unsigned char Tmp1=0;
   unsigned char *ptr;
   unsigned char *ptr2;
   cmd=Sck->RxPk->SckT;
   switch(cmd) //Osi6 application
   {
      case CMD_RESET:
      {
         reset_cpu();
      }
      break;
      case CMD_CHG_ID:
      {
         write_eeprom(IDOeI,Sck->RxPk->Data[0]);
         pdgv->ID[1]=Sck->RxPk->Data[0];
      }
      break;
      //-----------------------
      case CMD_PING:
      {
         Len=(sizeof(Version)-1);
         Sck->TxPk=dgvMalloc(Len+7);
         if(Sck->TxPk==0)break;
         Mk_Response(Sck);
         Sck->TxPk->Len=Len;
         strcpy(&Sck->TxPk->Data[0],Version);
      }
      break;
      //-----------------------
      case CMD_WEE:
      {
         Len=Sck->RxPk->Len;
         Len--;
         Tmp0=Sck->RxPk->Data[0];
         ptr=&Sck->RxPk->Data[1];
         while(Len--)
         {
            write_eeprom(Tmp0,*ptr);
            Tmp0++;
            ptr++;
         }
      }
      break;
      case CMD_REE:
      {
         if(Sck->RxPk->Len>1)
         {
            Tmp0=Sck->RxPk->Data[0];
            Len=Sck->RxPk->Data[1];
            Sck->TxPk=dgvMalloc(Len+7);
            if(Sck->TxPk==0)break;
            Mk_Response(Sck);
            Sck->TxPk->Len=Len;
            ptr=&Sck->TxPk->Data[0];
            while(Len--)
            {
               *ptr=read_eeprom(Tmp0);
               Tmp0++;
               ptr++;
            }
         }
         else
         {
            Sck->TxPk=dgvMalloc(8);
            if(Sck->TxPk==0)break;
            Mk_Response(Sck);
            Sck->TxPk->Len=1;
            Sck->TxPk->Data[0]=read_eeprom(Sck->RxPk->Data[0]);
         }
      }
      break;
      case CMD_WRAM:
      {
         Len=Sck->RxPk->Len;
         Len--;
         //if((Sck->RxPk->Data[0]+Len)>MaxMemSys)break;
         ptr=(unsigned char*)MemSysPtr;
         ptr+=Sck->RxPk->Data[0];
         memcpy(ptr,&Sck->RxPk->Data[1],Len);
      }
      break;
      case CMD_RRAM:
      {
         ptr=(unsigned char*)MemSysPtr;
         ptr+=Sck->RxPk->Data[0];
         if(Sck->RxPk->Len>1)
         {
            Len=Sck->RxPk->Data[1];
            Sck->TxPk=dgvMalloc(Len+8);
            if(Sck->TxPk==0)break;
            Mk_Response(Sck);
            Sck->TxPk->Len=Len;
            memcpy(&Sck->TxPk->Data[0],ptr,Len);
         }
         else
         {
            Sck->TxPk=dgvMalloc(8);
            if(Sck->TxPk==0)break;
            Mk_Response(Sck);
            Sck->TxPk->Len=1;
            Sck->TxPk->Data[0]=*ptr;
         }
      }
      break;
      //------------------------
      case CMD_SBIT_RAM:
      case CMD_CBIT_RAM:
      case CMD_XBIT_RAM:
      case CMD_INC_RAM:
      case CMD_DEC_RAM:
      {
         Len=Sck->RxPk->Len;
         Len--;
         //if((Sck->RxPk->Data[0]+Len)>MaxMemSys)break;
         ptr=(unsigned char*)MemSysPtr;
         ptr+=Sck->RxPk->Data[0];
         ptr2=&Sck->RxPk->Data[1];
         while(Len--)
         {
            if(cmd==CMD_SBIT_RAM)
               *ptr|=*ptr2;
            if(cmd==CMD_CBIT_RAM)
               *ptr&=~(*ptr2);
            if(cmd==CMD_XBIT_RAM)
               *ptr^=*ptr2;
            if(cmd==CMD_INC_RAM)
               *ptr+=*ptr2;
            if(cmd==CMD_DEC_RAM)
               *ptr-=*ptr2;
            ptr++;
            ptr2++;
         }
      }
      break;
      //------------------------
      case CMD_SBIT_EE:
      case CMD_CBIT_EE:
      case CMD_XBIT_EE:
      case CMD_INC_EE:
      case CMD_DEC_EE:
      {
         Len=Sck->RxPk->Len;
         Len--;
         Tmp1=Sck->RxPk->Data[0];
         ptr=&Sck->RxPk->Data[1];
         while(Len--)
         {
            Tmp0=read_eeprom(Tmp1);
            if(cmd==CMD_SBIT_EE)
               Tmp0|=*ptr;
            if(cmd==CMD_CBIT_EE)
               Tmp0&=~(*ptr);
            if(cmd==CMD_XBIT_EE)
               Tmp0^=*ptr;
            if(cmd==CMD_INC_EE)
               Tmp0+=*ptr;
            if(cmd==CMD_DEC_EE)
               Tmp0-=*ptr;
            write_eeprom(Tmp1,Tmp0);
            Tmp1++;
            ptr++;
         }
      }
      break;
      //------------------------
      case CMD_SEND_Tsk:
      {
         Tmp0=Sck->RxPk->Data[1];      //ADDRES
         Sck->TxPk=dgvMalloc(9);
         if(Sck->TxPk==0)break;
         memset((void *)Sck->TxPk,0,9);
         Mk_Response(Sck);
         Sck->TxPk->IdT=Sck->RxPk->Data[0];          //target
         Sck->TxPk->SckS='R';
         Sck->TxPk->SckT=read_eeprom(Tmp0);
         Sck->TxPk->Len=2;
         Sck->TxPk->Data[0]=read_eeprom(Tmp0+1);
         Sck->TxPk->Data[1]=read_eeprom(Tmp0+2);
      }
      break;
      //------------------------
      case CMD_IF_EQ_RAM:
      case CMD_IF_MA_RAM:
      {
         ptr=(unsigned char*)MemSysPtr;
         ptr2=(unsigned char*)MemSysPtr;
         ptr+=Sck->RxPk->Data[0];
         ptr2+=Sck->RxPk->Data[1];
         Tmp0=Sck->RxPk->Data[2];
         if(cmd==CMD_IF_MA_RAM)
         {
            if(*ptr>*ptr2)
            {
               Tmp0+=3;
            }
            else
            {
               Tmp0+=6;
            }
         }
         else
         {
            if(*ptr==*ptr2)
            {
               Tmp0+=3;
            }
            else
            {
               Tmp0+=6;
            }
         }
         InstTask(Tmp0);
      }
      break;
      //------------------------
      case CMD_CPY_R2R:
      {
         ptr=(unsigned char*)MemSysPtr;
         ptr2=(unsigned char*)MemSysPtr;
         ptr+=Sck->RxPk->Data[0];
         ptr2+=Sck->RxPk->Data[1];
         *ptr2=*ptr;
      }
      break;//*/
      //------------------------
      case CMD_CPY_R2E:
      {
         ptr=MemSysPtr;
         ptr+=Sck->RxPk->Data[0];
         write_eeprom(Sck->RxPk->Data[1],*ptr);
      }
      break;// */
      //------------------------
      case CMD_CPY_E2R:
      {
         ptr=(unsigned char*)MemSysPtr;
         ptr+=Sck->RxPk->Data[1];
         *ptr=read_eeprom(Sck->RxPk->Data[0]);
      }
      break;// */
      //------------------------
      case CMD_CPY_E2E:
      {
         write_eeprom(Sck->RxPk->Data[1],read_EEPROM(Sck->RxPk->Data[0]));
      }
      break;// */
      //------------------------
      case CMD_IF_EQ_EE:
      case CMD_IF_MA_EE:
      {
         Tmp0=read_eeprom(Sck->RxPk->Data[0]);
         Tmp1=read_eeprom(Sck->RxPk->Data[1]);
         Len=Sck->RxPk->Data[2];
         if(cmd==CMD_IF_MA_EE)
         {
            if(Tmp0>Tmp1)
            {
               Len+=3;
            }
            else
            {
               Len+=6;
            }
         }
         else
         {
            if(Tmp0==Tmp1)
            {
               Len+=3;
            }
            else
            {
               Len+=6;
            }
         }
         InstTask(Len);
      }
      break;// */
      //------------------------
      case CMD_Dom_OmOff:
      {
         Len=Sck->RxPk->Len;
         ptr2=&Sck->RxPk->Data[0];
         while(Len--)
         {
            //if(*ptr2!=255)
            if(*ptr2>=(*(unsigned char*)&iGP.IOs[0]) && *ptr2<=(*(unsigned char*)&iGP.IOs[IOs_Count-1]))
            {
               ptr=(unsigned char*)MemSysPtr;
               ptr+=*ptr2;
               if((*ptr&127)>64)
                  *ptr=0;
               else
                  *ptr=127;
               ptr2++;
            }
         }
      }
      break;
      //------------------------
      case CMD_Bind_Stps:
      {
         ptr=(unsigned char*)MemSysPtr;
         ptr+=Sck->RxPk->Data[0];   //posicion de memroria de relay
         ptr2=(ptr+2);
         Tmp1=AbsDiff8(*ptr,*ptr2);
         Tmp0=absd((signed int8)Sck->RxPk->Data[1]);   //valor abs
         //fprintf(lnk1,"[%u]>[%u]",Tmp0,Tmp1);
         if(Tmp0>Tmp1)
         {
            Tmp0=Sck->RxPk->Data[1];
            Tmp1=*ptr+((signed int8)Tmp0);
            if(0<(signed int8)Tmp0)
            {
               if(Tmp1>126)
                  break;
            }
            else
            {
               if(Tmp1<2)
                  break;
            }
            *ptr=*ptr2+((signed int8)Tmp0);
         }
      }
      break; // */
      //------------------------
      case CMD_CONFIRM_TCP:
      {
         if(Sck->TxPk!=0)
         {
            dgvFree((unsigned char*)Sck->TxPk);
            Sck->TxPk=0;
            Sck->TxTOut=0;
            Sck->TxSts=0;
         }
         if(iSck.TxPk!=0)
         {
            dgvFree((unsigned char*)iSck.TxPk);
            iSck.TxPk=0;
            iSck.TxTOut=0;
            iSck.TxSts=0;
         }
      }
      break;
      //------------------------
      case CMD_RUN_RgTSK:
      {
         Tmp0=Sck->RxPk->Data[0];
         Tmp1=Sck->RxPk->Data[1];
         if(Tmp0>Tmp1)
         {
            Len=Tmp0;
            Tmp0=Tmp1;
            Tmp1=Len;
         }
         if((Tmp1-Tmp0)<=21)
         {
            while(Tmp0<=Tmp1)
            {
               InstTask(Tmp0);
               Tmp0+=3;
            }
         }
      }
      break;//*/
      //------------------------
      case CMD_RUN_2TSK:
      {
         InstTask(Sck->RxPk->Data[0]);
         InstTask(Sck->RxPk->Data[1]);
      }
      break;
      //------------------------ */
      default:
      {
            Sck->TxPk=dgvMalloc(7);
            if(Sck->TxPk==0)break;
            Mk_Response(Sck);
            Sck->TxPk->Len=0;
            Sck->TxPk->SckT=83;
      }
      break;
   }
   if(Sck->TxPk!=0)
   {
      Sck->TxPk->Ctrl|=pdgv_UDP;
      Pdgv_AddCrc(Sck);
      /*
      if(Sck->RxPk->Ctrl&128)
      {
         Tmp0=pdgv->ID[1];
         while(Tmp0--)
         {
            restart_wdt();
            delay_ms(5);
         }
      }
      // */
      delay_ms(1);
   }
}

