#include <main16.h>
//#INCLUDE <stdlib.h>
uint8_t crx_timeout = 1;
uint16_t rx_timeout = 0;  
uint16_t pwm_cycle = 0;   
uint16_t pwm_servo = 0;                    
uint16_t pwm_motor = 0;
uint16_t pwm_motor_tmp = 0;
uint8_t direction = 1;          
uint8_t inv_direction = 0;  
uint8_t cmd = 0;                   
uint8_t rx_byte = 0;
uint8_t rx_byte2 = 0;
                    
void off_motor(void)
{
	output_bit(PIN_motor1b,0);
	output_bit(PIN_motor1,1); 
	output_bit(PIN_motor2,0);
	output_bit(PIN_motor2b,1); 
}

void set_motor1(uint8_t direc)                                                                            
{
	if(direc!=0)
	{
		output_bit(PIN_motor1b,0); //pnp    
		delay_us(1);             
		output_bit(PIN_motor1,0);  //npn 
	}                         
	else
	{
	    output_bit(PIN_motor1,1);  //npn
	    delay_us(1);
		output_bit(PIN_motor1b,1); //pnp 
	}
}
                                                                                                                 
void set_motor2(uint8_t direc)
{
	if(direc!=0)
	{
		output_bit(PIN_motor2,0);  //pnp    
		delay_us(1);                
		output_bit(PIN_motor2b,0); //npn                                  
	}                                    
	else
	{
	    output_bit(PIN_motor2b,1); //npn
	    delay_us(1);
		output_bit(PIN_motor2,1);  //pnp     
	}
}                        


#INT_TIMER0                            
void Tmr0_fnc(void) //RTC for TimeOuts
{           
    set_timer0(188);       
	pwm_cycle++;
	if(rx_timeout>0 && crx_timeout!=0)
		rx_timeout--;
	if(pwm_cycle == 1000)   
		pwm_cycle = 0;
	//-----------------------	               
	if(pwm_servo > pwm_cycle)              
	{
		output_high(PIN_servo);    
	}                                        
	else                                                                   
	{                                                   
		output_low(PIN_servo);
	} 
	if(pwm_motor < 100 || rx_timeout==0)
	{
		off_motor();
		pwm_motor = 0;
	}
	else                         
	{
		off_motor();
	    set_motor1(direction==0);
		if(pwm_motor > pwm_cycle)
		{                                                
			set_motor2(direction!=0);     
		}
		else                        
		{
			set_motor2(direction==0);         
		}
	}
	//-----------------------*/  	
	clear_interrupt(INT_TIMER0);
} 
                            
char control(void);
void main()                                                  
{                                                                      
	off_motor();
	uint16_t bateria = 0;
	uint16_t lst_bateria = 0;
	int8_t temp=4;                                         
	uint16_t count = 0;
	pwm_servo = 72; 
	pwm_motor = 0;                  
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
	while(--temp)
	{                                                                       
		output_bit(led,1);
		delay_ms(50);
		restart_wdt();                               
		output_bit(led,0);
		delay_ms(50);                                  
	}
	while(TRUE)
	{                       
		if(control()==1)                                                                               
		{
			count++;
			//-------------------------------------
			bateria = read_adc(ADC_START_AND_READ);
			if(count>60000 || lst_bateria!=bateria)
			{
				lst_bateria=bateria;
				count = 0;                       
				//bateria/=256;
				LOGf("*B%Lu\n", bateria);
			}                
			//-------------------------------------
		}
		//sleep(); 
		restart_wdt();                         
   }

}

char control(void)         
{
	uint16_t tempu16 = 0;
	if(kbhit(lnk1)!=0)
	{                   
		if(cmd==0)  
		{
			output_bit(led,1);
			cmd = fgetc(lnk1); 
			if(cmd=='A')     
				crx_timeout = 1;
			if(cmd=='a')               
				crx_timeout = 0;
				                              
			if(cmd!='X' && cmd!='Y' && cmd!='y')  
	    	{                      
	    		cmd=0;                  
				rx_byte=0;                                                                   
				rx_byte2=0;
				output_bit(led,0);           
				return 0;                   
			}                          
			if(cmd=='Y' || cmd=='y') 
				rx_timeout = 20000;
			if(cmd=='y')
			{
				inv_direction = 1;
				cmd='Y';                
			}
			else
			{
				inv_direction = 0;		   	
			}		   	
		}                    
		if(rx_byte==0)                      
		{                        
			rx_byte=fgetc(lnk1);                              
			if(rx_byte < 0x31 || rx_byte > 0x39) //debe ser 1 ~ 9
			{                                                    
				cmd=0;                                         
				rx_byte=0;
				rx_byte2=0;
				output_bit(led,0);
				return 0;                       
			}                      
			switch(cmd)
	    	{                         
	    		case 'Y':     
	    		{           
		    		rx_byte -= 0x31;			//0 ~ 50 ~ 89 -> 1000 ~ 0 ~ -750
		    		if(inv_direction)
		    			rx_byte = 8 - rx_byte;
					direction = (rx_byte >= 5);                 
		    		if(direction)           
				    	rx_byte = rx_byte - 5;			//marcha atras max 3 
		    		else                                         
		    			rx_byte = 4 - rx_byte;	//marcha adelante max 49
	    			tempu16 = 204;    
	    			tempu16 *= rx_byte;                
		    		pwm_motor_tmp = tempu16;
	    		}                                                          
	    		break;
	    		case 'X':
	    		{
		    		rx_byte -= 0x31;
		    		tempu16 = 31;
		    		tempu16 *= rx_byte;
		    		tempu16 /= 10;                    
		    		pwm_servo = 60 + tempu16;    // 60 ~ 87 -> 24/89       
	    		}             
	    		break;
			}                                             
			rx_byte2=0;                                                 
			//return 0;                                                        
		}
		if(rx_byte2==0)    //tercer character x99
		{                   
			rx_byte2=fgetc(lnk1);        
			if(rx_byte2 < 0x30 || rx_byte2 > 0x39)// 0 ~ 9
			{            
				cmd=0;                          
				rx_byte=0;           
				rx_byte2=0;           
				output_bit(led,0);   
				return 0;
			}                                   
			switch(cmd)   
	    	{                       
	    		case 'Y':
	    		{                      
		    		rx_byte2 -= 0x30;
		    		if(inv_direction)
			    		rx_byte2 = 9 - rx_byte2;
		    		if(!direction) //marcha atras max 3
		    		{                                              
		    			rx_byte2 = 10 - rx_byte2;
		    			rx_byte2 %= 10;   
		    		}                                                            
		    		tempu16 = 20;                                                     
		    		tempu16 *= rx_byte2;                                                                          
		    		pwm_motor_tmp += tempu16;                         
	    			pwm_motor = pwm_motor_tmp;
                	//fprintf(lnk1,"[%u %u] %u %Lu\n", rx_byte, rx_byte2, direction, pwm_motor);              
                	//LOGf("*A%Lu\n", pwm_motor);                                
	    		}                                      
	    		break;                                            
	    		case 'X':
	    		{                                    
		    		rx_byte2 -= 0x30;   
		    		tempu16 = 31;
		    		tempu16 *= rx_byte2;
		    		tempu16 /= 100;
		    		pwm_servo += tempu16;            
		    		//LOGf("*D%Lu\n", pwm_servo);
	    		}
	    		break;                  
			}                       
			cmd=0;    
			rx_byte=0;           
			rx_byte2=0;
			output_bit(led,0);
			return 0;
		}                
	}
	return 1;
}
