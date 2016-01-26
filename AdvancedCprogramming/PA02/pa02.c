#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "answer02.h"

int main(int argc, char * * argv)
{
  //first function
  int n = 8;
  char * stra = malloc(sizeof(char) * n);
    
  const char *strb = "I Am GOOOOOOOOOOOD";
  strcpy(stra, "Helooo how are you");    
  printf("\n\nContonation is :%s\n\n", strcat_ex(&stra, &n, strb));
  free(stra);
  
  //FOR SECOND FUNCTION
  int len = 3;
  char *  * string = explode("testing\nthe\r turnnnnnnn\tbrrruuh", " \t\v\n\r\f", &len);
  


  int i;
  //const char *delims = " \t\v\n\r\f"; 
  //printf("bruuh : %s\n", explode(string, delims, 3));
  
  for(i=0; i < len; i++)//testing purposes
    {
      printf("%s\n", string[i]);
    }
  //gottta free it.....
  free(string);
  
  
  //FOR THIRD FUNCTION
  
  int abc = 4;   
  char * * strArr1 = explode("homie how u doing bruh hows it going bruuuuuhh, 264 is craay", " ", &abc);
  //call the functioonnnn
  char * str = implode(strArr1, abc, ", ");
  
  printf("\n%s\n", str);
  
  free(strArr1);
  
  free(str);
  
  
 
  //FOR FOURTH FUNCTION
  int len4 = 16;
  // int z = 0;
  char * * strArr4 = explode("An Apple is Applely", " ", &len4);
   
  
  //  for(z=0; z < len4; z++)
  //{
  //	printf("%s\n", strArr4[z]);
  //}
  //call it
  sortStringArray(strArr4, len4);
  //then implode into a string
  char * str4 = implode(strArr4, len4, " ");
  
  printf("%s\n", str4); 
  
  free(strArr4);//free explodew stuuuffffff
  
  
  
  //FOR FIFTH FUNCTION   

  //pretty much same as previous fuction except dealing with characters this time indivisually
  char * sorting = strdup("hello people how are you?");  
  printf("Before sorting : %s\n", sorting);
  
  sortStringCharacters(sorting);
     
  printf("after sorting: %s\n", sorting);

    
  //FOR SIXTH FUNCTION
  
    int bro;
    const char * sentence = ("Give me six hours to chop down a tree and I will Spend\n""the first four hours sharpening my Axe");
    char * * sentence_arr = explode (sentence, "\n", &bro);
    destroyStringArray(sentence_arr, bro);
    
    destroyStringArray(NULL, 0);//as given in the .h file
    return EXIT_SUCCESS;

}
