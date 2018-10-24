/*
 *
 *  Author: Jacob Sanchez
 *  Date: 10/23/18
 *  CS 211 Project 4: Restaurant Waitling List System
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Now we do not have to type enum everytime calling boolean
typedef enum {FALSE = 0, TRUE, NO = 0, YES}boolean;
///waiting indicates the group is physically in the Restaurant
///called indicates the group is on the waitlist but not physically inside the restaurant
typedef enum {waiting = 0, called = 1}status;
///Each Node is a group waiting
typedef struct groupStruct{
    char* name;
    int size_of_group;
    status status;
    struct groupStruct* next;
}waitlist;

void displayListInformation(waitlist** hd);
void clearToEoln();


/* FUNCTION PROTOTYPES */
/* restuarantWaitlist.c */
void clearToEoln();
int getNextNWSChar();
int getPosInt();
char *getName();
void printCommands();

/* waitlistlinkedListFunctions.c */
void doAdd(waitlist **hd, int debugMode);
void doCallAhead(waitlist **hd, int debugMode);
void doWaiting(waitlist **hd, int debugMode);
void doRetrieve(waitlist **hd, int debugMode);
void doList(waitlist **hd, int debugMode);
void doDisplay(waitlist **hd);

/* waitlistlinkedListImplementation.c */
void addToList(waitlist **hd, char *name, int size, status status);
int doesNameExist(waitlist **hd, char *name);
boolean updateStatus(waitlist **hd, char *name, int debugMode);
void retrieveAndRemove(waitlist **hd, int tableAvailable, int debugMode);
int countGroupsAhead(waitlist **hd, char *name, int debugMode);
void displayGroupSizeAhead(waitlist **hd, int groupsAhead);
void displayListInformation(waitlist **hd);
