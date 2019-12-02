#include <sys/types.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    pid_t childpid1;
    pid_t childpid2;
    pid_t ret_value;
    int status;
    
    if ((childpid1 = fork()) == -1)
    {
        perror("Can't fork");
        exit(3);
    }
    else if (childpid1 == 0)
    {
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
            
        return 2;
    }

    if (childpid1 != 0 && childpid2 != 0)
    {
        printf("\nParent Pid = %d, Child1 pid = %d, GR_id = %d\n", getpid(), childpid1, getpgrp());
        printf("\t\t   Child2 pid = %d\n", childpid2);
         
        ret_value = wait( &status );
            
        if ( WIFEXITED(status) )
            printf("Parent: child %d finished with %d code.\n", ret_value, WEXITSTATUS(status) );
        else if ( WIFSIGNALED(status) )
			printf( "Parent: child %d finished from signal with %d code.\n\n", ret_value, WTERMSIG(status));
		else if ( WIFSTOPPED(status) )
			printf("Parent: child %d finished from signal with %d code.\n\n", ret_value, WSTOPSIG(status));
        
        ret_value = wait( &status );
            
        if ( WIFEXITED(status) )
                printf("Parent: child %d finished with %d code.\n", ret_value, WEXITSTATUS(status) );
        else if ( WIFSIGNALED(status) )
			printf( "Parent: child %d finished from signal with %d code.\n\n", ret_value, WTERMSIG(status));
		else if ( WIFSTOPPED(status) )
			printf("Parent: child %d finished from signal with %d code.\n\n", ret_value, WSTOPSIG(status));
            
        return 0; 
    }
    
}