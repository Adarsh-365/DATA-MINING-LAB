#include<stdio.h>
#include<gmp.h>
#include <time.h>

int miillerTest(mpz_t d, mpz_t n){
    gmp_randstate_t state;
    mpz_t random_num, upper_limit,n_4,n_1,x;
    mpz_inits(random_num,n_4,upper_limit,n_1,x,NULL);
    
    unsigned long seed;

    gmp_randinit_mt(state);
    seed = time(NULL); 
    gmp_randseed_ui(state, seed);

   
    mpz_init(random_num);
    mpz_sub_ui(n_4,n,4);
    mpz_add_ui(n_4,n_4,2);
    long long int n4;
    n4 = mpz_get_ui(n_4);
    mpz_init_set_ui(upper_limit,n4 ); 
    mpz_urandomm(random_num, state, upper_limit);
    mpz_add_ui(random_num, random_num, 1); // Ensures the range is 1 to 1000

    // Print the random number
   // gmp_printf("Random number: %Zd\n", random_num);
    
    mpz_powm(x,random_num,d,n);
   // gmp_printf("x =  %Zd\n", x);

    mpz_sub_ui(n_1,n,1);
    int flag;
    if(mpz_cmp_ui(x,1)==0 || mpz_cmp(x,n_1)==0){
        flag = 1;
        return flag;
    }
    

    while(mpz_cmp(d,n_1)!=0){
        
        mpz_mul(x,x,x);
        mpz_mod(x,x,n);
        mpz_mul_ui(d,d,2);
        if (mpz_cmp_ui(x,1)==0){
            return 0;
        }
        
        if (mpz_cmp(x,n_1)==0){
            return 1;
        }
        
        
        
        
    }
    
    
    return 0;
    
    
}


int isPrime(mpz_t n, mpz_t k){

    mpz_t d,mod2,i;
    mpz_inits(d,i,mod2,NULL);
    mpz_sub_ui(d,n,1);
    mpz_mod_ui(mod2,d,2);
    while(mpz_cmp_ui(mod2,0)==0){
        mpz_div_ui(d,d,2);
        mpz_mod_ui(mod2,d,2);
        
        
    }
   
   // gmp_printf("\n d =  %Zd",d);
    int test;
    
    for(mpz_set_ui(i,0);mpz_cmp(i,k)<0;mpz_add_ui(i,i,1))
    {
    
		test = miillerTest(d, n);
		//printf(" test = %d \n",test);
		if (test==0)
		    return 0;
    }
    
    
    return 1;
}



int main(){
    
    mpz_t n , k;
    mpz_inits(n,k,NULL);
    mpz_set_ui(k,10);
    mpz_set_ui(n,10001);
    printf("Enter the N  \n");
	gmp_scanf("%Zd",n);
	printf("\n");
	printf("Enter the k  \n");
	gmp_scanf("%Zd",k);
    
    int flag=0;
    gmp_printf("\n k =  %Zd",k);
    gmp_printf("\n n =  %Zd",n);
    clock_t start = clock();
    flag = isPrime(n, k);
    clock_t end = clock();
    //printf("%d",flag); 
    if (flag==1){
        gmp_printf("\n %Zd is prime number by miillerTest",n);
    }
    else{
         gmp_printf("\n %Zd is not prime number by miillerTest",n);
    }
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    // Print the result
    printf("\n Time taken by function: %f seconds\n", time_taken);
    
    
    
    return 0;
    
}