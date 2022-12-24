/* card.h*/
#ifndef CARD_H 
#define CARD_H 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NullChar        (int)'\0'

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[40];
    uint8_t primaryAccountNumber[40];
    uint8_t cardExpirationDate[7];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

char* cardErrorEnum_to_Text(EN_cardError_t Enum); 

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

void getCardHolderNameTest(void);
void getCardExpiryDateTest (void);
void getCardPANTest (void);

#endif