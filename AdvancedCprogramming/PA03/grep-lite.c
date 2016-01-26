#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define BUFFERSIZE 2000
#define TRUE 1
#define FALSE 0

int main(int argc , char * argv[])
{
  //PART1
  int i;
  int a;
  char buffer[BUFFERSIZE];


  for (i = 0; i < argc; i++)//for help message
    {
      if(strcmp(argv[i], "--help") == 0)
	{
	  printf("\n\nUsage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input. PATTERN is a\nstring. grep-lite will search standard input line by line, and (by default) print out those lines which\ncontain pattern as a substring.\n\n  -v, --invert-match     print non-matching linesn\n -n, --line-number      print line numbers with output\n  -q, --quiet            suppress all output\n\nExit status is 0 if any line is selected, 1 otherwise;\nif any error occurs, then the exit status is 2.\n\n");
	  return EXIT_SUCCESS;
	}      
    }
  
  if (argv[i-1][0] == '-')//PART 3
    {
      fprintf(stderr,"Last arguement  ie. the pattern cannot start with '-'\n");
	  return 2;
    }
  
  if(argc < 3)//simple strstr
    {
      while (fgets(buffer, BUFFERSIZE, stdin) != (NULL))
	{
	  if(strstr(buffer, argv[i-1]) !=  NULL)
	    {
	      printf("%s", buffer);
	      break;
	    }     
	} 
      return EXIT_SUCCESS;
    }  	
 
  for (a = 0; a < argc; ++a)
    {
      if((strcmp(argv[a+1], "-q") == 0) || (strcmp(argv[a+1], "--quiet") == 0) || (strcmp(argv[a+2], "-q") == 0) || (strcmp(argv[a+2], "--quiet") == 0) )
      {
	return EXIT_SUCCESS;
      }

      else if(((strcmp(argv[a+1], "-v") == 0) && (strcmp(argv[a+2], "-v") == 0)) || ((strcmp(argv[a+1], "--invert-match") == 0) && (strcmp(argv[a+2], "--invert-match") == 0)))//for single usage
	  {	  
	    while (fgets(buffer, BUFFERSIZE, stdin) != (NULL))
	      {
		
		if(strstr(buffer, argv[i-1]) !=  NULL)
		  { continue;}		
		else
		  { printf("%s", buffer);}      
	      }   
	    break;
	    return EXIT_SUCCESS;
	  }
      
      else if ((((strcmp(argv[a+1], "-v") == 0) || (strcmp(argv[a+1], "--invert-match") == 0)) && ((strcmp(argv[a+2], "-n") == 0) || (strcmp(argv[a+2], "--line-number") == 0))) || (((strcmp(argv[a+2], "-v") == 0) || (strcmp(argv[a+2], "--invert-match") == 0)) && ((strcmp(argv[a+1], "-n") == 0) || (strcmp(argv[a+1], "--line-number")))))
	{
	  int linenum1 = 1;
	   while (fgets(buffer, BUFFERSIZE, stdin) != (NULL))
	      {
		
		if(strstr(buffer, argv[i-1]) !=  NULL)
		  {
		    linenum1 = linenum1 +1;
		    continue;
		  }		
		else
		  { printf("%d:%s", linenum1, buffer);}      
		linenum1++;
	      }   
	   
	    break;
	  
	  return EXIT_SUCCESS;
	}      
      
     
      
      
      else{
	if((strcmp(argv[a+1], "-v") == 0) || (strcmp(argv[a+1], "--invert-match") == 0))//for single usage
	  {	  
	    while (fgets(buffer, BUFFERSIZE, stdin) != (NULL))
	      {
		
		if(strstr(buffer, argv[i-1]) !=  NULL)
		  { continue;}		
		else
		  { printf("%s", buffer);}      
	      }   
	    break;
	    return EXIT_SUCCESS;
	  }
	
	else if((strcmp(argv[a+1], "-n") == 0) || (strcmp(argv[a+1], "--line-number") == 0) || (strcmp(argv[a+2], "-n") == 0))
	  {
	    int linenum = 1;
	  
	    while (fgets(buffer, BUFFERSIZE, stdin) != (NULL))
	      {
		if(strstr(buffer, argv[i-1]) !=  NULL)
		  {
		    
		    printf("%d:%s\n", linenum, buffer);
		    break;
		  }
		linenum++;		
	      }
	    return EXIT_SUCCESS;
	  }	
      }
    }//for loop ends
  
  
   return 0 ;
}

