#include "server.h"

ST_cardData_t cardData_INS;
ST_accountsDB_t accountRefrence_INS;


uint8_t accountsDB_len;

/* global sequence number*/
uint32_t G_transactionSequenceNumber = 1;

EN_transState_t  G_stateOfTransaction;


/* global array of [ST_accountsDB_t] for the valid accounts database*/
ST_accountsDB_t accountsDB[255] = {

    {2000.0, RUNNING, "8989374615436851"},{100.0, BLOCKED, "5807007076043875"},
    {10000.0, RUNNING, "6851007076043875"},{500.0, BLOCKED, "580700707606851"},
    {5000.0, RUNNING, "5807461076043875"},{50.0, BLOCKED, "7461007076043875"}
};

/* global array of [ST_transaction_t] for the valid accounts database*/
ST_transaction_t transactionDB[255] = {0};

char* serverTransStaterEnum_to_Text(EN_transState_t serverEnum)
{
    switch (serverEnum) 
    {
      case APPROVED: return "APPROVED";
      case DECLINED_INSUFFECIENT_FUND: return "DECLINED_INSUFFECIENT_FUND";
      case DECLINED_STOLEN_CARD: return "DECLINED_STOLEN_CARD";
      case FRAUD_CARD: return "FRAUD_CARD";
      case INTERNAL_SERVER_ERROR: return "INTERNAL_SERVER_ERROR";
    }

}

char* serverErrorEnum_to_Text(EN_serverError_t serverEnum)
{
    switch (serverEnum) 
    {
      case SERVER_OK: return "SERVER_OK";
      case SAVING_FAILED: return "SAVING_FAILED";
      case TRANSACTION_NOT_FOUND: return "TRANSACTION_NOT_FOUND";
      case ACCOUNT_NOT_FOUND: return "ACCOUNT_NOT_FOUND";
      case LOW_BALANCE: return "LOW_BALANCE";
      case BLOCKED_ACCOUNT: return "BLOCKED_ACCOUNT";
    }

}

char* serverAccountStateEnum_to_Text(EN_accountState_t serverEnum)
{
    switch (serverEnum) 
    {
      case RUNNING: return "RUNNING";
      case BLOCKED: return "BLOCKED";
    }

}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    accountsDB_len = strlen((char*)accountsDB);

    for (int i = 0; i < accountsDB_len; i++) {
        if (strcmp(cardData->primaryAccountNumber, accountRefrence->primaryAccountNumber[i]) == 0) 
        {
            return SERVER_OK;

        }
    }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    if(accountRefrence->state == BLOCKED)
    {
        return BLOCKED_ACCOUNT;
    } 
    else
    {
        return SERVER_OK;
    }
    
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,  ST_accountsDB_t *accountRefrence)
{
    
        if (termData->transAmount > accountRefrence->balance)
        {
            return LOW_BALANCE;
        }
        else
        {
            return SERVER_OK;
        }
    
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    if(transactionDB[transactionSequenceNumber].transactionSequenceNumber == 0)
    {
        return TRANSACTION_NOT_FOUND;
    }
    else
    {
        return SERVER_OK;
    }
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{

    transData->transState = G_stateOfTransaction;
    transData->transactionSequenceNumber = G_transactionSequenceNumber;

    /*transaction history array*/
    transactionDB[G_transactionSequenceNumber] = *transData;

    G_transactionSequenceNumber++;

    getTransaction(transData->transactionSequenceNumber, transData);


}

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    /*
    * account does not exist return FRAUD_CARD
    * amount is not available  return DECLINED_INSUFFECIENT_FUND
    * account is blocked will return DECLINED_STOLEN_CARD
    * transaction can't be saved will return INTERNAL_SERVER_ERROR
    * else  returns APPROVED
    * update the database with the new balance
    */
   
    if(isValidAccount(&cardData_INS, &accountRefrence_INS))
    {
        G_stateOfTransaction = FRAUD_CARD;
        return FRAUD_CARD;
    }

    if(isBlockedAccount(&accountRefrence_INS)){
        G_stateOfTransaction = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    if(isAmountAvailable(transData,&accountRefrence_INS))
    {
        G_stateOfTransaction = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    accountRefrence_INS.balance -= transData->terminalData.transAmount;
    G_stateOfTransaction = APPROVED;
    return APPROVED;
}

/* Test Functions*/
void recieveTransactionDataTest(void)
{

}