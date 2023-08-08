
 /*
  * @Title      	: Card Module
  * @Filename   	: card.h
  * @Author     	: Mahmoud Mowafey
  * @Origin Date	: Mar 28, 2023
  * @Version		: 1.0.0
  * @Compiler		: MinGW
  * @Target     	: General Purpose Processor / PCs
  * @Notes			: The code is written with ANSI_C Standard.
  *
  * THIS SOFTWARE IS PROVIDED BY HACKER KERMIT- TEAM_1 at Sprints_Automotiv_BC_W11.
  *
  */
#ifndef CARD_H_
#define CARD_H_
#define EXPIRY_DATE_MAX_SIZE	5
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
/**************************************************************************************************************************************/
/*
* Defines three members which specify the card structure. 
*/
/**************************************************************************************************************************************/
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

/***************************************************************************************************************************************/
/*
* Defines four errors which specify the error kind.
*/
/**************************************************************************************************************************************/
typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/**************************************************************************************************************************************/
/*
*							Prototypes for all used functions inside the card module.
*/
/**************************************************************************************************************************************/
 EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
 EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
 EN_cardError_t getCardPAN(ST_cardData_t *cardData);


#endif /* CARD_H_ */































