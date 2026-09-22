#include<stdio.h>
#include<string.h>
#include<ctype.h>


struct Contact
{
    char name[50];
    char phone[15];
    char email[50];
};

struct Addressbook
{
    struct Contact c[100];

    int contact_count;
};


void load_contact(struct Addressbook *book)
{
    FILE *fp;
    int i;

    fp = fopen("Addressbook.txt", "r");

    if (fp == NULL) 
    {
        printf("No saved contacts found.\n");
        book->contact_count = 0;
        return;
    }

    fscanf(fp, "%d\n", &book->contact_count);

    for(i = 0; i < book->contact_count; i++)
    {
        fscanf(fp, "%49[^,],", book->c[i].name);
        fscanf(fp, "%14[^,],", book->c[i].phone);
        fscanf(fp, "%49[^\n]\n", book->c[i].email);

    }

    fclose(fp);
}


int is_name(char name[])
{
    int i = 0, flag = 0;
    while(name[i])
    {
        if(name[i] == '.' || name[i] == ' ' || islower(name[i]) || isupper(name[i]))
        {
            
        }
        else
        {
            flag = 1;
            return 0;
        }
        i++;
    }
    return 1;
}


int is_phone(char phone[])
{
    int i = 0, flag = 0;
    int len = strlen(phone);
    while(phone[i])
    {
        if(isdigit(phone[i]) && len == 10)
        {

        }
        else
        {
            flag = 1;
            return 0;
        }
        i++;
    }
    return 1;
}


int is_email(char email[])
{
    int len = strlen(email);
    int i, j = 0, flag;
    char check[] = "@gmail.com";

    //check @gmail.com is present or not
    for(i = (len - 10); email[i]; i++)
    {
        if(email[i] == check[j])
        {
            j++;
        }
        else
        {
            return 0;
        }
    }

    //check min 6 char need except @gmail.com
    if((len - 10) < 6)
    {
        return 0;
    }

    //check upper is present
    for(i = 0; i < (len - 10); i++)
    {
        if(isupper(email[i]))
        {    
            return 0;
        }
        
    }
    return 1;
}


int is_duplicate_phone(char phone[], struct Addressbook *book)
{
    int i;

    for(i = 0; i < (book->contact_count); i++)
    {
        if(strcmp(phone, (book->c[i].phone)) == 0)
        {
            return 1;
        }
    }
    return 0;
}


int is_duplicate_email(char email[], struct Addressbook *book)
{
    int i;

    for(i = 0; i < (book->contact_count); i++)
    {
        if(strcmp(email, (book->c[i].email)) == 0)
        {
            return 1;
        }
    }
    return 0;
}


void create_contact(struct Addressbook *book)
{
    int i = 0;
    char name[50];
    char phone[15];
    char email[50];
    int *count = &book -> contact_count;

    //name
    do
    {
        
        printf("\nEnter the name : ");
        scanf(" %[^\n]", name);

        if(is_name(name))
        {
            
            strcpy(book -> c[(*count)].name, name);
            break;
        }    
        else
        {
            printf("\nInvalid input\n\n");
        }

    }while (1);


    //phone number
    do
    {
        
        printf("Enter the phone no : ");
        scanf("%s", phone);

        if(is_phone(phone))
        {
            if(!is_duplicate_phone(phone, book))
            {
                strcpy(book -> c[(*count)].phone, phone);
                break;
            }
            else
            {
                printf("This phone number is already existed\n");
            }     
        }
        else
        {
            printf("\nInvalid input\n\n");
        }

    }while (1);

    //email
    do
    {
        
        printf("Enter the email : ");
        scanf("%s", email);

        if(is_email(email))
        {
            if(!is_duplicate_email(email, book))
            {
                strcpy(book -> c[(*count)].email, email);
                break;
            }
            else
            {
                printf("This email is already existed\n");
            }
        }
        else
        {
            printf("\nInvalid input\n\n");
        }

    }while (1);

    book->contact_count += 1;
}


