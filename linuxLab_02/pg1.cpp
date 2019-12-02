#include <sys/types.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    pid_t childpid1;
    pid_t childpid2;
    
    if ((childpid1 = fork()) == -1)
    {
        perror("Can't fork");
        exit(3);
    }
    else if (childpid1 == 0)
    {
        printf("\nChild Pid =  %d, Parent pid = %d, GR_id = %d\n", getpid(), getppid(), getpgrp());
        sleep(2);   
        printf("\nChild Pid =  %d, Parent pid = %d, GR_id = %d\n", getpid(), getppid(), getpgrp());
        
        return 1;
    }
    
    if ((childpid2 = fork()) == -1)
    {
        perror("Can't fork");
        exit(3);
    }   
    else if (childpid2 == 0)
    {
        printf("\nChild Pid =  %d, Parent pid = %d, GR_id = %d\n", getpid(), getppid(), getpgrp());
        sleep(2);
        printf("\nChild Pid =  %d, Parent pid = %d, GR_id = %d\n", getpid(), getppid(), getpgrp());
            
        return 2;
    }

    if (childpid1 != 0 && childpid2 != 0)
    {
        printf("\nParent Pid = %d, Child1 pid = %d, GR_id = %d\n", getpid(), childpid1, getpgrp());
        printf("\t\t   Child2 pid = %d\n", childpid2);
        
        return 0; 
    }
    
}