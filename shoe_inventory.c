#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// Struct to store shoe details
struct Shoe {
    int stockNumber;
    int styleNumber; //0 - 50
    int sizes[12]; //NUMBER OF PAIRS FOR SIZE 3 - 14
    float price;
};

// Function prototypes
void Create(struct Shoe *shoeRecord);
void Read(struct Shoe *shoeRecord);
void Update(struct Shoe *shoeRecord);
void Delete(struct Shoe *shoeRecord);
bool CheckIfExisting(int Number, int choice);

int main()
{
    int userChoice;

    while (1) {
        struct Shoe shoeRecord;

        printf("\nSHOE INVENTORY MENU:\n");
        printf("\t1: CREATE : INSERT\n");
        printf("\t2: READ : DISPLAY AS A WHOLE | SPECIFIC\n");
        printf("\t3: UPDATE : PRICE | NUMBER ON HAND\n");
        printf("\t4: DELETE : DATA | INVENTORY\n");
        printf("\t5: EXIT\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                Create(&shoeRecord);
                break;
            case 2:
                Read(&shoeRecord);
                break;
            case 3:
                Update(&shoeRecord);
                break;
            case 4:
                Delete(&shoeRecord);
                break;
            case 5:
                printf("\nDo you want to continue the exit?\n");
                printf("\tEnter Y for YES and N for NO: ");
                scanf(" %c", &userChoice);

                if (userChoice == 'Y'){
                    printf("\nThank you for using out program!");
                    return 1;
                }

                break;
        }
    }
}

