#include <stdio.h>
//#include <string.h>
#include <stdlib.h>


#include "answer06.h"


SparseNode * SparseNode_create(int index, int value)
{  
  if(value == 0)
    {
      return NULL;//DONT need 0 values
    }

  SparseNode * n = malloc(sizeof(SparseNode));
  
  if (n == NULL)
    {
      fprintf(stderr, "\nAllocation failed 1.\n");
      return (NULL);//error here
    }
  // printf("\n%d\n", index);
  
  n -> index = index;
  n -> value = value;
  n -> right = NULL;
  n -> left = NULL;
  
  return n;
}



SparseNode * SparseArray_insert(SparseNode * array, int index, int value)
{
  if(array == NULL)
    {
      return(SparseNode_create(index, value));
    }
  
  if((array -> index) == index)
    {
      array -> value = value;//relpacing with new value
    }
  
  else if((array -> index) > index)
    {  
      array -> left = SparseArray_insert(array->left, index, value);//recursion here 
    }
  else
    {
      array -> right = SparseArray_insert(array->right, index, value);//recusrion here
    }
  /*
    if((array -> left) == NULL)
    {
    SparseNode * p  = SparseNode_create(index, value);
    array -> left = p;
    }
    else
    {
    SparseArray_insert(&(array -> left), value);
    }
    }
    
    else
    {
    if((arra -> right) == NULL)
	{
	SparseNode * p = SparseNode_create(index, value);
	
	}
	}
  */
  
  return array;
  
}


SparseNode * SparseArray_build(int * indices, int * values, int length)
{
 
  SparseNode * Node_root = NULL;
   int i = 0;
  
  for (i = 0; i < length; i++)
    {
      Node_root = SparseArray_insert(Node_root, indices[i], values[i]);
    }
  
  return Node_root;
  
}


void SparseArray_destroy(SparseNode * array)
{  
  if (array == NULL)
    {
      return;					
    }
  
  SparseArray_destroy(array->left);
  SparseArray_destroy(array->right);
  
  free(array);
  
  array = NULL;     
  

}

int SparseArray_getMin(SparseNode *array)
{
  if(array->left == NULL)
    {
    return array->index;
    }
  
  //newindex ptr to array 
  
  /* SparseNode *num = array;
  
  while(num -> left != NULL)
    {
      num = num->left ;
    }
  */
  
  
  return SparseArray_getMin(array->left);
 
  //return (mleft<mright)?(mleft<pt?mleft:pt):(pt<mright?pt:mright);
}

      


int SparseArray_getMax(SparseNode * array)
{
  if(array->right == NULL)
    {
      return array->index;
    }
  
  
  return SparseArray_getMax(array->right);
}


SparseNode * SparseArray_getNode(SparseNode * array, int index)
{
  
  if(array == NULL)
    {
      return NULL;
    }
  
  if((array -> index) == index)
    {
      return array;
    }
  
  SparseNode * location;//up top  maybe???
  location = SparseArray_getNode(array->left, index);
  
  if(location != NULL)
    {
      return location;
    }
  
  return SparseArray_getNode(array->right, index);
}


