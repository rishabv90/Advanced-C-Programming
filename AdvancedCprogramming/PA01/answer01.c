
#include "answer01.h"

// NOTE: You are NOT to use the strings library on this assignment,
// as stated in the README.

// DO NOT BEGIN WORKING ON THIS FILE UNTIL YOU HAVE COMPLETELY AND
// THOROUGHLY READ THE README FILE!!!

int arraySum(int * array, int len)
{
  
  int sum=0;
  int i=0;
  
  for(i=0; i < len ; i++)
    {
      sum = sum + array[i];
    }
   
    return sum;
}

int arrayCountNegative(int * array, int len)
{
  int negative = 0;
  int j;
  
  for(j=0; j < len; j++)
    {
      if(array[j] < 0)
	{
	  negative++;
	}
    }
      
    return negative;
}

int arrayIsIncreasing(int * array, int len)
{   
  int inc = 0;
  int i = 0;


  if ((len == 0)||(len == 1))
    {
      return 1;
    }
  else
    {
      for(i=0; i < (len-1); i++)
	{
	  if((array[i] < array[i+1]) || (array[i] == array[i+1]))
	    {
	      inc = 1;
	      printf("\n1\n");
	    }
	  
	  else 
	    {
	      printf("2\n");
	      inc = 0;
	       break;
	    }
	}         

  return inc;
    }
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
  int i;
  int index;
  

  for(i=0; i < len; i++)
    {
      if(haystack[i] == needle)
	{
	  index = i;
	}
      else if(haystack[i] != needle)
	{
	  return -1;
	  break;
	}
    }
  return index;
    
}

int arrayFindSmallest(int * array, int len)
{
  int smallest = 0;
  int i;
  

  if ( len == 0)
    {
      smallest = 0;
      return smallest;
    }
  else
    {
  
      for(i = 1; i < len; i++)
	{
	  if(array[i] < array[smallest])
	    {
	      smallest = i;
	    }
	}     
      return smallest;
    }
}

size_t my_strlen(const char * str)
{
  int length = 0;
 
  while (str[length] != '\0')
    {
      length++;
    }
  
   
    return length;
}

char * my_strchr(const char * str, int ch)
{
  int i =0;
  int count=0;
  
  int length = my_strlen(str);

  if (ch == '\0')
    {
      return (char *)(str + length);  
    }
  
  for(i=0; i < length; i++)
    {

      if ((length == 0) || (str[i] != ch))
	{
	  return NULL;
	}  
  
      
      else if(str[i] == ch)
	{
      	  count = i;
	  break;
     	}
         
    }
 
  //printf("\nthe position is %d\n", count);

  return (char*) str + count;
}

char * my_strstr(const char * haystack, const char * needle)
{
  int i;
  int j;
  int flag = 0;
  
  if((haystack == NULL) || (needle == NULL))
    {
      //printf("nigga\n");
      return NULL;
    }
   
  if (needle[0] == '\0')//error here
    {
      // printf("nigga2\n");
      return (char*)haystack;
    }
  
  for (i=0; haystack[i] != '\0'; i++)
    {
      if (haystack[i] == needle[0])
	{
	  for(j=i; ; j++)
	    {
	      if(needle[j-i] == '\0')
		{
		  flag = 1;
		  break;
		}
	      if(haystack[j] == needle[j-i])
		{
		  continue;
		}
	      else
		{
		  break;
		}
	    }
	}
      if (flag == 1)
	{
	  break;
	}    
    }

  if (flag)
    {
      return (char *)(haystack + i);
    }
  else
    {
    return NULL;
    }
}

char * my_strcpy(char * dest, const char * src)
{
  int i;
  
  for (i=0; src[i] != '\0'; ++i)
    {
      dest[i] = src[i]; 
    }

  dest[i] = '\0';
  
  return (char *)dest;
}

char * my_strcat(char * dest, const char * src)
{
  int i,j = 0;
  int position = 0;
 
  
  
  for(i=0; dest[i] != '\0'; ++i)
    {
      position++;
      continue;
    }

   for(j=0; src[j] != '\0'; ++j)
    {
      dest[position] = src[j];
      position++;
    }
   dest[position] = '\0';
  
  return (char *)dest;
}

int my_isspace(int ch)
{
  int zero = 0;
  int one = 0;

 
  
  if((ch == ' ') || (ch == '\f') || (ch == '\n') || (ch == '\n') || (ch == '\r') || (ch == '\t') || (ch == '\t') || (ch == '\v'))  
		  {
		    one = 1;
		    return one;
		  }   
  else
    {
       for(ch = 'A'; ch <= 'Z'; ++ch)
	 {
	   zero = 0;
     	 }
     return zero; 
    }
}

int my_atoi(const char * str)
{
  int i,len,first,next,a = 0;
  
  len = my_strlen(str);
  
  while (my_isspace(str[a]))
    { 
      a++;
    }

  for (i=a; i < len; i++)
    {
      if (str[i] == '-' )
	{
	  first = -1;
	}
      if(str[i] >= '0' && str[i] <= '9')
	{
	  next = next + 10;
	  next = next + ((int)str[i] - '0');
	    }
    }
  
  return (first * next);
}

