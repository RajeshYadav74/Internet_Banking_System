#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void toregister();
void tologin();
void showbalance();
void deposit();
void withdrawl();
int transfer();
void update_password();
void account_details();
void transaction_details();

    
typedef struct user_info{
    char fname[30];
    char lname[30];
    char phone_num[15];
    char account_num[20];
    char password[15];
    float balance;
}info;


     info usr,usr1;         
       


    int choice,opt;
    float amount;
    
    FILE *fp,*det_p; 
                 
    char filename[15];
    char det_name[15];
    char phone_num[15];
    char ac_num[20];
    char password[15];
    char conti='Y';
    char ch;

int main(){



    printf("Welcome to Internet Banking\n\n");
    puts("1. Register Your Account ");
    puts("2. Login to Your Account");
    printf("\nYour choice ");
    scanf("%d",&choice);
   
   switch(choice){
     case 1: toregister(); break;
     case 2: tologin(); break;
     default: puts(" You have entered invalid option"); 
   }


      return 0;
}

    void toregister(){
        system("cls");

        printf("\nEnter Your first name: ");
        scanf("%s",usr.fname);

        printf("\nEnter Your last name: ");
        scanf("%s",usr.lname);

        printf("\nEnter Your Account Number: ");
        scanf("%s",usr.account_num);

        printf("\nEnter Your Phone Number: ");
        scanf("%s",usr.phone_num);

        printf("\nEnter Your Password: ");
        scanf("%s",usr.password);

        usr.balance=0.0;

        strcpy(filename,usr.account_num);
        fp=fopen(strcat(filename,".txt"),"w");
        fwrite(&usr,sizeof( info),1,fp);

        if(fwrite!=0){
            printf("\n\n Account succesfully created");
        }
        else{
            printf("Something went wrong please try again");
        }
     fclose(fp);

}

void tologin(){
     system("cls");

        printf("\nEnter your account number : ");
        scanf("%s",ac_num);
       
        printf("\nEnter Your password : ");
        scanf("%s",&password);

        strcpy(filename,ac_num);
        fp=fopen(strcat(filename,".txt"),"r");
        
        if(fp==NULL){
            puts("Account Not Register ");
        }
         else{
            fread(&usr,sizeof(info),1,fp);
            fclose(fp);
            
         if(!strcmp(password,usr.password)){

            printf("\n\n\tWelcome %s %s",usr.fname,usr.lname);

            while(conti=='Y'){
            printf("\n1. For Account details  ");
            printf("\n2. For Balance Inquiry ");
            printf("\n3. For Depositing cash  ");
            printf("\n4. For Cash withdrawl  ");
            printf("\n5. For Online transaction  ");
            printf("\n6. To Update Your password  ");
            printf("\n7. To check Your transaction detail  ");
          
            printf("\nYour choice ");
            scanf("%d",&opt);
           
            switch(opt){
                case 1:
                        account_details(); break; 
                         
                case 2:
                        showbalance();  break;

                case 3:
                        deposit();break;
                       

                case 4: 
                        withdrawl(); break;

                case 5:

                        transfer();  break;
                
                case 6:  
                        update_password();break;


                case 7: 
                        transaction_details();break;
                       

            

                default: 
                        puts("Invalid option");

                       
            }
            printf("\n\nDo you want to continue, if yes then press Y\n");
            scanf("%s",&conti);


            
            }
            

        }
         else{
            printf("\nInvalid password");
        }

        }


}

void showbalance(){
     printf("\nYour current balance is Rs. %.2f",usr.balance); 


}

void deposit(){
                 printf("\nEnter an amount  that you want to deposit ");
                       scanf("%f",&amount);
                       usr.balance+=amount;

                       fp=fopen(filename,"w");
                       fwrite(&usr,sizeof( info),1,fp);
                         fclose(fp);

                       if(fwrite!=NULL){
                        printf("\nRs. %.2f has been deposited in your account ",amount);
                        printf("\nYour current balance is Rs. %.2f",usr.balance);
                      
                        strcpy(det_name,password);
                        det_p=fopen(strcat(det_name,".txt"),"a");
                        if(det_p==NULL){
                            printf("Details not recorded");
                            
                        }
                         else{
                            time_t get_time;
                            time(&get_time);
                            fprintf(det_p,"\nRs. %.2f has deposited in  your account",amount);
                            fprintf(det_p,"\nDate/time : %s",ctime(&get_time));
                            fprintf(det_p,"Total balance : %.2f \n",usr.balance);

                            fclose(det_p);
                        }
                        
                        
                       }
                       
                      
}