SparseNode * SparseArray_remove(SparseNode * array, int index)
{

   if(array == NULL)
     {// End of array
    return NULL;
     }
   //
   if (index < (array -> index))
     {//left 
       array -> left = SparseArray_remove(array->left, index);
       return array;
     }
   //right stuufff
   if (index > (array -> index))
     {
       array -> right = SparseArray_remove(array->right, index);
       return array;
     }
   
   if((array -> left) == NULL)
     {
       if((array -> right) == NULL)  // array == children here 
	 {
	   free(array);
	   return NULL;
	 }
       else  // Only has right childright exit only
	 {
	   SparseNode * new = array -> right;  // Replace with right child
	   
	   free(array);
	   
	   return new;
	 }
     }
   if((array -> right) == NULL)  // Only has left child
     {//child on the left shoud be here
       SparseNode * new = array -> left;  
       
       free(array);
       
       return new;
     }

SparseNode * successor = (array -> right);  // Look within right half from target node
  
  while((successor -> left) != NULL)  // Find left-most node in that right half ^^
    {  
    successor = (successor -> left);
    }
  
  int value = (array -> value);



  (array -> index) = (successor -> index); 
  (array -> value) = (successor -> value);

  (successor -> index) = index;
  (successor -> value) = value;
  //call here function
  (array -> right) = SparseArray_remove(array -> right, index);  
  
  return array;
   
   
   
  /*
  if(array == NULL)
    {
      return NULL;
    }
  
  
  SparseNode * remove1 = SparseArray_getNode(array, index);
    if(remove1 == NULL)
      {
	return NULL;
      }
  
  if(remove1 -> right == NULL && remove1 -> left == NULL)
    {
      free(remove1);
      return array;
    }
  

  
  if(remove1 -> right == NULL)
    {
      
      SparseNode *tmp = remove1 -> left;

      remove1->left = tmp->left;
      remove1->right = tmp->right;
      remove1->value = tmp->value;
      remove1->index = tmp->index;

      free(tmp);//for memory leak
      
      return array;
    }

   if(remove1->left == NULL)
    {
      
      SparseNode *tmp = remove1 -> right;

      remove1 -> left = tmp->left;
      remove1 -> right = tmp->right;
      remove1 -> value = tmp->value;
      remove1 -> index = tmp->index;

      free(tmp);//for memory leak
      
      return array;
    }

   SparseNode * val_small = NULL;
   
   val_small = SparseArray_getNode(val_small, SparseArray_getMin(remove1->right));

   remove1 -> index = val_small -> index;
   remove1 -> value = val_small -> value;
   // remove->left = val_small -> left;
   //remove->right = val_small -> right;
   
   //free()

   return SparseArray_remove(val_small, val_small->index);*/
  
}

SparseNode * SparseArray_copy(SparseNode * array)
{//checkfirst  
  //then malloc the stuff for root
  //then assign values to each on the new thing
  //use recursion though
  if (array == NULL)
    {
      return NULL;
    }

  SparseNode * Node_root = malloc(sizeof(SparseNode));

  Node_root -> index = array -> index;
  Node_root -> value = array -> value;

  //recursion here for l/r
  Node_root -> left = SparseArray_copy(array -> left);
  Node_root -> right = SparseArray_copy(array -> right);
      


  return Node_root;
}



//definitions
SparseNode * SparseArray_insertMerge( SparseNode * array, int index, int value );
SparseNode * mergeHelp(SparseNode * copy, SparseNode * array_2);


SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
  int index = 0;
  int min = 0;
  int max = 0;
  
  if(array_1 == NULL)
    {
    return array_2;
    }
  
  if(array_2 == NULL)
    {
    return array_1;
    }
  
  
  SparseNode * copy1 = SparseArray_copy(array_1);//first copying here 
  
  copy1 = mergeHelp(copy1, array_2);//copying 1st to second
  
  
  // min & max vals here for 

  min = SparseArray_getMin(copy1);
  max = SparseArray_getMax(copy1);
  
  for(index = min; index <= max; index++)
    {
      if (SparseArray_getNode(copy1, index) && (SparseArray_getNode(copy1, index) -> value == 0))	
	{
	  copy1 = SparseArray_remove(copy1, index);
	}
    }
  
  return copy1;
}

SparseNode * mergeHelp(SparseNode * copy, SparseNode * array_2)
{
  if(array_2 == NULL)
    {
      return copy;
    }
  
  copy = SparseArray_insertMerge(copy, array_2 -> index, array_2 -> value);
  
  copy = mergeHelp(copy, array_2 -> left);
 
  copy = mergeHelp(copy, array_2 -> right);
  
  return copy;
}

SparseNode * SparseArray_insertMerge( SparseNode * array, int index, int value )
{
   if(value == 0)  // Don't want 0 value nodesno zero values here
     {
       return array;
     }

   if(array == NULL)  // free(array); ????
     { 
       return SparseNode_create(index, value);  // list is empty bruh
     }


   if((array -> index) == index)
     {
       (array -> value) += value;  // tryna merge this stuff
       return array;
     }
   
   if((array -> index) > index)
     {// direction towards left
      array -> left = SparseArray_insertMerge(array -> left, index, value); 
      return array;
    }
   
   //if statement for right move
   array -> right = SparseArray_insertMerge(array -> right, index, value);  

   
   return array;
}


