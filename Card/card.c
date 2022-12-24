#include "card.h"

/* For test functions: */
ST_cardData_t cardData_ST;

char* cardErrorEnum_to_Text(EN_cardError_t Enum) 
{
   switch (Enum) 
   {
      case CARD_OK: return "CARD_OK";
      case WRONG_NAME: return "WRONG_NAME";
      case WRONG_EXP_DATE: return "WRONG_EXP_DATE";
      case WRONG_PAN: return "WRONG_PAN";
   }
}

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    uint32_t cardHolderName_len;
    fgets(cardData->cardHolderName, 40, stdin);
    cardHolderName_len = strlen(cardData->cardHolderName)-1;
    cardData->cardHolderName[cardHolderName_len] = NullChar;
    printf("cardHolderName_len : %d \n",cardHolderName_len);
    for (int i = 0; i < cardHolderName_len; ++i )
    {
        if ((isalpha(cardData->cardHolderName[i]) == 0)  || (isblank(cardData->cardHolderName[i]) != 0))
        {
            return WRONG_NAME;
        }
        
    }
    /* == 0 means null ascii*/
    if (cardData->cardHolderName[0] == NullChar || cardHolderName_len < 20 || cardHolderName_len > 24 )
    {
        return WRONG_NAME;
    }

    /* For readbility or can just retur CARD_OK directly*/
    else
    {
        return CARD_OK;
    }
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    uint8_t MM[3]={0};
    uint8_t YY[3]={0};
    uint8_t MM_Num = 0;
    uint8_t YY_Num = 0;
    uint8_t cardExpirationDate_len;
    
    fgets(cardData->cardExpirationDate, 7, stdin);
    cardExpirationDate_len = strlen(cardData->cardExpirationDate)-1;
    cardData->cardExpirationDate[cardExpirationDate_len] == NullChar;
    printf("cardExpirationDate_len : %d \n",cardExpirationDate_len);
    MM[0] = cardData->cardExpirationDate[0];
    MM[1] = cardData->cardExpirationDate[1];
    MM[2]= NullChar;
    YY[0] = cardData->cardExpirationDate[3];
    YY[1] = cardData->cardExpirationDate[4];
    YY[2] = NullChar;
    MM_Num = atoi(MM);
    YY_Num = atoi(YY);
    if (cardData->cardExpirationDate[0] == NullChar || !(MM_Num >= 01 && MM_Num <= 12  && YY_Num >= 20 && cardData->cardExpirationDate[2] == (int)'/'))
    {
        return WRONG_EXP_DATE;
    }
    else 
    {
        return CARD_OK;
    }

}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    uint8_t primaryAccountNumber_len;
    
    fgets(cardData->primaryAccountNumber, 40, stdin);
    primaryAccountNumber_len = strlen(cardData->primaryAccountNumber)-1;
    cardData->primaryAccountNumber[primaryAccountNumber_len] == NullChar;
    printf("primaryAccountNumber_len : %d \n",primaryAccountNumber_len);
    for (int i = 0; i < primaryAccountNumber_len; ++i )
    {
        if ( isdigit(cardData->primaryAccountNumber[i]) == 0)
        {
            return WRONG_PAN;
        }
        
    }
    if (cardData->primaryAccountNumber[0] == NullChar || primaryAccountNumber_len < 16 || primaryAccountNumber_len > 19 )
    {
        return WRONG_PAN;
    }
     else
    {
        return CARD_OK;
    }
}

/* Test Functions*/
void getCardHolderNameTest(void)
{   char* EnumTemp = NULL;
    printf("Tester Name: Abdelazim Ahmed\n");
    printf("Function Name: getCardHolderName\n");
    
    /* Test Case 1:*/
    printf("Test Case 1:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardHolderName(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_NAME\n");

    /* Test Case 2:*/
    printf("Test Case 2:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardHolderName(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_NAME\n");

    /* Test Case 3:*/
    printf("Test Case 3:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardHolderName(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_NAME\n");

    /* Test Case 4: */
    printf("Test Case 4:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardHolderName(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_NAME\n");

    /* Test Case 5: */
    printf("Test Case 5:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardHolderName(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: CARD_OK\n");

}
void getCardExpiryDateTest(void)
{char* EnumTemp = NULL;
    printf("Tester Name: Abdelazim Ahmed\n");
    printf("Function Name: getCardExpiryDate\n");
    
    /* Test Case 1:*/
    printf("Test Case 1:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardExpiryDate(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_EXP_DATE\n");

    /* Test Case 2:*/
    printf("Test Case 2:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardExpiryDate(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_EXP_DATE\n");

    /* Test Case 3:*/
    printf("Test Case 3:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardExpiryDate(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_EXP_DATE\n");
    
    /* Test Case 4:*/
    printf("Test Case 4:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardExpiryDate(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: CARD_OK\n");
}
void getCardPANTest (void)
{
     char* EnumTemp = NULL;
    printf("Tester Name: Abdelazim Ahmed\n");
    printf("Function Name: getCardPAN\n");
    
    /* Test Case 1:*/
    printf("Test Case 1:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardPAN(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_PAN\n");

    /* Test Case 2:*/
    printf("Test Case 2:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardPAN(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_PAN\n");

    /* Test Case 3:*/
    printf("Test Case 3:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardPAN(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_PAN\n");

    /* Test Case 4: */
    printf("Test Case 4:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardPAN(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: WRONG_PAN\n");

    /* Test Case 5: */
    printf("Test Case 5:\n");
    printf("Input Data:");
    EnumTemp = cardErrorEnum_to_Text(getCardPAN(&cardData_ST));
    printf("Expected Result: %s\n",EnumTemp);
    printf("Actual Result: CARD_OK\n");
}

