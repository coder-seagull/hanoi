/*
 Towers of Hanoi -- binary v.1
 -----------------------------
 An iterative solution to the Towers of Hanoi using binary encodings.
*/

#include <stdio.h>

void build  (int n);
void sides  (int step,
             int n,
             int bin);
void middle (int step,
             int n,
             int bin);
void swap   (char *a,
             char *b);
int  pow_2  (int exp);

int main (void)
{
   int units;

   printf("Enter a number of units to be moved: ");
   scanf("%d", &units);

   build(units);

   return 0;
}

void build (int n)
 {
   int step; /* step no. */
   int type = 0; /* type of move */
   int bin = 0; /* code for location in construction tree */

   for (step = 0; step < pow_2(n) - 1; step++)
      {
       type = type % 4;

       switch(type)
          {
           case 0: sides(step, n, bin);
                   bin++;
                   break;
           case 1: middle(step, n, bin);
                   break;
           case 2: sides(step, n, bin);
                   bin++;
                   break;
           case 3: middle(step, n, bin);
                   break;
          }

       type++;
      }

   return;
}

void sides (int step,
            int n,
            int bin)
{
   int store = bin;
   int r = 0; /* remainder */
   int k = 0; /* first non-zero digit from right to left */
   int d; /* digit */
   int i; /* index variable */

   /* Determine position of first non-zero digit from right to left */
   while (r == 0 && k < n - 1)
      {
       r = bin % 2;
       
       if (r == 0)
          {
           k++;
           bin = bin / 2;
          }
      }

   bin = store;

   char src = 'A';
   char aux = 'B';
   char des = 'C';

   /* Determine the bottom src-aux-des, configuration */
   for (i = n - 2; i >= 0; i--)
      {
       d = bin / pow_2(i);

       if (d == 0)
          swap (&aux, &des);
       else
          {
           bin = bin - pow_2(i);
           swap (&aux, &src);
          }
      }

   for ( ; k >= 0; k--)
       {
        if (k % 2 == 0)
           printf("Towers (%d, %c, %c, %c)\n", k + 1, src, des, aux);
        else
           printf("Towers (%d, %c, %c, %c)\n", k + 1, src, aux, des);
       }
 
   printf("\t\t\t Step %d: Move from %c to %c\n", step + 1, src, des);

   return;
}

void middle (int step,
             int n,
             int bin)
{
   int store = bin;
   int r = 0; /* remainder */
   int k = 1; /* first non-zero digit from right to left */
   int d; /* digit */
   int i; /* index variable */

   while (r == 0 && k < n)
      {
       r = bin % 2;
       bin = bin / 2;
       
       if (r == 0)
          k++;
      }

   bin = store;

   char src = 'A';
   char aux = 'B';
   char des = 'C';

   /* Determines the bottom configuration of next move */
   for (i = n - 2; i >= 0; i--)
      {
       d = bin / pow_2(i);

       if (d == 0)
          swap (&aux, &des);
       else
          {
           bin = bin - d * pow_2(i);
           swap (&aux, &src);
          }
      }

   if (k % 2 == 0)
      printf("\t\t\t Step %d: Move from %c to %c\n", step + 1, aux, des);
   else
      printf("\t\t\t Step %d: Move from %c to %c\n", step + 1, des, aux);

   return;
}

void swap (char *a,
           char *b)
{
   char save;

   save = *a;
   *a = *b;
   *b = save;

   return;
}

int pow_2 (int exp)
{
   int power;
   int i;

   if (exp == 0)
      power = 1;
   else
      power = pow_2(exp - 1) * 2;

   return power;
}