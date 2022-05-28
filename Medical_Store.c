#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
struct medicine
{
    char name[50];
    int price;
    int stock;
};
void create(struct medicine *m,int n);
void display(struct medicine *m,int i);
int search(struct medicine *m,int n,char name[50]);
int purchase(struct medicine *m,int n);
int add(struct medicine *m,int n);
void update(struct medicine *m,int n);
void main()
{
    struct medicine m[20];
    int ch,n,i,x;
    printf("\t\t\t\t\t\t\t\t\t\t*******************************************\n");
    printf("\t\t\t\t\t\t\t\t\t\t\tMEDICAL STORE MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t\t\t\t\t\t*******************************************\n");
    do
    {
        printf("\n\t\t\t\t\t\t\t\t\t\t1.Create Store\n\t\t\t\t\t\t\t\t\t\t2.Display the Store\n\t\t\t\t\t\t\t\t\t\t3.Purchase Medicine\n\t\t\t\t\t\t\t\t\t\t4.Add a medicine to the store\n\t\t\t\t\t\t\t\t\t\t5.Update the Price of the medicine\n\t\t\t\t\t\t\t\t\t\t6.Exit\n");
        printf("\t\t\t\t\t\t\t\t\t\tEnter your choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:printf("\nEnter the number of medicine to be added in store : ");
                    scanf("%d",&n);
                    create(m,n);
                    printf("\n\nSUCCESSFULLY CREATED THE STORE\n\n");
                    break;
            case 2:printf("\nName of Medicine\t\tPrice\t\t\tStock\n");
                     display(m,n);
                    break;
            case 3:x=purchase(m,n);
                   if(x != -1)
                        printf("\n\nPURCHASE IS SUCCESSFULL\n\n\n");
                   break;
            case 4:if(n<5)
                   {
                        x=add(m,n);
                        if(x==0)
                        {
                             n++;
                             printf("\n\nADDED SUCCESSFULLY\n\n\n");
                        }
                   }
                   else
                        printf("\n\nSORRY THE STORE IS FULL\n\n");
                   break;
            case 5:update(m,n);
                    break;
            case 6:exit(1);
            default:printf("\n\nWrong Choice\n\n\n");

        }
    }while(1);
}
void create(struct medicine *m,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("\nEnter the name of medicine : ");
        scanf("%s",m[i].name);
        printf("\nEnter the price of medicine : ");
        scanf("%d",&m[i].price);
        printf("\nEnter the stock of medicine : ");
        scanf("%d",&m[i].stock);
    }
}
void display(struct medicine *m,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%s\t\t\t%d\t\t\t%d\n",m[i].name,m[i].price,m[i].stock);
}
int search(struct medicine *m,int n,char name[50])
{
    int i;
    for(i=0;i<n;i++)
    {
        if(strcmp(m[i].name,name)==0)
            return i;
    }
    return -1;
}
int purchase(struct medicine *m,int n)
{
    FILE *fptr;
    char name[45],namemed[50],dob[11];
    int age,stk,x,total;
    long int mobile_no;
    printf("\nEnter the name of medicine to be purchased : ");
    scanf("%s",namemed);
    x=search(m,n,namemed);
    if(x != -1)
    {
        printf("\nEnter the stock of the Medicine : ");
        scanf("%d",&stk);
        if(m[x].stock > stk)
        {
           m[x].stock=m[x].stock - stk;
           total=m[x].price * stk;

           fptr=fopen("Customer.txt","w");
           if(fptr != NULL)
           {
               printf("\nEnter the name of the customer : ");
               scanf("%s",name);
               printf("\nEnter the age : ");
               scanf("%d",&age);
               printf("\nEnter the mobile_no : ");
               scanf("%ld",&mobile_no);
               printf("\nEnter the Date of purchase : ");
               scanf("%s",dob);

               fprintf(fptr,"Name :%s\nAge :%d\nMobile No :%ld\n",name,age,mobile_no);
           }
           else
           {
                printf("\nSORRY THE FILE IS NOT OPENED PROPERLY\n\n");
                return -1;
           }
        }
        else
        {
            printf("\n\nSORRY ONLY %d STOCK IS AVAILABLE\n\n",m[x].stock);
            return -1;
        }
    }
    else
    {
         printf("\n\nSORRY THE MEDICINE IS NOT FOUND\n\n");
         return -1;
    }
    fclose(fptr);
    fptr=fopen("bill.txt","w");
    if(fptr != NULL)
    {
        fprintf(fptr,"\t\t\t\t\tBILL\n\nDate : %s\nName of Customer : %s\n\nName of Medicine\t\tQuantity\tUnit_Price\tTotal_Price\n",dob,name);
        fprintf(fptr,"%s\t\t\t%d\t\tRS %d\tRS %d",m[x].name,stk,m[x].price,total);
    }
    fclose(fptr);
    return 0;
}
int add(struct medicine *m,int n)
{
    char name[50];
    int x,s;
    printf("\nEnter the name of the medicine : ");
    scanf("%s",name);
    x=search(m,n,name);
    if(x == -1)
    {
        strcpy(m[n].name,name);
        printf("\nEnter the price of the medicine : ");
        scanf("%d",&m[n].price);
        printf("\nEnter the stock of the medicine : ");
        scanf("%d",&m[n].stock);
        return 0;
    }
    else
    {
        printf("\n\nTHE MEDICINE IS ALREADY THERE IN THE STORE\n\n\n");
        printf("Enter the Stock : ");
        scanf("%d",&s);
        m[x].stock=m[x].stock + s;
        printf("\nADDED SUCCESSFULLY\n\n");
     }
}
void update(struct medicine *m,int n)
{
    char name[50];
    int x;
    printf("\nEnter the name of the medicine whose price is to be updated : ");
    scanf("%s",name);
    x=search(m,n,name);
    if(x!= -1)
    {
        printf("\nEnter the new Price : ");
        scanf("%d",&m[x].price);
        printf("\nUPDATED SUCCESSFULLY\n\n\n");
    }
    else
        printf("\n\nSORRY THE MEDICINE IS NOT PRESENT IN THE STOCK\n\n\n");
}