int search_contact(struct Addressbook *book)
{
    int search_op, i;
    int flag_phone;
    int flag_email;

    char search_name[50];
    char search_phone[50];
    char search_email[50];

    

    do
    {
        printf("\n------------------------------------------\n");
        printf("              Search by:\n");
        printf("------------------------------------------\n");
        printf("1.Name\n");
        printf("2.Phone\n");
        printf("3.Email\n");
        printf("------------------------------------------\n");
        printf("Select the option: ");

        if(scanf("%d", &search_op) != 1)
        {
            printf("\nInvalid input\n");
            while(getchar() != '\n');
    
            continue;
        }
        

        if(search_op <= 3)
        {
            break;
        }
        else
        {
            printf("\nInvalid input, Try again\n");
        }
    
    }while(1); 
    

    int flag1 = 0, flag2 = 0, flag3 = 0;

    switch (search_op)
    {
        case 1:
        {
            printf("\nEnter the name: ");
            scanf("%s", search_name);

            if(!is_name(search_name))
            {
                printf("\nInvalid input\n");
                return -2;
            }
            
            printf("\n              Name found\n");
            printf("------------------------------------------\n");
            for(i = 0; i < (book->contact_count); i++)
            {
                if(strstr((book->c[i].name), search_name) != NULL) 
                {
                    printf("Contact  : %d\n", i + 1);
                    printf("Name     : %s\n", (book->c[i].name));
                    printf("Phone no : %s\n", (book->c[i].phone));
                    printf("Email    : %s\n", (book->c[i].email));
                    printf("\n"); 
                    flag1 = 1;
                }
            }
            printf("------------------------------------------\n");

            if(!flag1)
            {
               printf("Name is not found\n");
               return -2;
            }
            else 
            {
                return -1;
            }
            

            break;
        }
        
        case 2:
        {
            printf("\nEnter the phone no : ");
            scanf("%s", search_phone);

            if(!is_phone(search_phone))
            {
                printf("\nInvalid input\n");
                return -2;
            }
            
                

            for(i = 0; i < (book->contact_count); i++)
            {
                flag_phone = strcmp((book->c[i].phone), search_phone);

                if(!flag_phone) 
                {
                    printf("\n          Phone number found\n");
                    printf("------------------------------------------\n");
                    printf("Contact  : %d\n", i + 1);
                    printf("Name     : %s\n", (book->c[i].name));
                    printf("Phone no : %s\n", (book->c[i].phone));
                    printf("Email    : %s\n", (book->c[i].email));
                    printf("------------------------------------------\n");
                    
                    flag2 = 1;
                    return i;
                }
                
            } 

            if(!flag2)
            {
                printf("Phone no is not found\n");
                return -2;
            }

            break;     
        }
        
        case 3:
        {
            printf("\nEnter the email : ");
            scanf("%s", search_email);

            if(!is_email(search_email))
            {
                printf("\nInvalid input\n");
                return -2;
            }
            

            for(i = 0; i < (book->contact_count); i++)
            {
                flag_email = strcmp((book->c[i].email), search_email);

                if(!flag_email) 
                {
                    printf("\n            Email found\n");
                    printf("------------------------------------------\n");
                    printf("Contact  : %d\n", i + 1);
                    printf("Name     : %s\n", (book->c[i].name));
                    printf("Phone no : %s\n", (book->c[i].phone));
                    printf("Email    : %s\n", (book->c[i].email));
                    printf("------------------------------------------\n");

                    flag3 = 1;
                    return i;
                }
                
            }

            if(!flag3)
            {
                printf("Email is not found\n");
                return -2;
            }

            break;
        }
        

    }
}


void edit_contact(struct Addressbook *book, int contact_index)
{

    //edit

    char new_name[50];
    char new_phone[50];
    char new_email[50];

    int search_option;

    do
    {
        printf("\n------------------------------------------\n");
        printf("What you want to edit :\n");
        printf("------------------------------------------\n");
        printf("1.Name\n");
        printf("2.Phone\n");
        printf("3.Email\n");
        printf("------------------------------------------\n");
        printf("Select the option : ");
        
        if(scanf("%d", &search_option) != 1)
        {
            printf("\nInvalid input\n");
            while(getchar() != '\n');
        
            continue;
        }

        if(search_option <= 3)
        {
            break;
        }
        else
        {
            printf("\nInvalid input, Try again\n");
        }
        
    }while(1); 

    switch(search_option)
    {
        case 1:
        {
            printf("\nEnter the new name : ");
            scanf(" %[^\n]", new_name);

            if(is_name(new_name))
            {
                    strcpy((book->c[contact_index].name), new_name);   

                    printf("\nUpdated Contact\n");
                    printf("------------------------------------------\n");
                    printf("Contact  : %d\n", contact_index);
                    printf("Name     : %s\n", (book->c[contact_index].name));
                    printf("Phone no : %s\n", (book->c[contact_index].phone));
                    printf("Email    : %s\n", (book->c[contact_index].email));
                    printf("------------------------------------------\n");

            }
            else
            {
                printf("\nInvalid input\n\n");
            }
            break;
        }
        case 2:
        {
            printf("\nEnter the new phone number: ");
            scanf(" %s", new_phone);

            if(is_phone(new_phone))
            {
                if(!is_duplicate_phone(new_phone, book))
                {
                    strcpy((book->c[contact_index].phone), new_phone);

                    printf("\nUpdated Contact\n");
                    printf("------------------------------------------\n");
                    printf("Contact  : %d\n", contact_index);
                    printf("Name     : %s\n", (book->c[contact_index].name));
                    printf("Phone no : %s\n", (book->c[contact_index].phone));
                    printf("Email    : %s\n", (book->c[contact_index].email));
                    printf("------------------------------------------\n");
                }    
                else
                {
                    printf("\nThis phone number is already existed\n");
                }  
            }
            else
            {
                printf("\nInvalid input\n\n");
            }
            break;
        }
        case 3:
        {
            printf("\nEnter the new email: ");
            scanf(" %s", new_email);

            if(is_email(new_email))
            {
                if(!is_duplicate_email(new_email, book))
                {
                    strcpy((book->c[contact_index].email), new_email);
                  
                    printf("\n           Updated Contact\n");
                    printf("------------------------------------------\n");
                    printf("Contact  : %d\n", contact_index);
                    printf("Name     : %s\n", (book->c[contact_index].name));
                    printf("Phone no : %s\n", (book->c[contact_index].phone));
                    printf("Email    : %s\n", (book->c[contact_index].email));
                    printf("------------------------------------------\n");
                }
                else
                {
                    printf("\nThis email is already existed\n");
                }      
            }
            else
            {
                printf("\nInvalid input\n\n");
            }
            break;
        }
    }

}


