#include <stdio.h>
#include "app.h"
#include "Terminal.h"
#include "Server.h"
#include "Card.h"
#include <string.h>
#include <time.h>



int main() {
	ST_cardData_t cardData ;
	ST_terminalData_t termData;
	

	//printf("%s\n", getresponce(getCardHolderName(&cardData)));
	
	//printf("%s\n", getresponce(getCardExpiryDate(&cardData)));

	 //printf("%s\n", getresponce(getCardPAN(&cardData)));
	//printf("%s\n", getresponce1(getTransactionDate(&termData)));
	//printf("%s\n", getresponce1(isCardExpired(cardData , termData)));
	//printf("%s\n", getresponce1(getTransactionAmount(&termData)));
	//printf("%s\n", getresponce1(setMaxAmount(&termData)));
	//printf("%s\n", getresponce1(isBelowMaxAmount(&termData)));

	//filltransaction(&transaction);
	//printf("%s\n" , serverresponce(isValidAccount(&cardData)));

	//printf("%s\n", serverresponce(isAmountAvailable(&termData)));

	///////////////////////////////////////////////////
	// card data

	/*int x = getCardHolderName(&cardData);
	while (1) {
		if (x != OK) {
		printf("wrong name\n");
		getCardHolderName(&cardData);
		}
		else
			break;
		
	}*/

	char ss[100];
	strcpy(ss, getresponce(getCardHolderName(&cardData)));

	while (strcmp(ss, "WRONG_NAME") == 0) {
		printf("wrong name\n");
		strcpy(ss, getresponce(getCardHolderName(&cardData)));
	}

	getCardExpiryDate(&cardData);
	getTransactionDate(&termData);

	if (isCardExpired(cardData, termData) == EXPIRED_CARD) {
		printf("Card Expired");
		return 0;
	}

	getCardPAN(&cardData);

	if (isValidAccount(&cardData) != SERVER_OK) {
		printf("No valid account");
		return 0;
	}
	//terminal data
	

	


	getTransactionAmount(&termData);
	setMaxAmount(&termData);
	if (isBelowMaxAmount(&termData) != OKk) {
		printf("EXCEED_MAX_AMOUNT");
		return 0;
	}
	// server 
	// 


	
	

	if (isAmountAvailable(&termData)== LOW_BALANCE) {
		printf("low balance");
		return 0;
	};

	
	

	ST_transaction_t transaction = { cardData , termData , 0 , 0 };
	//printf("%s", serverresponce(recieveTransactionData(&transaction)));
	 ;
	if (recieveTransactionData(&transaction) == APPROVED) {
		printf("process approved");
	}
	else{
		printf("Error");
	}
	

	return 0;
	 
}