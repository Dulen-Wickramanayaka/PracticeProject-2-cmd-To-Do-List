#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 51

// defining the structure of one node in the list
typedef struct node{
    char task[MAX];
    struct node* next;
} node;

void manual(void); // printing the user guide
char getfunc(void); // getting the function call from user
char printerror(void); // printing a error messege if user did unrecognied thing and returns that it is an error
node *addtask(node *head); // getting a input and adding in to the linked list
void printlist(node *head); // printing the list
node *deletetask(node *head); // deleting a specific task in the list
void free_list(node *head); // freeing the allocated memmory for each node

int main(void)
{
    manual();
    //initializing the linked list
    node *list = NULL;
    while (true)
    {
        char func = getfunc(); // this is a single char which represents a specific function
    
        if(func == 'E') continue;
        else if(func == 'Q') break;
        else if(func == 'A') list = addtask(list);
        else if(func == 'V') printlist(list);
        else if(func == 'D') list = deletetask(list);
        else if(func == 'H') manual();
    }

    free_list(list);
    return 0;
}

void manual(void)
{
    printf("\nUSER MANUAL - \n");
    printf("*Each task should be smaller than 50 characters\n");
    printf("    A - add task\n    V - view list\n    D - delete task\n    Q - quit program\n    H - help\n");

}

char getfunc(void)
{
    char input;
    printf("\nEnter function: ");
    scanf(" %c", &input);  // Read a single character, space before %c skips any whitespace

    int i = 0; // i is incremented if any extra characters are inputed
    while (getchar() != '\n') i++; // Clear any extra characters remaining in the input buffer

    if (i > 0) return printerror(); // return error if more than one charcters are entered

    input = toupper(input); // uppercasing the input function call letter

    char funclist[] = "AVDQH"; // list of valid function call letters
    if (strchr(funclist, input) == NULL) return printerror(); // return error if input is not in valid list

    return input;
}

char printerror(void)
{
    printf("    Unrecognized function!\n");
    return 'E'; // E represents an error messege
}

node *addtask(node *head)
{
    node *n = malloc(sizeof(node)); // alocating memory and defining a new node
    n->next = NULL;  

    // getting user input
    char task[MAX]; // buffer to store inputted task
    printf("    Enter new task : ");
    scanf(" %[^\n]s",task);

    if(strlen(task) > MAX)
    {
        printf("    faild to add - task should be smaller than %d characters!\n", (MAX - 1));
        free(n);
        return head;
    }
    strcpy(n->task, task); // copying the inputed task to the task field in new node

    if(head == NULL) // iflist is empty making new node the first
    {
        return n;
    }

    //iterating through the list and adding new node to the end
    node *ptr = head;
    while(ptr != NULL)
    {
        if (ptr->next == NULL)
        {
            ptr->next = n;
            break;
        }
        ptr = ptr->next;
    }

    return head;
}

void printlist(node *head)
{
    if(head == NULL)
    {
        printf("    list is empty!\n");
        return;
    }
    printf("\n");
    // iterating through list and printing task field of each node
    node *ptr = head;
    int i = 1;
    while (ptr != NULL)
    {
        printf("    %2d - %s\n",i ,ptr->task);
        ptr = ptr->next;
        i++;
    }
}

node *deletetask(node *head)
{
    if (head == NULL) 
    {
        printf("    list is empty!\n");
        return NULL;
    }
    printf("    Enter the index: ");
    int index = 0;
    scanf(" %d", &index);

    index--;
    node *temp;

    if (index == 0)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    else
    {
        node *ptr = head;
        for (int i = 0; i < (index - 1); i++)
        {
            if (ptr->next->next == NULL)
            {
                printf("    Out of range!\n");
                return head;
            }
            ptr = ptr->next;
        }
        temp = ptr->next;
        ptr->next = ptr->next->next;
        free(temp);
    }
    printf("    successfully deleted requested task!\n");
    return head;
}

void free_list(node *head)
{
    if (head == NULL) return;
    free_list(head->next);
    free(head);
}
