//#include <18F14K22.h>
#include <18F25K20.h>
#include "eeprom.h"
#include "Libdgv.h"
#include "DgvH.h"
#include "DgvP.h"
#include "main.h"
//#ignore_warnings 216
//-------------------
#define DgvTask 1
//-------------------
TS_DGV_OS iGP;
DgvSck iSck;
TS_PDGV *pdgv;
//------------------------
unsigned char RBsts=0;
//------------------------
#INT_TIMER0
void Tmr0_fnc(void) //RTC for TimeOuts
{
   clear_interrupt(INT_TIMER0);
} 

#INT_TIMER1
void Tmr1_fnc(void) //Rx2_Control
{
   clear_interrupt(INT_TIMER1);
   Set_timer1(0x00FF);
}

#INT_TIMER2
void Tmr2_fnc(void) 
{
   clear_interrupt(INT_TIMER2);
   Set_timer2(0);
}

#INT_TIMER3
void Tmr3_fnc(void) //Diming control
{
   Set_timer3(25500);
/*   if(pTmrs->OverFlowEv!=0)
   {
      if(pTmrs->TmpCount1==0)
      {
         pTmrs->TmpCount1=pTmrs->Prescale;
         if(pTmrs->TmpCount2==0)
         {
            InstTask(pTmrs->OverFlowEv);
         }
         pTmrs->TmpCount2++;
      }
      pTmrs->TmpCount1--;
   }
   pTmrs++;
   if(pTmrs>&iGP.Tmrs[Tmrs_Count-1])
      pTmrs=&iGP.Tmrs[0];*/
} 

#INT_EXT
void IntExt(void)
{
   ext_int_edge(0,L_TO_H);
   clear_interrupt(INT_EXT);
   INT0IF = FALSE;
    enable_interrupts(INT_EXT);
}

#INT_RB
void SerialRx2(void) 
{
   unsigned char iRBsts=0;
   iRBsts=PORTB;
   RBsts=iRBsts;
   clear_interrupt(INT_RB);
}

#INT_AD
void AnalogIn(void) 
{
   iGP.IOs[iGP.AdChl].Value=read_adc(ADC_READ_ONLY);
}

