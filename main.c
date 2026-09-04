#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 40

// Database for a library format id name author

typedef struct {
    int id;
    char book_name[DIM];
    char book_author[DIM];
} Element;

typedef struct node{
    Element d;
    struct node *next;
} node;

typedef struct node *LINK;


//proto 
void add_book(FILE *fp);
void search_book(FILE *fp);
void print_database_stats(FILE *fp);


// main 
int main(int argc, char *argv[])
{
    int menu;

    if(argc != 2) {
        printf("Error: databse name missing\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r+");
    if(fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    for(;;)
    {
        printf("\n=== MAIN MENU ===\n");
        printf("\n1) Enter new book");
        printf("\n2) Search book");
        printf("\n3) Update book");
        printf("\n4) Database stats");
        printf("\n5) Exit\n\n");

        scanf("%d",&menu);

        switch(menu)
        {
            case 1:
            {
                add_book(fp);
                break;
            }
            case 2:
            {
                search_book(fp);
                break;
            }
            
            case 3:
            {
                //modifiy book func(fp);
                break;
            }
            
            case 4:
            {
                print_database_stats(fp);
                break;
            }
            
            case 5:
            {
                printf("\nClosing the program, Goodbye!\n");
                exit(EXIT_SUCCESS);
                break;
            }
            default:
                printf("\nEnter a valid number");
        }


    }

    fclose(fp);

    return 0;
}



// Menu func: 
// op1
void add_book(FILE *fp)
{
    char buffer[DIM];
    int id,next_id;
    char book_name[DIM];
    char book_author[DIM];

    next_id = 0;

    rewind(fp);
    while (fscanf(fp, "%d %39s %39s", &id, book_name, book_author) == 3) {
        next_id = id + 1;
    }

    printf("\n\n=== New book ===");
    fprintf(fp,"%d",next_id);

    printf("\nEnter new book name: ");
    fgets(buffer, DIM, stdin);
    fgets(buffer, DIM, stdin);
    fprintf(fp,"\n%s",buffer);

    printf("\nEnter new book author: ");
    fgets(buffer, DIM, stdin);
    fprintf(fp,"%s",buffer);

    return;
}

//op2
void search_book(FILE *fp)
{
    int id,flag;
    char Sbook_name[DIM], tmp_name[DIM];
    char Sbook_author[DIM], tmp_author[DIM];

    rewind(fp);
    flag = 0;

    printf("\n\n=== Search book ===");
    printf("\nEnter book name: ");
    fgets(Sbook_name, DIM, stdin);
    fgets(Sbook_name, DIM, stdin);
    Sbook_name[strcspn(Sbook_name, "\n")] = '\0'; // remove the \n 

    printf("\nEnter new book author: ");
    fgets(Sbook_author, DIM, stdin);
    Sbook_author[strcspn(Sbook_author, "\n")] = '\0';

    while (fscanf(fp, "%d %39s %39s", &id, tmp_name, tmp_author) == 3 && !flag) {
        if(strcmp(Sbook_name,tmp_name) == 0 && strcmp(Sbook_author,tmp_author) == 0) {
            flag = 1;
        }
    }
    
    if(flag == 1) 
        printf("\nBook found!\nBook id = %d\n",id);
    else {
        printf("\nBook not found!\n");
    }
}

//op3
void update_book(FILE *fp)
{
    int id,flag;
    char tmp_name[DIM];
    char tmp_author[DIM];

    printf("\n\n=== Update book ===");
    printf("\nEnter book id: ");
    fscanf("%d",&id);

    int temp_ID;
    flag = 0;
    while (fscanf(fp, "%d %39s %39s", &temp_ID, tmp_name, tmp_author) == 3 && !flag) {
        if(temp_ID == id) {
            printf("\n== Book found ==\n");
            printf("\nName: %s",tmp_name);
            printf("\nSurname: %s\n",tmp_author);
            // update or remove book feature 
        }
    }
}

// op4 Data base stats section and list function
LINK new_node()
{
    LINK d = malloc(sizeof(node));
    if(d == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return d;
}

void free_list(LINK *lis)
{
    LINK tmp;

    while(*lis != NULL)
    {
        tmp = *lis;
        *lis = (*(lis))->next;
        free(tmp);
    }
}

void print_database_stats(FILE *fp)
{
    rewind(fp);
    int id,counter;
    char book_name[DIM];
    char book_author[DIM];
    LINK head,tail;
    head = NULL;

    rewind(fp);
    while (fscanf(fp, "%d %39s %39s", &id, book_name, book_author) == 3) {
        LINK p = new_node();
        p->next = NULL;

        p->d.id = id;
        strcpy(p->d.book_name, book_name);
        strcpy(p->d.book_author, book_author);

        if(head == NULL) {
            head = p;
            tail = p;
        }
        else {
            tail->next = p;
            tail = p;
        }
    } 

    LINK tmp = head;
    counter = 0;

    while(tmp != NULL)
    {
        counter++;
        tmp = tmp->next;


    }
    //we want to allocate the whole database as a linked list not just read from the text

    //then print some data about the database reading from the list
    printf("\n== Data Base Stats ==\n");
    printf("Total: %d\n",counter);
    printf("\n");



    free_list(head);
}

