#include<stdio.h>
#include "lru.h"
#include "utils.h"


unsigned lru_simulate(unsigned pages[], unsigned pages_len, unsigned table_len)
{
    printf("\n\nrunning LRU simulation\n");
    
    
    for(int i=0; i<pages_len; i++)
    {
        printf("%d ", pages[i]);
    }
    
    printf("\n");
    
//    clock(pages, pages_len, table_len);
    lru(pages, pages_len, table_len);
    
    return 0;
}


//lru function
void lru(unsigned reference[], unsigned length, const int frame_size)
{
	//count array is search for LRU
	int count[10],i,j,set,cnt,cnt2,cnt3,bcnt,page_num;
	int page_fault=0;
	//max frames size up to 10
    int page_frames[10];
	//check existence
	int exist;
	//index for filling
	int ptr=0;
	//index for replacement
	int victim;

	//initilizing distance and frame array	
	for(i=0; i<frame_size; i++)
	{
		page_frames[i]=-1;
	}

	for(j=0; j<length; j++)
	{
		//get current page from the array
		page_num=reference[j];

		//print out every sequence
		printf("\n\n[%d] Page = %d",j+1,page_num);

		//call find function to see if there is any vaule exist in the frame
		exist=exists(frame_size, page_frames, page_num);
		
		//if empty fill the frames
		if (exist==0)
		{
			if(page_frames[ptr] == -1)
			{
				//filling empty frame count as page fault
				page_frames[ptr]=page_num;
				page_fault++;
				ptr++;
				printf("\tEmpty frame is filled by page = %d", page_num);
				//if frame pointer exceed the frame size reset the pointer
				if(ptr==frame_size)
					ptr=0;
			}

			//if frame is full find victim for replacement
			else if(page_frames[ptr] != -1)
			{		
				//reset to 0
				for(set=0; set<frame_size; set++)
					count[set] = 0;
			
				//check past pages in reference array for LRU
				for(bcnt=j-1, cnt=1; cnt<=frame_size-1; cnt++, bcnt--)			
				{		
					for(cnt2=0; cnt2<frame_size; cnt2++)
					{
						//if found LRU set to 1
						if(page_frames[cnt2] == reference[bcnt])
							count[cnt2] = 1;
					}
				}

				//search for not used page
				for(cnt3=0; cnt3<frame_size; cnt3++)
				{
					//if found set this index for replacement
					if(count[cnt3] == 0)
						victim=cnt3;
				}	

				//replace new page with the LRU page
				printf("\tPage is not available replaced with Page = %d", page_frames[victim]);
				page_frames[victim]=page_num;
				page_fault++;
			}
		}
		else
			printf("\tPage = %d is already in frames", page_num);

		//call display function to print out the result
		display(page_frames, frame_size);
	}

		printf("\n\n************ Total Page Faults: %d ************", page_fault);
}


