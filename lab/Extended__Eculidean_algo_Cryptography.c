// def ExtendedEuclideanIterative(a, b):

//     x0 = 1
//     x1 = 0
//     y0 = 0
//     y1 = 1
//     while b != 0:
//         quotient = a // b

//         r =  a % b
//         a=b
//         b=r
//         x2 =  x0 - quotient * x1
//         y2 =  y0 - quotient * y1
//         x0 = x1
//         y0 = y1
//         x1 = x2
//         y1 = y2


//     print(x0,y0)
//     return (a, x0, y0)
// ExtendedEuclideanIterative(6,14)


#include<stdio.h>
#include<gmp.h>


int main() {


	mpz_t x0;
	mpz_t x1;
	mpz_t y0;
	mpz_t y1;
	mpz_t x2;
	mpz_t y2;
	mpz_t a;
	mpz_t b;
	mpz_t zero;

	mpz_t qnt;
	mpz_t rem;

	mpz_t temp1;
	mpz_t temp2;
	mpz_init(temp1);
	mpz_init(temp2);

	mpz_set_ui(x0,1);
	mpz_set_ui(y0,0);
	mpz_set_ui(x1,0);
	mpz_set_ui(y1,1);
	mpz_set_ui(x2,0);
	mpz_set_ui(y2,0);
	mpz_set_ui(zero,0);
	mpz_set_ui(qnt,0);
	mpz_set_ui(rem,0);

	printf("Enter the first number \n");
	gmp_scanf("%Zd",a);
	printf("Enter the first number \n");
	gmp_scanf("%Zd",b);


	int j;
	j = mpz_cmp(b,zero);

	while(j>0 || j<0) {

		mpz_div(qnt,a,b);
        
        
		mpz_mod(rem,a,b);
	
	
	
		mpz_set(a,b);
		mpz_set(b,rem);
		
		mpz_mul(temp1,qnt,x1);
		mpz_sub(x2,x0,temp1);

		mpz_mul(temp1,qnt,y1);
		mpz_sub(y2,y0,temp2);
	
		
		mpz_set(x0,x1);
		mpz_set(y0,y1);
		mpz_set(x1,x2);
		mpz_set(y1,y2);
		j = mpz_cmp(b,zero);
		
	
	}		
	printf("\n");
	printf("the value of x and y are = ");
    gmp_printf("%Zd %Zd",x0,y0);









	return 0;
}

