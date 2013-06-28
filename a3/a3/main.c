
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define DEFAULT 6
#define BUF_SIZE 12
#define PIPE_SIZE 2

//functions for each child process
void wall_clock();
void count_down(int start);

//global arrays
int pfd1[PIPE_SIZE];
int pfd2[PIPE_SIZE];
char buf[BUF_SIZE];

//main
int main(int argc, const char * argv[])
{
    int time=DEFAULT;
    //parse args
    if(argc==2)
    {
        time=atoi(argv[1]);
    }
    
	//create pipe 1 with error checking
    if (pipe(pfd1) == -1)
    {
        printf("Error opening pipe 1!\n");
        exit(1);
    }
    
	//create pipe 2 with error checking
    if (pipe(pfd2) == -1)
    {
        printf("Error opening pipe 2!\n");
        exit(1);
    }
    
    printf("Pipes opened, now creating child process!\n");
    
    //child 1
    switch (fork())
    {
            //error checking
        case -1:
            printf("Error forking child 1!\n");
            exit(1);
            
            //child 1 process
        case 0:
            wall_clock();
            exit(1);
            
        default:
            break;
    }
    
    //child 2
    switch (fork())
    {
            //error checking
        case -1:
            printf("Error forking child 2!\n");
            exit(1);
            
            //child 2 process
        case 0:
            count_down(time);
            exit(1);
            
        default:
            break;
    }
    
    printf("Parent closing pipes\n");
    
	//pipe close error checking
    if (close(pfd1[0]) == -1)
    {
        printf("Error closing reading end of the pipe 1\n");
        exit(EXIT_FAILURE);
    }
    
    if (close(pfd1[1]) == -1)
    {
        printf("Error closing writing end of the pipe 1\n");
        exit(EXIT_FAILURE);
    }
    
    if (close(pfd2[0]) == -1)
    {
        printf("Error closing reading end of the pipe 2\n");
        exit(EXIT_FAILURE);
    }
    
    if (close(pfd2[1]) == -1)
    {
        printf("Error closing writing end of the pipe 2\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Parent waiting for children completion...\n");
    
	//wait until child process is terminated
    if (wait(NULL) == -1)
    {
        printf("Error wating, no child process is ended!\n");
        exit(EXIT_FAILURE);
    }
    if (wait(NULL) == -1)
    {
        printf("Error wating, no child process is ended!\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Time to print out a Friendly Message!\n");
	printf("Parent process finishing, bye!\n");
    exit(EXIT_SUCCESS);
    
}

void count_down(int start)
{
    //string signal to end process
	strcpy(buf, "time to die");
    
    printf("\nChild 2 process executing...\n");
    
	//close unused pipes
    if (close(pfd2[0]) == -1)
    {
        printf("Error closing reading end of pipe 2\n");
        _exit(1);
    }
    
	if (close(pfd1[1]) == -1)
    {
        printf("Error closing writing end of pipe 1\n");
        _exit(1);
    }
    
    if (close(pfd1[0]) == -1)
    {
        printf("Error closing reading end of pipe 1\n");
        _exit(1);
    }
    
    //count down
    for( ;start>0; start--)
    {
		printf("Count Down: 00:0%d\n", start);
        //send signal to child 1 process not to end
        write(pfd2[1], "not die yet",12);
        //count down every second
		sleep(1);
    }
    
    //signal to sibling to DIE
    write(pfd2[1], buf, sizeof(buf));
    
	//close pipe 2 writing end
    if (close(pfd2[1]) == -1)
    {
        printf("Error closing writing end of pipe 2");
        _exit(EXIT_FAILURE);
    }
    
	//back to main
    printf("Count Down: 0\n");
	printf("End of Count Down(child 2) process...\n");
    exit(1);
}

void wall_clock()
{
	//temp buffer to get termination string
	char str1[BUF_SIZE];
    
	strcpy(str1, "time to die");
    
	printf("\nChild 1 process executing...\n");
    
    time_t now;
    struct tm *lcltime;
    
	//close unsed pipes
    if (close(pfd1[0]) == -1)
    {
        printf("Error closing reading end of pipe 1\n");
        _exit(1);
    }
    
	if (close(pfd2[1]) == -1)
    {
        printf("Error closing writing end of pipe 2\n");
        _exit(1);
    }
    
	if (close(pfd1[1]) == -1)
    {
        printf("Error closing writing end of pipe 1\n");
        _exit(1);
    }
    
	//show current time
    for(;;)
    {
        
        now = time ( NULL );
        lcltime = localtime ( &now );
        
		//read message from child 2 process
		int status = read(pfd2[0], buf, 12);
        
		//compare buffer
        int ret = strcmp(str1, buf);
        
		//if not end print current status and buffer
		if (ret != 0)
		{
			//printf("Read status: %d, Buffer= %s\n", status, buf);
            printf ("The time is %d:%d:%d\n", lcltime->tm_hour, lcltime->tm_min, lcltime->tm_sec );
            //show ever second
            sleep(1);
		}
		
		//if end signal came in
		if(ret == 0)
        {
			//close writing end
            if (close(pfd2[0]) == -1)
            {
                printf("Error closing writing end of pipe 2\n");
                _exit(1);
            }
            
            //return back to parent
            printf("End of Wall Clock(child 1) process...\n");
            exit(1);
        }
    }
    
}

