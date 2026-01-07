#include "addressbook.h"
#include <string.h>     //defining all functions in this file
void pull_file_data(struct AddressBook * addressBook ,char * file_name){
    FILE * fp=fopen(file_name,"r"); //fetching data from database to structure
    int i=0;
    addressBook->contactCount=0; 
    fseek(fp,0,SEEK_END);  //checking if there is any data in database 
    if(ftell(fp)!=0){
        rewind(fp); //moving offset to start of file
        while(!feof(fp)){   
            fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            i++;
        }
    }
    addressBook->contactCount=i;  //count of no of data
    fclose(fp);
}

void push_data_tofile(struct AddressBook * addressBook, char * file_name){
    FILE * cp =fopen("database.csv","w");   //func to push the data from structure to database
	for(int i=0;i<addressBook->contactCount;i++){
    	fprintf(cp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	fclose(cp);
}
int duplicatemobile(struct AddressBook * addressBook,char * mobno){
    for(int i=0;i<addressBook->contactCount;i++){   //checking if mobile number is duplicate
        if(strcmp(mobno,addressBook->contacts[i].phone)==0){
            printf("Duplicate value\n");
            return 0;
        }
    }
    return 1;      
}
int duplicateemail(struct AddressBook * addressBook,char * mobno){
    for(int i=0;i<addressBook->contactCount;i++){  //checking if email is duplicate
        if(strcmp(mobno,addressBook->contacts[i].phone)==0){
            printf("Duplicate value\n");
            return 0;
        }
    }
    return 1;      
}
int validatemobile(char * mobno){
    int flag=0;   //validating mob no 
    if((strlen(mobno)==10)&&(mobno[0]>'5' && mobno[0]<='9')){
        for(int i=1;i<strlen(mobno);i++){
            if( !(mobno[i]>='0'&&mobno[i]<='9') ){
                return 0;
            } 
        }   
        return 1;     
    }
}
int validateemail(char * email){   //validating email
    if(email[0] !='@' && email[0]!=' ' && email[0]!= '\t'){
        char * ptr=strstr(email,"@gmail.com");
        if(ptr==NULL){
            return 0;
        }
        if(strcmp(ptr,"@gmail.com")==0){
            return 1;
        } 
        return 0;
    }
    return 0;
}
               
        /*for(int i=0;i<10;i++){
            if(str[i]!=email[i+(strlen(email)-10)]){
                return 0;
            }

        }*/
void add_contact(struct AddressBook *addressBook){  //to add contact
    char name[40];    
    char mobno[15];
    char email[20];
    printf("Enter name:");
    scanf(" %[^\n]",name);
    printf("Enter mobile number:");
    scanf("%s",mobno);
    int flag=1;
    while(flag){
        if(validatemobile(mobno)&&duplicatemobile(addressBook,mobno)){
            flag=0;
        }
        else{ 
            printf("Enter valid mobile number!\n"); 
            scanf("%s",mobno);  //giving user chance to again give input if entered wrong
        }
    }   
    printf("Enter email id:");
    scanf("%s",email);
    flag=1;
    while(flag){
        if(validateemail(email)&&duplicateemail(addressBook,email) ){
            flag=0;
        }
        else{
            printf("Enter valid email id!\n"); 
            scanf("%s",email);
        }
    }  
    int i=addressBook->contactCount;
    strcpy(addressBook->contacts[i].name,name);  //copying data to structure
    strcpy(addressBook->contacts[i].phone,mobno);
    strcpy(addressBook->contacts[i].email,email);
    addressBook->contactCount++;

}
void search_contact(struct AddressBook *addressBook)
{
    int option;  //searching function
    addressBook->ir_size=0;
    printf("Enter 1 to search by name:\n");
    printf("Enter 2 to search by phone:\n");
    printf("Enter 3 to search by email:\n");
    printf("Enter your option:");
    scanf("%d",&option);
    switch(option){    //here we are giving option to user to search by name or phone or email
        case 1:          // we are saving the matched indexes in the index record first and 
            char name[20];  //using them we are printing the matched values
            printf("Enter a name:");  //case 1 is for name, multiple names is possible
            scanf(" %[^\n]",name);
            for(int i=0;i<addressBook->contactCount;i++){
                if(strcmp(name,addressBook->contacts[i].name)==0){
                    addressBook->index_record[addressBook->ir_size]=i;
                    addressBook->ir_size++;
                }
            }
            if(addressBook->ir_size==0)   // of not found printing contact not found
                printf("contact not found\n");
            for(int i=0;i<addressBook->ir_size;i++){
                int j=addressBook->index_record[i];
                printf("%d .%s,%s,%s\n",i+1,addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
            }
            break;
        case 2:
            char mob[20];   //case 2 is for mob no searching 
            int k=0;
            printf("Enter a phone num:");
            L1:
            scanf(" %s",mob); //mob no is unique so, we are taking slno directly 1 
            if(validatemobile(mob)){ //as we are already checking duplicate no 2nd match can be found
                for(k;k<addressBook->contactCount;k++){
                    if(strcmp(mob,addressBook->contacts[k].phone)==0){
                        addressBook->index_record[addressBook->ir_size]=k;
                        addressBook->ir_size++;
                        break;
                    }
                }
                if(k==addressBook->contactCount){  //if no match found printing contact not found
                    printf("Contact not found\n");
                    break;
                }

                printf("%d. %s,%s,%s\n",1,addressBook->contacts[k].name,addressBook->contacts[k].phone,addressBook->contacts[k].email);
            }
            else{ 
                printf("Enter valid number: ");
                goto L1;
            }
            break;    
        case 3:     //case 3 is for email
            char email[20];
            int i=0;
            printf("Enter a email:");
            L2:
            scanf(" %s",email);   //same as phone no duplicates allowed
            if(validateemail(email)){
                for(i;i<addressBook->contactCount;i++){
                    if(strcmp(email,addressBook->contacts[i].email)==0){
                        addressBook->index_record[addressBook->ir_size]=i;
                        addressBook->ir_size++;
                        break;
                    }
                }
                if(k==addressBook->contactCount){//if not found, printing contact not found
                    printf("Contact not found\n");
                    break;
                }
                printf("%d .%s,%s,%s\n",1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            else  
            {
                printf("Enter a valid email : ");
                goto L2;
            }
            break;
        default:
            printf("Enter valid number!\n");

    }
}
void edit_contact(struct AddressBook *addressBook)
{
    search_contact(addressBook);  //calling search func to search what we want to edit
    if(addressBook->ir_size==0){  //if not found returning
        return;
    }
    int slno;
    printf("Enter which slno you want to edit=");
    L3:
    scanf("%d",&slno);      // taking slno from user to edit which slno
    if(slno>addressBook->ir_size){
        printf("Enter a valid slno:");
        goto L3;    //printing the selected contact
    }
    printf("%s,",addressBook->contacts[addressBook->index_record[slno-1]].name);
    printf("%s,",addressBook->contacts[addressBook->index_record[slno-1]].phone);
    printf("%s\n",addressBook->contacts[addressBook->index_record[slno-1]].email);
    int opt;
    do{            // giving user chance to edit after editing 
        printf("Enter what you want to edit\n");
        printf("1 to edit name\n");  //giving user chance to edit name, or mob, or email 1 at a time
        printf("2 to edit mobno\n");
        printf("3 to edit email\n");
        printf("4 to exit\n");
        printf("enter opt=");
        scanf("%d",&opt);
        switch(opt){
            case 1:    //case 1 is to edit name
                char name[20];
                printf("Enter name:");
                scanf(" %[^\n]",name);   //we are copying the new name in that position
                strcpy(addressBook->contacts[addressBook->index_record[slno-1]].name,name);
                break;
            case 2:          //case 2 is for mob no
                char mob[20];
                printf("Enter mobno:");
                L1:
                scanf(" %s",mob);   //giving user to enter again if entered invalid
                if(validatemobile(mob)&&duplicatemobile(addressBook,mob))
                    strcpy(addressBook->contacts[addressBook->index_record[slno-1]].phone,mob);
                else{
                    printf("Enter valid number:");
                    goto L1;
                }
                break;
            case 3:                //case 3 is for email
                char email[20];     
                printf("Enter email:");
                L2: 
                scanf(" %s",email);   //giving user to enter again if entered invalid
                if(validateemail(email)&&duplicateemail(addressBook,email))
                    strcpy(addressBook->contacts[addressBook->index_record[slno-1]].email,email);
                else{
                    printf("Enter valid mail:");
                    goto L2;
                }
                break;
            case 4:  //case 4 is for exiting the edit function
                printf("Exiting.....\n");
                break;    
        }
    }while(opt!=4);
}
void delete_contact(struct AddressBook *addressBook)
{
    search_contact(addressBook);  //calling search to search which contact we want to delete
    if(addressBook->ir_size==0){  //if not found returning
        return;
    }
    int slno;
    printf("Enter which slno you want to delete=");
    L3:       //taking slno if multiple options found, user will give 1 slno
    scanf("%d",&slno);
    if(slno>addressBook->ir_size){
        printf("Enter a valid slno:");
        goto L3;
    }      //first printing the selected contact
    printf("%s,",addressBook->contacts[addressBook->index_record[slno-1]].name);
    printf("%s,",addressBook->contacts[addressBook->index_record[slno-1]].phone);
    printf("%s\n",addressBook->contacts[addressBook->index_record[slno-1]].email);
    char opt;      
    printf("ARE YOU SURE : \n PRINT Y IF SURE, N IF NOT: ");  //giving confirmation message
    L4:
    scanf(" %c",&opt);
    if((opt!='Y' && opt!='N')){
        printf("Enter valid option:");
        goto L4;
    }
    switch(opt){
        case 'Y':  //case y for yes
            int k =addressBook->index_record[slno-1];
            for(int i=k;i<addressBook->contactCount-1;i++){  //shifting upwards from that
                addressBook->contacts[i]=addressBook->contacts[i+1];
            }
            addressBook->contactCount--;
            printf("DELETION SUCCESSFUL..\n");  
        case 'N':   //case n for no
            break;
    }
}
void list_contacts(struct AddressBook *addressBook)  //to list/print the contacts available
{
    if(addressBook->contactCount==0){     //if no contacts found printing message
        printf("Contacts not available\n");
    }
    else{ //printing the contacts till contactcount
        for(int i=0;i<(addressBook->contactCount);i++){
            printf("%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }
}

