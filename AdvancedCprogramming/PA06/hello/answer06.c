#include "answer06.h"
#include <stdio.h>
#include <stdlib.h>


void getMin(SparseNode * array, int * min_ptr);  // Helper functions
void getMax(SparseNode * array, int * max_ptr);
SparseNode * mergeHelp(SparseNode * copy, SparseNode * array_2);
SparseNode * SparseArray_insertMerge( SparseNode * array, int index, int value );


/* 
 * Create a single instance of a sparse array tree node with a specific
 * index and value. This Sparse array will be implemented by a binary tree.
 *
 * Arguments:
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the node just constructed
 *
 * This is a constructor function that allocates
 * memory for a sparse array tree node, and it copies the integer values, and sets the 
 * subtree pointers to NULL. 
 */
SparseNode *SparseNode_create(int index, int value)
{
  SparseNode * ptr = malloc(sizeof(SparseNode));
  
  ptr -> index = index;
  ptr -> value = value;
  
  ptr -> left = NULL;
  ptr -> right = NULL;
  
  return ptr;
}


/* Add a particular value into a sparse array tree on a particular index.
 *
 * Arguments:
 * *array        the root node of the sparse array tree
 * index         the index to be stored in the node
 * value         the value to be stored in the node
 * 
 * returns:
 * SparseNode *  the pointer points to the root node of the modified sparse 
 *               array tree
 *
 * The sparse array tree uses the index as a key in a binary search tree.
 * If the index does not exist, create it. 
 * If the index exists, REPLACE the value to the new one. Use the index to
 * determine whether to go left or right in the tree (smaller index
 * values than the current one go left, larger ones go right).
 */
SparseNode * SparseArray_insert ( SparseNode * array, int index, int value )
{
  if(value == 0)  // Don't want 0 value nodes
    return array;
  
  if(array == NULL)  // free(array); ????
    return SparseNode_create(index, value);  // Empty list
  
  if((array -> index) == index)
    {
      (array -> value) = value;  // If same index, "merge" the values
      return array;
    }
  
  if((array -> index) > index)
    {
      (array -> left) = SparseArray_insert(array -> left, index, value);  // Move to left side
      return array;
    }
  
  (array -> right) = SparseArray_insert(array -> right, index, value);  // Move to right side
  
  return array;
}


/* Build a sparse array tree from given indices and values with specific length.
 *
 * Arguments:
 * index*         a pointer points to the start position of the index array
 * value*         a pointer points to the start position of the value array
 * length         the size of both array
 * 
 * returns:
 * SparseNode *   the pointer points to the root node of sparse array tree
 *                just constructed
 *
 * It returns a sparse array tree. 
 * You need to insert tree nodes in order
 *
 * (the first sparse array node contains indices[0] and values[0], second node
 * contains indices[1] and values[1]. Basically, each tree node is constructed
 * with each pair in indices and values array. In other words, elements of 
 * indices and values with the same index should go into the same node.)
 */
SparseNode *SparseArray_build(int * indicies, int * values, int length)
{
  SparseNode * root = NULL;  // Empty tree to start
  int i;
  
  for(i = 0; i < length; i++)
    {
      root = SparseArray_insert(root, indicies[i], values[i]);  // Insert all data one node at a time
    }
  
  return root;
}


/* Destroy an entire sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * void
 *
 * traversing the binary tree in postorder. Use the
 * SparseNode_destroy () function to destroy each node by itself.
 */
void SparseArray_destroy ( SparseNode * array )
{
  if(array == NULL)  // If empty, free pointer
    {
      free(array);
      return;
    }
  
  SparseArray_destroy(array -> left);  // Free each node in every branch
  SparseArray_destroy(array -> right);
  free(array);
}


/* Retrieve the smallest index in the sparse array tree.
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the smallest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMin ( SparseNode * array )
{
  int min = 0;
  int * min_ptr = &min;
  
  getMin(array, min_ptr);  // Helper uses pointer to track minimum index
  
  return (* min_ptr);
}

void getMin(SparseNode * array, int * min_ptr)
{
  if(array == NULL)  // End of array
    return;
  
  if((array -> index) < (* min_ptr))  // Update minimum
    (* min_ptr) = (array -> index);
  
  getMin((array -> left), min_ptr);  // Move to left (smaller indicies)
}


/* Retrieve the largest index in the sparse array tree. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * int            the largest index in the sparse array tree
 *
 * (Hint: consider the property of binary search tree) 
 */
int SparseArray_getMax ( SparseNode * array )
{
  int max = 0;
  int * max_ptr = &max;
  
  getMax(array, max_ptr);  // Helper uses pointer to track maximum index
  
  return (* max_ptr);
}

void getMax(SparseNode * array, int * max_ptr)
{
  if(array == NULL)  // End of array
    return;
  
  if((array -> index) > (* max_ptr))  // Update maximum
    (* max_ptr) = (array -> index);
  
  getMax((array -> right), max_ptr);  // Move to right (larger indicies)
}


/* Retrieve the node associated with a specific index in a sparse
 * array tree.  
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to search
 * 
 * returns:
 * SparseNode*    the node with the index that you searched from the tree.
 *                If no node found, NULL should be returned. 
 *                
 * Hint: If the given index is smaller than the current
 * node, search left ; if it is larger, search right.
 */
SparseNode * SparseArray_getNode(SparseNode * array, int index )
{
  if(array == NULL)  // End of array
    return NULL;
  
  if((array -> index) == index)  // Found it!
    {
      return array;
    }
      
  if((array -> index) > index)  // If too big, move left
    return SparseArray_getNode(array -> left, index);
  
  return SparseArray_getNode(array -> right, index);  // Too small => move right
}


