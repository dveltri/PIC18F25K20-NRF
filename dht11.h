#ifndef dht11_h
#define dht11_h
typedef struct
{
   uint16_t humidity_max; 
   uint16_t humidity;   
   uint16_t humidity_min;
   uint16_t temperature_max;
   uint16_t temperature;  
   uint16_t temperature_min; 
}dht11_data_t;
int8 update_dht11(dht11_data_t *data);
#endif
