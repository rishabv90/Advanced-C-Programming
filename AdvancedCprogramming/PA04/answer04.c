#include "answer04.h" 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define FALSE 0
#define TRUE 1
#define MAGIC_NUMBER 0x21343632

#pragma pack(1)

/*
  -----------------------------------------------
  | magic-number | width | height | comment-len |  16 bytes
  |----------------------------------------------
  |           comment with null-byte            |  comment-len bytes
  |----------------------------------------------
  |                 pixel data                  |  width*height bytes
  -----------------------------------------------
 */
Image * Image_load(const char * filename)
{
  FILE * fp = NULL;
  size_t read;
  ImageHeader header;
  Image * im = NULL, *img = NULL;
  int err = FALSE;
  //size_t n_bytes = 0;
  
  
  if(!err) 
    { 
      // Open filename
      fp = fopen(filename, "rb");
      if(!fp) 
	{
	  
	  fprintf(stderr, "\n1Failed to open file '%s'\n", filename);
	  err = TRUE;
	}
    }
  
  if(!err) 
    { 
      // Read the header
      read = fread(&header, sizeof(ImageHeader), 1, fp);
      if(read != 1) 
	{
	  fprintf(stderr, "\n2Failed to read header from '%s'\n", filename);
	  err = TRUE;
	}
    }
  if(!err)
    {
      if (header.magic_number != MAGIC_NUMBER)
	{
	  fprintf(stderr, "\n3Magic number is in correct\n");
	  err = TRUE;
	}
      if ((header.width == 0) || (header.height == 0))
	{
	  fprintf(stderr,"\n4Width or Height Cannot be zero\n");
	  err = TRUE;
	}
      if (header.comment_len == 0) 
	{
	  printf("\n5Comment length cannot be zero\n");  //
	  err =TRUE;
	}
    }
  
  if (!err)
    { 
      //ALLOCATION STUFF
      im = malloc(sizeof(Image));
      if(im == NULL)
	{
	  fprintf(stderr, "\n6Malloc not working for im\n");
	  err = TRUE;
	}
      
      im->width = header.width;
      im->height = header.height;
      
      im->comment = malloc(sizeof(char) * (header.comment_len));


      if(im->comment == NULL)
	{
	  fprintf(stderr, "\n7Malloc not working for header comment\n");
	  err = TRUE;
	}
    }
  if(!err)
    {
      read = fread(im->comment, sizeof(char), header.comment_len, fp);

      if(read != header.comment_len)
	{
	  fprintf(stderr, "\n8cannot read comment from image\n");
	  err = TRUE;
	}
    }
     
  if(!err)
    {
      if((im->comment[header.comment_len-1]) != '\0')//might get error here
	{
	  fprintf(stderr, "\n9Last value is NOT null character in comment");
	  err = TRUE;
	}     
    }
  
  
  if(!err)
    {
      //data stuff
      im->data = malloc(header.width * header.height * sizeof(uint8_t));//weird
     
      if(im->data == NULL)
	{
	  fprintf(stderr, "\n10Malloc not working for dataFailed to allocate image data\n");
	  err = TRUE;
	}
     
    }
  
  if(!err)
    {
      //data stuff for pixel
      read = fread(im->data, sizeof(uint8_t), (header.width * header.height), fp);//there is something here
      if(read != (header.width * header.height))//might get error here
	{
	  fprintf(stderr, "\n11stray bites at the end of bmp file\n");
	  err = TRUE;
	}
    }
  
  if(!err)
    {
      
      img = im;
      im = NULL;
    }
  
  //}FOR END OF FILE POSTION AT THIS POINT
  
  if(im != NULL)
    {
      //freeing stuff
      free(im->comment);

      free(im->data);
      free(im);
      //im = '\0';
    }
 
  if(fp)
    {
      fclose(fp);
    }
     
  return img;//im instead of img  
}






int Image_save(const char * filename, Image * image)
{
  FILE * op = NULL;
  //size_t read;
  ImageHeader header;
  //Image * im = NULL;
  int err = FALSE;
  //uint8_t * count_data = NULL;
  size_t write = 0;
  //char * count_comment = NULL;
  

  if(!err)
    {
      //open file stuff
      op = fopen(filename, "wb");
      
      if(op == NULL)
	{
	  fprintf(stderr,"\n12Failed to open filename to write\n");
	  return FALSE;
	}
      
      //hearder write stuff
      
      header.width = image->width;
      header.height = image->height;
      header.magic_number = MAGIC_NUMBER;
      
      header.comment_len = 1 + strlen(image->comment);

    }
  
  if(!err)
    {
      write = fwrite(&header, sizeof(ImageHeader), 1, op);
      
      if(write != 1)
	{
	  fprintf(stderr,"\n13Problem is write stuff\n");
	  fprintf(stderr, "\n13FROM this %zd too %zd\n", write, sizeof(header));
	  err = TRUE;
	}
    }
      

  if(!err)
    {
      //write comment stuff
      //count_comment = malloc((header.comment_len)* (sizeof(char)));
     
      //write = fwrite(&header, sizeof(Imageheader), 1, fp);
      
	  //copy it here
      //  strcpy(count_comment, image->comment);
	  write = fwrite(image->comment, sizeof(char), header.comment_len, op);
	  
	  
	  if(write != header.comment_len)
	    {
	      fprintf(stderr, "\n14Comment cannot be read\n");
	      err = TRUE;
	    }
    }
  
  if(!err)
	{
	  //_data = (uint8_t *)malloc((header.height * header.width)*(sizeof(uint8_t)));
	  /*
	  int i;
	  for(i = 0; i < (header.height * header.width); i++)
	    {
	      count_data[i] = (image->data[i]);
	      
	      }*/
	  write = fwrite(image->data, sizeof(uint8_t), (header.height * header.width), op);
	   
	  if(write != (header.height * header.width))
	    {
	      fprintf(stderr, "\n15Pixels cannot be read\n");
	      err = TRUE;
	    }
	} 


  /*  if(err == TRUE)
	{
	  free (count_data);
	  free(count_comment);
	}
  */  
      if(op)
	{
	  fclose(op);
	}
      
  return TRUE;
}



void Image_free(Image * image)
{
   	free(image->data);
	free(image->comment);
	free(image);//aparently we can free NULL too
}


void linearNormalization(int width, int height, uint8_t * intensity)
{
  int len = width * height;
  int max= 0; 
  int min = 255;
  int i;
  
  for(i = 0; i < len ; ++i)
    {
      if(intensity[i] > max)
	{
	  max = intensity[i];
	}
      if(intensity[i] < min)
	{
	  min = intensity[i];
	}
    }

  for(i = 0; i < len; ++i)
    {
      intensity[i] = (intensity[i] - min) * 255/ (max - min);
    }

}


