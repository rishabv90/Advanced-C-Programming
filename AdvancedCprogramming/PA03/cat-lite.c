#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 512

void display();

void display()
{
//LOCAL DECLARATIONS
char buffer[SIZE];

do
{
        size_t bytes = fread(buffer, sizeof(char), SIZE, stdin);
        fwrite(buffer, sizeof(char), bytes, stdout);
        fflush(stdout);
        if (bytes < SIZE)
                if (feof(stdin))
                        break;
}while(1);

}

int main(int argc , char * * argv)
{

  int i;
  //part 1 
  for (i = 0; i < argc; i++)
    {
      //printf("here %d\n", i);

      if(strcmp(argv[i], "--help") == 0)

	{
	  // printf("help message here \n");
	  printf("\n\nUsage: cat-lite [--help] [FILE]...\nWith no FILE, or when FILE is -, read standard input.\n\nExamples:\n  cat-lite README   Print the file README to standard output.\n  cat-lite f - g    Print f's contents, then standard input,\n                    then g's contents.\n  cat-lite          Copy standard input to standard output.\n\n");
	  return EXIT_SUCCESS;
	}
    }

  //part 2
  
  FILE * fp;  
  int j = 0;
  int ch = 0;
  
  if(argc == 1)
    {
      display();
      return EXIT_SUCCESS;
    }
   
  for(j = 1; j < argc; j++)
  {    
    fp = fopen(argv[j], "r"); 
    
    if(fp != NULL)
      {
	while((ch = getc(fp)) != EOF)
	  {
	    putc(ch, stdout);	   
	  }

	fclose(fp);
      }
    else if(strcmp(argv[j], "-") == 0)
      {
	display();
	return EXIT_SUCCESS;
      }
    
    else
      {
	fprintf(stderr, "cat cannot open %s\n", argv[j]);
	break;
	return EXIT_FAILURE;
      }
    
   }

 
  
  return EXIT_SUCCESS ;
}

