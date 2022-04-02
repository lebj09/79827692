



#define F_CPU 16000000UL

#include <avr/io.h>
#include "ST7735.h"
#include "LCD_GFX.h"



#define F_CPU 16000000UL
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
//#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>



float yr = 0 ;
float yr_last = 0 ;
	int x = 80;
	int y =64;
	int swap =0;
	int swapp =0;
	int px = 6;
	int py = 64;

void Initialize()
{
	lcd_init();
}

int main(void)
{
	
	
	
	ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2);
		ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2)|(1 << ADATE);
		DIDR0 = (1 << ADC5D);
		ADCSRA |= (1 << ADSC);
		
		




	
	
	Initialize();
	
	LCD_setScreen(WHITE);

	
		
				LCD_drawBlock(px,py,2,50,RED,1);
				
				LCD_drawBlock(153,64,2,50,RED,1);
				
				
	
		
    while (1) 
    {
		
		LCD_drawBlock(px,py,2,50,RED,1);
		
		if(py<50 && swap==0){
			LCD_drawBlock(px,py,2,50,WHITE,1);
			py++;
			py++;
			LCD_drawBlock(px,py,2,50,RED,1);
			if(py==50){swapp=1;}
		}
		else{
			
			LCD_drawBlock(px,py,2,50,WHITE,1);
			py--;
			py--;
			LCD_drawBlock(px,py,2,50,RED,1);
			if(py==20){swapp=0;}
			
		}



		LCD_drawBlock(x,y,2,2,GREEN,1);
		
		if(x<145 && swap==0){
			LCD_drawBlock(x,y,2,2,WHITE,1);
			x=x+2;
			LCD_drawBlock(x,y,2,2,GREEN,1);
			if(x==146){swap=1;}
		}
		else{
			
				LCD_drawBlock(x,y,2,2,WHITE,1);
				x=x-2;
				LCD_drawBlock(x,y,2,2,GREEN,1);
				if(x==16){swap=0;}
			
		}
		
		
			yr = ADC*58/1024;
			LCD_drawBlock(153,yr_last,2,50,WHITE,1);
			yr=yr_last;
			LCD_drawBlock(153,64-yr,2,50,RED,1);
	
	
		
	}
}


