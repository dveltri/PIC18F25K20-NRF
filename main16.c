#include <main16.h>
#include "dht11.c"

#INT_TIMER0                            
void Tmr0_fnc(void) //RTC for TimeOuts
{           
	set_timer0(188);              
	//-----------------------*/  	
	clear_interrupt(INT_TIMER0);
} 

void main()
{             
	uint16_t bateria = 0;                                            
	uint16_t lst_bateria = 0;
	int8_t temp=4;
	uint8_t result=0;
	setup_timer_0( RTCC_INTERNAL);
	clear_interrupt(INT_TIMER0);
	enable_interrupts(INT_TIMER0);                                 
	enable_interrupts(GLOBAL);                     
	setup_adc(ADC_CLOCK_INTERNAL);     
	//setup_vref(VREF_COMP_DAC_OFF);
	setup_adc_ports(sAN2);
	ANSELA.ANSA2 = 1;
	set_adc_channel(2);
	ADCON1.ADCS = 2;                                 
	LOG("-------\n");   	
	dht11_data_t dht11;
	memset(&dht11,0,sizeof(dht11_data_t));
	dht11.humidity = 0;
	dht11.temperature = 0;
	LOG("-------\n");                                            
	while(--temp)               
	{
		output_bit(led,1);
		delay_ms(50);
		restart_wdt();         
		output_bit(led,0);
		delay_ms(50);
	}// */
	while(TRUE)               
	{                                          
		//TODO: User Code                                                           
		output_bit(led,1);     
		delay_ms(50);
		//sleep();                                                                
		restart_wdt();
		result = update_dht11(&dht11);                                                     
    	restart_wdt();
    	if (result!=0)
    		LOGf("*E%u\n",result);    
		LOGf("*H min:%Lu",dht11.humidity_min);  
		LOGf(" max:%Lu",dht11.humidity_max);  
		LOGf(" cur:%Lu\n",dht11.humidity);  
    	restart_wdt();  
		LOGf("*T min:%Lu",dht11.temperature_min);  
		LOGf(" max:%Lu",dht11.temperature_max);  
		LOGf(" cur:%Lu\n",dht11.temperature);
    	restart_wdt();   
		bateria = read_adc(ADC_START_AND_READ);
		//lst_bateria=bateria;
		//bateria/=256;
    	restart_wdt();  
		LOGf("*B%Lu\n", bateria);
    	restart_wdt();  
		output_bit(led,0);
		delay_ms(50);  
		restart_wdt(); 
		sleep();     
		restart_wdt();                                                                                                
	}

}
