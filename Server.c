#include <stdio.h>
#include "app.h"
#include "Terminal.h"
#include "Server.h"
#include "Card.h"
#include <string.h>
#include "server.h"

static int c = 500;

extern ST_accountsDB_t data[10] = {

	{10000 ,"5244395522419985"},
	{10516 , "5244395522419985"},
	{1610 , "5244395522419985"},
	{1054 ,  "5244395522419985"},
	{100.2 ,  "5244395522419985"},
	{11005 ,  "5244395522419985"}

};


ST_transaction_t transaction[255];
void filltransaction(ST_transaction_t* transaction) {
	for (int i = 0; i < 255; i++) {
		*transaction[i].cardHolderData.cardExpirationDate = "00000";
		*transaction[i].cardHolderData.cardHolderName = "0000000000000000000000000";
		*transaction[i].cardHolderData.primaryAccountNumber = "00000000000000000000";
		transaction[i].terminalData.maxTransAmount = 0;
		transaction[i].terminalData.transAmount = 0;
		*transaction[i].terminalData.transactionDate = "00000000000";
		transaction[i].transactionSequenceNumber = 0;
		transaction[i].transState = 0;

	}
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	
	for (int i = 0; i < 255; i++) {

		if ((strcmp(cardData->primaryAccountNumber , data[i].primaryAccountNumber)) == 0) {
			
			//printf("%s\n", cardData->primaryAccountNumber);
			//printf("%s\n", data[i].primaryAccountNumber);
			c = i;
			return SERVER_OK;
		}
		
	}
	return ACCOUNT_NOT_FOUND;
}

 char* serverresponce(EN_transState_t responce) {
	switch (responce)
	{
	case 0: return "APPROVED";
	case 1: return "DECLINED_INSUFFECIENT_FUND";
	case 2: return "DECLINED_STOLEN_CARD";
	case 3: return "INTERNAL_SERVER_ERROR";
	
	}

}

 char* serverresponce2(EN_serverError_t responce) {
	 switch (responce)
	 {
	 case 0: return "SERVER_OK";
	 case 1: return "SAVING_FAILED";
	 case 2: return "TRANSACTION_NOT_FOUND";
	 case 3: return "ACCOUNT_NOT_FOUND";
	 case 4: return "LOW_BALANCE";

	 }

 }


 EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	
	 
		 if (termData->transAmount <=  data[c].balance ) {
			

			 return SERVER_OK;
			// printf("%d       trans  %d   ", data[c].balance);
		 }
		 return LOW_BALANCE;
	 
 }




 EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	 //printf("%s", serverresponce2(isValidAccount(&transData)));


	/* if (isValidAccount(&transData) == ACCOUNT_NOT_FOUND) {
		 transData->transState = ACCOUNT_NOT_FOUND;
		 return ACCOUNT_NOT_FOUND;
	 }

	 if (isAmountAvailable(&transData)!= SERVER_OK) {
		 transData->transState = DECLINED_INSUFFECIENT_FUND;
		 return DECLINED_INSUFFECIENT_FUND;
	 }
	 */
	 if (saveTransaction(&transData) == SAVING_FAILED) {
		 transData->transState = INTERNAL_SERVER_ERROR;
		 return INTERNAL_SERVER_ERROR;
	 }
	 transData->transState = APPROVED;
	 return  APPROVED;
 }



 EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	 if (transData->transState == DECLINED_STOLEN_CARD || transData->transState == DECLINED_INSUFFECIENT_FUND)
	 {
		 
		 return SAVING_FAILED;
	 }
	 
		 transaction[c].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
		 transaction[c].terminalData.transAmount = transData->terminalData.transAmount;

		 transaction[c].transactionSequenceNumber = transData->transactionSequenceNumber;
		 transaction[c].transState = transData->transState;
	 strcpy(transaction[c].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
	 strcpy(transaction[c].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
	 strcpy(transaction[c].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);

	 strcpy(transaction[c].terminalData.transactionDate, transData->terminalData.transactionDate);
	 sequancenumbre++;
	 return OK;
 }

 


	