/* Remove a value associated with a particular index from the sparse
 * array. It returns the new
 * sparse array tree ( binary tree root ). 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * index          the index of the node you want to remove
 * 
 * returns:
 * SparseNode*    the root node of the sparse array tree that you just modified
 *          
 *    
 * HINT : First, you need to find that node. Then, you will need to isolate
 * several different cases here :
 * - If the array is empty ( NULL ), return NULL
 * - Go left or right if the current node index is different.
 * - If both subtrees are empty, you can just remove the node.
 * - If one subtree is empty, you can just remove the current and
 * replace it with the non - empty child.
 * - If both children exist, you must find the immediate successor of
 * the current node ( leftmost of right branch ), swap its values with
 * the current node ( BOTH index and value ), and then delete the
 * index in the right subtree.
*/
SparseNode * SparseArray_remove ( SparseNode * array, int index )
{
  if(array == NULL)  // End of array
    return NULL;
  
  if (index < (array -> index))
    {
      array -> left = SparseArray_remove(array->left, index);
      return array;
    }

  if (index > (array -> index))
    {
      array -> right = SparseArray_remove(array->right, index);
      return array;
    }
  

  //////////////////// Handle node according to # of children ////////////////////
  if((array -> left) == NULL)
    {
      if((array -> right) == NULL)  // array = LEAF
        {
          free(array);
          return NULL;
        }
      else  // Only has right child
        {
          SparseNode * new = array -> right;  // Replace with right child
          free(array);
          return new;
        }
    }
  if((array -> right) == NULL)  // Only has left child
    {
      SparseNode * new = array -> left;  // Replace with left child
      free(array);
      return new;
    }
  
  
  //////////////////// Two children ////////////////////
  SparseNode * successor = (array -> right);  // Look within right half from target node
  
  while((successor -> left) != NULL)  // Find left-most node in that right half ^^
    successor = (successor -> left);
  
  int value = (array -> value);
  (array -> index) = (successor -> index);
  (array -> value) = (successor -> value);
  (successor -> index) = index;
  (successor -> value) = value;
  (array -> right) = SparseArray_remove(array -> right, index);  // delete successor  ??????
  return array;
}


/* The function makes a copy of the input sparse array tree
 * and it returns a new copy. 
 *
 * Arguments:
 * *array         the root node of a sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                copied from the input sparse array tree.
 *       
 */
SparseNode * SparseArray_copy(SparseNode * array)
{
  if(array == NULL)  // Leaf
    return NULL;
  
  SparseNode * copy = NULL;
  
  copy = SparseArray_insert(copy, array -> index, array -> value);
  
  (copy -> left) = SparseArray_copy(array -> left);
  (copy -> right) = SparseArray_copy(array -> right);
  
  return copy;
}


/* Merge array_1 and array_2, and return the result array. 
 * This function WILL NOT CHANGE the contents in array_1 and array_2.
 *
 * Arguments:
 * *array_1         the root node of the first sparse array tree
 * *array_2         the root node of the second sparse array tree
 * 
 * returns:
 * SparseNode*    the root node of the new sparse array tree that you just
 *                merged from the two input sparse array tree
 *     
 * When merging two sparse array tree:
 * 1. The contents in array_1 and array_2 should not be changed. You should make
 *    a copy of array_1, and do merging in this copy.
 * 2. array_2 will be merged to array_1. This means you need to read nodes in 
 *    array_2 and insert them into array_1.
 * 3. You need to use POST-ORDER to traverse the array_2 tree. 
 * 4. Values of two nodes need to be added only when the indices are the same.
 * 5. A node with value of 0 should be removed.
 * 6. if array_2 has nodes with index different than any nodes in array_1, you
 *    should insert those nodes into array_1.
 * 
 * Hint: you may write new functions
 */
SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
  int index;
  int min;
  int max;
  
  if(array_1 == NULL)
    return array_2;
  
  if(array_2 == NULL)
    return array_1;
  
  SparseNode * copy1 = SparseArray_copy(array_1);  // Make copy of array_1
  copy1 = mergeHelp(copy1, array_2);  // Merge array_2 values into copy
  
  min = SparseArray_getMin(copy1);
  max = SparseArray_getMax(copy1);
  
  for(index = min; index <= max; index++)
    {
      if (SparseArray_getNode(copy1, index) && (SparseArray_getNode(copy1, index) -> value == 0))
	copy1 = SparseArray_remove(copy1, index);
    }
  
  return copy1;
}


SparseNode * mergeHelp(SparseNode * copy, SparseNode * array_2)
{
  if(array_2 == NULL)
    return copy;
  
  copy = SparseArray_insertMerge(copy, array_2 -> index, array_2 -> value);
  copy = mergeHelp(copy, array_2 -> left);
  copy = mergeHelp(copy, array_2 -> right);
  return copy;
}

SparseNode * SparseArray_insertMerge( SparseNode * array, int index, int value )
{
  if(value == 0)  // Don't want 0 value nodes
    return array;
  
  if(array == NULL)  // free(array); ????
    return SparseNode_create(index, value);  // Empty list
  
  if((array -> index) == index)
    {
      (array -> value) += value;  // If same index, "merge" the values
      return array;
    }
  
  if((array -> index) > index)
    {
      (array -> left) = SparseArray_insertMerge(array -> left, index, value);  // Move to left side
      return array;
    }
  
  (array -> right) = SparseArray_insertMerge(array -> right, index, value);  // Move to right side
  
  return array;
}
