

#include <stdio.h>
#include "clock.h"
#include "utils.h"

void fifo(int * pg, int page_file_len);

unsigned clock_simulate()
{
    printf("running clock simulation\n");
    
    int page_file [30] = {2,3,2,1,5,2,4,5,3,2,5,2};
   
    for(int i=0; i<30; i++)
    {
        printf("%d ", page_file[i]);
    }
    
    printf("\n");
    
    fifo(page_file, 12);
    
    return 0;
}

void fifo(int * pg, int page_file_len)
{
    int fr[10];
    
    
    
	int i; //loop index
	int f=0;
	int r=0;
	int s=0;
	int flag=0;
	int count=0;
//	printf("\nEnter size of page frame:");
//	scanf("%d",&psize);
    int frame_len=3;
    //init to -1
	for(i=0;i<frame_len;i++)
	{
		fr[i]=-1;
	}
    
    
	while(s<page_file_len)
	{
		flag=0;
		int num=pg[s];
		for(i=0;i<frame_len;i++)
		{
			if(num==fr[i]) //check for existing match & break
			{
				s++;
				flag=1;
				break;
			}
		}
		if(flag==0) //if does not exist
        {
            r=r % frame_len; //reset frame counter at 3 -- like clock
            fr[r]=num;
            

            printf("%d, %d", fr[r], pg[s+1]);
            if(fr[r]==pg[s+1])
                printf("hit");
            else
                r++;
            s++;
            count++;
			
		}
        
        //print current frame
		printf("\n");
		for(i=0;i<frame_len;i++)
		{
			printf("%d\t",fr[i]);
		}
	}
    
    //print fault counts
    printf("\nPage Faults=%d",count);
    getchar();
}