void withdrawl(){
                        printf("\nEnter an amount to withdrawl\n ");
                        scanf("%f",&amount);
                        usr.balance-=amount;

                        fp=fopen(filename,"w");
                         fwrite(&usr,sizeof( info),1,fp);
                         if(fwrite!=NULL){
                            printf("\nRs. %.2f has been withdrawl from your account",amount);
                             printf("\nYour current balance is Rs. %.2f",usr.balance);
                         }
                       fclose(fp);
                        strcpy(det_name,password);
                        det_p=fopen(strcat(det_name,".txt"),"a");
                        if(det_p==NULL){
                            printf("Details not recorded");
                            
                        }
                         else{
                            time_t get_time;
                            time(&get_time);
                            fprintf(det_p,"\nRs. %.2f has withdrawl from  your account\n",amount);
                             fprintf(det_p,"Date/time : %s",ctime(&get_time));
                             fprintf(det_p,"remaining balance : %.2f \n",usr.balance);

                            fclose(det_p);
                        }
                        

}
  
int transfer(){
                       puts("\nEnter the account number to transfer the money");
                       scanf("%s",&ac_num);
                       puts("Enter amount to transfer");
                       scanf("%f",&amount);
                       strcpy(filename,ac_num);
                       
                        fp=fopen(strcat(filename,".txt"),"r");
                        if(fp==NULL){
                        puts("Account not register");
                        return  0;
                    } 
                        fread(&usr1,sizeof( info),1,fp);
                    
                      fclose(fp);
                       if(amount>usr.balance){
                        puts("insufficient balance");
                       }else{
                         
                        
                        fp=fopen(filename,"w");
                        usr1.balance+=amount;
                        fwrite(&usr1,sizeof(info),1,fp);
                        fclose(fp);
                         if(fwrite!=NULL){
                            printf("\nYou have transfer Rs. %.2f to account number: %s",amount,ac_num);
                           usr.balance-=amount;
                            printf("\nYour current balance is Rs. %.2f",usr.balance);
                           strcpy(filename,usr.account_num);
                            fp=fopen(strcat(filename,".txt"),"w");
                           
                            fwrite(&usr,sizeof(info),1,fp);
                        fclose(fp);

                         }

                          fclose(fp);
                        strcpy(det_name,password);
                        det_p=fopen(strcat(det_name,".txt"),"a");
                        if(det_p==NULL){
                            printf("Details not recorded");
                            
                        }else{
                             time_t get_time;
                            time(&get_time);
                            fprintf(det_p,"\nRs. %.2f has transfered from  your account to account number: %s \n",amount,ac_num);
                              fprintf(det_p,"Date/time : %s",ctime(&get_time));
                              fprintf(det_p,"remaining balance : %.2f \n",usr.balance);

                            fclose(det_p);
                
                       }
                       
                        

}
}

 void update_password(){
    puts("\nPlease enter your new password");
    scanf("%s",&password);
    strcpy(usr.password,password);
    fp=fopen(filename,"w");
    fwrite(&usr,sizeof (info),1,fp);
    if (fwrite!=NULL){
        puts("Passowrd succesfully updated");
    }
    fclose(fp);

 }

 void account_details(){
    printf("\n\tAccount details\n");
    for(int i=0; i<=50;i++){
        printf("-");
    }
    printf("\nName of the account holder : %s %s",usr.fname,usr.lname);
    printf("\nAccount number : %s ",usr.account_num);
    printf("\nphone number : %s ",usr.phone_num);
     printf("\npassword : %s ",usr.password);
    printf("\nCurrent balance : %.2f ",usr.balance);

 }
    
void transaction_details(){
  
        strcpy(det_name,password);
        det_p=fopen(strcat(det_name,".txt"),"r");
       
        if(det_p==NULL){
            printf("Transaction details not found");
        }
        
        else{
             ch=fgetc(det_p);
             printf("\n\tTransaction details\n");
             for(int i=0;i<=50;i++){
                printf("-");
             }
             printf("\n");
            while((ch!=EOF)){
                printf("%c",ch);
                ch=fgetc(det_p);
            }
}
    fclose(det_p);
}    
        
      
    
