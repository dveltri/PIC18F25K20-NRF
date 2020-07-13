#ifndef bmp280_h
#define bmp280_h
typedef struct
{
   uint16_t hPa;
}bmp280_t;

#define BMP280_CSB PIN_C4

int8_t bmp280_init(int8_t nada);

#endif