// Function to create and insert a new shoe record
void Create(struct Shoe *shoeRecord) {
    FILE *inventory = fopen("inventory.txt", "a");
    if (inventory == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int i;
    char userChoice;

    while (1) {
        printf("Enter the stock number: ");
        scanf("%d", &shoeRecord->stockNumber);

        if (CheckIfExisting(shoeRecord->stockNumber, 1)) 
            printf("INPUT ANOTHER NUMBER\n");
        else
            break;
    }

    while (1) {
        printf("Enter the style number: ");
        scanf("%d", &shoeRecord->styleNumber);

        if (CheckIfExisting(shoeRecord->styleNumber, 2) || shoeRecord->styleNumber > 50) 
            printf("INPUT ANOTHER NUMBER\n");
        else
            break;
    }

    printf("Enter the price: ");
    scanf("%f", &shoeRecord->price);

    printf("\nEnter the number on hand for size 3 - 14\n");
    for (i = 0; i < 12; i++) {
        printf("Size %d: ", i + 3);
        scanf("%d", &shoeRecord->sizes[i]);
    }

    printf("\nEnter [Y] to continue the insertion and [N] for cancellation: ");
    scanf(" %c", &userChoice);

    userChoice = toupper(userChoice);

    if (userChoice == 'Y') {
        fprintf(inventory, "%d %d ", shoeRecord->stockNumber, shoeRecord ->styleNumber);

        for (i = 0; i < 12; i++)
            fprintf(inventory, "%d ", shoeRecord->sizes[i]);
        
        fprintf(inventory, "%.2f\n", shoeRecord->price);

        printf("\nSuccessfully inserted.\n");
    }
    else
        printf("\nCancellation confirmed.\n");
    
    fclose(inventory);
}

// Function to read and display shoe records
void Read(struct Shoe *shoeRecord) {
    FILE *inventory = fopen("inventory.txt", "r");
    if (inventory == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int i, userChoice, count = 1;
    bool ifFound = false;

    printf("\nMENU FOR DISPLAYING THE RECORD/S\n");
    printf("\t1: DISPLAY ALL SHOES RECORD\n");
    printf("\t2: DISPLAY SPECIFIC SHOE\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &userChoice);

    if (userChoice == 1) {
        while (fscanf(inventory, "%d %d", &shoeRecord->stockNumber, &shoeRecord->styleNumber) != EOF) {
            for (i = 0; i < 12; i++)
                fscanf(inventory, "%d", &shoeRecord->sizes[i]);
            
            fscanf(inventory, "%f", &shoeRecord->price);

            printf("\nSHOE #%d\n", count++);
            printf("STOCK NUMBER : %d\n", shoeRecord->stockNumber);
            printf("STYLE NUMBER : %d\n", shoeRecord->styleNumber);

            printf("\nNUMBER ON HAND FOR SIZE 3 - 14\n");
            for (i = 0; i < 12; i++)
                printf("SIZE %d: %d\n", i + 3, shoeRecord->sizes[i]);

            printf("\nPRICE : %.2f\n", shoeRecord->price);
        }
    }
    else if (userChoice == 2) {
        int stockNumber, styleNumber;

        printf("Enter the stock number: ");
        scanf("%d", &stockNumber);
        printf("Enter the style number: ");
        scanf("%d", &styleNumber);

        while (fscanf(inventory, "%d %d", &shoeRecord->stockNumber, &shoeRecord->styleNumber) == 2) {
            if (shoeRecord->stockNumber == stockNumber && shoeRecord->styleNumber == styleNumber) {
                for (i = 0; i < 12; i++)
                    fscanf(inventory, "%d", &shoeRecord->sizes[i]);

                fscanf(inventory, "%f", &shoeRecord->price);

                printf("\nSHOE #%d\n", count);
                printf("STOCK NUMBER : %d\n", shoeRecord->stockNumber);
                printf("STYLE NUMBER : %d\n", shoeRecord->styleNumber);

                printf("\nNUMBER ON HAND FOR SIZE 3 - 14\n");
                for (i = 0; i < 12; i++)
                    printf("SIZE %d: %d\n", i + 3, shoeRecord->sizes[i]);

                printf("\nPRICE : %.2f\n", shoeRecord->price);

                ifFound = true;
                break;
            }

            char c;
            while ((c = fgetc(inventory)) != '\n') {
                if (c == EOF)
                    break;
            }

            count++;
        }

        if (!ifFound)
            printf("\nRECORD NOT FOUND.\n");
    }

    fclose(inventory);
}

// Function to update shoe records
void Update(struct Shoe *shoeRecord) {
    FILE *inventory = fopen("inventory.txt", "r");
    if (inventory == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE *tempFile = fopen("tempFile.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int i, userChoice, stockNumber, styleNumber;
    bool ifFound = false;
    char confirmation;

    printf("\nMENU FOR UPDATING THE RECORD\n");
    printf("\t1: UPDATE THE PRICE\n");
    printf("\t2: UPDATE THE NUMBER ON HAND\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &userChoice);

    printf("Enter the stock number: ");
    scanf("%d", &stockNumber);
    printf("Enter the style number: ");
    scanf("%d", &styleNumber);

    while (fscanf(inventory, "%d %d", &shoeRecord->stockNumber, &shoeRecord->styleNumber) != EOF) {
        for (i = 0; i < 12; i++)
            fscanf(inventory, "%d", &shoeRecord->sizes[i]);

        fscanf(inventory, "%f", &shoeRecord->price);

        if (stockNumber == shoeRecord->stockNumber && styleNumber == shoeRecord->styleNumber) {
            ifFound = true;

            if (userChoice == 1) {
                float tempPrice, tempHolder;

                printf("CURRENT PRICE OF STOCK NUMBER %d: %.2f\n", shoeRecord->stockNumber, shoeRecord->price);
                printf("Enter the new price: ");
                scanf("%f", &tempPrice);

                printf("\nEnter [Y] to confirm the change price and [N] for cancellation: ");
                scanf(" %c", &confirmation);
                confirmation = toupper(confirmation);

                if (confirmation == 'Y') {
                    tempHolder = shoeRecord->price;
                    shoeRecord->price = tempPrice;
                    tempPrice = tempHolder;

                    printf("\nSuccessfully change the price from %.2f into %.2f of stock number %d.\n", tempPrice, shoeRecord->price, shoeRecord->stockNumber);
                }
                else
                    printf("\nCancellation confirmed.\n");
            }
            else if (userChoice == 2) {
                int tempSize, tempNumber, tempHolder;

                printf("\nEnter the size[3-14] to change number on hand: ");
                scanf("%d", &tempSize);

                printf("\nCURRENT NUMBER ON HAND FOR SIZE %d FOR STOCK NUMBER %d: %d\n", tempSize, shoeRecord->stockNumber, shoeRecord->sizes[tempSize - 3]);
                printf("Enter the new number on hand for size %d: ", tempSize);
                scanf("%d", &tempNumber);

                printf("\nEnter [Y] to confirm the change number on hand and [N] for cancellation: ");
                scanf(" %c", &confirmation);
                confirmation = toupper(confirmation);

                if (confirmation == 'Y') {
                    tempHolder = shoeRecord->sizes[tempSize - 3];
                    shoeRecord->sizes[tempSize - 3] = tempNumber;
                    tempNumber = tempHolder;

                    printf("\nSucessfully change the number on hand of size %d from %d into %d of stock number %d.\n", tempSize, tempNumber, shoeRecord->sizes[tempSize - 3], shoeRecord->stockNumber);
                }
                else    
                    printf("\nCancellation confirmed.\n");
            }
        }

        fprintf(tempFile, "%d %d ", shoeRecord->stockNumber, shoeRecord->styleNumber);
        for (i = 0; i < 12; i++)
            fprintf(tempFile, "%d ", shoeRecord->sizes[i]);
        fprintf(tempFile, "%.2f\n", shoeRecord->price);
    }

    if (!ifFound)
        printf("\nRECORD NOT FOUND\n");


    fclose(inventory);
    fclose(tempFile);

    remove("inventory.txt");
    rename("tempFile.txt", "inventory.txt");
}

// Function to delete shoe records
void Delete(struct Shoe *shoeRecord) {
    FILE *inventory = fopen("inventory.txt", "r");
    if (inventory == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE *tempFile = fopen("tempFile.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int i, userChoice, stockNumber, styleNumber;
    bool ifFound = false;
    char confirmation;

    printf("\nMENU FOR DELETING THE RECORD\n");
    printf("\t1: DELETE SPECIFIC SHOE RECORD\n");
    printf("\t2: DELETE WHOLE SHOE RECORD\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &userChoice);

    if (userChoice == 1) {
        printf("Enter the stock number: ");
        scanf("%d", &stockNumber);
        printf("Enter the style number: ");
        scanf("%d", &styleNumber);

        while (fscanf(inventory, "%d %d", &shoeRecord->stockNumber, &shoeRecord->styleNumber) != EOF) {
            for (i = 0; i < 12; i++)
                fscanf(inventory, "%d", &shoeRecord->sizes[i]);
            fscanf(inventory, "%f", &shoeRecord->price);

            if (stockNumber == shoeRecord->stockNumber && styleNumber == shoeRecord->styleNumber){
                ifFound = true;

                printf("\nEnter [Y] to confirm the change number on hand and [N] for cancellation: ");
                scanf(" %c", &confirmation);
                confirmation = toupper(confirmation);

                if (confirmation == 'Y') {
                    printf("\nSuccessfully delete the record of stock number %d.\n", shoeRecord->stockNumber);
                    continue;
                }
                else    
                    printf("\nCancellation confirmed.\n");
            }

            fprintf(tempFile, "%d %d ", shoeRecord->stockNumber, shoeRecord->styleNumber);
            for (i = 0; i < 12; i++)
                fprintf(tempFile, "%d ", shoeRecord->sizes[i]);
            fprintf(tempFile, "%.2f\n", shoeRecord->price);
        } 

        if (!ifFound)
            printf("\nRECORD NOT FOUND.\n");

        fclose(inventory);
        fclose(tempFile);

        remove("inventory.txt");
        rename("tempFile.txt", "inventory.txt");
        
    }
    else if (userChoice == 2) {
        fclose(inventory);
        fclose(tempFile);

        remove("inventory.txt");
        rename("tempFile.txt", "inventory.txt");

        printf("\nSuccessfully delete all records.\n");
    }
    
}

// Function to check if a number exists in the inventory file
bool CheckIfExisting(int number, int choice) {
    FILE *inventory = fopen("inventory.txt", "r");

    int stockNumber, styleNumber;

    while (fscanf(inventory, "STOCK NUMBER: %d | STOCK STYLE: %d ", &stockNumber, &styleNumber) == 2) {
        if (choice == 1 && stockNumber == number) {
            fclose(inventory);
            return true;
        }
        else if (choice == 2 && styleNumber == number) {
            fclose(inventory);
            return true;
        }
        
        char c;
        while ((c = fgetc(inventory)) != '\n'){
            if (c == EOF)
                break;
        }
    }

    fclose(inventory);
    return false;
}