#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
static float balance = 0;


/*
Exit Error Codes:
1 - pSize exceeds maximum value of 30. int array pCards can only hold 30 values.
2 - dSize exceeds maximum value of 30. int array dCards can only hold 30 values.
*/


float deposit(float x);
float placebet(float balance);
int play(float bet);
void gameUpdate(int *pCards, int*dCards, int pSize, int dSize);

void gameUpdate(int *pCards, int*dCards, int pSize, int dSize){
	int dTot = 0;
	int dAce = 0;
	int pTot = 0;
	int pAce = 0;
	system("CLS");
	printf("Dealer Shows: ");
	Sleep(100);
	for(int i = 0; i < dSize; i++){
		if(dCards[i] == 1){
			printf("A ");
			dTot += 11;
			dAce++;
		}else{
			printf("%d ",dCards[i]);
			dTot += dCards[i];
		}
	}
	if(dTot > 21 && dAce > 0){
		dTot -= 10;
		dAce --;
	}
	printf("(%d)",dTot);
	printf("\n");
	printf("Player Shows: ");
	Sleep(100);
	for(int i = 0; i < pSize; i++){
		if(pCards[i] == 1){
			printf("A ");
			pTot += 11;
			pAce++;
		}else{
			printf("%d ",pCards[i]);
			pTot += pCards[i];
		}
		if(pTot > 21 && pAce > 0){
			pAce--;
			pTot-=10;
		}
	}
	
	printf("(%d)",pTot);
	printf("\n");
}

float deposit(float x){
	do{
		system("CLS");
		float y;
		printf("Deposit Amount: ");
		scanf("%f",&y);
		if(y > 0)
			return y;
		printf("Invalid Amount.\nPlease Try Again.\n");
	}while(1);
}

float placebet(float balance){
	float bet;
	printf("Enter Bet Amount: ");
	do{
		scanf("%f",&bet);
		if(bet > 0 && bet <= balance)
			break;
		else if(bet > balance){
			printf("You do not have enough balance to cover your bet.\nPlease enter valid bet amount: ");
			continue;
		}
		printf("Bet must be larger than 0.\nPlease enter valid bet amount: ");
	}while(1);
	float bj = 1.5 * bet;
	//Return 0-Lose 1-Win 2-Push 3-Blackjack 4-Double Win 5- Double Lose//
	switch(play(bet)){
		case 0:
			printf("You lost %.2f \n",bet);
			getch();
			return balance-bet;
		break;
		case 1:
			printf("You won %.2f \n",bet);
			getch();
			return balance+bet;
		break;
		case 2:
			getch();
			return balance;
		break;
		case 3:
			printf("\nYou won %.2f \n",bet*1.5);
			getch();
			return balance+bj;
		break;
		case 4:
			printf("You won %.2f \n",bet*2);
			getch();
			return (balance+bet+bet);
		break;
		case 5:
			printf("You lost %.2f \n",bet*2);
			getch();
			return (balance-bet-bet);
		break;
		default:
			getch();
		break;
	}
}

