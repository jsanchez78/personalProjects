#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 typedef struct StackStruct{
                unsigned capacity;
                int top;
                char* darr;
        } Stack;
        ///initialize stack
        void init(Stack* s){
                s->capacity = 2;
                s->darr = (char*)malloc(sizeof(char)*(s->capacity));
                s->top = 0;
        }
	///Check if stack is empty
        bool is_empty(Stack* s){
                if(s->top == 0)
                  return 1;
                else
                  return 0;
        }
	char top(Stack* s){
        return s->darr[s->top-1];
        }
        bool is_full(Stack* s){
                if(s->top >= (s->capacity))
                  return 1;
                else
                  return 0;
        }
        void pop(Stack* s){
          if(is_empty(s))
              printf("Stack is already empty!\n");
          else if(top(s)=='\0')
            s->top = s->top - 2;
          else
            s->top = s->top - 1;
      }
        void grow(Stack* s){
          char* grow;
          grow = s->darr;
          s->capacity = s->capacity + 2;
          s->darr = (char*)malloc(sizeof(char)*(s->capacity));
          int i;
          for(i=0;i<(s->top);i++){
                  s->darr[i] = grow[i];
          }
          free(grow);
          grow = NULL;
        }
        void push(Stack* s,char *input,int i){
                    if(is_full(s)){
                      grow(s);
                      printf("Pheeww, we avoided a stack overflow!\n");
                      s->darr[s->top] = input[i];//-3 because size grew by 2
                      s->top = s->top + 1;
                    }
                    else{
                      s->darr[s->top] = input[i];
                      s->top = s->top + 1;
              }
      }
              void reset(Stack* s){
                      free(s->darr);
                      s->darr = NULL;
                      s->capacity = 0;
                      s->top = -1;
              }
int main (int argc, char** argv){
  Stack symbols;
  init(&symbols);
  char input[301];
  char popped_value;
  char missing_symbol;
  /* set up an infinite loop */
  while (1)
  {
    /* get line of input from standard input */
    printf ("\nEnter input to check or q to quit\n");
    fgets(input, 300, stdin);

    /* remove the newline character from the input */
    int i = 0;
    while (input[i] != '\n' && input[i] != '\0')
    {
       i++;
    }
    input[i] = '\0';
    /* check if user enter q or Q to quit program */
    if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
      break;
    printf ("%s\n", input);
    /* run the algorithm to determine is input is balanced */
         int j;
         for(j=0;j<i;j++){
                 if(input[j] == '(' || input[j] == '[' || input[j] == '<' || input[j] == '{')
                         push(&symbols,&input[j],j);
                 else if(input[j] == ')' || input[j] == ']' || input[j] == '>' || input[j] == '}'){
                               popped_value=top(&symbols);
                               pop(&symbols);
                               printf("%s\n",&popped_value);
                           }
         }
         if(is_empty(&symbols)){
           reset(&symbols);
         }
        else{
          missing_symbol = top(&symbols);
          switch(missing_symbol){
            case '{':
              printf("Your missing '}' symbol!\n");
              break;
            case '(':
              printf("Your missing ')' symbol!\n");
              break;
            case '<':
              printf("Your missing '>' symbol!\n");
              break;
            case '[':
              printf("Your missing ']' symbol!\n");
              break;
            default:
              printf("%c\n",missing_symbol);
              printf("Expresion is balanced!\n");
              break;
          }//End of switch statement
        }///Checking to see what symbols are missing (why stack is not empty)
       }///End of While loop
  printf ("\nGoodbye\n");
  return 0;
}
