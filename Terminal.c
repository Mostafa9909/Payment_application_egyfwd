#include <stdio.h>
#include "app.h"
#include "Terminal.h"
#include "Server.h"
#include "Card.h"
#include <string.h>
#include <time.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {

	printf("please enter the transaction date\n");
	unsigned char s[1000];

	gets(s);

	//   25/06/2022
	int day;
	int month;
	int year;
	termData->transactionDate[10] = NULL;

	if (strlen(s) != 10 || s == NULL) {
		return WRONG_DATE;
	}
	day = (s[0] - '0') * 10 + (s[1] - '0');
	month = (s[3] - '0') * 10 + ((s[4] - '0'));
	year = (s[6] - '0') * 1000 + (s[6] - '0') * 100 + (s[6] - '0') * 100 + (s[6] - '0') * 100;



	if (month < 1 || month >12 || day < 0 || day>30) {
		return WRONG_DATE;
	} 

	for (int i = 0; i < 11; i++) {
		termData->transactionDate[i] = s[i];
		//printf( "%c", termData->transactionDate[i]);

	}
	return OK;
	






	return OK;

}


const char* getresponce1(EN_cardError_t responce) {
	switch (responce)
	{
	case 0: return "ok";
	case 1: return "WRONG_DATE";
	case 2: return "EXPIRED_CARD";
	case 3: return "INVALID_CARD";
	case 4: return "INVALID_AMOUNT";
	case 5: return "EXCEED_MAX_AMOUNT";
	case 6: return "INVALID_MAX_AMOUNT";
	case 7: return "INVALID_CARD";
	


	}

}

isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	//TRANSACTION DATE FORMATE---> 25/06/ 2022

	//CARD EXPIRATION DATE FORMAT ---> 05 / 25
	int monthtr = (termData.transactionDate[3] - '0') * 10 + ((termData.transactionDate[4] - '0'));
	int yeartr = (termData.transactionDate[8] - '0') * 10 + (termData.transactionDate[9] - '0');

	int monthex = (cardData.cardExpirationDate[0] - '0') * 10 + ((cardData.cardExpirationDate[1] - '0'));
	int yearex = (cardData.cardExpirationDate[3] - '0') * 10 + (cardData.cardExpirationDate[4] - '0');
	//printf("monthtr: %d  yeartr: %d  monthex: %d  yearex:  %d", monthtr, yeartr, monthex, yearex);


	if (yearex > yeartr) {
		return OK;
	}
	if (yearex == yeartr) {
		if (monthex > monthtr) {
			return OK;
		}
	}
	return EXPIRED_CARD;


}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf(" please enter Transaction Amount\n");
	float s=0;
	scanf("%f", &s);
	if ( s <= 0) {
		return INVALID_AMOUNT;
	}
	termData->transAmount = s;
		return OK;
	
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf(" please enter maximum Amount\n");
	float s = 0;
	scanf("%f", &s);
	if (s <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	termData->maxTransAmount = s;
	return OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	//printf("max%f    trans%f", termData->maxTransAmount, termData->transAmount);
	if (termData->maxTransAmount >= termData->transAmount) {
		
		return OKk;
	}
	return EXCEED_MAX_AMOUNT;
}