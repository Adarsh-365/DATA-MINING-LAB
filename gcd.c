#include<stdio.h>
#include<gmp.h>
#include<stdlib.h>

struct term
{
mpz_t coefficient;
mpz_t degree;
struct term * next;
};

void inverse(mpz_t result, mpz_t a, mpz_t b)
{
  mpz_t r[3], x[3], y[3], q, t, t2;
  mpz_inits(q, t, t2, NULL);
  for(int i=0;i<3;i++)
  {
    mpz_inits(r[i], x[i], y[i], NULL);
  }
  mpz_set_ui(x[0], 1);
  mpz_set_ui(y[0], 0);
  mpz_set_ui(x[1], 0);
  mpz_set_ui(y[1], 1);
  mpz_set(r[0], a);
  mpz_set(r[1], b);
  mpz_set_ui(r[2], 1);
  while(mpz_cmp_ui(r[2], 0)!=0)
  {
    mpz_fdiv_q(q, r[0], r[1]);
    mpz_mul(t, q, x[1]);
    mpz_sub(x[2], x[0], t);
    mpz_mul(t, q, y[1]);
    mpz_sub(y[2], y[0], t);
    mpz_mul(t, a, x[2]);
    mpz_mul(t2, b, y[2]);
    mpz_add(r[2], t, t2);

    mpz_set(r[0], r[1]);
    mpz_set(r[1], r[2]);
    mpz_set(x[0], x[1]);
    mpz_set(x[1], x[2]);
    mpz_set(y[0], y[1]);
    mpz_set(y[1], y[2]);
  }
  if(mpz_cmp_ui(r[0], 1) == 0)
  {
    mpz_mod(x[0], x[0], b);
    mpz_set(result, x[0]);
  }
  else
  {
    mpz_set(result, NULL);
  }
}

struct term * sub(struct term * head1, struct term * head2, mpz_t n)
{
  struct term * result_head=NULL, * result_last, *newnode;
  while(head1 != NULL && head2 != NULL)
  {
    if(mpz_cmp(head1->degree, head2->degree)<0)
    {
      newnode = (struct term *) malloc(sizeof(struct term));
      mpz_inits(newnode -> coefficient, newnode -> degree, NULL);
      newnode -> next = NULL;
      mpz_t t;
      mpz_inits(t, NULL);
      mpz_mul_si(t, head2->coefficient, -1);
      mpz_mod(t, t, n);
      mpz_set(newnode -> coefficient, t);
      mpz_set(newnode -> degree, head2 -> degree);
      if(result_head == NULL)
      {
        result_head = newnode;
        result_last = newnode;
      }
      else
      {
        result_last -> next = newnode;
        result_last = newnode;
      }
      head2 = head2 -> next;
    }
    else if(mpz_cmp(head1->degree, head2->degree)>0)
    {
      newnode = (struct term *) malloc(sizeof(struct term));
      mpz_inits(newnode -> coefficient, newnode -> degree, NULL);
      newnode -> next = NULL;
      mpz_set(newnode -> coefficient, head1 -> coefficient);
      mpz_set(newnode -> degree, head1 -> degree);
      if(result_head == NULL)
      {
        result_head = newnode;
        result_last = newnode;
      }
      else
      {
        result_last -> next = newnode;
        result_last = newnode;
      }
      head1 = head1 -> next;
    }
    else
    {
      newnode = (struct term *) malloc(sizeof(struct term));
      mpz_inits(newnode -> coefficient, newnode -> degree, NULL);
      newnode -> next = NULL;
      mpz_t t;
      mpz_inits(t, NULL);
      mpz_sub(t, head1->coefficient, head2->coefficient);
      mpz_mod(t, t, n);
      mpz_set(newnode -> coefficient, t);
      mpz_set(newnode -> degree,head1 -> degree);
      if(result_head == NULL)
      {
        result_head = newnode;
        result_last = newnode;
      }
      else
      {
        result_last -> next = newnode;
        result_last = newnode;
      }
      head1 = head1 -> next;
      head2= head2 -> next;
    }
  }

