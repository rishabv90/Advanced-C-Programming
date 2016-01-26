#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(int argc , char * * argv)
{

  int i;

  if (argc == 1)
    {
      // printf("PLEASE ENTER SOMETHING\n");
      return EXIT_FAILURE;
    }
  
  else
    {
      for(i = 1; i < (argc); i++)
	{
	  printf("%s ", argv[i]);
	} 
    }
  
  printf("\n");
  
  return 0;
}
