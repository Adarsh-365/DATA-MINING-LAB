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


    mpz_t random1,ui1;
    mpz_inits(random1,ui1,NULL);
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    
    //gmp_printf("%Zd",random1);
    mpz_t P,G,a,b,x,y,ka,kb,temp22;
    mpz_inits(P,G,a,b,x,y,ka,kb,temp22,NULL);
    mpz_set_ui(P,1009);
    mpz_set_ui(G,11);

    //char message[100] = "HelloSHA2";

    mpz_set_ui(a,4);
    mpz_set_ui(b,3);

    //alice side
    mpz_powm(x,G,a,P);

    //bob side
    mpz_powm(y,G,b,P);

    //alice review y and bob recive x


    //alice side
    mpz_powm(ka,y,a,P);

    //bob side
    mpz_powm(kb,x,b,P);

    gmp_printf("Alice pair Private = %Zd Secret =  %Zd",a,ka);



    printf("\n");
    gmp_printf("Bob pair Private = %Zd Secret =  %Zd",b,kb);
    printf("\n");

    
    char Message[100] = "Hello World";
    printf("Message is %s ",Message);
     printf("\n");
        
    char Dl[10] = "$";
    //Add Message and UID with $ i.e. MD
    
    
    char Encrypted_message[strlen(Message)];
    char Encrypted_KEYA[strlen(Message)];
    char Encrypted_KEYB[strlen(Message)];
    //printf("Message is %d ",Message[ii]);
    
    for (size_t i = 0; i < strlen(Message); i++) {
        
        Encrypted_KEYA[i] = ( mpz_get_ui(ka)+ i) % 256;
        Encrypted_KEYB[i] = ( mpz_get_ui(ka)+ i) % 256;
       
    }
    for (size_t i = 0; i < strlen(Message); i++) {
        Encrypted_message[i] = Encrypted_KEYA[i]^Message[i];
        
         //printf("\n %02x",Encrypted_message[i] );
        
    }
    strcpy(Message,Encrypted_message);
    
   
    
  printf("Encrypted_message is %s ",Encrypted_message);
  
  
  //--------------------------------------------------
    
   // printf("\nMD is %s",Encrypted_message);
     printf("\n");
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    //Create hash of MD
    SHA256((unsigned char*)Encrypted_message,strlen(Encrypted_message),hash);
    printf("\nSHA-256 hash of %s : ",Encrypted_message);
    
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
      printf("%02x", hash[i]);
     }
     char Hash_string[500];
     hash_to_string(hash, sizeof(hash), Hash_string);
     // printf("\n");
     //printf("\nSHA-1 hash of %s : ",Hash_string);
      printf("\n");
     
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
     //Convert hash hex to number
     mpz_import(Hash_number,sizeof(Message),1,sizeof(char),0,0,Hash_string);
     gmp_printf("\nMD_number %Zd",Hash_number);
     
    //Create hash ciphertext by encryption
    
    mpz_powm(ciphertext, Hash_number, e, n);
    
    Ciphertext_string = mpz_get_str(NULL,10,ciphertext);
    //add ciphertext in MD send to B
     strcat(Message,Dl);
     strcat(Message,Ciphertext_string);
     
     gmp_printf("\n \n Ciphertext %Zd",ciphertext);
     printf("\n");
     printf("\nMessage is  =  %s",Message);
    
    
    
    char* token = strtok(Message, "$");
    char dest_decryt[5000];
   
    char Hash1_decryt[5000];

    int count1=0;
    while (count1<3) 
    {
     
      if(count1==0){
          strcpy(dest_decryt, token);
          }
          if(count1==1){
          strcpy(Hash1_decryt, token);
         
          }
         
          token = strtok(NULL, "$");
          count1 +=1;
     }
    printf("\n\n dest_decryt is  =  %s",dest_decryt);
   
    printf("\n Hash1_decryt is  =  %s",Hash1_decryt);
    printf("\n");
    
    mpz_set_str(ciphertext,Hash1_decryt,10);
    mpz_powm(op_ex,ciphertext , d, n);
     
    
    //gmp_printf("\n MD_number %Zd",op_ex);
    
    
    char output[100];
    size_t count;
    mpz_export(output,&count,1,sizeof(char),0,0,op_ex);
     printf("\n");
    printf("\n After Decrypted hash = %s",output);
    
    
    char TEST_MD[1000];
    
   
    printf("\n B recieve string message and UID = %s",dest_decryt);
    //printf("\n B recieve string message and UID = %s",Message);
    
        
    
    
    
    
    unsigned char hash_dec[SHA256_DIGEST_LENGTH];
    //Create hash of MD
    SHA256((unsigned char*)dest_decryt,strlen(dest_decryt),hash_dec);
    printf("\nSHA-256 hash of %s : ",dest_decryt);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
      printf("%02x", hash_dec[i]);
     }
     char Hash_string_dec[1000];
     hash_to_string(hash, sizeof(hash), Hash_string_dec);
     //printf("\nhash in string %s",Hash_string_dec);

     int DS;
     DS = strcmp(output,Hash_string_dec);
    // printf("\n----------------->%d \n",DS);
     if(DS==0){
          printf("\n\n Authentication Successfull \n");
     }
     else{
     printf("\n\n Authentication Failed \n");
     
     }


  for (size_t i = 0; i < strlen(Message); i++) {
        Encrypted_message[i] = Encrypted_KEYB[i]^dest_decryt[i];
        
        
    }
printf("\n Decrypted Message %s \n",Encrypted_message );






  return 0;
}
