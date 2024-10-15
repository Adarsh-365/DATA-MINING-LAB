
#include<stdio.h>
#include<gmp.h>


int main() {


	mpz_t N;
	mpz_t temp1;

	mpz_t zero;
	mpz_t op;
	mpz_t one;
	mpz_t a;
	
	mpz_set_ui(N,0);

	mpz_set_ui(a,0);
	mpz_set_ui(temp1,0);
	mpz_set_ui(zero,0);
	mpz_set_ui(op,0);
	mpz_set_ui(one,1);
	
	printf("Enter the first number \n");
	gmp_scanf("%Zd",N);


    int is_prime = 1;
    int j;
    int i;
    j = mpz_cmp(a,N);
    long long int xyz = mpz_get_ui(N);
    mpz_add(a,a,one);
   while(j<0 || j>0)
   {
        
       
        mpz_pow_ui(temp1,a,xyz);
        mpz_sub(op,temp1,a);
        mpz_mod(op,op,N);
       
      
        mpz_add(a,a,one);
        j = mpz_cmp(a,N); 
       
        i = mpz_cmp(op,zero); 
        if (i>0 || i <0){
            
               is_prime = 0;
               break;
        }
   }
               
    if (is_prime) 
    {
        gmp_printf("%Zd is Prime by Fermat's Test ",N);
    } else 
    {
        gmp_printf("%Zd is not Prime by Fermat's Test ",N);
    }
    
    
  
        
        
  



	return 0;
}