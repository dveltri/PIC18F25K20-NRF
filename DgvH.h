#define configTOTAL_HEAP_SIZE 1024 //(768) SI SE BAJA MUCHO NO PUEDE CONFORMAR LA RESPUESTA DE 64BYTE
#define EnShwMem 0
//------------------------------------------------------------------------------------------------
void InitDgvHeap(void);
void *dgvMalloc(unsigned int16 xWantedSize);
void dgvFree(unsigned char *puc );
#if EnShwMem
void ShwMem(void);
unsigned char ChkMem(void);
#endif
//------------------------------------------------------------------------------------------------
#define malloc dgvMalloc
#define free dgvFree