  while(head1!=NULL)
  {
    newnode = (struct term *) malloc(sizeof(struct term));
    mpz_inits(newnode -> coefficient, newnode -> degree, NULL);
    newnode -> next = NULL;
    mpz_set(newnode -> coefficient, head1 -> coefficient);
    mpz_set(newnode -> degree, head1 -> degree);
    if(result_head == NULL)
    {
      result_head = newnode;
      result_last = newnode;
    }
    else
    {
      result_last -> next = newnode;
      result_last = newnode;
    }
    head1 = head1 -> next;
  }

  while(head2!=NULL)
  {
    newnode = (struct term *) malloc(sizeof(struct term));
    mpz_inits(newnode -> coefficient, newnode -> degree, NULL);
    newnode -> next = NULL;
    mpz_t t;
    mpz_inits(t, NULL);
    mpz_mul_si(t, head2->coefficient, -1);
    mpz_mod(t, t, n);
    mpz_set(newnode -> coefficient, t);
    mpz_set(newnode -> degree, head2 -> degree);
    if(result_head == NULL)
    {
      result_head = newnode;
      result_last = newnode;
    }
    else
    {
      result_last -> next = newnode;
      result_last = newnode;
    }
    head2 = head2 -> next;
  }
  return result_head;
}

struct term * add(struct term * head1, struct term * head2, mpz_t n)
{
  struct term * result_head=NULL, * result_last, *newnode;
  while(head1 != NULL && head2 != NULL)
  {
    if(mpz_cmp(head1->degree, head2->degree)<0)
    {
      newnode = (struct term *) malloc(sizeof(struct term));
      mpz_inits(newnode -> coefficient, newnode -> degree, NULL);
      newnode -> next = NULL;
      mpz_set(newnode -> coefficient, head2 -> coefficient);
      mpz_set(newnode -> degree, head2 -> degree);
      if(result_head == NULL)
      {
        result_head = newnode;
        result_last = newnode;
      }
      else
      {
        result_last -> next = newnode;
        result_last = newnode;
      }
      head2 = head2 -> next;
    }
    else if(mpz_cmp(head1->degree, head2->degree)>0)
    {
      newnode = (struct term *) malloc(sizeof(struct term));
      mpz_inits(newnode -> coefficient, newnode -> degree, NULL);
      newnode -> next = NULL;
      mpz_set(newnode -> coefficient, head1 -> coefficient);
      mpz_set(newnode -> degree, head1 -> degree);
      if(result_head == NULL)
      {
        result_head = newnode;
        result_last = newnode;
      }
      else
      {
        result_last -> next = newnode;
        result_last = newnode;
      }
      head1 = head1 -> next;
    }
    else
    {
      newnode = (struct term *) malloc(sizeof(struct term));
      mpz_inits(newnode -> coefficient, newnode -> degree, NULL);
      newnode -> next = NULL;
      mpz_t t;
      mpz_inits(t, NULL);
      mpz_add(t, head1->coefficient, head2->coefficient);
      mpz_mod(t, t, n);
      mpz_set(newnode -> coefficient, t);
      mpz_set(newnode -> degree,head1 -> degree);
      if(result_head == NULL)
      {
        result_head = newnode;
        result_last = newnode;
      }
      else
      {
        result_last -> next = newnode;
        result_last = newnode;
      }
      head1 = head1 -> next;
      head2= head2 -> next;
    }
  }


  while(head1!=NULL)
  {
    newnode = (struct term *) malloc(sizeof(struct term));
    mpz_inits(newnode -> coefficient, newnode -> degree, NULL);
    newnode -> next = NULL;
    mpz_set(newnode -> coefficient, head1 -> coefficient);
    mpz_set(newnode -> degree, head1 -> degree);
    if(result_head == NULL)
    {
      result_head = newnode;
      result_last = newnode;
    }
    else
    {
      result_last -> next = newnode;
      result_last = newnode;
    }
    head1 = head1 -> next;
  }

