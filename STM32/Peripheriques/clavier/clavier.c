/**
 ** Communication avec le clavier
 **
 ** Permet de lire le clavier matriciel connecté sur le port B de la Nucleo
 **
 ** @file        clavier.c
 ** @version     1
 ** @author      Jean-Francois NEZAN
 **
 */

/* ----- Dépend de la cible ------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "clavier.h"


char clavier_scrute(void) {
	uint16_t col = 0,col2=1;
	char ret = 0;

	/* Parcours des colonnes et lecture des lignes */
	while(!ret) {
		if (col==0)
			col2 = 0x01;
		else
			col2 = col2 << 1;
		col = (col+1)%3;	
		
		HAL_GPIO_WritePin(GPIOB, col2, GPIO_PIN_SET);		
		HAL_GPIO_WritePin(GPIOB, ~col2, GPIO_PIN_RESET);		


		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)==1)
		{ 
			while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)==1);
			if (col==0) ret = '1';
			else if (col==2) ret = '2';
			else if (col==1) ret = '3';
		}
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==1)
		{ 
			while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==1);
			if (col==0) ret = '4';
			else if (col==2) ret = '5';
			else if (col==1) ret = '6';
		}
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==1)
		{ 
			while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)==1);
			if (col==0) ret = '7';
			else if (col==2) ret = '8';
			else if (col==1) ret = '9';
		}
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==1)
		{ 
			while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)==1);
			if (col==0) ret = '*';
			else if (col==2) ret = '0';
			else if (col==1) ret = '#';
		}
	}			

	/**/
	
	HAL_GPIO_WritePin(GPIOB, 0x07, GPIO_PIN_RESET);
	return ret;
}
