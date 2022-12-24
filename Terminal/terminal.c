#include "terminal.h"


/* For test functions: */
ST_terminalData_t terminalData_ST;
ST_cardData_t cardData_ST_temp;


char* terminalErrorEnum_to_Text(EN_terminalError_t terminalEnum)
{
    switch (terminalEnum) 
    {
      case TERMINAL_OK: return "TERMINAL_OK";
      case WRONG_DATE: return "WRONG_DATE";
      case EXPIRED_CARD: return "EXPIRED_CARD";
      case INVALID_CARD: return "INVALID_CARD";
      case INVALID_AMOUNT: return "INVALID_AMOUNT";
      case EXCEED_MAX_AMOUNT: return "EXCEED_MAX_AMOUNT";
      case INVALID_MAX_AMOUNT: return "INVALID_MAX_AMOUNT";
    }
}

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    uint8_t DD[3]={0};
    uint8_t MM[3]={0};
    uint8_t YYYY[5]={0};

    uint8_t DD_Num = 0;
    uint8_t MM_Num = 0;
    uint16_t YYYY_Num = 0;

    uint32_t transactionDate_len;

    fgets(termData->transactionDate, 12, stdin);
    transactionDate_len = strlen(termData->transactionDate)-1;
    termData->transactionDate[transactionDate_len] = NullChar;
    printf("transactionDate_len : %d \n",transactionDate_len);

    DD[0] = termData->transactionDate[0];
    DD[1] = termData->transactionDate[1];
    DD[2] = NullChar;


    MM[0] = termData->transactionDate[3];
    MM[1] = termData->transactionDate[4];
    MM[2]= NullChar;

    YYYY[0] = termData->transactionDate[6];
    YYYY[1] = termData->transactionDate[7];
    YYYY[2] = termData->transactionDate[8];
    YYYY[3] = termData->transactionDate[9];
    YYYY[4] = NullChar;
    
    DD_Num = atoi(DD);
    MM_Num = atoi(MM);
    YYYY_Num = atoi(YYYY);

    if (termData->transactionDate[0] == NullChar || !(  DD_Num >= 01 && DD_Num <= 31  &&  MM_Num >= 01 && MM_Num <= 12  && YYYY_Num >= 2000 && termData->transactionDate[2] == (int)'/' && termData->transactionDate[5] == (int)'/'))
    {
        return WRONG_DATE;
    }
    else 
    {
        return TERMINAL_OK;
    }

}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    /* Another idea*/
    /*uint8_t termData_MM[3]={0};
    uint8_t termData_YY[3]={0};
    uint8_t cardData_MM[3]={0};
    uint8_t cardData_YY[3]={0};
    */

    if(cardData->cardExpirationDate[3] > termData->transactionDate[8])
    {
        return TERMINAL_OK;
    }
    else if (cardData->cardExpirationDate[3] < termData->transactionDate[8]) 
    {
        return EXPIRED_CARD;
    }
    /* (cardData->cardExpirationDate[3] == termData->transactionDate[8]) */
    else
    {
        if(cardData->cardExpirationDate[4] > termData->transactionDate[9])
        {
            return TERMINAL_OK;   
        }
        else if (cardData->cardExpirationDate[4] < termData->transactionDate[9]) 
        {
            return EXPIRED_CARD;
        }
        else
        {
            if(cardData->cardExpirationDate[0] > termData->transactionDate[3])
            {
                 return TERMINAL_OK;   
            }
            else if (cardData->cardExpirationDate[0] < termData->transactionDate[3]) 
            {
                 return EXPIRED_CARD;
            } 
            else 
            {
                if(cardData->cardExpirationDate[1] > termData->transactionDate[4])
                {
                    return TERMINAL_OK;   
                }
                else if (cardData->cardExpirationDate[1] < termData->transactionDate[4]) 
                {
                     return EXPIRED_CARD;
                } 
                else
                {
                     return TERMINAL_OK;
                }
            }

        }   
    }  
    
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    scanf("%f",&termData->transAmount);
    if (termData->transAmount <= 0.0)
    {
        return INVALID_AMOUNT;
    }
    else
    {
        return TERMINAL_OK;
    }    
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{   if(maxAmount <= 0.0 )
    {
        return INVALID_MAX_AMOUNT;
    }
    else 
    {
        termData->maxTransAmount = maxAmount;
        return TERMINAL_OK;
    }
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    else 
    {
        return TERMINAL_OK;
    }
}





