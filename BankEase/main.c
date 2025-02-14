#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int i, j;
int main_exit;
void edit();
void closed();
void fordelay(int j);
void menu();
void new_acc();
void edit();
void transact();
void see();
void erase();
void view_list();

struct date
{
    int month, day, year;
};

struct
{
    char name[60];
    int acc_no, age;
    char address[60];
    char citizenship[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
} add, upd, check, rem, transaction;

unsigned int sec = 0;
clock_t stopclock = CLOCKS_PER_SEC;

void main()
{
    char pass[15], password[15] = "BankEase";
    int i = 0;
    printf("\n\n\t Enter the password to login :");
    printf("\033[8m");
    scanf("%s", pass);
    printf("\033c");
    if (strcmp(pass, password) == 0)
    {
        printf("\n\n Password match ! Loading ");
        system("cls");
        fordelay(2);
        menu();
    }
    else
    {
        printf("\033c");
        printf("\n\n Wrong Password !");
    login_try:
        printf("\n Enter 1 to try again and 0 to exit :");
        scanf("%d", &main_exit);
        if (main_exit == 1)
        {
            system("cls");
            main();
        }
        else if (main_exit == 0)
        {
            closed();
        }
    }
}

void menu()
{
    int choice;
    printf("\033c");
    system("cls");
    printf("\n");
    printf("\33[1;31m");
    printf("\n\n\t\tBankEase Banking Management System ");
    printf("\n\n\n\t\t       \033[1;32m WELCOME TO THE MENU ");
    printf("\033[0m");
    printf("\033[1;33m");
    printf("\n\n\t1. Create new account \n\t2. Update information of existing account \n\t3. For transaction\n\t4. Check the details of existing account \n\t5. Remove existing account \n\t6. View Customer's list \n\t7. Exit \n\n\n\n\t\t Enter your choice: ");
    scanf("%d", &choice);
    system("cls");
    printf("\033c");
    switch (choice)
    {
    case 1:
        new_acc();
        break;
    case 2:
        edit();
        break;
    case 3:
        transact();
        break;
    case 4:
        see();
        break;
    case 5:
        erase();
        break;
    case 6:
        view_list();
        break;
    case 7:
        closed();
        break;
    }
}

void fordelay(int j)
{
    int milli_seconds = 1000 * j;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

void new_acc()
{
    int choice;
    FILE *ptr;
account_no:
    system("cls");
    printf("\t\t\t          ADD RECORD ");
    printf("\n\n\n Enter today's date (mm/dd/yyyy) :");
    scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);
    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if (check.acc_no == add.acc_no)
        {
            printf("Account no. already in use !");
            goto account_no;
        }
        add.acc_no = check.acc_no;
        printf("\n Enter the name :");
        scanf("%s", add.name);
        printf("\n Enter the date of birth (mm/dd/yyyy) : ");
        scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);
        printf("\n Enter the age :");
        scanf("%d", &add.age);
        printf("\n Enter the address :");
        scanf("%s", add.address);
        printf("\n Enter the citizenship nuumber :");
        scanf("%s", add.citizenship);
        printf("\n Enter the phone number :");
        scanf("%f", &add.amt);
        printf("\n Type of account : \n\t #Saving \n\t #Fixed1(for 1year) \n\t #Fixed2(for 2 years) \n\t #Fixed3(for 3 years) :");
        scanf("%s", add.acc_type);
        fprintf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        fclose(ptr);
        printf("\n Account created successfully !");
    add_invalid:
        printf("\n\n\n\t Enter 1 to go to the main menu and 0 to Exit: \n");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
        {
            menu();
        }
        else if (main_exit == 0)
        {
            closed();
        }
        else
        {
            printf("\n Invalid!");
            goto add_invalid;
        }
    }
}