void delete_contact(struct Addressbook *book, int contact_index)
{
    int i;
    char ch;

    printf("\nAre you sure want to delete this contact?\n");
    printf("Enter y/n : ");
    scanf(" %c", &ch);

    if(ch == 'y')
    {
        for(i = contact_index; i < (book->contact_count); i++)
        {
            book->c[i] = book->c[i + 1];
        }
        book->contact_count -= 1;

        printf("\nContact deleted successfully\n");
    } 
    else
    {
        printf("\nDelete operation canceled\n");
    }
}


void list_contact(struct Addressbook *book)
{
    int i;

    if((book->contact_count) > 0)
    {
        printf("\n------------------------------------------\n");
        printf("            Address Book:\n");
        printf("------------------------------------------\n");
        for(i = 0; i < (book->contact_count); i++)
        {
            
            printf("Contact  : %d\n", i + 1);
            printf("Name     : %s\n", (book->c[i].name));
            printf("Phone no : %s\n", (book->c[i].phone));
            printf("Email    : %s\n", (book->c[i].email));

            if(i < (book->contact_count) - 1)
               printf("\n");
        }
        printf("------------------------------------------\n");
    }
    else
    {
        printf("\nAddresssbook is empty\n");
    }

    
}


void save_contact(struct Addressbook *book)
{
    FILE *fp;
    int i;

    fp = fopen("Addressbook.txt", "w");

    fprintf(fp, "%d\n", book->contact_count);

    for(i = 0; i < book->contact_count; i++)
    {
        fprintf(fp, "%s,", book->c[i].name);
        fprintf(fp, "%s,", book->c[i].phone);
        fprintf(fp, "%s\n", book->c[i].email);
    }

    fclose(fp);
    printf("\nContacts saved successfully\n");
}



int main()
{
    int mode, contact_index;
    struct Addressbook book;


    book.contact_count = 0;
    load_contact(&book);

    do
    {
        printf("\n------------------------------------------\n");
        printf("           Address Book Menu:\n");
        printf("------------------------------------------\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("------------------------------------------\n");
        printf("Select the mode: ");
        
        
        if(scanf("%d", &mode) != 1)
        {
            printf("\nInvalid input\n");
            while(getchar() != '\n');
        
            continue;
        }

        switch(mode)
        {
            case 1:
            {
                create_contact(&book);
                break;
            }
            case 2:
            {
                search_contact(&book);
                break;
            }
            case 3:
            {
                int flag1 = search_contact(&book);

                if(flag1 == -1)
                {
                    printf("\nEnter contact no for edit: ");
            
                    if(scanf("%d", &contact_index) != 1)
                    {
                        printf("\nInvalid input\n");
                        while(getchar() != '\n');
        
                        continue;
                    }

                    if (contact_index <= book.contact_count)
                    {
                        edit_contact(&book, contact_index - 1);
                    }
                    else
                    {
                        printf("\nInvalid contact number\n");
                    }
                }
                else if(flag1 != -2)
                {
                    contact_index = flag1;
                    if (contact_index <= book.contact_count)
                    {
                        edit_contact(&book, contact_index);
                    }
                    else
                    {
                        printf("\nInvalid contact number\n");
                    }
                }

                break;
            }
            case 4:
            {
                int flag2 = search_contact(&book);
                
                if(flag2 == -1)
                {
                   printf("\nEnter contact no for delete: ");
                   if(scanf("%d", &contact_index) != 1)
                   {
                      printf("\nInvalid input\n");
                      while(getchar() != '\n');
        
                      continue;
                    }

                    if(contact_index <= book.contact_count)
                    {
                       delete_contact(&book, contact_index - 1);
                    }
                    else
                    {
                       printf("\nInvalid contact number\n");
                    }
                }  
                else if(flag2 != -2)
                {
                    contact_index = flag2;
                    if(contact_index <= book.contact_count)
                    {
                       delete_contact(&book, contact_index);
                    }
                    else
                    {
                       printf("\nInvalid contact number\n");
                    }
                }  
                break;
            }
            case 5:
            {
                list_contact(&book);
                break;
            }
            case 6:
            {
                save_contact(&book);
                break;
            }
            
        }
    
    }while (mode != 7);
    

    return 0;
}



