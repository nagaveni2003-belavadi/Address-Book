#include <stdio.h>
#include<string.h>
#include "contact.h"
#include<ctype.h>

/* Function definitions */
// void init_intitalization(AddressBook *addressbook)
// {
// }

int valid_name(char* );
int valid_name(char* name)//validation of name
{
    //1 rule only alphabets
    for(int i=0;name[i]!='\0';i++)
    {
        if(!(islower(name[i])||isupper(name[i])||isspace(name[i])))
        {
            printf("Name should contains only alphabet characters! Try again.\n\n");
            return 0;
        }
    }
    return 1;
}
// phone number:

int valid_phone_number(char* ,AddressBook*);
int valid_phone_number(char* phone_number,AddressBook* addressbook)//validation of phone_number
{   
    int len=strlen(phone_number);
    if(!(phone_number[0]>='6' && phone_number[0]<='9'))
    {
        printf("phone number should be starts with >=6 and <=9.\n\n");
        return 0;
    }
    for(int i=0;i<len;i++)
    {
        if(!(isdigit(phone_number[i])))
        {
            printf("Phone number should contains only numbers! Try again\n\n");
            return 0;
        }
    }
    if(len!=10)
    {
        printf("phone number should contains 10 digits.\n\n");
        return 0;
    }
    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(strcmp(phone_number,addressbook->contact_details[i].Mobile_number)==0)
        {
            printf("Phone number should be unique! Try again\n\n");
            return 0;
        }
    }
    return 1;
}
//emailid :

int valid_email_id(char* ,AddressBook* );
int valid_email_id(char* email_id,AddressBook* addressbook)//validation of email_id
{
    for(int i=0;i<addressbook->contact_count;i++)
    {
        if(strcmp(email_id,addressbook->contact_details[i].Mail_ID)==0)
        {
            printf("Email_ID should be unique! Try again.\n\n");
            return 0;
        }
    }

    int len=strlen(email_id);
    int count=0;
    for(int i=0;i<len;i++)
    {
        if(email_id[i]=='@')
        {
            count++;
        }
    }
    if(count!=1)
    {
        printf("Mail_id should contain only one @ symbol! Try again.\n\n");
        return 0;
    }

    for(int i=0;i<len;i++)
    {
        if((email_id[i]>='A' && email_id[i]<='Z'))
        {
            printf("In mail_id Only lower case is consider.\n\n");
            return 0;
        }
    }
    char substr[6]=".com";
    char* substring=strstr(email_id,substr);
    if(substring == NULL)
    {
        printf("Mail_id should conatins @ and .com\n\n");
        return 0;
    }

    for(int i=0;i<2;i++)
    {
        if(email_id[i]=='@')
        {
            printf("mail_id atleast contains 4 characters before the @ symbol! Try again\n\n");
            return 0;
        }
    }

    int k;char ch='@';
    char* str=strstr(email_id,substr);
    char* ptr=strchr(email_id,ch);
    if(str-ptr<2)
    {
        printf("Domain name should be after the @ symbol! Try again\n\n");
        return 0;
    }

    for(int i=0;i<len;i++)
    {
        if(email_id[i]==' ')
        {
            printf("In email_id there is no spaces! Try again\n\n");
            return 0;
        }
    }

    int i,count1=0,alpha_count=0;
    int j=0;
    while(email_id[j]!='@')
    {
        if(email_id[j]>='a'&&email_id[j]<='z')
        {
            alpha_count++;
        }
        j++;
    }
    if(alpha_count<1)
    {
        printf("Atleast one alphabet should be present before '@'\n\n");
        return 0;
    }

    for(i=0;email_id[i]!='\0';i++)
    {
        if(email_id[i]=='@')
        {
            break;
        }
    }
    if(email_id[i-1]=='.'||email_id[i+1]=='.')
    {
        printf("Position of the '.' not valid\n\n");
        return 0;
    }
    for(int j=i;email_id[j]!='\0';j++)
    {
        if(email_id[j]=='.')
        count1++;
    }
    if(count1>1)
    {
        printf("after @ only one '.' should be there\n\n");
        return 0;
    }

    if(email_id[len-1]=='.')
    {
        printf("In email_id last . should not there!\n\n");
        return 0;
    }
    return 1;
}
//create contact:

