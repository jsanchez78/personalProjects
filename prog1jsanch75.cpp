#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
using namespace std;
char notsorandom; // Global variable which will be the correct guess everytime


///Menu function which is called everytime the program runs in the main

void menu(){
    cout << "\n\nProgram #1: Mind Reader" << endl;
    cout << "Author: Jacob Sanchez" << endl;
    cout << "Date: June 22, 2018" << endl;
    cout << "System:   C++ in Atom on Mac" << "\n\n\n";

}
///This function generates the random letter which will be on the diagnol (multiples of 9)
//The function returns that letter as a char
char diagnol(){
    //generating a random letter whcih will be placed along the diagonal
    srand(time(0));
    int randnum = rand() % 57+65;
    while(randnum>90 && randnum<97){
        randnum = rand() % 57+65;
    }
    char randchar = (char) randnum;
    return randchar;
}
///This function tells the user what to input and prints the correct guess to the screen
void user(){
    int digit;
    cout << "Enter a two digit number between 10-99: " << endl;
    cin >> digit;
    while(digit > 99 || digit < 10){
        cout << "Enter a valid number below: " << endl;
        cin >> digit;
    }
    cout << "You chose the number: " << digit << endl;
    //Displaying the users digit - (onesplace + tens place)
    int tensplace = digit/10;
    int onesplace = digit % 10;
    int subtraction = digit - (tensplace + onesplace);
    cout << digit << " - (" << tensplace << " + " << onesplace << ") = " << subtraction << endl;
    cout << "The letter corresponding to " << subtraction <<" is " << notsorandom << endl;
}

//Main function displays the grid
//Also calls other functions of course
int main(){
    srand(time(0));
    menu();
    notsorandom = diagnol();
    //Displaying the grid with the random letters on the screen
    for(int i=99;i>=0;i--){
        int randnum = rand() % 57+65;
        while(randnum>90 && randnum<97){
            randnum = rand() % 57+65;
        }
        char randchar = (char) randnum;
        cout << setw(4) << i <<":" << randchar;
        if(i % 9 ==0 && i % 10 != 0 && i != 90){
            cout << "\b" << notsorandom;
        }
        else if(i % 10 == 0 && i != 90){
            cout << endl;
        }
        else if(i == 90){
            cout << "\b" << notsorandom << endl;

        }
    }
    user();
    main();
}