void main(void)
{
   //--------------------------------------------------------------------------- Init
   disable_interrupts(GLOBAL);
   //setup_oscillator(OSC_16MHZ|OSC_INTRC);//OSC_PLL_ON
   //OSCCON   =(OSC_16MHZ|OSC_INTRC);
   //OSCTUNE  =(0x40);
   //while((OSCCON&OSC_STATE_STABLE)==0);
   //while((OSCCON&OSC_STATE_EXT_RUNNING)!=0);
   //--------------------------------------------------------------------------- Declare Vars of Main
   DgvSck *Sck;
   TS_IOs *pIOs;
   TS_Srv_Stk *pSvr;
   TS_Tmrs *pTmrs;
   unsigned int16  countReadin  =0;   // Global temp var 8bit
   unsigned int8  Idx   =0;   // Main Counter
   unsigned int8  Tmp8  =0;   // Global temp var 8bit
   unsigned int8  Tmp8b =0;   // Global temp var 8bit
   unsigned int16 Tmp16 =0;   // Global temp var 16bit
   unsigned int16 IOsts =0;   // Global temp var 16bit
   restart_wdt();
   //--------------------------------------------------------------------------- Init Hws, Interrupts, Drvs, Structs
   {
      SET_TRIS_A(0xFF);//0xE0
      PORTA =  0;
      
      ANSELH = 0x00;
      PORTB =  0;
      SET_TRIS_B(0xFF);
      WPUB=0xFF;
      
      SET_TRIS_C(0x80);
      PORTC =  0;

      //SET_TRIS_D(0xFF);
      //PORTD =  0;

      SET_TRIS_E(0xFF);
      PORTE =  0;
      //--------------------------------
      bit_clear(INTCON2,0);
      //--------------------------------
      ANSEL  = 0x80;//setup_adc_ports(RC3_RC6_ANALOG);
      ANSELH = 0x01; 
   }
   //--------------------------------------------------------------------------- Clear and SetUp HW
   {
      clear_interrupt(INT_EXT);
      clear_interrupt(INT_RDA);
      clear_interrupt(INT_RB);
      clear_interrupt(INT_AD);
      clear_interrupt(INT_TIMER0);
      clear_interrupt(INT_TIMER1);
      clear_interrupt(INT_TIMER2);
      clear_interrupt(INT_TIMER3);
      //--------------------------------
      setup_adc(ADC_CLOCK_INTERNAL);
      setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);      // RTCC_DIV_2, RTCC_DIV_4, RTCC_DIV_8, RTCC_DIV_16,RTCC_DIV_32,RTCC_DIV_64,RTCC_DIV_128,RTCC_DIV_256
      setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);         // T1_DIV_1, T1_DIV_2, T1_DIV_4, T1_DIV_8
      //setup_timer_2(T2_DIV_BY_16,0,1);                // T2_DIV_1, T2_DIV_2, T2_DIV_4, T2_DIV_8, T2_DIV_16
      setup_timer_3(T3_INTERNAL|T3_DIV_BY_1);         // T3_DIV_1, T3_DIV_2, T3_DIV_4, T3_DIV_8
      //setup_comparator(NC_NC_NC_NC);                  // This device COMP currently not supported by the PICWizard
      restart_wdt();
      //--------------------------------
      output_low(LEDC);
      input(LED1);
      input(LED2);
      input(LED3);
   }
   //--------------------------------------------------------------------------- Init Structures
   {
      restart_wdt();
      initUsart();
      InitDgvHeap();
      restart_wdt();
      InitDgvP();
      restart_wdt();
      memset(&iGP,0,sizeof(TS_DGV_OS));
      memset(&iSck,0,sizeof(DgvSck));
      //-------------------------------- Inicializacion de IOs dedicados
      //-------------------------------- Inicializacion de entradas Analogicas
      //-------------------------------- Inicializacion de entradas Digitales
      Tmp16=read_EEPROM(In_Neg);
      Tmp16<<=8;
      Tmp16=read_EEPROM(In_NegH);
      IOsts=read_EEPROM(In_typ_sate);
      IOsts<<=8;
      IOsts|=read_EEPROM(In_typ_sateH);
      pIOs=&iGP.IOs[0];
      for(Idx=0;Idx<IOs_Pins;Idx++)  //Entradas 
      {
         pIOs->Flags=IO_Flg_Typ_In;
         if((IOsts&1)!=0)
            pIOs->Flags=IO_Flg_Typ_InD;
         if((Tmp16 &1)!=0)
            pIOs->Flags|=IO_Flg_Neg;
         pIOs->HigEvt=read_EEPROM(IO_02_Hold_Ev+(Idx<<1));
         pIOs->LowEvt=read_EEPROM(IO_02_Tap_Ev+(Idx<<1));
         pIOs++;
         Tmp16>>=1;
         IOsts>>=1;
      }
      //-------------------------------- 
      restart_wdt();
      //--------------------------------  Inicializacion de Logical Timers
      pTmrs=&iGP.Tmrs[0];
      for(Tmp8=0;Tmp8<Tmrs_Count;Tmp8++)
      {
         pTmrs->Prescale=read_EEPROM(TIMER1_Ps+(Tmp8<<1));
         pTmrs->TmpCount1=pTmrs->Prescale;
         pTmrs->TmpCount2=pTmrs->Prescale;
         pTmrs->OverFlowEv=read_EEPROM(TIMER1_Ev+(Tmp8<<1));
         //pTmrs->Iterations=read_EEPROM(ITERATIONS+(Tmp8<<1));
         pTmrs++;
      }
      restart_wdt();
      //--------------------------------  Inicializacion de Servicios
      iGP.Srv[Hw_Tmrs].ConstTime=429;
      iGP.Srv[Hw_Read_INP].ConstTime=63;
      iGP.Srv[Hw_Procc_INP].ConstTime=1953;//3906;//(125*31,25);
      iGP.Srv[Hw_ADC].ConstTime=31250;
      //--------------------------------*/
   }
   //--------------------------------------------------------------------------- Start Interrups
   {
      iGP.AdChl=0;
      set_adc_channel(7);
      delay_us(20);
      read_adc(ADC_START_ONLY);
      restart_wdt();
      //--------------------------------
      switch ( restart_cause() )
      {
         case WDT_TIMEOUT:
         {
           Error(Er_WDT);
         }
      }
      //--------------------------------
      //enable_interrupts(INT_RDA);
      //enable_interrupts(INT_AD);
      //enable_interrupts(INT_RA);
      //enable_interrupts(INT_RB);
      //enable_interrupts(INT_TIMER0);
      //enable_interrupts(INT_TIMER1);
      //enable_interrupts(INT_TIMER2);
      //enable_interrupts(INT_TIMER3);
      RBIE=TRUE;               //BUG al querer usar INT_RA..setea TODO IOCB en lugar de solo RABIE. DECLARADO MANUALMENTE
      INTCON|=0x08;
      INTCON&=~0x01;
      IOCB=0xF0;
      enable_interrupts(GLOBAL); 
      //--------------------------------
   }
   InstTask(read_EEPROM(Start_Ev));
   //--------------------------------------------------------------------------- */
   while(true)
   {
      countReadin++;
      restart_wdt();
      //======================================================================== Dgv Protocolo v1
      {
         while(kbhit(lnk1)!=0)
         {
            Pdgv_Osi2(fgetc(lnk1),(lnk1-1));
         }// */
         /*while(kbhit(lnk2)!=0)
         {
            Pdgv_Osi2(fgetc(lnk2),(lnk2-1));
         }// */
         for(Idx=0;Idx<Lnk_Count;Idx++)
         {
            Sck=&pdgv->Sck[Idx];
            if(Sck->RxSts>=Osi3)
            {
               if(Pdgv_Osi3(Sck))
               {
                  SetOff(LED1);
                  Pdgv_Osi4(Sck);
                  Pdgv_Osi5(Sck);
               }
               if(Sck->RxPk!=0)
               {
                  dgvFree((unsigned char*)Sck->RxPk);
                  Sck->RxPk=0;
               }
               Sck->RxTOut=0;
               Sck->RxSts=Osi2;
               SetOff(LED1);
               SetOff(LED1);
            }
            else
            {
               if(Sck->RxSts!=Osi2 && Sck->RxTOut!=0 && TimeDiff(Sck->RxTOut)>ParmRxTOut)
               {
                  if(Sck->RxPk!=0)
                  {
                     dgvFree(Sck->RxPk);
                     Sck->RxPk=0;
                  }
                  SetOff(LED1);
                  Error(Er_TimOut);
                  Sck->RxSts=Osi2;
                  Sck->RxTOut=0;
               }
            }
            Pdgv_TxStsMch(Sck);
         }
      }
      restart_wdt();
      //======================================================================== Hw Inputs,Proc inputs, Tmrs Producto
      {
         pSvr=&iGP.Srv[0];
         for(Idx=0;Idx<Svr_Count;Idx++)
         {
            if((pSvr->ConstTime>0 && TimeDiff(pSvr->LastTime)>pSvr->ConstTime))
            {
               pSvr->LastTime=get_timer0();
               switch(Idx)
               {
                  case Hw_Read_INP:
                  {
                     IOsts=GetInputs();
                     pIOs=&iGP.IOs[0];
                     for(Tmp8=0;Tmp8<IOs_Pins;Tmp8++)
                     {
                        switch((pIOs->Flags&0x07))
                        {
                           case IO_Flg_Typ_In:
                           case IO_Flg_Typ_InD:
                           {
                              if(bit_test(IOsts,Tmp8))
                              {
                                 //bit_set(pIOs->Flags,3);
                                 pIOs->Flags|=IO_Flg_Sts;
                              }
                              else
                              {
                                 //bit_clear(pIOs->Flags,3);
                                 pIOs->Flags&=~IO_Flg_Sts;
                              }
                              //-----------------------------
                              if((pIOs->Flags&IO_Flg_Neg)!=0)
                              {
                                 pIOs->Flags^=IO_Flg_Sts;
                              }
                              //-----------------------------
                              if((pIOs->Flags&IO_Flg_Sts)!=0)
                              {
                                 if(pIOs->Value < 255)
                                    pIOs->Value++;
                                 if((pIOs->Flags&7)==IO_Flg_Typ_InD)
                                    pIOs->LstVal=pIOs->Value;
                              }
                              else
                              {
                                 if(pIOs->Value > 0)
                                    pIOs->Value--;
                                 if((pIOs->Flags&7)==IO_Flg_Typ_InD)
                                    pIOs->Value=0;
                              }
                           }
                           break;
                        }
                        pIOs++;
                     }
                  }
                  break;
                  case Hw_Procc_INP:
                  {
                     for(Tmp8=0;Tmp8<10;Tmp8++)
                     {
                        pIOs=&iGP.IOs[Tmp8];
                        switch((pIOs->Flags&0x07))
                        {
                           case IO_Flg_Typ_In:
                           {
                              Tmp8b=AbsDiff8(pIOs->LstVal,pIOs->Value);
                              if(Tmp8b>15)
                              {
                                 Tmp8b=pIOs->Value;
                                 if(pIOs->LstVal<Tmp8b)
                                 {
                                    if((pIOs->Flags&IO_Flg_LSts)==0)
                                    {
                                       //bit_set(pIOs->Flags,7);
                                       pIOs->Flags|=IO_Flg_LSts;
                                       InstTask(pIOs->HigEvt);
                                    }
                                 }
                                 else
                                 {
                                    if((pIOs->Flags&IO_Flg_LSts)!=0)
                                    {
                                       //bit_clear(pIOs->Flags,7);
                                       pIOs->Flags&=~IO_Flg_LSts;
                                       InstTask(pIOs->LowEvt);
                                    }
                                 }
                                 pIOs->LstVal=Tmp8b;
                              }
                           }
                           break;
//                           case IO_Flg_Typ_InAC:
//                           break;
//                           case IO_Flg_Typ_InAV:
//                           break;
                           case IO_Flg_Typ_InD:
                           {
                              if((pIOs->Flags&IO_Flg_Sts)!=0)
                              {
                                 if(pIOs->Value>250)                                //Event Long Press
                                 {
                                    InstTask(pIOs->HigEvt);
                                 }
                              }
                              else
                              {
                                 pIOs->LstVal-=pIOs->Value;
                                 if((pIOs->LstVal>10) && (pIOs->LstVal<200))        //Event Short Press
                                 {
                                    InstTask(pIOs->LowEvt);
                                 }
                                 pIOs->LstVal=0;
                              }
                           }
                           break;
                        }
                     }
                  }
                  break;
                  case Hw_Tmrs:
                  {
                     pTmrs=&iGP.Tmrs[0];
                     for(Tmp8=0;Tmp8<Tmrs_Count;Tmp8++)
                     {
                        if(pTmrs->OverFlowEv!=0 && pTmrs->TmpCount1!=0)
                        {
                           pTmrs->TmpCount1--;
                           if(pTmrs->TmpCount1==0)
                           {
                              pTmrs->TmpCount1=pTmrs->Prescale;
                              pTmrs->TmpCount2--;
                              if(pTmrs->TmpCount2==0)
                              {
                                 pTmrs->TmpCount2=pTmrs->Prescale;
                                 InstTask(pTmrs->OverFlowEv);
                              }
                           }
                        }
                        else
                        {
                           pTmrs->TmpCount2=pTmrs->Prescale;
                        }
                        pTmrs++;
                     }
                  }
                  break;
                  case Hw_ADC:
                  {
                     set_adc_channel(iGP.AdChl+7);
                     delay_us(20);
                     iGP.AdChl++;
                     if(iGP.AdChl>1)
                        iGP.AdChl=0;
                     read_adc(ADC_START_ONLY);
                  }
                  break;// */
               }
            }
            pSvr++;
         }
      }
      restart_wdt();
      //======================================================================== Dgv Kernel
      {
         Idx=0;
         while(Idx<Events_Count && (iSck.TxPk==0))   // procesa tareas internas hasta que txpk sea diferente de 0
         {
            Tmp8=iGP.Events[Idx];
            if(Tmp8>=LsEventos && Tmp8<=Task1)
            {
               iSck.RxPk=dgvMalloc(9);
               iSck.RxPk->Ctrl   =read_EEPROM(Kdgv_Ctrl);
               iSck.RxPk->IdS    =read_EEPROM(Kdgv_IdS);
               iSck.RxPk->IdT    =pdgv->ID[1];
               iSck.RxPk->SckS   =read_EEPROM(Tmp8);
               iSck.RxPk->SckT   =iSck.RxPk->SckS;
               iSck.RxPk->Len    =2;
               iSck.RxPk->Data[0]=read_EEPROM(Tmp8+1);
               iSck.RxPk->Data[1]=read_EEPROM(Tmp8+2);
               iSck.RxPk->Data[2]=Tmp8;
               output_high(LED1);
               Pdgv_Osi5(&iSck);
               {
                  dgvFree(iSck.RxPk);
                  iSck.RxPk=0;
                  iSck.RxTOut=0;
                  iSck.RxSts=0;
               }
               iGP.Events[Idx]=0;
               Idx=0;
            }
            else
            {
               iGP.Events[Idx]=0;
               Idx++;
            }
         }
         input(LED1);
         Pdgv_TxStsMch(&iSck);
      }
      restart_wdt();
      //======================================================================== Driver Hw Outputs
      {
         pIOs=&iGP.IOs[0];
         for(Tmp8=0;Tmp8<IOs_Count;Tmp8++)    //escribe todas las salidas
         {
            switch((pIOs->Flags&IO_Flg_Typ_Msk))
            {
               //------------------------------------
               case IO_Flg_Typ_Out:                   //tipo de salida On/Off
               {
                  if((pIOs->Flags&IO_Flg_Sts)==0)
                     pIOs->LstVal=pIOs->Value;
                  if((pIOs->LstVal)!=0)
                  {
                     SetOutput(Tmp8,1);
                  }
                  else
                  {
                     SetOutput(Tmp8,0);
                  }
               }
               break;
               //------------------------------------
            }
            pIOs++;
         }
      }
      //======================================================================== Driver Hw Outputs
   }
}

