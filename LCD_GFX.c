/*
 * LCD_GFX.c
 *
 * Created: 9/20/2021 6:54:25 PM
 *  Author: You
 */ 

#include "LCD_GFX.h"
#include "ST7735.h"

/******************************************************************************
* Local Functions
******************************************************************************/



/******************************************************************************
* Global Functions
******************************************************************************/

/**************************************************************************//**
* @fn			uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
* @brief		Convert RGB888 value to RGB565 16-bit color data
* @note
*****************************************************************************/
uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((((31*(red+4))/255)<<11) | (((63*(green+2))/255)<<5) | ((31*(blue+4))/255));
}

/**************************************************************************//**
* @fn			void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color)
* @brief		Draw a single pixel of 16-bit rgb565 color to the x & y coordinate
* @note
*****************************************************************************/
void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color) {
	LCD_setAddr(x,y,x,y);
	SPI_ControllerTx_16bit(color);
}

/**************************************************************************//**
* @fn			void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor)
* @brief		Draw a character starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor){
	uint16_t row = character - 0x20;		//Determine row of ASCII table starting at space
	int i, j;
	if ((LCD_WIDTH-x>7)&&(LCD_HEIGHT-y>7)){
		for(i=0;i<5;i++){
			uint8_t pixels = ASCII[row][i]; //Go through the list of pixels
			for(j=0;j<8;j++){
				if ((pixels>>j)&1==1){
					LCD_drawPixel(x+i,y+j,fColor);
				}
				else {
					LCD_drawPixel(x+i,y+j,bColor);
				}
			}
		}
	}
}


/******************************************************************************
* LAB 4 TO DO. COMPLETE THE FUNCTIONS BELOW.
* You are free to create and add any additional files, libraries, and/or
*  helper function. All code must be authentically yours.
******************************************************************************/

/**************************************************************************//**
* @fn			void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius,uint16_t color)
* @brief		Draw a colored circle of set radius at coordinates
* @note
*****************************************************************************/
void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius,uint16_t color)
{
	
	
	
	int d = 1 - radius;
	int p_x = 1;
	int p = -2 * radius;
	int x = 0;
	int y = radius;

	


	while (x < y) {
		if (d >= 0) {
			y--;
			p += 2;
			d += p;
		}
		x++;
		p_x += 2;
		d += p_x;

		LCD_drawPixel(x0 + x, y0 + y, color);
		LCD_drawPixel(x0 - x, y0 + y, color);
		LCD_drawPixel(x0 + x, y0 - y, color);
		LCD_drawPixel(x0 - x, y0 - y, color);
		LCD_drawPixel(x0 + y, y0 + x, color);
		LCD_drawPixel(x0 - y, y0 + x, color);
		LCD_drawPixel(x0 + y, y0 - x, color);
		LCD_drawPixel(x0 - y, y0 - x, color);
		LCD_drawPixel(x0, y0 + radius, color);
		LCD_drawPixel(x0, y0 - radius, color);
		LCD_drawPixel(x0 + radius, y0, color);
		LCD_drawPixel(x0 - radius, y0, color);
	
	
}
	
	

}


/**************************************************************************//**
* @fn			void LCD_drawLine(short x0,short y0,short x1,short y1,uint16_t c)
* @brief		Draw a line from and to a point with a color
* @note
*****************************************************************************/
void LCD_drawLine(short x0,short y0,short x1,short y1,uint16_t c)
{
	 
	 int dy = 0;
	 int dx = 0;
	 int stepx= 0;
	 int stepy = 0;
	 
	 dy = y1 - y0; //work out delta of x and y
	 dx = x1 - x0;
	 
	 
	 if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; } // absolute value of each
	 if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
	 dy <<= 1;                                              // dy is now 2*dy
	 dx <<= 1;                                              // dx is now 2*dx
	 LCD_drawPixel(x0, y0, c);
	 if (dx > dy) {
		 int fraction = dy - (dx >> 1);                     // same as 2*dy - dx
		 while (x0 != x1) {
			 if (fraction >= 0) {
				 y0 += stepy;
				 fraction -= dx;                            // same as fraction -= 2*dx
			 }
			 x0 += stepx;
			 fraction += dy;                                // same as fraction -= 2*dy
			 LCD_drawPixel(x0, y0, c);
		 }
		 } else {
		 int fraction = dx - (dy >> 1);
		 while (y0 != y1) {
			 if (fraction >= 0) {
				 x0 += stepx;
				 fraction -= dy;
			 }
			 y0 += stepy;
			 fraction += dx;
			 LCD_drawPixel(x0, y0, c);
		 }
	 }
}



/**************************************************************************//**
* @fn			void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint16_t color)
* @brief		Draw a colored block at coordinates
* @note
*****************************************************************************/
void LCD_drawBlock(uint8_t x, uint8_t y, uint8_t w, uint8_t h,uint16_t color,uint8_t f)
{

	int x1 =x+w/2;
	int x2 =x-w/2;
	int y1 =y+h/2;
	int y2 =y-h/2;
	 
	LCD_drawLine(x1, y1, x1, y2, color);
	LCD_drawLine(x1, y1, x2, y1, color);
	LCD_drawLine(x2, y2, x1, y2, color);
	LCD_drawLine(x2, y2, x2, y1, color);
	 

if(f==1){
	
	while (x2 != x1){
		
	LCD_drawLine(x2, y2, x2, y1, color);	
	x2++;
		
	}
	
	
}





}

/**************************************************************************//**
* @fn			void LCD_setScreen(uint16_t color)
* @brief		Draw the entire screen to a color
* @note
*****************************************************************************/
void LCD_setScreen(uint16_t color) 
{

	int x = 0; 
	int y = 0;
	
		      for (x = 0; x < 160; x++){
				  
		    LCD_drawLine(x,0, x, 127, color);
		      
			  
			  }
			  

			  
}

/**************************************************************************//**
* @fn			void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
* @brief		Draw a string starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
{
	
	
	

}
