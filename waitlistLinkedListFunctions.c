#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "restuarantWaitlist.h"



extern debugMode;

void doAdd (waitlist **hd, int debugMode)
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Add command requires an integer value of at least 1\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }

    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Add command requires a name to be given\n");
        printf ("Add command is of form: a <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }

    printf ("Adding In-restaurant group \"%s\" of size %d\n", name, size);

    // add code to perform this operation here

    if (doesNameExist(hd, name)){
        printf("adding in-resturant group %s\n of size %d\n", name, size);
        return;
    }
    else{
        if (debugMode== TRUE){
            displayListInformation(hd);
        }
        printf("Adding group %s of size %d",name , size);
        addToList(hd,name,size,waiting);
        return;
    }


}

void doCallAhead (waitlist** hd,int debugMode)
{
    /* get group size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 1\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }

    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Call-ahead command requires a name to be given\n");
        printf ("Call-ahead command is of form: c <size> <name>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        printf ("         <name> is the name of the group making the reservation\n");
        return;
    }

    printf ("Adding Call-ahead group \"%s\" of size %d\n", name, size);

    //check if the name already exists in the waitlist
    if(doesNameExist(hd, name)){
        printf("Name already exists in the wait list\n");
        return;
    }
///The group meets all requirements
    else{
        if(debugMode == TRUE){
            displayListInformation(hd);
        }
        printf ("Call-ahead group \"%s\" of size %d\n", name, size);
        addToList(hd, name, size, called);
        return;
    }
}

void doWaiting (waitlist** hd,int debugMode)
{
 /* get group name from input */
 char *name = getName();
 //char *status = getStatus();
 if (NULL == name)
   {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
   }
 printf ("Call-ahead group \"%s\" is now waiting in the restaurant\n", name);
 // change status of group waiting
  if(doesNameExist(hd, name)==0){
  		if(debugMode == TRUE){
  			displayListInformation(hd);
  		}
  		printf("Name does not exist in wait list\n");
  		return;
  	}
  updateStatus(hd, name, debugMode);
}
void doRetrieve (waitlist** hd)
{
    /* get table size from input */
    int size = getPosInt();
    if (size < 1)
    {
        printf ("Error: Retrieve command requires an integer value of at least 1\n");
        printf ("Retrieve command is of form: r <size>\n");
        printf ("  where: <size> is the size of the group making the reservation\n");
        return;
    }
    clearToEoln();
    printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

    // add code to perform this operation here
    retrieveAndRemove(hd,size,debugMode);
}
void doList (waitlist** hd)
{
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: l <name>\n");
        printf ("  where: <name> is the name of the group to inquire about\n");
        return;
    }

    printf ("Group \"%s\" is behind the following groups\n", name);

    //Print out groups ahead of certain
    if(doesNameExist(hd, name)){
		printf("Number of groups ahead of \"%s\": %d\n", name, countGroupsAhead(hd, name, debugMode));
		printf ("Group \"%s\" is behind the following groups\n", name);
		//list size of each group
		displayGroupSizeAhead(hd, countGroupsAhead(hd, name, debugMode));
		return;
	}
 	//add to back of the list
	else{
		printf("Name does not exist in list\n");
		return;
	}

}
void doDisplay (waitlist** hd)
{
    clearToEoln();
    printf ("Display information about all groups\n");

    // add code to perform this operation here
    displayListInformation(hd);
}