unsigned short GetInputs(void)
{
   unsigned short sts=0;
   sts|=input_state(GPIO00)<<0;
   sts|=input_state(GPIO01)<<1;
   sts|=input_state(GPIO02)<<2;
   sts|=input_state(GPIO03)<<3;
   sts|=input_state(GPIO04)<<4;
   sts|=input_state(GPIO05)<<5;
   sts|=input_state(GPIO06)<<6;
   sts|=input_state(GPIO07)<<7;
   sts|=input_state(GPIO08)<<8;
   sts|=input_state(GPIO09)<<9;
   sts|=input_state(GPIO10)<<10;
   sts|=input_state(GPIO11)<<11;
   sts|=input_state(GPIO12)<<12;
   sts|=input_state(GPIO13)<<13;
   sts|=input_state(GPIO14)<<14;
   sts|=input_state(GPIO15)<<15;
   return sts;
}

void SetOutput(unsigned char Out,unsigned char value)
{
   if(Out==0)output_bit(GPIO00,value);
   if(Out==1)output_bit(GPIO01,value);
   if(Out==2)output_bit(GPIO02,value);
   if(Out==3)output_bit(GPIO03,value);
   if(Out==4)output_bit(GPIO04,value);
   if(Out==5)output_bit(GPIO05,value);
   if(Out==6)output_bit(GPIO06,value);
   if(Out==7)output_bit(GPIO07,value);
   if(Out==8)output_bit(GPIO08,value);
   if(Out==9)output_bit(GPIO09,value);
   if(Out==10)output_bit(GPIO10,value);
   if(Out==11)output_bit(GPIO11,value);
   if(Out==12)output_bit(GPIO12,value);
   if(Out==13)output_bit(GPIO13,value);
   if(Out==14)output_bit(GPIO14,value);
   if(Out==15)output_bit(GPIO15,value);
}

#if (DgvTask!=0)
int8 InstTask(unsigned char Task)
{
   char Idx=0;
   if(Task<LsEventos || Task>Task1)
      return -1;
   for(Idx=0;Idx<Events_Count;Idx++)
   {
      if(iGP.Events[Idx]==Task)
         return Idx;
   }
   for(Idx=0;Idx<Events_Count;Idx++)
   {
      if(iGP.Events[Idx]==0)
      {
         iGP.Events[Idx]=Task;
         return Idx;
      }
   }
   Error(Er_NoEvtFree);
   return -1;
}
#endif
//==============================================================================
#include "DgvP.c"
//==============================================================================
#include "DgvHeap.c"
//==============================================================================  
#include "EeData.c"
//==============================================================================
#include "Libdgv.c"