  while(head2!=NULL)
  {
    newnode = (struct term *) malloc(sizeof(struct term));
    mpz_inits(newnode -> coefficient, newnode -> degree, NULL);
    newnode -> next = NULL;
    mpz_set(newnode -> coefficient, head2 -> coefficient);
    mpz_set(newnode -> degree, head2 -> degree);
    if(result_head == NULL)
    {
      result_head = newnode;
      result_last = newnode;
    }
    else
    {
      result_last -> next = newnode;
      result_last = newnode;
    }
    head2 = head2 -> next;
  }
  return result_head;
}

void display(struct term * head)
{
  if(head == NULL)
  {
    printf("<< Empty >>");
    return;
  }
  struct term * tmp = head;
  int flag = 1;
  while(tmp!=NULL)
  {
    if(mpz_cmp_ui(tmp -> coefficient, 0) == 0)
    {
      tmp = tmp -> next;
      continue;
    }
    if(mpz_cmp_ui(tmp->degree, 0)!=0 && mpz_cmp_ui(tmp->degree, 1)!=0)
    {
      if(!flag)
      {
        printf (" + ");
      }
      else
      {
        flag = 0;
      }
      gmp_printf("%Zd x ^ %Zd", tmp->coefficient, tmp->degree);
    }
    else if(mpz_cmp_ui(tmp->degree, 1)==0)
    {
      if(!flag)
      {
        printf (" + ");
      }
      else
      {
        flag = 0;
      }
      gmp_printf("%Zd x", tmp->coefficient);
    }
    else
    {
      if(!flag)
      {
        printf (" + ");
      }
      else
      {
        flag = 0;
      }
      gmp_printf("%Zd", tmp->coefficient);
    }
    tmp = tmp -> next;
  }
  printf("\n");
}

struct term * mul(struct term * head1, struct term * head2, mpz_t n)
{
  struct term * result_head = NULL, *newnode;

  while(head1 != NULL)
  {
    struct term * temp_head=NULL, *temp_last = NULL, * temp2 = head2 ;
    while(temp2 != NULL)
    {
      newnode = (struct term*)malloc(sizeof(struct term));
      newnode -> next = NULL;
      mpz_t t;
      mpz_inits(t, NULL);
      mpz_mul(t, head1 -> coefficient, temp2 -> coefficient);
      mpz_mod(t, t, n);
      mpz_set(newnode -> coefficient, t);
      mpz_add(t, head1 -> degree, temp2 -> degree);
      mpz_set(newnode -> degree, t);
      if(temp_head == NULL)
      {
        temp_head = newnode;
        temp_last = newnode;
      }
      else
      {
        temp_last -> next = newnode;
        temp_last = newnode;
      }
      temp2 = temp2 -> next;
    }
    if(result_head == NULL)
    {
      result_head = temp_head;
    }
    else
    {
      result_head = add(result_head, temp_head, n);
    }
    head1 = head1 -> next;
  }
  return result_head;
}

void division(struct term * quotient, struct term * remainder, struct term * head1, struct term * head2, mpz_t n)
{

  struct term * headq=NULL, *tailq, *newterm;

  while(mpz_cmp_ui(head1 -> coefficient, 0) == 0)
  {
  head1 = head1 -> next;
  if(head1 == NULL)
  {
    quotient -> next = NULL;
    remainder -> next = NULL;
    return;
  }
  }

  if(mpz_cmp(head2 -> degree, head1 -> degree) > 0)
  {
    remainder -> next = head1;
    quotient -> next = NULL;
    return;
  }

  else
  {
    while(head1!=NULL)
    {


    if(mpz_cmp(head2 -> degree, head1 -> degree) > 0)
    {
      remainder -> next = head1;
      quotient -> next = headq;
      return;
    }

    newterm = (struct term *)malloc(sizeof(struct term));
    mpz_inits(newterm -> coefficient, newterm -> degree, NULL);
    mpz_t temp;
    mpz_inits(temp, NULL);
    inverse(temp, head2->coefficient, n);
    mpz_mul(temp, temp, head1 -> coefficient);
    mpz_mod(temp, temp, n);
    newterm -> next = NULL;
    mpz_set(newterm -> coefficient, temp);
    mpz_sub(temp, head1->degree, head2 -> degree);
    mpz_set(newterm -> degree, temp);

    //gmp_printf("\n%Zd - %Zd\n", newterm->coefficient, newterm->degree);
    if(headq == NULL)
    {
      headq = newterm;
      tailq = newterm;
    }
    else
    {
      tailq -> next = newterm;
      tailq = newterm;
    }

    struct term *tmp;
    tmp = mul(head2, newterm, n);
    head1 = sub(head1, tmp, n);

    while(mpz_cmp_ui(head1 -> coefficient, 0) == 0)
    {
    head1 = head1 -> next;

    if(head1 == NULL)
    {
      quotient -> next = headq;
      remainder -> next = NULL;
      return;
    }
    }
    }
    quotient -> next = headq;
    remainder -> next = NULL;
  }
}

