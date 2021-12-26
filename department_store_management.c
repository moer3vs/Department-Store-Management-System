#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 20


// Struct definitions
typedef struct items
{
    char itemCode[MAX];
    char itemName[MAX];
    int quantity;
    float rate;
    char description[MAX];
}Item;

Item item;

void options();
int isCodeAvailable();
void addProd();
void deleteProd();
void editProd();
void display();

int main()
{
    options();
    system("cls");
    return 0;
}


void options()
{
    int choice;

    do
    {
        printf("\t\t\t\t\t******DEPARTMENT STORE MANAGEMENT******");
        printf("\n\t\t\t\t\t---------------------------------------");
        printf("\n\t\t\t\t\t\t1. ADD A PRODUCT");
        printf("\n\t\t\t\t\t\t2. DELETE A PRODUCT");
        printf("\n\t\t\t\t\t\t3. EDIT A PRODUCT");
        printf("\n\t\t\t\t\t\t4. DISPLAY STORE");
        printf("\n\t\t\t\t\t\t5. EXIT THE RROGRAM");
        printf("\n\t\t\t\t\t---------------------------------------\n");
        printf("\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            system("cls");
            addProd();
            break;
        case 2:
            system("cls");
            deleteProd();
            break;
        case 3:
            system("cls");
            editProd();
            break;
        case 4:
            system("cls");
            display();
            break;
        case 5:
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n");
            printf("\n\n\n\t\t\t\t\t    Thanks for using my program!\n\n\n");
            getch();
            exit(0);
            break;
        default:
            printf("\n\t\t\t\t\tWrong entry. Enter a number between 0 & 6\n\n\n");
            break;
        }
    } while (choice != 5);
}

