#include<stdio.h>
#include<string.h>
#include<ctype.h>

    #define RED     "\033[1;31m"
    #define GREEN   "\033[1;32m"
    #define YELLOW  "\033[1;33m"
    #define BLUE    "\033[1;34m"
    #define CYAN    "\033[1;36m"
    #define RESET   "\033[0m"


    char Username[20]="nehakumari";
    char Password[20]="neha@2007";
    char emailid[30];
    char contactNumber[11];


    int busNumber[3]={101,102,103};
    int booked_seats[3]={0,0,0};
    int available_seats[3]={50,50,50};
    int total_seats[3]={50,50,50};
    float fare[3]={500,650,900};
    float total_fare=0;

    char sourceCity[3][30]={"delhi","delhi","delhi"};
    char destinationCity[3][30]={"bihar","patna","kolkata"};

    int seats=0;
    int currentbus=-1;

    void signup();
    void login();
    void menu();
    void selectbus();
    void bookticket();
    void payment();
    void cancelticket();
    void checkstatus();


    int main()
    {
        int choice;
        printf(BLUE"*********BUS RESEVATION SYSTEM**********\n"RESET);
        printf("1. sign up\n");     
        printf("2. login\n");
        printf("3. exit\n");
        printf("please entr your choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            signup();
            break;
            case 2:
            login();
            break;
            case 3:
            printf("thank you!\n");
            break;
            default:
            printf("invalid choice!\n");
        }
        return 0;
        
    }

void signup()

{
    printf(YELLOW"\n=====USER REGISTRATION=====\n"RESET);
    
    while(1)
    {
        printf("\nplease entr your Username (min 10 character):");
        scanf(" %[^\n]",Username);
        if(strlen(Username)>=10)
        
        {
            printf("Username valid\n");
            break;
        }
        else
        {
           
            printf("invalid username! minimum 10 character required\n");
        
        }
        
    }    

    while(1)
        {
            printf("\nplease enter your password (min 9 character):");
            scanf(" %[^\n]",Password);
            if(strlen(Password)>=9)
            
            {
               
                printf("Password valid!\n");
                break;
            }
            else
            {
                printf("invalid Password! minimum 9 character required.\n");
                
            }
        }               
        
        while(1)
        {
            printf("\nplease enter your emailid:");
            scanf(" %[^\n]",emailid);
            if(strchr(emailid,'@')&& strchr(emailid,'.'))
            break;

            else
            {
                printf("invalid emailid!\n");
            }  
        }   
        while(1)
        {
            int valid=1;

                printf("\nplease enter your contact Number(10 digit):");
                scanf(" %[^\n]",contactNumber);

                if(strlen(contactNumber)!=10)
                valid=0;
                else
                {
                    for(int i=0;i<10;i++)
                    {
                        if(!isdigit(contactNumber[i]))
                        {
                            valid=0;
                            break;
                        }
                    }
                }
                if(valid)
                {
                  printf("contact Number valid!\n");
                  break;  
                }
                else
                {
                    printf("invalid contact Number!\n");
                }
                
        }
                printf(GREEN"\nregistration successful! please login.\n"RESET);
                login();
             
}   

    void login()
    {
        while(1)
        {
            char inputuser[20];
            char inputpass[20];

            printf("\n\033[1;31m******login******\n");
            printf("Enter your username:");
            scanf(" %[^\n]",inputuser);

            printf("Enter your password:");
            scanf(" %[^\n]",inputpass);

            if(strcmp(inputuser,Username)== 0 && strcmp(inputpass,Password)==0)

            {

                printf(GREEN"\nlogin successful! welcome,%s\n"RESET, Username);
                menu();
                return;
            }
            
            else
            {

            printf(RED"invalid Username or password!\n"RESET);
            }
        }
    }

    void menu()
    {
        int choice;
        do
        {
            printf(YELLOW"\n====USER MENU====\n"RESET);
            printf("1. book a ticket\n");
            printf("2. cancel a ticket\n");
            printf("3. check bus status\n");
            printf("4. logout\n");

            printf("Enter your choice:");
            scanf("%d",&choice);

            switch(choice)
            {
                case 1:
                bookticket();
                break;
                case 2:
                cancelticket();
                break;
                case 3:
                checkstatus();
                break;
                case 4:
                printf("logout Successful!\n");
                break;
                default:
                printf(RED"invalid choice!\n"RESET);
            }
        } while(choice!=4);
    }
    void selectbus()
    {
    
            printf(CYAN"\navailable buses:\n"RESET);
            for(int i=0;i<3;i++)
            {
                printf("%d: %s to %s | fare:%.2f | seats:%d\n",busNumber[i],sourceCity[i],destinationCity[i],fare[i],available_seats[i]);
            }

            int bn;

            printf("enter bus number:");
            scanf("%d",&bn);
            
            for(int i=0;i<3;i++)
            {
                if(busNumber[i]==bn)
                {
                    currentbus=i;
                    return;
                }
            
            }   
            printf("invalid bus number!\n");
            currentbus=-1;
    }
    void bookticket()
    
    {
        selectbus();

        if(currentbus==-1)
        return;
    

        printf("enter number of seats:");
        scanf("%d",&seats);

        if(seats > 0 && seats <= available_seats[currentbus])
        {
            total_fare=seats*fare[currentbus];
            payment();
        }
        else
        {
            printf("seats not available!\n");
        }
    }
    
    void payment()
    {

        int choice;
        printf("\n\033[0m====PAYMENT====\n");
        printf("total fare:%.2f\n",total_fare);
        printf("payment methode:\n");
        printf("1. upi\n");
        printf("2. debit card\n");
        printf("3. credit card\n");
        printf("enter your choice:");
        scanf("%d",&choice);

        if(choice >=1 && choice <=3)
        {
            available_seats[currentbus]-=seats;
            booked_seats[currentbus]+=seats;

            printf(GREEN"payment successful!\nticket booked successfully!\n"RESET);
        
        }
        else
        {
            printf(RED"payment cancelled!\n"RESET);
        }
    
    }
    void cancelticket()
    {
        int cancelseats;
        if(currentbus==-1 || booked_seats[currentbus]==0)
        {

            printf("No ticket booked!\n");
            return;
        }
        printf("Enter number of seats to cancel:");
        scanf("%d",&cancelseats);

        if(cancelseats > 0 &&  cancelseats <= booked_seats[currentbus])
        {
            booked_seats[currentbus]-=cancelseats;
            available_seats[currentbus]+=cancelseats;
        printf("Ticket  cancelled successfully!\n");
        }
        else
        {
            printf("invalid cancellation!\n");
        }
    }
    void checkstatus()
    {
        if(currentbus==-1)
        {
            printf("no booking done yet!\n");
            return;
        }

        printf(BLUE"\n=======BUS STATUS=======\n"RESET);
        printf("bus number:         %d\n",busNumber[currentbus]);
        printf("sourceCity:         %s\n",sourceCity[currentbus]);
        printf("destination City:   %s\n",destinationCity[currentbus]);
        printf("total seat:         %d\n",total_seats[currentbus]);
        printf("available seats:    %d\n",available_seats[currentbus]);
        printf("booked seats:       %d\n",booked_seats[currentbus]);
        printf("fare:               %.2f\n",fare[currentbus]);

    }
    




    





        















           