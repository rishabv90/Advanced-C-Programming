#include <stdio.h>
#include <stdlib.h>
#include "answer06.h"

SparseNode *SparseNode_create(int index, int value)
{
	if(value==0)
		return NULL;	// we dont want values that are '0'

	SparseNode *temp = malloc(sizeof(SparseNode));
	
	if(temp==NULL)
		return NULL;
	
	temp->left = NULL;
	temp->right = NULL;
	temp->index = index;
	temp->value = value;
	return temp;
}

SparseNode *SparseArray_insert(SparseNode *array, int index, int value)
{
	// *array : root node of tree
	// index  : index value to be added
	// value  : value to be added at index
/*
	if(value==0)	// if value is invalid, then nothing to be added
	{
		return NULL;
	}
BECAUSE IF WE DO HAVE AN ARRAY AND VALUE IS 0, THEN ARRAY WILL BE
REPLACED BY NULL, THIS WOULD BE WRONG.
Also, value is being checked in other function, and if value is 0, 
then NULL will be returned from Create function
	*/

	if(array == NULL)	// if at end of tree, create new value
	{				// if no array is present, make index root
		return SparseNode_create(index, value);
	}
	
	// Use the index to determine whether to go left or right 
	// in the tree (smaller * index values than the current one go
	// left, larger ones go right).
	if(array->index == index)
	{
		// if the index exists REPLACE with value of new one
		array->value = value;
	}
	else if(array->index > index)
	{
		array->left = SparseArray_insert(array->left, index, value);
	}
	else
	{
		array->right = SparseArray_insert(array->right, index, value);
	}
	return array;
}

SparseNode * SparseArray_build(int *indices, int *values, int length)
{
	SparseNode *root = NULL;
	int i = 0;
	for(i =0; i < length; ++i)
	{
		root = SparseArray_insert(root, indices[i], values[i]);
	}
	return root;
}

void SparseArray_destroy(SparseNode *array)
{
	if(array == NULL)
		return;
	SparseArray_destroy(array->left);
	SparseArray_destroy(array->right);
	free(array);
}

int SparseArray_getMin(SparseNode *array)
{
	if(array==NULL)
		return 2147483647;
	
	if(array->left==NULL && array->right==NULL)
		return array->index;
	
	int pt = array->index;
	int mleft = SparseArray_getMin(array->left);
	int mright = SparseArray_getMin(array->right);
return (mleft<mright)?(mleft<pt?mleft:pt):(pt<mright?pt:mright);
}


int SparseArray_getMax(SparseNode *array)
{
	if(array==NULL)
		return 0;
	
	if(array->left==NULL && array->right==NULL)
		return array->index;
	
	int pt = array->index;
	int mleft = SparseArray_getMax(array->left);
	int mright = SparseArray_getMax(array->right);
return (mleft>mright)?(mleft>pt?mleft:pt):(pt>mright?pt:mright);
}


SparseNode *SparseArray_getNode(SparseNode *array, int index)
{
	SparseNode *ptr;
	if(array == NULL)
		return NULL;
	if(array->index == index)
		return array;
	ptr =  SparseArray_getNode(array->left, index);
	if(ptr!=NULL)
		return ptr;
	return SparseArray_getNode(array->right, index);
}

SparseNode *SparseArray_remove(SparseNode *array, int index)
{
	if(array==NULL)
		return NULL;
	SparseNode *rm = SparseArray_getNode(array, index);
	if(rm == NULL)
		return NULL;
	if(rm->right==NULL && rm->left==NULL)
	{
		free(rm);
		return array;
	}
	if(rm->right == NULL)
	{
		SparseNode *tmp = rm->left;
		rm->left = tmp->left;
		rm->right = tmp->right;
		rm->index = tmp->index;
		rm->value = tmp->value;
		free(tmp);
		return array;
	}
	if(rm->left == NULL)
	{
		SparseNode *tmp = rm->right;
		rm->left = tmp->left;
		rm->right = tmp->right;
		rm->index = tmp->index;
		rm->value = tmp->value;
		free(tmp);
		return array;
	}
	
	SparseNode *nsmall = NULL;
	nsmall = SparseArray_getNode(nsmall, SparseArray_getMin(rm->right));
	rm->index = nsmall->index;
	rm->value = nsmall->value;
	return SparseArray_remove(nsmall, nsmall->index);
}

SparseNode *SparseArray_copy(SparseNode *array)
{
	if(array==NULL)
		return NULL;
	SparseNode *root = malloc( sizeof(SparseNode) );
	root->index = array->index;
	root->value = array->value;
	root->left = SparseArray_copy(array->left);
	root->right = SparseArray_copy(array->right);
	return root;
}

void travel_array2(SparseNode *root, SparseNode *array2)
{
	if(array2==NULL)
	  return;//array 1 ccopy of this
	travel_array2(root, array2->left);
	
	// find point in root that has the same index and sum
	// if sum == 0, delete that point
	
	// finds point in root with same index
	SparseNode *tmp = SparseArray_getNode(root, array2->index);
	if(tmp == NULL)	// if the value is not present in root
		SparseArray_insert(root, array2->index, array2->value);
	tmp->value += array2->value;
	if(tmp->value==0)
		SparseArray_remove(root, tmp->index);	
	
	travel_array2(root, array2->right);
	
	return;
}

SparseNode *SparseArray_merge(SparseNode *array1, SparseNode *array2)
{
	if(array1==NULL && array2==NULL)
		return NULL;
	else if(array1==NULL)//weirrd here
	  return SparseArray_copy(array2);//return NULL
	else if(array2 == NULL)//weird heere
	  return SparseArray_copy(array1);//return array1
	
	SparseNode *root = SparseArray_copy(array1);
	travel_array2(root, array2);
	
	return root;
}
