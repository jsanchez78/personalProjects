#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;
const int ELEMENTS=21;
int winner = (ELEMENTS/2);
int previouswinner;
int numofturns=0;
int humannum;
char carrot[ELEMENTS];
int arr[3];
int history[8][2]={};
char user;
int sum;
///Next task


int endgame();
void score();
int computer();
int userinput();
int sumofpreviousthreeturns();
void table();
void displaytable();



int main(){
    table();
    displaytable();
    main();
}
//This function displays the score board and moves the carrot to correct location
//program is ended if carrot reaches either side of the board
void score(){
    switch(winner){
        case 0:
            carrot[winner]='^';
            cout << "Computer" << setw(16)<< "Human" << endl;
            cout << "x---------x+++++++++x" << endl;
            cout << "Computer wins!" << endl;
            exit(0);
        case 15:
            carrot[winner]='^';
            cout << "Computer" << setw(16)<< "Human" << endl;
            cout << "x---------x+++++++++x" << endl;
            cout << "Humamn wins!" << endl;
            exit(0);
        default:
            break;
        }
        carrot[winner]='^';
        cout << "Computer" << setw(16)<< "Human" << endl;
        cout << "x---------x+++++++++x" << endl;
        for(int i=0;i<ELEMENTS;i++){
            cout << carrot[i] << setw(2);
            if(i==20){
                cout << endl;
            }
    }

}
///function keeps track of input and checks if computer guessed move correctly
int userinput(){
    score();
    numofturns++;
    cin >> user;
    if(user=='0' || user=='1'){
        switch(user){
            case '0':
                humannum=0;
                if(humannum==computer()){
                    cout << "\nComputer gets a point: " << humannum << endl;
                    carrot[winner]=' ';
                    previouswinner=winner;
                    winner--;
                    return 0;
                }
                else{
                    cout << "\nHuman gets a point: " << humannum << endl;
                    carrot[winner]=' ';
                    previouswinner=winner;
                    winner++;
                    return 0;
                }
                break;
            case '1':
                humannum=1;
                if(humannum==computer()){
                    cout << "Computer gets a point: " << humannum << endl;
                    carrot[winner]=' ';
                    previouswinner=winner;
                    winner--;
                    return 1;
                }
                else{
                    cout << "Human gets a point: " << humannum << endl;
                    carrot[winner]=' ';
                    previouswinner=winner;
                    winner++;
                    return 1;
                }
                break;
        }
    }
    return humannum;

}


//generates random numbers for computer if first turn
//chooses opposite number as user input if 2nd or 3rd turn
///reviews previous three turns if 4th turn or later
/// views sum of the three turns
///sum of 2 or 3 indicates a higher likely hood the user will enter a 1 (i.e. 110,111,001)
///sum of 0 or 1 indicates a higher likelyhoold the user will enter a 0 (i.e. 001,100,000)

int computer(){
    int computer;
    if(numofturns==0){
        srand(time(NULL));
        computer = rand()%2;
    }
    else if(numofturns==1 || numofturns==2){
        switch(humannum){
            case 0:
                computer=1;
                break;
            case 1:
                computer=0;
                break;
            default:
                break;
        }
    }
    else if(numofturns > 2){
        switch(sum){
            case 0:
                computer=0;
                break;
            case 1:
                computer=0;
                break;
            case 2:
                computer=1;
                break;
            case 3:
                computer=1;
                break;
        }

    }
    return computer;
}
//Create a function array to keep track of previousthree values entered by the user
///Function enters the three moves into an array and computes the sum to be used by the computer to guess the next term
int sumofpreviousthreeturns(int arr[]){
    for(int i=2;i>-1;i--){
        arr[i]=userinput();
        if(i==2){
            sum=arr[i];
        }
        else{
            sum=arr[i]+sum;
        }
    }


    return sum;
}


///function indicates what the previousthree moves were and weather the computer or human had the correct guess
void table(){
    int sum = sumofpreviousthreeturns(arr);
	switch(sum){
		case 0:
			if((winner - previouswinner) < 0){
				history[0][0]=1;
			}
			else{
				history[0][1]=1;
			}
			break;
		case 1:
			if(arr[0]==1 && (winner - previouswinner < 0)){history[1][0]=1;}
			else if(arr[0]==1 && (winner - previouswinner > 0)){history[1][1]=1;}
			else if(arr[1]==1 && (winner - previouswinner < 0)){history[2][0]=1;}
			else if(arr[1]==1 && (winner - previouswinner > 0)){history[2][1]=1;}
			else if(arr[2]==1 && (winner - previouswinner < 0)){history[4][0]=1;}
			else if(arr[2]==1 && (winner - previouswinner > 0)){history[4][1]=1;}
			break;
		case 2:
			if(arr[2]==0 && (winner - previouswinner < 0)){history[3][0]=1;}
			else if(arr[2]==0 && (winner - previouswinner > 0)){history[3][1]=1;}
			else if(arr[1]==0 && (winner - previouswinner < 0)){history[5][0]=1;}
			else if(arr[1]==0 && (winner - previouswinner > 0)){history[5][1]=1;}
			else if(arr[0]==0 && (winner - previouswinner < 0)){history[6][0]=1;}
			else if(arr[0]==0 && (winner - previouswinner > 0)){history[6][1]=1;}
			break;
		case 3:
			if((winner - previouswinner) < 0){
				history[7][0]=1;
			}
			else{
				history[7][1]=1;
			}
			break;
	}
}

//function simply displays 8 x 2 array of the three recent moves
//number on the far right is the most recent value
void displaytable(){
    cout << setw(8) << "0" << setw(6) << "1" << endl;
    cout << setw(8) << "---" << setw(6) << "---" << endl;
    cout << "000" << setw(6)<< history[0][0] << setw(6) << history[0][1] << endl;
    cout << "001" << setw(6)<< history[1][0] << setw(6) << history[1][1] << endl;
    cout << "010" << setw(6)<< history[2][0] << setw(6) << history[2][1] << endl;
    cout << "011" << setw(6)<< history[3][0] << setw(6) << history[3][1] << endl;
    cout << "100" << setw(6)<< history[4][0] << setw(6) << history[4][1] << endl;
    cout << "101" << setw(6)<< history[5][0] << setw(6) << history[5][1] << endl;
    cout << "110" << setw(6)<< history[6][0] << setw(6) << history[6][1] << endl;
    cout << "111" << setw(6)<< history[7][0] << setw(6) << history[7][1] << endl;
    cout << "Previous three: " << arr[2] << arr[1] << arr[0] << endl;
}
