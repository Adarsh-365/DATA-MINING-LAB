#include <stdio.h>
#include <gmp.h>
#include <string.h>
int main() {
    char c;
    
    c = 'a';
    char str1[100];
    int asci[100];
    printf("Enter The Plaintext ");
    scanf("%s",&str1);
    
    int length1;
    length1 = strlen(str1);
    // printf("\n the plaintext is %s of length ",str1);
    // printf("  of size %d",length1);
    
    for(int i = 0;i<length1;i++){

        c = str1[i];
        printf("%c is %d",c,(int)c);
        asci[i]=(int)c;
        printf("\n");
    }
    mpz_t message;
    mpz_set_ui(message,asci[0]);
    
    for(int j=1;j<length1;j++){
        mpz_mul_ui(message,message,1000);
        mpz_add_ui(message,message,asci[j]);
        
        
    }
    gmp_printf(" message convert to number %Zd ",message);
    //mpz_set_ui(message, 2005);
    
    
    
    
    
    
    
    
    
    
    mpz_t p,q,n,phi,e,d,ciphertext,plaintext,one1,temp1,gcd_temp;
    
    mpz_inits(p,q,n,phi,e,d,ciphertext,plaintext,temp1,gcd_temp, NULL);
    mpz_set_ui(one1,1);
    
   
    
    gmp_randstate_t state;
    
 
    
    gmp_randinit_mt(state);
    
    mpz_rrandomb(p, state, 50); 
    
    mpz_nextprime(p, p);
    
    mpz_rrandomb(q, state, 50); 
    
    mpz_nextprime(q, q);
    

    mpz_mul(n, p, q);
    
   
    mpz_t p_minus_1, q_minus_1;
    mpz_inits(p_minus_1, q_minus_1, NULL);
    
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    
    mpz_mul(phi, p_minus_1, q_minus_1);
    
    gmp_printf("\n p = %Zd q = %Zd  are random prime number \n",p,q);
    gmp_printf("n= p*q = %Zd phi = (p-1)*(q-1) %Zd  \n",n,phi);
    
   
    
   
    
    mpz_nextprime(e,p); 
    mpz_invert(d, e, phi);
   
    
   
  
    

    mpz_powm(ciphertext, message, e, n);
    
    
    mpz_powm(plaintext, ciphertext, d, n);
    
    char Decrp_Mes[100];
    int p1;
    int dm;
    p1=mpz_mod_ui(p,plaintext,1000);
    while(p1<0 || p1>0){
        mpz_mod_ui(p,plaintext,1000);
        dm = mpz_get_ui(p);
        Decrp_Mes[length1-1]=(char)dm;
        length1=length1-1;
        mpz_div_ui(plaintext,plaintext,1000);
        p1 = mpz_mod_ui(p,plaintext,1000);
    }
    
    
    gmp_printf("Public key: (e=%Zd, n=%Zd)\n", e, n);
    gmp_printf("Private key: (d=%Zd, n=%Zd)\n", d, n);
    gmp_printf("Original message: %s \n", str1);
    gmp_printf("Ciphertext: %Zd\n", ciphertext);
    gmp_printf("Decrypted message: %s \n", Decrp_Mes);
    
   
    return 0;
}
