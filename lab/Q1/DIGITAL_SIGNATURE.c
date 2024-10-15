#include<stdio.h>
#include<openssl/sha.h>
#include<string.h>
#include<gmp.h>



void hash_to_string(const unsigned char *hash, size_t length, char *output) {
    for (size_t i = 0; i < length; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[length * 2] = '\0';  // Null-terminate the string
}

int main(){

    //Create Message and UID
    mpz_t random1,ui1;
    mpz_inits(random1,ui1,NULL);
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    mpz_rrandomb(random1,state,20);
    mpz_set_ui(random1,123456789);
    char Message[100] = "Hello World!";
    printf("Message is %s ",Message);
    printf("\n");
    char UID[100] = "";
    char ui_temp[100] = "";
    long long int rand1;
    while(mpz_cmp_ui(random1,0)!=0){
        mpz_mod_ui(ui1,random1,16);
        mpz_div_ui(random1,random1,16);
        rand1 = mpz_get_ui(ui1);
        sprintf(ui_temp,"%lld",rand1);
        
        if(rand1==10){
          strcpy(ui_temp, "A");

          }
          if(rand1==11){
          strcpy(ui_temp, "B");
          }
          if(rand1==12){
          strcpy(ui_temp, "C");
          }
          if(rand1==13){
          strcpy(ui_temp, "D");
          }
          if(rand1==14){
          strcpy(ui_temp, "E");
          }
          if(rand1==15){
          strcpy(ui_temp, "F");
          }
          strcat(UID,ui_temp);
          }
        
        int length_uid = strlen(UID);
        char UID_TEMP[100];
        strcpy(UID_TEMP,UID);
        for(int i=0;i<length_uid;i++){
              
              UID[i]=UID_TEMP[length_uid-i-1];
        
        }
        printf("\nUID is %s",UID);
        printf("\n");
        char Dl[10] = "$";



        //Add Message and UID with $ i.e. MD

        strcat(Message,Dl);
        strcat(Message,UID);
        printf("\nMD is %s",Message);
        printf("\n");
        unsigned char hash[SHA_DIGEST_LENGTH];


        //Create hash of MD

        SHA1((unsigned char*)Message,strlen(Message),hash);
        printf("\nSHA-1 hash of %s : ",Message); 
        for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
           printf("%02x", hash[i]);
         }
        char Hash_string[200];


        //Converting Hash to string

        hash_to_string(hash, sizeof(hash), Hash_string);
        printf("\n");


        //now code for Encryption and Decryption

        mpz_t p,q,p_1,q_1,n,phi,e,d,Hash_number,ciphertext,op_ex;
        mpz_inits(p,q,p_1,q_1,n,phi,e,d,Hash_number,ciphertext,op_ex,NULL);
        mpz_rrandomb(p,state,1000);
        mpz_rrandomb(q,state,1000);
        mpz_nextprime(p,p);
        mpz_nextprime(q,q);
        mpz_mul(n,p,q);
        mpz_sub_ui(p_1,p,1);
        mpz_sub_ui(q_1,q,1);
        mpz_mul(phi,p_1,q_1);
        mpz_nextprime(e,p);    
        int j;    
        j = mpz_cmp(e,phi);    
        while (j>=0)    
          {
            mpz_sub_ui(p,p,1);        
            mpz_nextprime(e,p);        
            j = mpz_cmp(e,phi);
          }
        char* Ciphertext_string;
        mpz_invert(d,e,phi);



        //Convert hashstring  to mpz_t Number

        mpz_import(Hash_number,sizeof(Message),1,sizeof(char),0,0,Hash_string);
        gmp_printf("\nMD_number %Zd",Hash_number);



        //Create hash ciphertext by encryption and convert into string

        mpz_powm(ciphertext, Hash_number, e, n);
        Ciphertext_string = mpz_get_str(NULL,10,ciphertext);
        gmp_printf("\n \n Ciphertext %Zd",ciphertext);
        printf("\n");
        // Encryption completed.


        // Adding Encrypted hash with Message Digest

        strcat(Message,Dl);
        strcat(Message,Ciphertext_string);

        // Now Send Message to USER B
        

        // User B will split data using strtok token is $

        printf("\nMessage is  =  %s",Message);
        char* token = strtok(Message, "$");
        char dest_decryt[5000];
        char UID_decryt[5000];
        char Hash1_decryt[5000];
        int count1=0;
        while (count1<3) 
        {
          if(count1==0){
              strcpy(dest_decryt, token);
              }
              if(count1==1){
              strcpy(UID_decryt, token);
              }
              if(count1==2){
             
              strcpy(Hash1_decryt, token);
              }
              token = strtok(NULL, "$");
              count1 +=1;
         }
        printf("\n\n dest_decryt is  =  %s",dest_decryt);
        printf("\n UID_decryt is  =  %s",UID_decryt);
        printf("\n Hash1_decryt is  =  %s",Hash1_decryt);
        printf("\n");


        // convert encrypted hash to mpz and decrypt it

        mpz_set_str(ciphertext,Hash1_decryt,10);
        mpz_powm(op_ex,ciphertext , d, n);
        char Decrypted_Hash[100];
        size_t count;


         // convert decypted number to string you get hash

        mpz_export(Decrypted_Hash,&count,1,sizeof(char),0,0,op_ex);
        printf("\n");
        printf("\n After Decrypted hash = %s",Decrypted_Hash);


        // now add Message and UID and find its hash

        char TEST_MD[1000];
        strcat(dest_decryt,Dl);
        strcat(dest_decryt,UID_decryt);
        printf("\n B recieve string message and UID = %s",dest_decryt);
        unsigned char hash_dec[SHA_DIGEST_LENGTH];


        //Create hash of MD

        
        SHA1((unsigned char*)dest_decryt,strlen(dest_decryt),hash_dec);
        printf("\nSHA-1 hash of %s : ",dest_decryt);
        for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
          printf("%02x", hash_dec[i]);
         }
         char New_hash[1000];
         hash_to_string(hash, sizeof(hash), New_hash);

        // compare decrypted hash with new hash

         int DS;
         DS = strcmp(Decrypted_Hash,New_hash);
        // checking  DS 
         if(DS==0){
              printf("\n\n Authentication Successfull \n");
         }
         else{
         printf("\n\n Authentication Failed \n");  
         }
  return 0;
}
