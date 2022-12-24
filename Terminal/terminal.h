/* terminal.h*/

#ifndef TERMINAL_H 
#define TERMINAL_H 

#include "../Card/card.h"

typedef struct ST_terminalData_t
{
     float transAmount;
     float maxTransAmount;
     uint8_t transactionDate[12];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
     TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

char* terminalErrorEnum_to_Text(EN_terminalError_t terminalEnum);

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional

/* Test Functions*/
void getTransactionDateTest(void);
void isCardExpiredTest(void);
void getTransactionAmountTest(void);
void setMaxAmountTest(void);
void isBelowMaxAmountTest(void);

#endif
