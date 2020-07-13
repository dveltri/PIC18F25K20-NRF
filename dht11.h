#ifndef dht11_h
#define dht11_h
typedef struct
{
   uint16_t humidity;
   uint16_t temperature;
}dht11_data_t;
int8 update_dht11(dht11_data_t *data);
#endif
