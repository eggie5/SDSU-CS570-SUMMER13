

#include <stdio.h>
#include "clock.h"
#include "utils.h"

#define TRUE 1
#define FALSE 0




unsigned clock_simulate(unsigned pages[], unsigned pages_len, unsigned table_len)
{
    printf("running clock simulation\n");
    
   
    for(int i=0; i<pages_len; i++)
    {
        printf("%d ", pages[i]);
    }
    
    printf("\n");
    
    clock(pages, pages_len, table_len);
    
    return 0;
}



void clock(unsigned * pg, unsigned pages_len, const int frame_len)
{
	int ptr=0;
	int hit;
    int fault_count=-3;//offset b/c empty buffer isn't a fault
    
    int * frames=malloc(sizeof(int) * frame_len);
    for(int i=0;i<frame_len;i++)
    {
        frames[i]=-1;
    }
    
    int * r=malloc(sizeof(int)*frame_len);
    for(int i=0;i<frame_len;i++)
    {
        r[i]=0;
    }
    
    
    //iterate all the pages
    int s=0;
    while(s < pages_len)
	{
        ptr=ptr % frame_len; //reset frame counter at 3 -- like clock

		int page=pg[s];
        
        hit=0;
        int index=find(&hit, frames, page, frame_len);
			
        if(hit==TRUE)
        {
            if(frames[ptr]!=-1)
                r[index]=1;//When the page is referenced, the use bit is set to 1
            s++;
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
                fault_count++;
            }
            else if(r[ptr]==1)
            {
                r[ptr]=0; //reset bit
                ptr++;
            }
            
        }
        
        print_frame(frames, r, frame_len);
	}
    
    //print fault counts
    printf("\n\nPage Faults=%d", fault_count);
    
}

int find(int *hit_p, int* frames, int page, const int frame_len)
{
    for(int i=0; i<frame_len; i++)
    {
        if(page == frames[i])
        {
            *hit_p=1;
            return i; //return index in buffer
        }
    }
    return -1;
}



