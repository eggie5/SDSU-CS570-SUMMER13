//
//  main.c
//  a3
//
//  Created by Alex Egg on 6/27/13.
//  Copyright (c) 2013 Alex Egg. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#define DEFAULT 6
#define BUF_SIZE 256

void wall_clock();
void count_down(int start);
int pfd2[2]; //global
int pfd1[2];

int main(int argc, const char * argv[])
{
    
    
    ssize_t numRead = -1;
    /* Note: working under the assumption that the messages
     are of equal length*/
    const char* messageOne = "Hello from child ONE.\n";
    const char* messageTwo = "Hello from child TWO.\n";
    
    const unsigned int commLen = strlen(messageOne) + 1;
    
    char buf[BUF_SIZE];
    
    if (pipe(pfd1) == -1)
    {
        printf("Error opening pipe 1!\n");
        exit(1);
    }
    
    if (pipe(pfd2) == -1)
    {
        printf("Error opening pipe 2!\n");
        exit(1);
    }
    
    printf("Piped opened with success. Forking ...\n");
    
    // child 1
    switch (fork())
    {
        case -1:
            printf("Error forking child 1!\n");
            exit(1);
            
        case 0:
            wall_clock();
            exit(1);
            
        default:
            break;
    }
    
    // child 2
    switch (fork())
    {

        case -1:
            printf("Error forking child 2!\n");
            exit(1);
        case 0:
            count_down(DEFAULT);
            exit(1);
        default:
            break;
    }
    
    printf("Parent closing pipes.\n");
    
    if (close(pfd1[0]) == -1)
    {
        printf("Error closing reading end of the pipe.\n");
        exit(EXIT_FAILURE);
    }
    
    if (close(pfd2[1]) == -1)
    {
        printf("Error closing writing end of the pipe.\n");
        exit(EXIT_FAILURE);
    }
    
    if (close(pfd2[0]) == -1)
    {
        printf("Error closing reading end of the pipe.\n");
        exit(EXIT_FAILURE);
    }
    
    if (close(pfd1[1]) == -1)
    {
        printf("Error closing writing end of the pipe.\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Parent waiting for children completion...\n");
   
    
    if (wait(NULL) == -1)
    {
        printf("Error waiting.\n");
        exit(EXIT_FAILURE);
    }
    if (wait(NULL) == -1)
    {
        printf("Error waiting55.\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Parent finishing.\n");
    exit(EXIT_SUCCESS);
    
}

void count_down(int start)
{
    int pipe[2];
    char buf[100];
    strcpy(buf, "time to die");
    
    printf("\nChild 2 executing...\n");
    /* close reading end of second pipe */
    if (close(pfd2[0]) == -1)
    {
        printf("Error closing reading end of pipe 2.\n");
        _exit(1);
    }
    /* close writing end of first pipe */
    if (close(pfd1[1]) == -1)
    {
        printf("Error closing writing end of pipe 1.\n");
        _exit(1);
    }
    
    if (close(pfd1[0]) == -1)
    {
        printf("Error closing reading end of pipe 1.\n");
        _exit(EXIT_FAILURE);
    }
    
    
    for( ;start>0; start--)
    {
        //hack around blocking read in wall-clock
        write(pfd2[1], "asdf",4);
        //close(pfd2[1]);
        sleep(1);
    }

    //signal to sibling to DIE
    write(pfd2[1], buf, sizeof(buf));
    
    if (close(pfd2[1]) == -1)
    {
        printf("Error closing writing end of pipe 2.");
        _exit(EXIT_FAILURE);
    }
    
    printf("countdown returning to parent\n");
    _exit(1);
}

void wall_clock()
{
    
   // int pipe[2];
    char buff[12];
    char str1[12];
    strcpy(str1, "time to die");
    
    time_t now;
    struct tm *lcltime;
    
    if (close(pfd1[0]) == -1)
    {
        printf("Error closing reading end of pipe 1.\n");
        _exit(1);
    }
    /* close writing end of second pipe */
    if (close(pfd2[1]) == -1)
    {
        printf("Error closing writing end of pipe 2.\n");
        _exit(1);
    }
    /* close writing end of second pipe */
    if (close(pfd1[1]) == -1)
    {
        printf("Error closing writing end of pipe 1.\n");
        _exit(1);
    }
    

    
    for(;;)
    {
        
        now = time ( NULL );
        lcltime = localtime ( &now );
        
        printf ( "The time is %d:%d:%d\n", lcltime->tm_hour, lcltime->tm_min, lcltime->tm_sec );
        
        sleep(1);
        
        
        int status = read(pfd2[0], buff, 12);
        printf("read status: %d, buff=%s\n", status, buff);
        
        
        
        int ret = strcmp(str1, buff);
        if(ret==0)
        {
            if (close(pfd2[0]) == -1)
            {
                printf("Error closing writing end of pipe 2.\n");
                _exit(1);
            }
            
            
            printf("wall_clock returning to parent\n");
            _exit(1);
            
        }
      
    }
    
}

