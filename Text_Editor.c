#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define strong "\e[1m"
#define light "\e[2m"
#define em "\e[3m"
#define undscrl "\e[4m"
#define clear "\e[0m"
#define new_node (struct Node *)malloc(sizeof(struct Node))

int text_count = 0;
int prev;
int number;
char word[100];
char reff[100];
char alt[100];
char x[100];

struct Node
{
    char data[100];
    struct Node *next;
} *backup = NULL, *backup1 = NULL, *rev = NULL, *front = NULL, *rear = NULL;

void push(struct Node **tmp, char *data)
{
    struct Node *t = new_node;
    if (t == NULL)
    {
        printf("STACK OVERFLOW\n");
    }
    else
    {
        strcpy(t->data, data);
        t->next = *tmp;
        *tmp = t;
    }
}

char *pop(struct Node **tmp)
{
    struct Node *t;
    if (tmp == NULL)
    {
        printf("STACK UNDERFLOW\n");
        exit(1);
    }
    else
    {
        t = *tmp;
        *tmp = (*tmp)->next;
        strcpy(x, t->data);
        free(t);
    }
    return x;
}

char *top(struct Node **tmp)
{
    strcpy(x, (*tmp)->data);
    return x;
}

int empty(struct Node **tmp)
{
    return (*tmp == NULL);
}

void txt_push(char *data)
{
    struct Node *t;
    t = (struct Node *)malloc(sizeof(struct Node));
    strcpy(t->data, data);
    t->next = NULL;
    if (front == NULL)
    {
        front = rear = t;
    }
    else
    {
        rear->next = t;
        rear = t;
    }
}
char *txt_pop()
{
    struct Node *t;
    if (front == NULL)
    {
        printf("TXT is Empty\n");
    }
    else
    {
        strcpy(x, front->data);
        t = front;
        front = front->next;
        free(t);
    }
    return x;
}

char *txt_top()
{
    strcpy(x, front->data);
    return x;
}

int txt_empty()
{
    return (front == NULL);
}

void enter()
{
    char s[100];
    printf("Enter the Text : ");
    scanf(" %[^\n]s", s);
    int n = strlen(s), k = 0;
    for (int i = 0; i < n; i++)
    {
        alt[k] = s[i];
        if (s[i] == ' ' || i == n - 1)
        {
            txt_push(alt);
            text_count++;
            memset(alt, '\0', strlen(alt));
            k = -1;
        }
        k++;
    }
    printf("\n");
}

void printem()
{
    if (txt_empty())
    {
        printf(em "Nothing to print.. Please Enter Text\n\n" clear);
        enter();
    }
    else
    {
        do
        {
            strcpy(reff, txt_top());
            txt_pop();
            push(&backup, reff);
            printf(em "%s" clear, reff);
        } while (!txt_empty());
        while (!empty(&backup))
        {
            push(&rev, top(&backup));
            pop(&backup);
        }
        while (!empty(&rev))
        {
            txt_push(top(&rev));
            pop(&rev);
        }
        printf("\n\n");
    }
}

void printbold()
{
    if (txt_empty())
    {
        printf(strong "Nothing to print.. Please Enter Text\n\n" clear);
        enter();
    }
    else
    {
        do
        {
            strcpy(reff, txt_top());
            txt_pop();
            push(&backup, reff);
            printf(strong "%s" clear, reff);
        } while (!txt_empty());
        while (!empty(&backup))
        {
            push(&rev, top(&backup));
            pop(&backup);
        }
        while (!empty(&rev))
        {
            txt_push(top(&rev));
            pop(&rev);
        }
        printf("\n\n");
    }
}

void printundscrl()
{
    if (txt_empty())
    {
        printf(undscrl "Nothing to print.. Please Enter Text\n\n" clear);
        enter();
    }
    else
    {
        do
        {
            strcpy(reff, txt_top());
            txt_pop();
            push(&backup, reff);
            printf(undscrl "%s" clear, reff);
        } while (!txt_empty());
        while (!empty(&backup))
        {
            push(&rev, top(&backup));
            pop(&backup);
        }
        while (!empty(&rev))
        {
            txt_push(top(&rev));
            pop(&rev);
        }
        printf("\n\n");
    }
}

