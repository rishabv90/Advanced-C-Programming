#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "answer02.h"

char * strcat_ex(char * * dest, int * n, const char * src)//giving error somewhere here
{
  //CHeck if big enough, if not allocate a new larger one and copy old string to the new buffer, then free old buffer.
   
  if (*dest == NULL)//no guarentee of value of N//CASE 1
    {
      //printf("helloo1\n");
       char * buffer =  malloc((sizeof(char)) * (1 + 2 * strlen(src)));
       //dest  == 0


       *n =(1 + 2 * strlen(src));
       //folowing the gien stuff in the .h file.


       *dest = buffer;
       //NO NEED TO free
       strcat(*dest, " ");//accounting for the space we get.


       strcat(*dest, src);
      return (*dest);
    }

  else if(*n < (strlen(*dest) + strlen(src)))//CASE 2 we know that the valuse of n is smaller and dest is not null
    {
      //printf("helloo2\n");
	  
       char * buffer = malloc((sizeof(char))* (1 + 2 * (strlen(*dest) + strlen(src))));

       *n = 1 + 2 * (strlen(*dest) + strlen(src));

       //using because of const char
       strcpy(buffer, *dest);
       //printf("buffer is %s", buffer);
       free(*dest);

       *dest = buffer; // to the beginging of the file      

       strcat(*dest, " ");
       strcat(*dest, src);

       return (*dest);
    }
  else //CAse 3 No malloc required
	  {
	    // printf("helloo3\n");
	    strcat(*dest, " ");
	    strcat(*dest, src);
	    //printf("here");
	    return(*dest);
	  }
	return (* dest);
}


char * * explode(const char * str, const char * delims, int * arrLen)
{
  int i = 0;
  int j = 0;
  //int length = 0;
  
   // printf("the String is : %s\n", str);
   //length = strlen(str);
  
  while(str[i] != '\0')//toget strlen and null check
     {
       if(strchr(delims, str[i]) != NULL)//checking for null
	 {
	   j++;
	 }
       i++;
   }
   
   



  *arrLen = j+1;//gives us the number of strings
   char * *strArr = (char * *)malloc((*arrLen) * sizeof(char*));

   int counter = 0;
   int end = 0;
   int k = 0;

   int strArr_k = 0;
   
   while(k <= strlen(str))
     {
       if((strchr(delims,str[k]) != NULL) || (str[k] == '\0'))
	 {
	   strArr[strArr_k] = (char*)malloc((counter + 1) * sizeof(char));
	   //???????
	   memcpy(strArr[strArr_k], &str[end], k - (end -1));
	   //printf("HERERERE");	   
	   strArr[strArr_k][k - end] = '\0';
	  


	   end = k + 1;

	   
	   
	   counter = 0;
	   //pritnf("here111");
	   strArr_k++;
	   // printf("the value of strArr_ k is %d", strArr_k);
	 }
       else
	 {
	   counter++;
	 }
       k++;
     }

   
   
   
   //const char ch;

   // printf("the delims are : %s\n", delims);
   
     // printf("the string is :%d\n", i);
  
  

   return (strArr);
}


char * implode(char * * strArr, int len, const char * glue)
{
  int i = 0;
  int sum = 0;
   int j = 1;
  
  for(i = 0; i < len ; i++)
    {
      //printf("here")
      sum = sum + strlen(strArr[i]);
   
    }
  sum = sum + (((len -1) * strlen(glue)) + 1);


  char * i_string = malloc(sizeof(char) * sum); // creating string for implode
  
  strcpy(i_string, strArr[0]);
  //printf("the string is %s", i_string);
  
  while(j < len)
    {
      strcat(i_string, glue);
    
      strcat(i_string, strArr[j]);
      j++;
    }
  
  return(i_string);
  

}

int cmpfunc1(const void * one, const void * two)
{
  char const * *one_1 = (char const * *)one;

  char const * *two_2 = (char const * *)two;



  return strcmp(*one_1, *two_2);
}

void sortStringArray(char * * arrString, int len)
{
  // printf("here\n");
  // printf("the string is : %s", arrString);
  qsort(arrString, len, sizeof(char*), cmpfunc1);

  
}

int cmpfunc2(void* a, void* b)
{
  return(strcmp((char const *)a, (char const *)b));
}

void sortStringCharacters(char * str)
{
  //printf("%s\n", str);
  //printf("blah\n");
  //int length = strlen(str);

  //SEG FUALT HERE?????
  
  qsort((void *)str, strlen(str), sizeof(char), cmpfunc2);
  
}


void destroyStringArray(char * * strArr, int len)
{

  //JUST have to free all the memory using 1 for loop for each location in the string and the string itself
  int i;
  
  for (i=0; i < len ; i++)
    {
      free(strArr[i]);
    }
  free(strArr);
  
}


