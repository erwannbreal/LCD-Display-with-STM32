/*
 * LCD.c
 *
 *  Created on: Sep 24, 2024
 *      Author: Erwann
 */
#include "main.h"

#define SLAVE_ADRESS_LCD 0x4E

//extern I2C_HandleTypeDef hi2c1;

void lcd_enable(void) {  //pulse the Enable pin (E) to transmit data
	HAL_Delay(10);
    HAL_GPIO_WritePin(GPIOA, E_Pin, GPIO_PIN_SET);  // Enable pin high
    HAL_Delay(1);  // Small delay
    HAL_GPIO_WritePin(GPIOA, E_Pin, GPIO_PIN_RESET);  // Enable pin low
    HAL_Delay(10);
}

void lcd_print (int input){  //print a caracter on the display (exemple : 0x45 -> 'E')
	HAL_GPIO_WritePin(GPIOA, RS_Pin, SET); //RS=1 for data
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOA, D7_Pin, (input >> 7)& 0x01);
	HAL_GPIO_WritePin(GPIOA, D6_Pin, (input >> 6)& 0x01);
	HAL_GPIO_WritePin(GPIOA, D5_Pin, (input >> 5)& 0x01);  //Upper Bits
	HAL_GPIO_WritePin(GPIOA, D4_Pin, (input >> 4)& 0x01);

	HAL_GPIO_WritePin(GPIOA, D3_Pin, (input >> 3)& 0x01);
	HAL_GPIO_WritePin(GPIOA, D2_Pin, (input >> 2)& 0x01);  //Lower Bits
	HAL_GPIO_WritePin(GPIOC, D1_Pin, (input >> 1)& 0x01);
	HAL_GPIO_WritePin(GPIOC, D0_Pin, input & 0x01);

	lcd_enable(); //pulse the Enable pin (E)
HAL_Delay(40);

}

void lcd_cmd (int cmd){
	HAL_GPIO_WritePin(GPIOA, RS_Pin, RESET); //RS=0 for command
	HAL_Delay(20);

	HAL_GPIO_WritePin(GPIOA, D7_Pin, (cmd >> 7)& 0x01);
	HAL_GPIO_WritePin(GPIOA, D6_Pin, (cmd >> 6)& 0x01);
	HAL_GPIO_WritePin(GPIOA, D5_Pin, (cmd >> 5)& 0x01);
	HAL_GPIO_WritePin(GPIOA, D4_Pin, (cmd >> 4)& 0x01);

	HAL_GPIO_WritePin(GPIOA, D3_Pin, (cmd >> 3)& 0x01);
	HAL_GPIO_WritePin(GPIOA, D2_Pin, (cmd >> 2)& 0x01);
	HAL_GPIO_WritePin(GPIOC, D1_Pin, (cmd >> 1)& 0x01);
	HAL_GPIO_WritePin(GPIOC, D0_Pin, cmd & 0x01);

	lcd_enable(); //pulse the Enable pin (E)
HAL_Delay(40);

}

void lcd_init () {
HAL_Delay(80);
HAL_GPIO_WritePin(GPIOA, RS_Pin, RESET); //RS=0 for command
HAL_GPIO_WritePin(GPIOA, E_Pin, RESET);
HAL_Delay(5);

	lcd_cmd(0x38);  //00111000 -> Function set, N=1(2line) et F=0(5x08 dots)
	lcd_enable(); //pulse the Enable pin (E)

HAL_Delay(40);

	lcd_cmd(0x38); //00111000 -> Function set, N=1(2line) et F=0(5x08 dots)
	lcd_enable(); //pulse the Enable pin (E)

HAL_Delay(40);

	lcd_cmd(0xE); //00001110 -> Display On/Off, B=1(nlink on) ; C=1(cursor on) ; D=0(display off)
	lcd_enable(); //pulse the Enable pin (E)

HAL_Delay(40);

	lcd_cmd(0x06); //000001(I/D)(S) -> Entry mode set ; I/D=1(increment by 1) S/H=0 (No Shift)
	lcd_enable(); //pulse the Enable pin (E)

HAL_Delay(40);

	lcd_cmd(0x01); //00000001 -> Display clear
	lcd_enable(); //pulse the Enable pin (E)

HAL_Delay(40);
}

void lcd_cursor() {  //increment cursor by 1
	HAL_GPIO_WritePin(GPIOA, RS_Pin, RESET); //RS=0 for command
	HAL_GPIO_WritePin(GPIOA, E_Pin, RESET);
	HAL_Delay(40);

	lcd_cmd(0x14);	//00010100
	lcd_enable();
}

void lcd_space(int a) {
	HAL_GPIO_WritePin(GPIOA, RS_Pin, RESET); //RS=0 for command
	HAL_GPIO_WritePin(GPIOA, E_Pin, RESET);
	HAL_Delay(40);
	for (int i=0; i<=a; i++){
		lcd_print(0x20);
	}
}

void lcd_clear(void) {
HAL_GPIO_WritePin(GPIOA, RS_Pin, RESET); //RS=0 for command

	lcd_cmd(0x01); //00000001 -> Display clear
	lcd_enable(); //pulse the Enable pin (E)

		HAL_Delay(40);

}



