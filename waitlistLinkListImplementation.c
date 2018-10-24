#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "restuarantWaitlist.h"



extern debugMode;

//Enqueue newGroup onto waitlist
void addToList(waitlist** hd,char* name,int size,status status){
    waitlist* newGroup = (waitlist*)malloc(sizeof(waitlist));
    newGroup->size_of_group = size;
    newGroup->name=name;
    newGroup->next = NULL;

    ///Update status of group accordingly
    if(status==waiting)
        newGroup->status = waiting;
    else
        newGroup->status = called;

    ///No one is waiting for a seat
    if(*hd==NULL){
        *hd = newGroup;
        return;
    }
        ///There are people waiting
    else{
        waitlist* tmp = *hd;
        while(tmp->next!=NULL)
            tmp = tmp->next;
        tmp->next = newGroup; ///Enqueue newGroup to waitlist
        return;
    }
}
boolean doesNameExist(waitlist** hd,char* name){
    if(*hd==NULL)
        return 0;
    waitlist* tmp = *hd;
    while(tmp!=NULL){
        if(strcmp(tmp->name,name) == 0)
            return 1;
        tmp = tmp->next;
    }
///The name given is the first of its kind
    return 0;
}
boolean updateStatus(waitlist** hd,char* name,int debugMode){
  int i = 1;
  waitlist* tmp = *hd;
  char* stat;
	if(tmp == NULL){
		printf("List Empty: Can't Update\n");
		return FALSE;
	}
	printf("DEBUG MODE\n#\tName\tSize\tStatus\n");
  //Traverse through list until find the group
  while(tmp != NULL){
    if(debugMode == TRUE){
      if(tmp->status == waiting)
        stat = "Present";
      else
        stat = "Not Present";
      printf("%d\t%s\t%d\t%s\n", i, tmp->name, tmp->size_of_group, stat);
      i++;
    }
    if(strcmp(tmp->name, name) == 0){
      if(tmp->status == waiting){
        tmp ->status = called;
        return FALSE;
      }
      else{
        tmp->status = waiting;
        return TRUE;
      }
    }
    tmp = tmp->next;
  }
  return FALSE;
}
char* retrieveAndRemove(waitlist **hd, int tableAvailable, int debugMode){
    waitlist *tmp = *hd;
    waitlist *p;
    char* groupSeated;
    int i = 1;
    //list is empty
    if(tmp == NULL){
        printf("List empty\n");
        return groupSeated;
    }
    //Group first in line is selected off waitlist
    if(tmp->size_of_group <= tableAvailable && tmp->status == 0){
        groupSeated = tmp -> name;
        *hd = (*hd)->next;
        free(tmp);
        if(debugMode == TRUE){
            displayListInformation(hd);
        }
        return groupSeated;
    }
    if(debugMode == TRUE)
        printf("DEBUG MODE\n#\tName\tSize\tStatus\n");
    //Group after the first in line is selected off of waitlist
    while(tmp->next != NULL){
        if(debugMode == TRUE){
            char *stat;
            if(tmp->status == waiting)
                stat = "Present";
            else
                stat = "Not Present";
            printf("%d\t%s\t%d\t%s\n", i, tmp->name, tmp->size_of_group, stat);
            i++;
        }
        if(tmp->next->size_of_group <= tableAvailable){
            //if(tmp->next->status == 0){
                p = tmp->next;
                tmp->next = p->next;
                groupSeated = p->name;
                free(p);
                return groupSeated;
            //}
        }
        tmp = tmp->next;
    }

    printf("No valid group size for table size\n");
    groupSeated = "No valid group!";
    return groupSeated;
}
//Display new list of groups Waiting
void displayListInformation(waitlist** hd){
    int i=1;
    char* stat;
    if(*hd==NULL){
        printf("The Waiting List is Empty\n");
        return;
    }
    waitlist* tmp = *hd;
    while(tmp!=NULL){
        if(tmp->status==waiting)
            stat = "The Group is here!";
        else
            stat = "The Group is not here!";
        printf("#%d Name: %s Size: %d Status %s\n",i,tmp->name,tmp->size_of_group, stat);
        i++;
        tmp = tmp->next;
    }
    return;
}
int isEmpty (waitlist* hd)
{
    if (hd == NULL)
        return TRUE;
    else
        return FALSE;
}
////FALSE: Name does not exist
///TRUE: Name does exist on the waitlist



int countGroupsAhead(waitlist** hd,char* target,int debugMode){

    int counter = 0, i = 1;
    waitlist* tmp = *hd;
    if(tmp==NULL)
        return counter;
    if(debugMode == TRUE)
        printf("DEBUG MODE\n#\tName\tSize\tStatus\n");
    while(tmp!=NULL){
        if(debugMode == TRUE){
            char *stat;
            if(tmp->status == waiting)
                stat = "Present";
            else
                stat = "Not Present";
            printf("%d\t%s\t%d\t%s\n", i, tmp->name, tmp->size_of_group, stat);
            i++;
        }
        if(strcmp(tmp->name, target) == 0){
            return counter;
        }
        counter++;
        tmp = tmp->next;
    }
    printf("%s is not on the waitlist: ",target);
    counter = -1;
    return counter;
}
void displayGroupSizeAhead(waitlist** hd,int groupsAhead){
    waitlist* tmp = *hd;
    int counter = 0,i = 1;
    char *stat;
    if(tmp == NULL){
      printf("List is empty\n");
      return;
    }
    if(counter == groupsAhead){
  		printf("First on the list: No groups ahead\n");
  		return;
  	}
    printf("#\tName\tSize\tStatus\n");
    while(counter!=groupsAhead && tmp!=NULL){
        if(tmp->status == waiting)
            stat = "Present";
        else
            stat = "Not Present";
        printf("%d %s %d %s \n",i,tmp->name,tmp->size_of_group,stat);
        tmp = tmp->next;
        i++;
        counter++;
    }
}
