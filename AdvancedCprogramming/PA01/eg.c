#include <stdio.h>
#include <stdlib.h>



int main()
{
int array[4] = {4,3,2,1};
int sum,i=0;

for(i=0; i<4; i++)
{
  sum = sum + array[i];
}

printf("the sum is : %d \n", sum); 



return 0;


}
