

#include <stdio.h>
#include "clock.h"
#include "utils.h"

#define TRUE 1
#define FALSE 0

void fifo(int * pg, int page_file_len);
void print_frame(int * frames, int len);
void fifo(int * pg, int page_file_len);

unsigned clock_simulate()
{
    printf("running clock simulation\n");
    
    int page_file [12] = {2,3,2,1,5,2,4,5,3,2,5,2};
   
    for(int i=0; i<12; i++)
    {
        printf("%d ", page_file[i]);
    }
    
    printf("\n");
    
    fifo(page_file, 12);
    
    return 0;
}

//find if there any exist number between reference and frame
int find(int frame_size,int page_frames[],int page_num)
{
    int i, found = 0;
    
    //search frame
    for (i=1; i<=frame_size; i++)
    {
		//if found set 1
        printf("%d==%d\n", page_frames[i], page_num);
		if(page_frames[i]==page_num)
        {
            found=1;
            printf("  found %d in frame", page_num);
        }

    }

    return found;
}

void extracted_function(int *hit_p, int* frames, int page, const int frame_len)
{
    for(int i=0; i<frame_len; i++)
    {
        if(page == frames[i])
        {
            *hit_p=1;
            break;
        }
    }
}

void fifo(int * pg, int page_file_len)
{
	int ptr=0;
	int hit;
    const int frame_len=3;
    int frames[frame_len]={-1};
    for(int i=0;i<3;i++)
    {
        frames[i]=-1;
    }
    int r[frame_len]={0};
    
    
    //iterate all the pages
    int s=0;
    while(s < page_file_len)
	{
        ptr=ptr % frame_len; //reset frame counter at 3 -- like clock

		int page=pg[s];
        
        hit=0;
        extracted_function(&hit, frames, page, frame_len);
			
        if(hit==TRUE)
        {
            if(frames[ptr]!=-1)
                r[ptr]=1;//When the page is referenced, the use bit is set to 1
            s++;
           // ptr++;
        }
        else if(hit==FALSE)
        {
            if(r[ptr]==0)
            {
                
                frames[ptr]=page;
                if(frames[ptr]!=-1)
                    r[ptr]=1;
                s++;
                ptr++;
            }
            else if(r[ptr]==1)
            {
                r[ptr]=0; //reset bit
                ptr++;
            }
            
        }
        else
        {
            
        }
        
        print_frame(frames, frame_len);
	}
    
    //print fault counts
    //printf("\n\nPage Faults=%d",fault_count);
    
}



void print_frame(int * frames, int len)
{
    //print current frame
    printf("\n");
    for(int i=0;i<len;i++)
    {
        printf("%d\t",frames[i]);
    }
}
