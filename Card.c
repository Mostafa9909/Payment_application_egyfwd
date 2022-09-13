#include <stdio.h>
#include "app.h"
#include "Terminal.h"
#include "Server.h"
#include "Card.h"
#include <string.h>


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("please enter the name on the card\n");
	unsigned char s[1000];
	
	gets(s);

	(cardData)->cardHolderName[24] = NULL;

	if (strlen(s) > 24 || strlen(s) < 20 || s == NULL) {
		return WRONG_NAME;
	}
		
			
		
	
	for (int i = 0; i < strlen(s); i++) {
		(cardData)->cardHolderName[i] = s[i];
		
	}
	
	

	
		return OK;
	
	

}



EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	(cardData)->cardExpirationDate[5] = NULL;
	printf("please enter card expiration date\n");
	unsigned char s[1000];

	gets(s);

	int month;
	int year;
	

	if (strlen(s) !=5 || s == NULL ) {
		return WRONG_EXP_DATE;
	} 
	month = (s[0] - '0') * 10 + (s[1] - '0');
	year = (s[3] - '0') * 10 + ((s[4] - '0'));
	
	
	if (month < 1 || month >12 || year <22) {
		return WRONG_EXP_DATE;
	}

	for (int i = 0; i < 5; i++) {
		(cardData)->cardExpirationDate[i] = s[i];
		//printf("%c", (cardData)->cardExpirationDate[i]);
		
	}
	return OK;
	//printf("%d\n", strlen(s));


}
const char* getresponce(EN_cardError_t responce) {
	switch (responce)
	{
	case 0: return "ok";
	case 1: return "WRONG_NAME";
	case 2: return "WRONG_EXP_DATE";
	case 3: return "WRONG_PAN";

	}
}



EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("please enter the caed numbre \n");
	unsigned char s[1000];

	gets(s);



	if (strlen(s) > 19 || strlen(s) < 16 || s == NULL) {
		return WRONG_PAN;
	}
	for (int i = 0; i < 25; i++) {
		(cardData)->primaryAccountNumber[i] = NULL;
	}

	for (int i = 0; i < strlen(s); i++) {
		(cardData)->primaryAccountNumber[i] = s[i];

	}




	return OK;



}

