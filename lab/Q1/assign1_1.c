#include <stdio.h>
#include <gmp.h>

int main() {
    mpz_t p,q,n,phi,e,d,message,ciphertext,plaintext,one1,temp1,gcd_temp;
    
    mpz_inits(p,q,n,phi,e,d,message,ciphertext,plaintext,temp1,gcd_temp, NULL);
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
    
    gmp_printf("p = %Zd q = %Zd  are random prime number \n",p,q);
    gmp_printf("n= p*q = %Zd phi = (p-1)*(q-1) %Zd  \n",n,phi);
    
    mpz_sub(temp1,phi,one1);
    
    mpz_gcd(gcd_temp,e,phi);

    mpz_nextprime(e,p);
    int j;
    j = mpz_cmp(e,phi);
    printf("%d",j);
    while (j>=0)
    {   
        mpz_sub(e,e,one1);
        mpz_nextprime(e,p);
        j = mpz_cmp(e,phi);
        
    }
   

    
    mpz_invert(d, e, phi);
    mpz_set_ui(message, 2005);
    mpz_powm(ciphertext, message, e, n);
    
    
    mpz_powm(plaintext, ciphertext, d, n);
    
    
    gmp_printf("Public key: (e=%Zd, n=%Zd)\n", e, n);
    gmp_printf("Private key: (d=%Zd, n=%Zd)\n", d, n);
    gmp_printf("Original message: %Zd\n", message);
    gmp_printf("Ciphertext: %Zd\n", ciphertext);
    gmp_printf("Decrypted message: %Zd\n", plaintext);

    return 0;
}