void delete_Last()
{
    prev = 1;
    if (txt_empty())
    {
        printf(light "Nothing to delete\n\n" clear);
        enter();
    }
    else
    {
        while (!txt_empty())
        {
            push(&rev, txt_top());
            txt_pop();
        }
        push(&backup1, top(&rev));
        pop(&rev);
        printf(light "Last word deleted\n\n" clear);
        while (!empty(&rev))
        {
            push(&backup, top(&rev));
            pop(&rev);
        }
        while (!empty(&backup))
        {
            txt_push(top(&backup));
            pop(&backup);
        }
    }
    text_count--;
}

void undo()
{
    if(prev == 1)
    {
        if (empty(&backup1))
        {
            printf(light "Nothing to Undo\n\n" clear);
        }
        else
        {
            while (!txt_empty())
            {
                push(&rev, txt_pop());
            }
            push(&rev, top(&backup1));
            pop(&backup1);
            printf(light "Undo performed\n\n" clear);
            while (!empty(&rev))
            {
                push(&backup, top(&rev));
                pop(&rev);
            }
            while (!empty(&backup))
            {
                txt_push(top(&backup));
                pop(&backup);
            }
        }
        prev = 3;
        text_count++;
    }
    else if(prev == 2)
    {
        struct Node *p = front;
        for (int i = 1; i < number; i++)
        {
            p = p->next;
        }
        strcpy(p->data, word);
        printf(light "Undo performed\n\n" clear);
        prev = 3;
    }
    else
    {
        printf(light "Nothing to Undo\n\n" clear);
    }
}

void display()
{
    printf("1. Bold\n2. Italic\n3. Underlined\n\n");
    printf("Enter the preffered number : ");
    int choice;
    scanf("%d", &choice);
    printf("\n");
    if (choice == 1)
    {
        printbold();
    }
    else if (choice == 2)
    {
        printem();
    }
    else if (choice == 3)
    {
        printundscrl();
    }
    else
    {
        printf(strong "Invalid choice , enter Again\n\n" clear);
    }
}

void erase()
{
    if (txt_empty())
    {
        printf(light "Nothing to Erase\n\n" clear);
    }
    else
    {
        while (!txt_empty())
        {
            txt_pop();
        }
        while (!empty(&backup1))
        {
            pop(&backup1);
        }
        printf(light "Text has be Erased\n\n" clear);
    }
    text_count = 0;
}

void replace()
{
    printf("Enter the value of N : ");
    int n;
    scanf("%d", &n);
    if(text_count != 0 && (n <= text_count && n >= 1))
    {
        prev = 2;
        number = n;
        printf("\nEnter the new word : ");
        char s[100];
        scanf(" %[^\n]s", s);
        struct Node *p = front;
        for (int i = 1; i < n; i++)
        {
            p = p->next;
        }
        strcpy(word, p->data);
        strcpy(p->data, s);
        printf(light "\nText Replaced\n\n" clear);
    }
    else if(text_count == 0)
    {
        printf(light "No text available to replace\n\n" clear);
    }
    else
    {
        printf(light "Invalid Value Of n\n\n" clear);
    }
}

int main() // main function
{
    int choice;
    do
    {
        system("cls");
        printf("1. ENTER TEXT\n2. DISPLAY\n");
        printf("3. DELETE LAST WORD \n4. REPLACE Nth WORD\n");
        printf("5. UNDO LAST OPERATION\n6. ERASE FULL TEXT\n7. EXIT\n\n");
        printf("Enter Your Choice : ");
        scanf("%d", &choice);
        printf("\n");
        if (choice == 1)
            enter();
        else if (choice == 2)
            display();
        else if (choice == 3)
            delete_Last();
        else if (choice == 4)
            replace();
        else if (choice == 5)
            undo();
        else if (choice == 6)
            erase();
        else if (choice == 7)
        {
            printf(strong "\nThankyou..................\n" clear);
            break;
        }
        else
            printf(strong "Enter a valid choice \n\n" clear);
        printf("PRESS A KEY TO CONTINUE : ");
        getch();
    } while (1);
    return 0;
}
