#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_account();
void deposit_money();
void withdraw_money();
void display_details();
void display_all_account_details();

#define MAX_ACCOUNTS 100

typedef struct
{
    char name[50];
    int acc_no;
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int num_accounts = 0;

int main()
{
    while (1)
    {
        int choice;
        printf("\n\n*** Bank Management System ***");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Display Details");
        printf("\n5. Display All Account Details");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            display_details();
            break;
        case 5:
            display_all_account_details();
            break;
        case 6:
            printf("\nClosing the Bank, Thanks for your visit.\n");
            return 0;
        default:
            printf("\nInvalid choice!\n");
            break;
        }
    }
}

void create_account()
{
    if (num_accounts >= MAX_ACCOUNTS)
    {
        printf("Maximum number of accounts reached!\n");
        return;
    }

    Account acc;
    printf("\nEnter your name: ");
    scanf("%s", acc.name);
    printf("Enter your account number: ");
    scanf("%d", &acc.acc_no);

    // Check if account number already exists
    for (int i = 0; i < num_accounts; i++)
    {
        if (accounts[i].acc_no == acc.acc_no)
        {
            printf("Account with this account number already exists!\n");
            return;
        }
    }

    acc.balance = 0;
    accounts[num_accounts++] = acc;
    printf("\nAccount created successfully!\n");
}

void deposit_money()
{
    int acc_no;
    float money;
    printf("Enter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to deposit: ");
    scanf("%f", &money);

    for (int i = 0; i < num_accounts; i++)
    {
        if (accounts[i].acc_no == acc_no)
        {
            accounts[i].balance += money;
            printf("Successfully deposited Rs.%.2f. New balance is Rs.%.2f\n", money, accounts[i].balance);
            return;
        }
    }

    printf("Account number %d not found.\n", acc_no);
}

void withdraw_money()
{
    int acc_no;
    float money;
    printf("Enter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter the amount you wish to withdraw: ");
    scanf("%f", &money);

    for (int i = 0; i < num_accounts; i++)
    {
        if (accounts[i].acc_no == acc_no)
        {
            if (accounts[i].balance >= money)
            {
                accounts[i].balance -= money;
                printf("Successfully withdrawn Rs.%.2f. Remaining balance is Rs.%.2f\n", money, accounts[i].balance);
            }
            else
            {
                printf("Insufficient balance!\n");
            }
            return;
        }
    }

    printf("Account number %d not found.\n", acc_no);
}

void display_details()
{
    int acc_no;
    printf("Enter your account number: ");
    scanf("%d", &acc_no);

    for (int i = 0; i < num_accounts; i++)
    {
        if (accounts[i].acc_no == acc_no)
        {
            printf("\nAccount Details:\n");
            printf("Name: %s\n", accounts[i].name);
            printf("Account Number: %d\n", accounts[i].acc_no);
            printf("Balance: Rs.%.2f\n", accounts[i].balance);
            return;
        }
    }

    printf("Account number %d not found.\n", acc_no);
}

void display_all_account_details()
{
    printf("\nAll Account Details:\n");
    printf("Name\t\tAccount No\tBalance\n");
    for (int i = 0; i < num_accounts; i++)
    {
        printf("%s\t\t%d\t\t%.2f\n", accounts[i].name, accounts[i].acc_no, accounts[i].balance);
    }
}
