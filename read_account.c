#include <stdio.h>
#include <string.h>

void display_accounts();
void delete_account();
void edit_account_name();

const char *ACCOUNT_FILE = "account.dat";

typedef struct
{
    char name[50];
    int acc_no;
    float balance;
} Account;

int main()
{
    while (1)
    {
        int choice;
        printf("\n\n*** Bank Management System : Admin View***");
        printf("\n1. Display All Accounts");
        printf("\n2. Delete Account");
        printf("\n3. Edit Account Details");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display_accounts();
            break;
        case 2:
            delete_account();
            break;
        case 3:
            edit_account_name();
            break;
        case 4:
            printf("\nClosing the Bank, Thanks for your visit.\n");
            return 0;
        default:
            printf("\nInvalid choice!\n");
            break;
        }
    }
}

void display_accounts()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file == NULL)
    {
        printf("\nUnable to open file!!");
        return;
    }

    Account acc_read;
    printf("\n\n*** All Accounts ***\n");
    printf("Name\t\tAccount No\tBalance\n");
    printf("----------------------------------------\n");
    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        printf("%s\t\t%d\t\t%.2f\n", acc_read.name, acc_read.acc_no, acc_read.balance);
    }
    fclose(file);
}

void delete_account()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file == NULL)
    {
        printf("\nUnable to open file!!");
        return;
    }

    int acc_no;
    printf("Enter the account number to delete: ");
    scanf("%d", &acc_no);

    FILE *temp_file = fopen("temp.dat", "wb");
    if (temp_file == NULL)
    {
        printf("\nUnable to open temporary file!!");
        fclose(file);
        return;
    }

    Account acc_read;
    int found = 0;
    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)
        {
            found = 1;
        }
        else
        {
            fwrite(&acc_read, sizeof(acc_read), 1, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found)
    {
        remove(ACCOUNT_FILE);
        rename("temp.dat", ACCOUNT_FILE);
        printf("Account deleted successfully.\n");
    }
    else
    {
        remove("temp.dat");
        printf("Account number %d not found.\n", acc_no);
    }
}

void edit_account_name()
{
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL)
    {
        printf("\nUnable to open file!!");
        return;
    }

    int acc_no;
    printf("Enter the account number to edit: ");
    scanf("%d", &acc_no);

    Account acc_read;
    int found = 0;
    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_read.acc_no == acc_no)
        {
            found = 1;
            printf("Enter the new name: ");
            getchar(); // Consume the newline character
            fgets(acc_read.name, sizeof(acc_read.name), stdin);
            int ind = strcspn(acc_read.name, "\n");
            acc_read.name[ind] = '\0';

            fseek(file, -sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            printf("Account name updated successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Account number %d not found.\n", acc_no);
    }

    fclose(file);
}
