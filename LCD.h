/*
 * LCD.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Erwann
 */

#ifndef SRC_LCD_H_
#define SRC_LCD_H_

void lcd_init (void);
void lcd_enable (void);
void lcd_cursor();
void lcd_clear (void);
void lcd_print (int input);     
void lcd_space(int a);


#endif /* SRC_LCD_H_ */
