/*Name : Shwetha M K
Submission date : 7/12/2025
Project Name : AdressBook
Description : In addressbook there are 7 function:
1.create contact:if user giving input ,storing it in string and validating it ,if that string is valid then am adding it to structure.
2.search contact:asking how to search,by name or by phone number or by email_id....if name is repeating again asking for search by phone_number or email_id,if it is present printing the details,if not printing contact not found.
3.edit contact:firstly search,if present then asking which part do you want to edit ,name,phone number or email id,after taking input validating it and is it is valid then add to structure.
4.delete contact:first search ,if it is present then delete the whole details in structure.
5.list contact:list the whole contact details.
6.save contact:after completing the task save the structure into file.
7.save and exit:after completing the task save the structure into file and exit the code.
*/
#include <stdio.h>
#include "contact.h"
#include<string.h>
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"
#define BOLD_RED    "\033[1;31m"
#define BOLD_GREEN  "\033[1;32m"
#define BOLD_BLUE   "\033[1;34m"
#define BOLD_PURPLE "\033[1;35m"
#define BOLD_CYAN   "\033[1;36m"
#define BOLD    "\033[1m"
/* Structure declaration */

int main()
{
    /* Variable and structre defintion */
    int option;
    AddressBook addressbook;
    addressbook.contact_count = 0;
    FILE* fptr=fopen("data.txt","r");
    if(fptr==NULL)
    {
        printf("File not found\n");
    }
    else
    {
        rewind(fptr);
        fscanf(fptr,"#%d\n",&addressbook.contact_count);
        for(int i=0;i<addressbook.contact_count;i++)
        {
            fscanf(fptr," %[^,],%[^,],%[^\n]",addressbook.contact_details[i].Name,addressbook.contact_details[i].Mobile_number,addressbook.contact_details[i].Mail_ID);
            //getchar();
            }
    }
    fclose(fptr);
//arranging structure in order wise //same as bubble sort
    Contacts temp;
    for(int i = 0; i < addressbook.contact_count - 1; i++)
    {
        for(int j = 0; j < addressbook.contact_count - i - 1; j++)
        {
            if(strcasecmp(addressbook.contact_details[j].Name,addressbook.contact_details[j + 1].Name) > 0)
            {
                temp = addressbook.contact_details[j];
                addressbook.contact_details[j] = addressbook.contact_details[j + 1];
                addressbook.contact_details[j + 1] = temp;
            }
        }
    }

    while (1)
    {
        printf("Address book menu\n"); /* Give a prompt message for a user */
        printf("1.Add contact\n2.search contact\n3.Edit contact\n4.Delete contact\n5.list contact\n6.Save contact\n7.Exit\n");
        printf("Enter the option : ");
        scanf("%d", &option);

        switch (option) /* Based on choosed option */
        {
        //create a contacts
        case 1:
        {
            create_contact(&addressbook);
            break;
        }
        //search a contacts
        case 2:
        {
           // printf("Search Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4. Exit\nEnter the option : "); /* Providing menu */
           int search=1;
           while(search)
           { 
           search_contacts(&addressbook);
           printf("Do you want to continue to search?\n1.Yes\n0.No\n");
           scanf("%d",&search);
           }
            break;
        }
        //edit a contact
        case 3:
            //printf("Edit Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */
            int edit=1;
            while(edit)
            {
            edit_contact(&addressbook);
            printf("Do you want to continue to edit?\n1.Yes\n0.No\n");
            scanf("%d",&edit);
            }
            break;
        //Delete a contacts
        case 4:
        {
            //printf("Delete Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */
            int dlt=1;
            while(dlt)
            {
            delete_contact(&addressbook);
            printf("Do you want to continue to delete?\n1.Yes\n0.No\n");
            scanf("%d",&dlt);
            }
            break;
        }
        //List the contact details
        case 5:
        {
            //printf("List Contacts:\n");
            list_contacts(&addressbook);
            break;
        }
        //save to file
        case 6:
            printf("Saving contacts....!\n");
            save_contacts(&addressbook);
            break;
        //save to file and exit
        case 7:
            printf("INFO : Save and Exit...\n");
            save_contacts(&addressbook);
            return 0;
        
        default:
            printf("Invalid option \n");
            break;
        }
    }
    return 0;
}