void edit()
{
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.dat", "w");
    newrec = fopen("new.dat", "w");
    printf("\n Enter the account no. of the customer whose info you want to change :\n");
    scanf("%d", &upd.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if (add.acc_no == upd.acc_no)
        {
            test = 1;
            printf("\n Which information do you want to change : \n 1.Address \n 2.Phone \n]n Enter your choice: ");
            scanf("%d", &choice);
            system("cls");
            if (choice == 1)
            {
                printf("Enter Address :");
                scanf("%s", upd.address);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, upd.address, add.citizenship, &add.phone, &add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year);
                system("cls");
                printf("changes saved !");
            }
            else if (choice == 2)
            {
                printf("Enter the new phone number :");
                scanf("%lf", &upd.phone);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, upd.address, add.citizenship, &upd.phone, &add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year);
                system("cls");
                printf("changes saved !");
            }
            else
            {
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, upd.address, add.citizenship, &upd.phone, &add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year);
            }
        }
        fclose(old);
        fclose(newrec);
        remove("record.dat");
        rename("new.dat", "record.dat");
        if (test != 1)
        {
            system("cls");
            printf("\n record not found ! ");
        edit_invalid:
            printf("Enter 0 to try again, 1 to return to main menu & 2 to Exit: ");
            scanf("%d", &main_exit);
            system("cls");
            if (main_exit == 1)
            {
                menu();
            }
            else if (main_exit == 2)
            {
                closed();
            }
            else if (main_exit == 0)
            {
                edit();
            }
            else
            {
                printf("\n Invalid ");
                goto edit_invalid;
            }
        }
        printf("\n\n\n Enter 1 to go to the main menu & 0 to Exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
        {
            menu();
        }
        else
            closed();
    }
}

void transact()
{
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");
    printf("Enter the account no. of the customer: ");
    scanf("%d", &transaction.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if (add.acc_no == transaction.acc_no)
        {
            test = 1;
            if (strcmp(add.acc_type, "fixed1") == 0 || strcmp(add.acc_type, "fixed2") == 0 || strcmp(add.acc_type, "fixed3") == 0)
            {
                printf("You cannot deposit or withdraw cash in Fixed account \n");
                system("cls");
                menu();
            }
            printf("\n\n Do you want to \n1.Deposit \n2.Withdraw?? \nEnter your choice: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("Enter the amount you want to deposit: ₹");
                scanf("%f", &transaction.amt);
                add.amt += transaction.amt;
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, upd.address, add.citizenship, upd.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\n\n Deposited successfully !");
            }
            else if (choice == 2)
            {
                printf("Enter the amount you want to withdraw: ₹");
                scanf("%f", &transaction.amt);
                add.amt -= transaction.amt;
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, upd.address, add.citizenship, upd.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\n\n  Withdrawed successfully !");
            }
            else
            {
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, upd.address, add.citizenship, upd.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
            }
        }
        fclose(old);
        fclose(newrec);
        remove("record.dat");
        rename("new.dat", "record.dat");
        if (test != 1)
        {
            printf("\n\n Record not found !");
        transaction_invalid:
            printf("\n\n\n Enter 0 to try again, 1 to return to main menu & 2 to Exit");
            scanf("%d", &main_exit);
            system("cls");
            if (main_exit == 0)
            {
                transact();
            }
            else if (main_exit == 1)
            {
                menu();
            }
            else
            {
                printf("\n Invalid!");
                goto transaction_invalid;
            }
        }
        else
        {
            printf("\n Enter 1 to go to main menu & 0 to Exit: ");
            scanf("%d", &main_exit);
            system("cls");
            if (main_exit == 1)
            {
                menu();
            }
            else if (main_exit == 0)
            {
                closed();
            }
        }
    }
}

