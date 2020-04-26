typedef struct A_BLOCK_LINK
{
   struct A_BLOCK_LINK *pxNextFreeBlock;
   unsigned int16 xBlockSize;
} xBlockLink;
#define heapSTRUCT_SIZE sizeof(xBlockLink)
#define heapMINIMUM_BLOCK_SIZE  (heapSTRUCT_SIZE+1)
//---------------------------------
static xBlockLink xStart;
static union DGV_HEAP
{
   unsigned char Heap[ configTOTAL_HEAP_SIZE ];
} HDGV;
static xBlockLink xEnd;
//------------------------------------------------------------------------------------------------
void InitDgvHeap()
{
      xBlockLink *pxFirstFreeBlock;
      memset(HDGV.Heap,0,configTOTAL_HEAP_SIZE);
      xStart.pxNextFreeBlock = ( void * ) HDGV.Heap;
      xStart.xBlockSize = 0;
      xEnd.xBlockSize = (configTOTAL_HEAP_SIZE+1);
      xEnd.pxNextFreeBlock = 0;
      pxFirstFreeBlock = ( void * ) HDGV.Heap;
      pxFirstFreeBlock->xBlockSize = configTOTAL_HEAP_SIZE;
      pxFirstFreeBlock->pxNextFreeBlock = &xEnd;
#if EnShwMem
      ShwMem();
#endif
}

void prvInsertBlockIntoFreeList(unsigned char *ptr)
{
   xBlockLink *pxBlockToInsert;
   xBlockLink *pxIterator;
   //--------------------------
   pxBlockToInsert=(xBlockLink *)ptr;
   pxIterator = &xStart;
   while((pxIterator != &xEnd) && (pxIterator->pxNextFreeBlock < pxBlockToInsert))
   {
      pxIterator = pxIterator->pxNextFreeBlock;
   }
   if(pxIterator != &xEnd)
   {
      if(pxIterator->pxNextFreeBlock > pxBlockToInsert)
      {
         pxBlockToInsert->pxNextFreeBlock = pxIterator->pxNextFreeBlock;
         pxIterator->pxNextFreeBlock = pxBlockToInsert;
      }
   }
}

void *dgvMalloc(unsigned int16 xWantedSize)
{
   xBlockLink *pxBlock, *pxPreviousBlock, *pxNewBlockLink;
   unsigned char *ptr = 0;
   //----------------------------------------------------------
   if((xWantedSize==0) || (xWantedSize >= configTOTAL_HEAP_SIZE ))
      return 0;
   disable_interrupts(GLOBAL);
   xWantedSize += heapSTRUCT_SIZE;
   pxPreviousBlock = &xStart;
   pxBlock = &xEnd;
   ptr = (unsigned char *)&xStart;
   pxNewBlockLink = xStart.pxNextFreeBlock;
   //----------------------------------------------------------
   while(pxNewBlockLink != &xEnd)
   {
      if((pxNewBlockLink->xBlockSize > xWantedSize) && (pxBlock->xBlockSize > pxNewBlockLink->xBlockSize))
      {
         pxPreviousBlock = (xBlockLink *)ptr;
         pxBlock = pxNewBlockLink;
      }
      ptr = (unsigned char *)pxNewBlockLink;
      pxNewBlockLink = pxNewBlockLink->pxNextFreeBlock;
   }
   //----------------------------------------------------------
   if(pxBlock != &xEnd)
   {
      pxPreviousBlock->pxNextFreeBlock = pxBlock->pxNextFreeBlock;
      if( (pxBlock->xBlockSize - xWantedSize) > heapMINIMUM_BLOCK_SIZE )
      {
         ptr=(unsigned char *)pxBlock;
         ptr+=xWantedSize;
         pxNewBlockLink=(xBlockLink *)ptr;
         pxNewBlockLink->xBlockSize = (pxBlock->xBlockSize - xWantedSize);
         pxBlock->xBlockSize = xWantedSize;
         prvInsertBlockIntoFreeList((unsigned char *)pxNewBlockLink);
      }
      ptr = (unsigned char *)pxBlock;
      ptr+= heapSTRUCT_SIZE;
   }
   else
   {
        //LOG("No memoria\n");
        ptr = 0;
   }
   //----------------------------------------------------------
   enable_interrupts(GLOBAL); 
   return ptr;
}

void dgvFree(unsigned char *puc )
{
   xBlockLink *pxLink;
   if( puc != 0 )
   {
      puc -= heapSTRUCT_SIZE;
      disable_interrupts(GLOBAL);
      prvInsertBlockIntoFreeList(puc);
      //--------------------------------
      pxLink = xStart.pxNextFreeBlock;
      puc=(unsigned char *)pxLink;
      while(pxLink->pxNextFreeBlock!=&xEnd)
      {
         puc+=pxLink->xBlockSize;
         if(puc==((unsigned char *)pxLink->pxNextFreeBlock))
         {
            pxLink->xBlockSize+=pxLink->pxNextFreeBlock->xBlockSize;
            pxLink->pxNextFreeBlock=pxLink->pxNextFreeBlock->pxNextFreeBlock;
            puc=(unsigned char *)pxLink;
         }
         else
         {
            pxLink=pxLink->pxNextFreeBlock;
            puc=(unsigned char *)pxLink;
         }
      }
      enable_interrupts(GLOBAL); 
   }
}

#if EnShwMem
unsigned char ChkMem(void)
{
  xBlockLink *pxLink;
  pxLink = xStart.pxNextFreeBlock;
  while(pxLink<&xEnd)// && pxLink>&xStart)
  {
      pxLink=pxLink->pxNextFreeBlock;
  }
  if(pxLink>&xEnd || pxLink<&xStart)
  {
   return 1;
  }
  return 0;
}
void ShwMem(void)
{
  xBlockLink *pxLink;
  pxLink = &xStart;
  while(pxLink!=0)
  {
      fprintf(lnk1,"[%LX][%LX]->[%LX]\n",pxLink,pxLink->xBlockSize,pxLink->pxNextFreeBlock);
      pxLink=pxLink->pxNextFreeBlock;
  }
}
#endif
