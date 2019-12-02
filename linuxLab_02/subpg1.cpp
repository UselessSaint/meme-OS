#include <iostream>
#include <sys/types.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    printf("\nProcces %d: executed subpg1.exe\n", getpid());
    
    return 0;
}