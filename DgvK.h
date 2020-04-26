typedef enum
{
rt_OkZeroLen=0,
rt_Ok_Len,
rt_NoPermisos,
rt_Error,
rt_OOR,//(Out Of Range)
rt_ESize
}enum_pdgvcmd_response;

//------------------------------------------------------------------------------  comandos generales
typedef enum
{
Pdgv_inf,
Pdgv_login,
Pdgv_reset,
Pdgv_mesh,
//------------------------------------------------------------------------  comandos sobre ram
Ram_R_Byts,
Ram_W_Byts,
Ram_ADD_Byt,
Ram_SUB_Byt,
Ram_MOD_Byt,
Ram_BSHU_Byt,
Ram_BSHD_Byt,
Ram_BAND_Byt,
Ram_B_OR_Byt,
Ram_BCLR_Byt,
Ram_BXOR_Byt,
//------------------------------------------------------------------------  comandos sobre IO-pines
Port_R_Byt,
Port_W_Byt,
Port_ADD_Byt,
Port_SUB_Byt,
Port_MOD_Byt,
Port_BSHU_Byt,
Port_BSHD_Byt,
Port_BAND_Byt,
Port_B_OR_Byt,
Port_BCLR_Byt,
Port_BXOR_Byt,
//------------------------------------------------------------------------ Registros internos del CPU
Cpu_R_Ints,
Cpu_W_Ints,
Cpu_ADD_Byt,
Cpu_SUB_Byt,
Cpu_MOD_Byt,
Cpu_BSHU_Byt,
Cpu_BSHD_Byt,
Cpu_BAND_Byt,
Cpu_B_OR_Byt,
Cpu_BCLR_Byt,
Cpu_BXOR_Byt,
//------------------------------------------------------------------------ comando sobre parametros de PLC
Plc_CMDs,
Plc_vars_R, 
Plc_vars_W,
Plc_vars_ADD,
Plc_vars_SUB,
Plc_vars_MOD,
Plc_vars_BSHU,
Plc_vars_BSHD,
Plc_vars_BAND,
Plc_vars_B_OR,
Plc_vars_BCLR,
Plc_vars_BXOR,
//------------- Accesos al sistema de archivos
Svr_file
//-------------
}enum_cmd_pdgv;
//------------------------------------------------------------------------------
typedef struct
{
   unsigned char StkIdx;
   unsigned char PC[4];
}TS_KDGV;