struct term * gcd(struct term *a, struct term * b, mpz_t n)
{
  if(b == NULL)
  {
    return a;
  }
  else
  {
    struct term *quotient=NULL, *remainder=NULL;
    quotient = (struct term *)malloc(sizeof(struct term));
    remainder = (struct term*)malloc(sizeof(struct term));
    division(quotient, remainder, a, b, n);
    return gcd(b, remainder->next, n);
  }
}


int main()
{

  mpz_t n,coef,t, deg;
  mpz_inits(n, coef,t, deg, NULL);

  printf("Enter the value of n : ");
  gmp_scanf("%Zd", n);
  mpz_sub_ui(t, n, 1);
  printf("Enter the coefficient and degree in desc order of degrees of Polynomial 1 : \nNote: Enter 0 as coefficient to stop reading\n\n");
  struct term * head1=NULL, * last1 = NULL, * newterm;
  while(1)
  {
    gmp_scanf("%Zd %Zd", coef, deg);
    if(mpz_cmp(coef, t) > 0)
    {
      printf("Incorrect coefficient entered .... ");
      return 1;
    }
    if(mpz_cmp_ui(coef, 0)==0)
    {
      break;
    }
    if(head1==NULL)
    {
      head1 = (struct term *)malloc(sizeof(struct term));
      head1 -> next = NULL;
      mpz_inits(head1 -> coefficient, head1 -> degree, NULL);
      mpz_set(head1 -> coefficient, coef);
      mpz_set(head1 -> degree, deg);
      last1 = head1;
    }
    else
    {
      newterm = (struct term *)malloc(sizeof(struct term));
      newterm->next = NULL;
      mpz_inits(newterm -> coefficient, newterm -> degree, NULL);
      mpz_set(newterm -> coefficient, coef);
      mpz_set(newterm -> degree, deg);
      last1 -> next = newterm;
      last1 = newterm;
    }
  }

  //Display polynomial
  display(head1);

  printf("Enter the coefficient and degree in desc order of degrees of Polynomial 2 : \nNote: Enter 0 as coefficient to stop reading\n\n");

  struct term * head2=NULL, * last2 = NULL;
  while(1)
  {
    gmp_scanf("%Zd %Zd", coef, deg);
    if(mpz_cmp(coef, t) > 0)
    {
      printf("Incorrect coefficient entered .... ");
      return 1;
    }
    if(mpz_cmp_ui(coef, 0)==0)
    {
      break;
    }
    if(head2==NULL)
    {
      head2 = (struct term *)malloc(sizeof(struct term));
      head2 -> next = NULL;
      mpz_inits(head2 -> coefficient, head2 -> degree, NULL);
      mpz_set(head2 -> coefficient, coef);
      mpz_set(head2 -> degree, deg);
      last2 = head2;
    }
    else
    {
      newterm = (struct term *)malloc(sizeof(struct term));
      newterm->next = NULL;
      mpz_inits(newterm -> coefficient, newterm -> degree, NULL);
      mpz_set(newterm -> coefficient, coef);
      mpz_set(newterm -> degree, deg);
      last2 -> next = newterm;
      last2 = newterm;
    }
  }

  //Display polynomial
  display(head2);
  printf("\n\nGCD : ");
  display(gcd(head1, head2, n));


  return 0;
}
