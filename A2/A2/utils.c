//
//  utils.c
//  A2
//
//  Created by Alex Egg on 6/13/13.
//  Copyright (c) 2013 Alex Egg. All rights reserved.
//

#include <stdio.h>
#include <string.h>



unsigned read_page_file(unsigned (*pages_ptr)[])
{

    FILE * fp = fopen("/Users/eggie5/Development/cs570/A2/A2/pages.txt", "r");
    if (fp==NULL) {fputs ("File error", stderr); exit (1);}
    
    char buffer[4096];
    int len=fread(buffer, 1, sizeof(buffer), fp);
    
//    printf("numbers found: %d\n", len/2);
    unsigned pages_len=(len/2)+1;
    unsigned pages[pages_len];
    
    char * pch;
//    printf ("Splitting string \"%s\" into tokens:\n",buffer);
    pch = strtok (buffer," ");
    int i=0;
    while (pch != NULL)
    {

        unsigned page = atoi(pch);
        pages[i++]=page;
        pch = strtok (NULL, " ");
    }
    
    for(int j=0;j<pages_len;j++)
    {
//        printf("%d ", pages[j]);
        (*pages_ptr)[j]=pages[j];
    }
    
    
    return pages_len;
}


//find if there any exist number between reference and frame
int exists(int frame_size,int page_frames[],int page_num)
{
    int i, found = 0;
    
    //search frame
    for (i=0;i<frame_size;i++)
    {
		//if found set 1
		if(page_frames[i]==page_num)
            found=1;
    }
    
    //return
    return found;
}

void print_frame(int * frames, int * r, int len)
{
    //print current frame
    printf("\n");
    for(int i=0;i<len;i++)
    {
        printf("%d\t",frames[i]);
    }
    printf("\t");
    for(int i=0;i<len;i++)
    {
        printf("%d ",r[i]);
    }
}


//display function
void display(int page_frames[],int frame_size)
{
	int index;
    
	//print out the result of the clock argorithm
	printf("\n    Frames : \t");
	for(index=0; index<frame_size; index++)
    {
		printf("%d\t",page_frames[index]);
    }
}

