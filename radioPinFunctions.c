/*
* ----------------------------------------------------------------------------
* “THE COFFEEWARE LICENSE” (Revision 1):
* <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a coffee in return.
* -----------------------------------------------------------------------------
* Please define your platform spesific functions in this file ...
* -----------------------------------------------------------------------------
*/
#define set_bit(pin)  output_high(pin)
#define clr_bit(pin) output_low(pin)
#define check_bit(pin) input(pin)

/* ------------------------------------------------------------------------- */
void nrf24_setupPins()
{
   bit_clear(TRISB,0); //RF24_CS   PIN_B0
   bit_clear(TRISC,3); //RF24_CE   PIN_C3
   bit_set(TRISC,  4); //RF24_IRQ  PIN_C4
   bit_clear(TRISC,6); //SPI_MOSI  PIN_C6
   bit_set(TRISC,  7); //SPI_MISO  PIN_C7
   bit_clear(TRISA,7); //SPI_CLK   PIN_A7
}
/* ------------------------------------------------------------------------- */
void nrf24_ce_digitalWrite(uint8_t state)
{
    if(state)
    {
        set_bit(RF24_CE);
    }
    else
    {
        clr_bit(RF24_CE);
    }
}
/* ------------------------------------------------------------------------- */
void nrf24_csn_digitalWrite(uint8_t state)
{
    if(state)
    {
        set_bit(RF24_CS);
    }
    else
    {
        clr_bit(RF24_CS);
    }
}
/* ------------------------------------------------------------------------- */
