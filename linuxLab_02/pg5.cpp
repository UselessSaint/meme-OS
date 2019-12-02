#include <sys/types.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
#include <signal.h>

void catch_sig(int sig_numb)
{
    printf("\nSig. Catch. Numb = %d, Proc. = %d\n", sig_numb, getpid());
}

int main(void)
{
    pid_t childpid1;
    pid_t childpid2;
    pid_t ret_value;
    int status;
    int fd[2];
    
    char msg1[] = "Hello ";
    char msg2[] = "World!";
    
    char buff[64] = { 0 };
    
    signal(SIGINT, catch_sig);
    
    if (pipe(fd) == -1)
    {
        perror("Can't pipe");
        exit(1);
    }
    
    if ((childpid1 = fork()) == -1)
    {
        perror("Can't fork");
        exit(3);
    }
    else if (childpid1 == 0)
    {
        close(fd[0]);
        write(fd[1], msg1, sizeof(msg1)-1);
        return 1;
    }
    
    if ((childpid2 = fork()) == -1)
    {
        perror("Can't fork");
        exit(3);
    }   
    else if (childpid2 == 0)
    {   
        sleep(3);
        close(fd[0]);
        write(fd[1], msg2, sizeof(msg2)-1);
        return 2;
    }

    if (childpid1 != 0 && childpid2 != 0)       
    {
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
        
        close(fd[1]);
        read(fd[0], buff, sizeof(buff));
        std::cout << buff << "\n";
        
        return 0; 
    }
    
}