// A function to check if the code is already available
int isCodeAvailable(char code[])
{
    FILE *file;
    file = fopen("Record.txt", "r");
    if(file == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file!\n");
        exit(1);
    }

    // fread will keep reading until it reaches the EOF, then it'll return 0
    // fread returns the number of bytes read from a file stream
    // We can also use feof to check if the program reached the EOF
    // EX: while(!feof(file))
    while (fread(&item, sizeof(item), 1, file))
    {
        if(strcmp(code, item.itemCode) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void addProd()
{
    char code[MAX];
    FILE *file;
    file = fopen("Record.txt", "a");
    if(file == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file!\n");
        exit(1);
    }

    display();
jump:
    printf("\t\t\t\t\t    *****ADDING A PRODUCT*****\n\n");
    printf("\t\t\t\t   Enter \"end\" if you want to go back to main menu\n\n");
    printf("\t\t\t\t\t\tProduct Code:");
    scanf("%s", code);

    // If the user entered "end", the program will exist the function
    if (strcmp(code, "end") == 0)
    {
        system("cls");
        options();
    }

    // Checking if the code is already available in the .txt file
    // return 1 if found, 0 if not found
    if(isCodeAvailable(code) == 1)
    {
        printf("\n\n\t\t\t\t\tProduct already exists!\n\n\n");
        getch();
        // Goes to jump if the product already
        // exists to reprompt the user for input
        goto jump;
    }

    // Copying the code the user entered into the item struct
    strcpy(item.itemCode, code);

    printf("\t\t\t\t\t\tProduct Name:");
    scanf("%s", item.itemName);

    printf("\t\t\t\t\t\tProduct Rate:");
    scanf("%f", &item.rate);

    printf("\t\t\t\t\t\tProduct Quantity:");
    scanf("%d", &item.quantity);

    printf("\t\t\t\t\t\tDescription:");
    scanf("%s", item.description);

    // Writing the item struct into the file
    if(fwrite(&item, sizeof(item), 1, file))
    {
        printf("\n\t\t\t\t\t  Data has been stored successfully!\n\n\n");
    }
    fclose(file);
}

void deleteProd()
{
    FILE *file1, *file2;
    char code[MAX];

    file1 = fopen("Record.txt", "r");
    file2 = fopen("temp.txt", "w");
    if(file1 == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file 1!\n");
        exit(1);
    }

    if(file2 == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file 2!\n");
        fclose(file1);
        exit(1);
    }

    display();
jump:
    printf("\t\t\t\t\t    *****DELETING A PRODUCT*****\n\n");
    printf("\t\t\t\t   Enter \"end\" if you want to go back to main menu\n\n");
    printf("\t\t\t\t   Enter the code of the product you want to delete: ");
    scanf("%s", code);

    // If the user entered "end", the program will exist the function
    if (strcmp(code, "end") == 0)
    {
        system("cls");
        options();
    }

    // Checking if the code is already available in the .txt file
    // return 1 if found, 0 if not found
    if(isCodeAvailable(code) == 0)
    {
        printf("\n\n\t\t\t\t\t\tProduct doesn't exist!\n\n\n");
        getch();
        goto jump;
    }

    /* Read through record.txt file, and write the data into temp.txt file
    while only ignoring the item to be deleted. Then overwrite record.txt file
    using the temp.txt file we created */
    while (fread(&item, sizeof(item), 1, file1))
    {
        if (strcmp(code, item.itemCode) != 0)
        {
            fwrite(&item, sizeof(item), 1, file2);
        }
    }
    fclose(file1);
    fclose(file2);

    file1 = fopen("Record.txt", "w");
    file2 = fopen("temp.txt", "r");

    if(file1 == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file 1!\n");
        exit(1);
    }

    if(file2 == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file 2!\n");
        fclose(file1);
        exit(1);
    }

    while (fread(&item, sizeof(item), 1, file2))
    {
        fwrite(&item, sizeof(item), 1, file1);
    }

    printf("\n\v\t\t\t\t\t   Product deleted sucessfully!\n\n\n\n");

    fclose(file1);
    fclose(file2);
}

void editProd()
{
    char code[MAX];
    FILE *file1, *file2;

    display();
jump:
    printf("\t\t\t\t\t    *****UPDATING A PRODUCT*****\n\n");
    printf("\t\t\t\t   Enter \"end\" if you want to go back to main menu\n\n");
    printf("\t\t\t\t   Enter the code of the product you want to edit: ");
    scanf("%s", code);

    // If the user entered "end", the program will exist the function
    if (strcmp(code, "end") == 0)
    {
        system("cls");
        options();
    }

    /* Checking if the code is already available in the .txt file.
    It returns 1 if found, 0 if not found */
    if(isCodeAvailable(code) == 0)
    {
        printf("\n\n\t\t\t\t\t\tProduct doesn't exist!\n\n\n");
        getch();
        goto jump;
    }

    file1 = fopen("Record.txt", "r");
    file2 = fopen("temp.txt", "w");
    if(file1 == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file 1!\n");
        exit(1);
    }

    if(file2 == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file 2!\n");
        fclose(file1);
        exit(1);
    }

    /* A loop to search for the desired item code by reading
    through the whole file until it reaches the EOF.
    It'll keep writing data read from record.txt to temp.txt
    until it reaches the desired code, then it'll ask the user
    to enter the updated info. After writing data into temp.txt
    successfully, it'll write the data into the original record.txt
    file to update it */
    while(fread(&item, sizeof(item), 1, file1))
    {

        if(strcmp(code, item.itemCode) != 0)
        {
            fwrite(&item, sizeof(item), 1, file2);
        }
        else
        {
            printf("\t\t\t\t\t\tProduct Name:");
            scanf("%s", item.itemName);

            printf("\t\t\t\t\t\tProduct Rate:");
            scanf("%f", &item.rate);

            printf("\t\t\t\t\t\tProduct Quantity:");
            scanf("%d", &item.quantity);

            printf("\t\t\t\t\t\tDescription:");
            scanf("%s", item.description);

            fwrite(&item, sizeof(item), 1, file2);
        }
    }
    fclose(file1);
    fclose(file2);

    /* After saving the required data in temp.txt file, we'll overwrite
    the data from temp.txt to the original file record.txt */
    file1 = fopen("Record.txt", "w");
    file2 = fopen("temp.txt", "r");
    if(file1 == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file 1!\n");
        exit(1);
    }

    if(file2 == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file 2!\n");
        fclose(file1);
        exit(1);
    }

    while(fread(&item, sizeof(item), 1, file2))
    {
        fwrite(&item, sizeof(item), 1, file1);
    }

    printf("\n\n\t\t\t\t\tData has been updated successfully\n\n\n");

    fclose(file1);
    fclose(file2);
}

void display()
{
    int count = 0;
    FILE *file;
    file = fopen("Record.txt", "r");
    if(file == NULL)
    {
        printf("\n\n\t\t\t\tError occurred while opening the file!\n");
        exit(1);
    }

    printf("\t\t\t\t\t\t    AVAILABLE PRODUCTS\n");
    printf("\t\t\t\t\t\t***************************\n");
    printf("\t\t\t-------------------------------------------------------------------------\n");
    printf("\t\t\t CODE\t||    NAME\t||     RATE\t||   QUANTITY   ||  DESCRIPTION \n");
    printf("\t\t\t-------------------------------------------------------------------------\n");

    /*  Reading the item structs from the record.txt and printing them
    out to the console. Counter is a flag that checks if there
    are any products available or not */
    while (fread(&item, sizeof(item), 1, file))
    {
        printf("\t\t\t  %s\t||   %s\t||     %.2f\t||     %d\t||  %s\t\n", item.itemCode, item.itemName, item.rate, item.quantity, item.description);
        count++;
    }
    printf("\t\t\t-------------------------------------------------------------------------\n\n\n");

    /* If no items were found */
    if (count == 0)
    {
        system("cls");
        printf("\n\t\t\t\t\t   *No products available in store\n\n\n");
        getch();
    }
    fclose(file);
}

