#define DHT11_DATA_PIN PIN_B4
#include "dht11.h"

int8 _rx_byte(uint8_t *rx_byt)
{
   uint8_t bit_count=7;
   uint8_t time_us=0;
   *rx_byt=0;
   do
   {
      time_us=55;
      while(input_state(DHT11_DATA_PIN)==0)
      {
         delay_us(1);
         if(time_us--==0)
            return 11;
      }
      time_us=75;
      while(input_state(DHT11_DATA_PIN)!=0)
      {
         delay_us(1);
         if(time_us--==0)
            return 12;
      }
      *rx_byt<<=1;
      if(time_us<45)
         *rx_byt|=1;
   }
   while(bit_count--);
   return 0;
}

int8 update_dht11(dht11_data_t *data)
{
   int8 rv=0;
   uint8_t rx_byt=0;
   uint8_t rx_sum=0;
   uint8_t time_us=50;
   while(input_state(DHT11_DATA_PIN)==0)
   {
      delay_us(1);
      if(time_us--==0)
         return 1;
   }
   //trisb_bits.RB4=0;
   output_bit(DHT11_DATA_PIN, 0);
   delay_ms(19);
   output_bit(DHT11_DATA_PIN, 1);
   //trisb_bits.RB4=1;
   time_us=50;
   while(input_state(DHT11_DATA_PIN)!=0)
   {
      delay_us(1);
      if(time_us--==0)
         return 2;
   }
   time_us=55;
   while(input_state(DHT11_DATA_PIN)==0)
   {
      delay_us(1);
      if(time_us--==0)
         return 3;
   }
   time_us=100;
   while(input_state(DHT11_DATA_PIN)!=0)
   {
      delay_us(1);
      if(time_us--==0)
         return 4;
   }
   //---------------------------------- humidity
   rv=_rx_byte(&rx_byt);
   if(rv!=0)
      return 5;
   rx_sum+=rx_byt;
   data->humidity=rx_byt;
   //data->humidity*=100;
   rv=_rx_byte(&rx_byt);
   if(rv!=0)
      return 6;
   rx_sum+=rx_byt;
   //data->humidity+=rx_byt;
   //---------------------------------- temperature
   rv=_rx_byte(&rx_byt);
   if(rv!=0)
      return 7;
   rx_sum+=rx_byt;
   data->temperature=rx_byt;
   //data->temperature*=100;
   rv=_rx_byte(&rx_byt);
   if(rv!=0)
      return 8;
   rx_sum+=rx_byt;
   //data->temperature+=rx_byt;
   //---------------------------------- parity
   rv=_rx_byte(&rx_byt);
   if(rv!=0)
      return 9;
   if(rx_sum!=rx_byt)
      return 10;
   return 0;
}
