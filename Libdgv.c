
char Hex2Asc[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

int8 absd(int8 v1)
{
  if (v1&0x80)
    return (0x7F-(v1-0x80));
  else
    return v1;
}

unsigned int8 AbsDiff8(unsigned int8 v1,unsigned int8 v2)
{
  if (v1>v2)
    return(v1 - v2);
  else
    return(v2 - v1);
}

unsigned int16 AbsDiff16(unsigned int16 v1,unsigned int16 v2)
{
  if (v1>v2)
    return(v1 - v2);
  else
    return(v2 - v1);
}

unsigned int8 Diff8(unsigned int8 Lst,unsigned int8 Now)
{
  if (Now>=Lst)
    return(Now - Lst);
  else
    return(Now + (0xFF-Lst)+1);
}

unsigned int16 Diff16(unsigned int16 Lst,unsigned int16 Now)
{
  if (Now>=Lst)
    return(Now - Lst);
  else
    return(Now + (0xFFFF-Lst)+1);
}

unsigned int16 TimeDiff(unsigned int16 LastTime)
{
  if (GetRtc()>=LastTime)
    return(GetRtc() - LastTime);
  else
    return(GetRtc() + (0xFFFF-LastTime)+1);
}

unsigned int32 TimeDiff32(unsigned int32 LastTime)
{
   unsigned int t32;
   GetRtc32(t32);
   if (t32 >= LastTime)
      return(t32 - LastTime);
   else
      return(t32 + 1 + (0xFFFFFFFF - LastTime));
}

void Error(unsigned char ErrorCode)
{
   SetRed(LED2);
   delay_ms(5);
/*   fputc('\n',lnk1);
   fputc('&',lnk1);
   fputc(Hex2Asc[(ErrorCode>>4)&0x0F],lnk1);
   fputc(Hex2Asc[ErrorCode&0x0F],lnk1);
   fputc('\n',lnk1);
   // */
   //write_EEPROM(ErrorCode,(read_EEPROM(ErrorCode)+1));
}

void initUsart(void)
{
}