/* Test Functions*/
void getTransactionDateTest(void)
{
    char* EnumTemp = NULL;
    
    printf("\n");
    printf("Tester Name: Abdelazim Ahmed\n");
    printf("Function Name: getTransactionDate\n");
    
    /* Test Case 1:*/
    printf("Test Case 1:\n");
    printf("Input Data:");
    EnumTemp = terminalErrorEnum_to_Text(getTransactionDate(&terminalData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_DATE\n");

    /* Test Case 2:*/
    printf("Test Case 2:\n");
    printf("Input Data:");
    EnumTemp = terminalErrorEnum_to_Text(getTransactionDate(&terminalData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_DATE\n");

    /* Test Case 3:*/
    printf("Test Case 3:\n");
    printf("Input Data:");
    EnumTemp = terminalErrorEnum_to_Text(getTransactionDate(&terminalData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_DATE\n");
    
    /* Test Case 4:*/
    printf("Test Case 4:\n");
    printf("Input Data:");
    EnumTemp = terminalErrorEnum_to_Text(getTransactionDate(&terminalData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: TERMINAL_OK\n");
}

void isCardExpiredTest(void)
{
    printf("\n");
    printf("Tester Name: Abdelazim Ahmed\n");
    printf("Function Name: isCardExpired\n");
    
    /* Test Case 1:*/
    printf("Test Case 1:\n");
    printf("Input Data:");
    getCardExpiryDate(&cardData_ST_temp);
    getTransactionDate(&terminalData_ST);
    printf("Expected Result: %s\n",terminalErrorEnum_to_Text(isCardExpired(&cardData_ST_temp,&terminalData_ST)));
    printf("Actual Result: EXPIRED_CARD\n");

    /* Test Case 2:*/
    printf("Test Case 2:\n");
    printf("Input Data:");
    getCardExpiryDate(&cardData_ST_temp);
    getTransactionDate(&terminalData_ST);
    printf("Expected Result: %s\n",terminalErrorEnum_to_Text(isCardExpired(&cardData_ST_temp,&terminalData_ST)));
    printf("Actual Result: EXPIRED_CARD\n");

    /* Test Case 3:*/
    printf("Test Case 3:\n");
    printf("Input Data:");
    getCardExpiryDate(&cardData_ST_temp);
    getTransactionDate(&terminalData_ST);
    printf("Expected Result: %s\n",terminalErrorEnum_to_Text(isCardExpired(&cardData_ST_temp,&terminalData_ST)));
    printf("Actual Result: TERMINAL_OK\n");
    
    /* Test Case 4:*/
    printf("Test Case 4:\n");
    printf("Input Data:");
    getCardExpiryDate(&cardData_ST_temp);
    getTransactionDate(&terminalData_ST);
    printf("Expected Result: %s\n",terminalErrorEnum_to_Text(isCardExpired(&cardData_ST_temp,&terminalData_ST)));
    printf("Actual Result: TERMINAL_OK\n");
}

void getTransactionAmountTest(void)
{
    char* EnumTemp = NULL;

    printf("\n");
    printf("Tester Name: Abdelazim Ahmed\n");
    printf("Function Name: getTransactionAmount\n");
    
    /* Test Case 1:*/
    printf("Test Case 1:\n");
    printf("Input Data:");
    EnumTemp = terminalErrorEnum_to_Text(getTransactionAmount(&terminalData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: INVALID_AMOUNT\n");

    /* Test Case 2:*/
    printf("Test Case 2:\n");
    printf("Input Data:");
    EnumTemp = terminalErrorEnum_to_Text(getTransactionAmount(&terminalData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: TERMINAL_OK\n");
}

void setMaxAmountTest(void)
{   /* To store maxAmount & take from user */
    float temp = 0.0;

    printf("\n");
    printf("Tester Name: Abdelazim Ahmed\n");
    printf("Function Name: setMaxAmount\n");
    
    /* Test Case 1:*/
    printf("Test Case 1:\n");
    printf("Input Data: ");
    scanf("%f",&temp);
    printf("Expected Result: %s\n",terminalErrorEnum_to_Text(setMaxAmount(&terminalData_ST,temp)));
    printf("Actual Result: INVALID_MAX_AMOUNT\n");

    /* Test Case 2:*/
    printf("Test Case 2:\n");
    printf("Input Data:");
    scanf("%f",&temp);
    printf("Expected Result: %s\n",terminalErrorEnum_to_Text(setMaxAmount(&terminalData_ST,temp)));
    printf("Actual Result: INVALID_MAX_AMOUNT\n");
    
    /* Test Case 3:*/
    printf("Test Case 3:\n");
    printf("Input Data: ");
    scanf("%f",&temp);
    printf("Expected Result: %s\n",terminalErrorEnum_to_Text(setMaxAmount(&terminalData_ST,temp)));
    printf("Actual Result: TERMINAL_OK\n");

}

void isBelowMaxAmountTest(void)
{
    /* To store maxAmount & take from user */
    float temp = 0.0;

    printf("\n");
    printf("Tester Name: Abdelazim Ahmed\n");
    printf("Function Name: isBelowMaxAmount\n");
    
    /* Test Case 1:*/
    printf("Test Case 1:\n");
    printf("Input Data: TransactionAmount, MaxAmount\n");
    getTransactionAmount(&terminalData_ST);
    scanf("%f",&temp);
    setMaxAmount(&terminalData_ST,temp);
    printf("Expected Result: %s\n",terminalErrorEnum_to_Text(isBelowMaxAmount(&terminalData_ST)));
    printf("Actual Result: EXCEED_MAX_AMOUNT\n");

    /* Test Case 2:*/
    printf("Test Case 2:\n");
    printf("Input Data: TransactionAmount, MaxAmount\n");
    getTransactionAmount(&terminalData_ST);
    scanf("%f",&temp);
    setMaxAmount(&terminalData_ST,temp);
    printf("Expected Result: %s\n",terminalErrorEnum_to_Text(isBelowMaxAmount(&terminalData_ST)));
    printf("Actual Result: TERMINAL_OK\n");

}