void see()
{
    FILE *ptr;
    int test = 0, rate;
    int choice;
    float time;
    float intrst;
    ptr = fopen("record.dat", "r");
    printf("Do you want to check by \n1.Account No.\n2.Name \n Enter your choice :");
    if (choice == 1)
    {
        printf("Enter the account number:");
        scanf("%d", &check.acc_no);
        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
        {
            if (add.acc_no == check.acc_no)
            {
                system("cls");
                test = 1;
                printf("\n Account no. : %d \n Name : %s \n DOB : %d/%d/%d \n Age : %d \n Address : %d \n Citizenship no. : %s \n Phone Number : %.0lf \n Type of Account : %s \n Amount Deposited : ₹%.2f \n Date of deposit : %d/%d/%d \n\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                if (strcmp(add.acc_type, "fixed1") == 0 || strcmp(add.acc_type, "fixed2") == 0 || strcmp(add.acc_type, "fixed3 ") == 0)
                {
                    printf("\n\n You will get no interest ");
                }
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter the name : ");
        scanf("%s", check.name);
        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
        {
            if (strcmp(add.name, check.name) == 0)
            {
                system("cls");
                test = 1;
                printf("\n Account no. : %d \n Name : %s \n DOB : %d/%d/%d \n Age : %d \n Address : %d \n Citizenship no. : %s \n Phone Number : %.0lf \n Type of Account : %s \n Amount Deposited : ₹%.2f \n Date of deposit : %d/%d/%d \n\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                if (strcmp(add.acc_type, "fixed1") == 0 || strcmp(add.acc_type, "fixed2") == 0 || strcmp(add.acc_type, "fixed3 ") == 0)
                {
                    printf("\n\n You will get no interest ");
                }
            }
        }
    }
    fclose(ptr);
    if (test != 1)
    {
        system("cls");
        printf("\n Record not found !! ");
    see_invalid:
        printf("\n Enter 0 to try again, 1 to return to the main menu or 2 to Exit: ");
        scanf("%d", &choice);
        system("cls");
        if (main_exit == 0)
        {
            see();
        }
        else if (main_exit == 1)
        {
            menu();
        }
        else if (main_exit == 2)
        {
            closed();
        }
        else
        {
            system("cls");
            printf("\n Invalid!");
            goto see_invalid;
        }
    }
    else
    {
        printf("\n Enter 1 to go to main menu & 0 to Exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
        {
            system("cls");
            menu();
        }
        else
        {
            system("cls");
            closed();
        }
    }
}
void erase()
{
    FILE *old, *newrec;
    int test = 0;
    old = fopen("record.dat", "r");
    newrec = fopen("new.dat", "w");
    printf("Enter the account number you want to delete :");
    scanf("%d", &rem.acc_no);
    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF)
    {
        if (add.acc_no != rem.acc_no)
        {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", &add.acc_no, &add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, &add.address, &add.citizenship, &add.phone, &add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year);
        }
        else
        {
            test++;
            printf("\n Record deleted successfully ! \n\n");
        }
    }
    fclose(old);
    fclose(newrec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    if (test == 0)
    {
        printf("\n\n Record not found !");
    erase_invalid:
        printf("\n\n\n Enter 0 to try again, 1 to return to main menu & 2 to Exit");
        scanf("%d", &main_exit);
        if (main_exit == 0)
        {
            erase();
        }
        else if (main_exit == 1)
        {
            menu();
        }
        else if (main_exit == 2)
        {
            closed();
        }
        else
        {
            printf("\n Invalid!");
            goto erase_invalid;
        }
    }
    else
    {
        printf("\n Enter 1 to go to main menu & 0 to Exit: ");
        scanf("%d", &main_exit);
        system("cls");
        if (main_exit == 1)
        {
            menu();
        }
        else
        {
            closed();
        }
    }
}

void view_list()
{
    FILE *view;
    view = fopen("record.dat", "r");
    int test = 0;
    system("cls");
    printf("\n Account no. \t Name \t\t Address \t Phone  \n");
    while (fscanf(view, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d/ \n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year) != EOF)
    {
        printf("\n%6d\t %s\t\t %s\t\t %.0lf", add.acc_no, add.address, add.phone);
        test++;
    }
    fclose(view);
    if (test == 0)
    {
        system("cls");
        printf("\n No Records !!\n");
    }
view_list_invalid:
    printf("\n Enter 1 to go to main menu & 0 to Exit: ");
    scanf("%d", &main_exit);
    system("cls");
    if (main_exit == 1)
    {
        menu();
    }
    else if (main_exit == 0)
    {
        closed();
    }
    else
    {
        printf("\n Invalid ! \n");
        goto view_list_invalid;
    }
}

void closed()
{
    system("cls");
    printf("\n\n\n Made by Nishant. Thank you for using! ");
}