int play(float bet){
	system("CLS");
	int pCards[30];
	int dCards[30];
	do{
		dCards[0] = rand() % 13;
	}while(dCards[0] == 0);
	//dCards[0] = 1;//ForceDealerAce
	if (dCards[0] > 10)
		dCards[0] = 10;
	if(dCards[0] == 1)
		printf("Dealer Shows: A (11)\n");
	else
		printf("Dealer Shows: %d\n",dCards[0]);
	do{
		pCards[0] = rand() % 13;
	}while(pCards[0] == 0);
	do{
		pCards[1] = rand() % 13;
	}while(pCards[1] == 0);
	if (pCards[0] > 10)
		pCards[0] = 10;
	if (pCards[1] > 10)
		pCards[1] = 10;
	int pTotal,dTotal;
	printf("Player Shows: ");
	//pCards[0] = 1;pCards[1] =10;//Force BlackJack
	if((pCards[0] == 1 && pCards[1] == 10)||(pCards[0] == 10 && pCards[1] == 1)){
		if(dCards[0] == 1 || dCards[0] == 10){
			do{
				dCards[1] = rand() % 13;
			}while(dCards == 0);
			if(dCards[1] >= 10){
				if(dCards[0] == 1){
					system("CLS");
					printf("Dealer Shows: A 10\nPlayer Shows: A 10\nPUSH\n");
					return 2;
				}
			}
			if(dCards[1] == 1 && dCards[0] == 10){
				system("CLS");
				printf("Dealer Shows: A 10\nPlayer Shows: A 10\nPUSH\n");
				return 2;
			}
		}
		printf("A 10 \nBlack Jack! Player wins %.2f\n",bet*1.5);
		return 3;
	}else{
		for(int i = 0; i < 2; i++){
			if(pCards[i] == 1){
				printf("A ");
			}else{
				printf("%d ",pCards[i]);
			}
		}
	}
	int tempVal = pCards[0] + pCards[1];
	if(pCards[0] == 1 || pCards[1] == 1)
		tempVal += 10;
	printf("(%d)",tempVal);
	printf("\n");
	int action;
	int fMove = 0;
	int dSize = 1;
	int pSize = 2;
	//action: 0-stand 1-hit 2-double 3-split//
	do{
		if((pCards[0] == pCards[1])&&(fMove == 0)){
			printf("Stand[0] Hit[1] Double[2] Split[3]\n");
		}else{
			printf("Stand[0] Hit[1] Double[2]\n");
		}
		printf("Enter action: ");
		action = (getch() - 48);
		if((action == 3 && pCards[0] != pCards[1])||(action < 0 || action > 3)){
			system("CLS");
			gameUpdate(pCards, dCards, pSize, dSize);
			printf("Invalid Action TRY AGAIN\n");
			continue;
		}
		fMove = 1;
		if(action == 0){
			int dTot = 0;
			do{
				dTot = 0;
				do{
					dCards[dSize] = rand() % 13;
				}while(dCards[dSize] == 0);
				if (dCards[dSize] > 10)
					dCards[dSize] = 10;
				dSize++;
				if(dSize == 31)
					exit(2);
				gameUpdate(pCards, dCards, pSize, dSize);
				int dAce = 0;
				for(int i = 0; i < dSize; i++){
					if(dCards[i] == 1){
						dTot += 11;
						dAce ++;
					}else{
						dTot += dCards[i];
					}
					if(dTot > 21 && dAce > 0){
						dAce--;
						dTot-=10;
					}else if(dTot > 21 && dAce == 0){
						gameUpdate(pCards, dCards, pSize, dSize);
						printf("\nDealer Bust\n");
						return 1;
					}else if(dTot >= 17){
						int tempTot = 0;
						int tempAce = 0;
						for(int i = 0; i < pSize; i++){
							if(pCards[i] == 1){
								tempAce++;
								tempTot+=11;
							}else{
								tempTot+=pCards[i];
							}
						}
						while(tempTot > 21){
							if(tempAce == 0){
								return 0;
							}else{
								tempAce--;
								tempTot-=10;
							}
						}
						gameUpdate(pCards, dCards, pSize, dSize);
						if(tempTot == dTot){
							printf("\nPUSH\n");
							return 2;
						}else if(tempTot > dTot){
							printf("\nPlayer Wins \n");
							return 1;
						}else{
							printf("\nDealer Wins \n");
							return 0;
						}
					}
				}	
			}while(dTot < 17);
		}else if(action == 1){
			do{
				pCards[pSize] = rand() % 13;
			}while(pCards[pSize] == 0);
			if (pCards[pSize] > 10)
				pCards[pSize] = 10;
			pSize++;
			if(pSize == 31)
				exit(1);
			gameUpdate(pCards, dCards, pSize, dSize);
			int pTot = 0;
			int pAce = 0;
			for(int i = 0; i < pSize; i++){
				if(pCards[i] == 1){
					pTot += 11;
					pAce ++;
				}else{
					pTot += pCards[i];
				}
				if(pTot > 21 && pAce > 0){
					pAce--;
					pTot-=10;
				}else if(pTot > 21 && pAce == 0){
					gameUpdate(pCards, dCards, pSize, dSize);
					printf("\nPlayer Bust\nEnter any character to continue: ");
					return 0;
				}
			}
		}
	}while(action != 0 && action != 2);
}

int main(){
	srand(time(NULL));
	printf("-------------------------------\n");
	printf("----Welcome-to-BlackJack-v2----\n");
	printf("------Made-by-KingEvariste-----\n");
	printf("-------------------------------\n");
	printf("---Press-Any-Key-to-Continue---\n");
	printf("-------------------------------\n");
	getch();
	balance = deposit(balance);
	do{
		system("CLS");
		printf("Balance: %.2f\n",balance);
		if(balance > 0)
			balance = placebet(balance);
		else{
		printf("You ran out of money. Click any key to deposit more!");
		getch();
		balance = deposit(balance);
		}
	}while(1);
	return 0;
}