int create_contact(AddressBook *addressbook)
{
    int k=1;
    while(k)
    {
        char name[30];
        printf("Enter the Name: ");
        n_m:
        scanf(" %[^\n]",name);
        int valid_n=valid_name(name);
        
        if(valid_n!=0)  
        {
            strcpy(addressbook->contact_details[addressbook->contact_count].Name,name);
        }
        else{
            printf("Enter name again:");
            goto n_m;
        }

        char phone_number[11];
        printf("Enter phone number: ");
        p_n:
        scanf(" %[^\n]",phone_number);
        int valid_p=valid_phone_number(phone_number,addressbook);

        if(valid_p!=0)
        {
            strcpy(addressbook->contact_details[addressbook->contact_count].Mobile_number,phone_number);
        }
        else
        {
            printf("Enter phone number again: ");
            goto p_n;
        }

        char email_id[20];
        printf("Enter email_id: ");
        e_i:
        scanf(" %[^\n]",email_id);
        int valid_e=valid_email_id(email_id,addressbook);

        if(valid_e!=0)
        {
            strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID,email_id);
        }
        else
        {
            printf("Enter Email Id again: ");
            goto e_i;
        }
        addressbook->contact_count++;

        printf("Do you want to create contact?\n1.yes\n0.No\n");
        scanf("%d",&k);
    }
    return 0;
}
//list contact:

void list_contacts(AddressBook *addressbook)
{
    if(addressbook->contact_count==0)
    {
        printf("There are no contact details in the file\n");
        return;
    }
    printf("Name              Phone_number     email_id\n");
    for(int i=0;i<addressbook->contact_count;i++)
    {   
        printf("-------------------------------------------------------------------------------------------\n");
        printf("%-16s  %-10s       %s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
    }
    printf("\n");
}
//search contact:

int search_contacts(AddressBook *addressbook)
{
    if(addressbook->contact_count==0)
    {
        printf("There are no contact details in the file.\n");
        return -1;
    }
    printf("Search Menu\n1.search by name\n2.search by mobile numbre\n3.search by email_id\n4.exit\n");
    int option,option1;
    scanf("%d",&option);
    char name[20];
    char Mobile_number[11];
    char email_id[20];
    int count;
    int arr[count];
    int i,j;
    switch(option)
    {
        case 1:
        count=0;
        printf("Enter the name: ");
        scanf(" %[^\n]",name);
        for(i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(addressbook->contact_details[i].Name,name)==0)
            {
                printf("%s-%s-%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                arr[count]=i;
                count++;
            }
        }
        if(count>1)
        {
            printf("There are %d contacts with the same name\nSearch by phone number or email_id\n1.phone number\n2.email_id\n",count);
            scanf("%d",&option1);
            if(option1==1)
            {
                printf("Enter the Mobile number: ");
                scanf(" %[^\n]",Mobile_number);
                for(j=0;j<count;j++)
                {
                    if(strcmp(addressbook->contact_details[arr[j]].Mobile_number,Mobile_number)==0)
                    {  
                        printf("-------------------------------------------------------------------------------------------\n");
                        printf("%s-%s-%s\n",addressbook->contact_details[arr[j]].Name,addressbook->contact_details[arr[j]].Mobile_number,addressbook->contact_details[arr[j]].Mail_ID);
                        printf("-------------------------------------------------------------------------------------------\n");
                        return arr[j];
                    }
                }
            }
            if(option1==2)
            {
                printf("Enter the Email_id: ");
                scanf(" %[^\n]",email_id);
                for(j=0;j<count;j++)
                {
                    if(strcmp(addressbook->contact_details[arr[j]].Mail_ID,email_id)==0)
                    {
                        printf("-------------------------------------------------------------------------------------------\n");
                        printf("%s-%s-%s\n",addressbook->contact_details[arr[j]].Name,addressbook->contact_details[arr[j]].Mobile_number,addressbook->contact_details[arr[j]].Mail_ID);
                        printf("-------------------------------------------------------------------------------------------\n");
                        return arr[j];
                    }
                }
            }
        }
        else if(count==1)
        {
            printf("Contact found\n");
            return arr[0];
        }
        break;

        case 2:
        printf("Enter the Mobile number: ");
        scanf(" %[^\n]",Mobile_number);
        for(i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(addressbook->contact_details[i].Mobile_number,Mobile_number)==0)
            {
                printf("-------------------------------------------------------------------------------------------\n");
                printf("%s-%s-%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                printf("Contact found\n");
                printf("-------------------------------------------------------------------------------------------\n");
                return i;
                break;
            }
        } 
        break;
        
        case 3:
        printf("Enter the email_ID: ");
        scanf(" %[^\n]",email_id);
        for(i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(addressbook->contact_details[i].Mail_ID,email_id)==0)
            {
                printf("-------------------------------------------------------------------------------------------\n");
                printf("%s-%s-%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                printf("Contact found\n");
                printf("-------------------------------------------------------------------------------------------\n");
                return i;
                break;
            }
        }
        break;

        case 4:
        printf("Thank you\n");
        break;
    }
    if(option!=4)
    {
        printf("Contact is not found\n");
    }
}
//edit contact:

int edit_contact(AddressBook *addressbook)
{
    int search_contacts(AddressBook *);
    int i=search_contacts(addressbook);
    int option;
    char e_name[20];
    char e_phone[11];
    char e_email_id[30];
    if(i>=0 && i<=addressbook->contact_count)
    {
        printf("Edit Contact menu : \n1.edit the Name \n2.edit the Mobile number\n3.edit the Mail ID\n4.edit all the informations\nEnter the option : ");
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                e_n:
                printf("Enter the editting name: ");
                scanf(" %[^\n]",e_name);
                int valid_f_e_n=valid_name(e_name);
                if(valid_f_e_n!=0)
                {
                    strcpy(addressbook->contact_details[i].Name,e_name);
                    printf("Edit completed.\n\n");
                }
                else
                {
                    goto e_n;
                }
            break;

            case 2:
                e_p:
                printf("Enter the editting mobile number: ");
                scanf(" %[^\n]",e_phone);
                int valid_f_e_p=valid_phone_number(e_phone,addressbook);
                if(valid_f_e_p!=0)
                {
                    strcpy(addressbook->contact_details[i].Mobile_number,e_phone);
                    printf("Edit completed.\n\n");
                }
                else
                {
                    goto e_p;
                }
            break;

            case 3:
                f_e_id:
                printf("Enter the editting Email_ID: ");
                scanf(" %[^\n]",e_email_id);
                int valid_f_e_e=valid_email_id(e_email_id,addressbook);
                if(valid_f_e_e!=0)
                {
                    strcpy(addressbook->contact_details[i].Mail_ID,e_email_id);
                    printf("Edit completed.\n");
                }
                else
                {
                    goto f_e_id;
                }
            break;

            case 4:
            e_f_n:
            printf("Enter the editting name: ");
            scanf(" %[^\n]",e_name);
            int valid_e_n=valid_name(e_name);
            if(valid_e_n!=0)
            {
                strcpy(addressbook->contact_details[i].Name,e_name);
            }
            else
            {
                goto e_f_n;
            }
            e_f_p:
            printf("Enter the editting phone_number: ");
            scanf(" %[^\n]",e_phone);
            int valid_e_p=valid_phone_number(e_phone,addressbook);
            if(valid_e_p!=0)
            {
                strcpy(addressbook->contact_details[i].Mobile_number,e_phone);
            }
            else
            {
                goto e_f_p;
            }
            e_f_e_id:
            printf("Enter the editting email_id: ");
            scanf(" %[^\n]",e_email_id);
            e_e_id:
            int valid_e_e=valid_email_id(e_email_id,addressbook);
            if(valid_e_e!=0)
            {
                strcpy(addressbook->contact_details[i].Mail_ID,e_email_id);
            }
            else
            {
                goto e_f_e_id;
            }
            printf("Editting successful\n\n");
            break;
        }
    }
}
//delete contact:

int delete_contact(AddressBook *addressbook)
{
    int search_contacts(AddressBook *);
    int i=search_contacts(addressbook);
    int option;
    if(i>=0 && i<=addressbook->contact_count)
    {
        printf("Do you really want to delete the details?\n1.yes\n2.No\n");
        scanf("%d",&option);
        if(option==1)
        {
            addressbook->contact_count--;
            for(int j=i;j<addressbook->contact_count;j++)
            {
                addressbook->contact_details[j]=addressbook->contact_details[j+1];
            }
            printf("Delete completed\n");
        }
        return 0;
    }
}

//
//save contacts:
//
int save_contacts(AddressBook *addressbook)
{
    FILE* fptr=fopen("data.txt","w");
    if(fptr==NULL)
    {
        printf("File Not found\n");
        return 0;
    }

    Contacts temp;
    for(int i = 0; i < addressbook->contact_count - 1; i++)
    {
        for(int j = 0; j < addressbook->contact_count - i - 1; j++)
        {
            if(strcasecmp(addressbook->contact_details[j].Name,addressbook->contact_details[j + 1].Name) > 0)
            {
                temp = addressbook->contact_details[j];
                addressbook->contact_details[j] = addressbook->contact_details[j + 1];
                addressbook->contact_details[j + 1] = temp;
            }
        }
    }

    rewind(fptr);
    fprintf(fptr,"#%d\n",addressbook->contact_count);
    for(int i=0;i<addressbook->contact_count;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID);
    }

    fclose(fptr);
    printf("Save Completed\n\n");
    return 0;
}