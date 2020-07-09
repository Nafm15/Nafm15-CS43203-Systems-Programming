/*CS43203: Systems Programming
/Name: Nafees Mahmood
/Date: 04/03/2020
/Assignment: pipex.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define err(m,x)  {perror(m); exit(x);}

main(int ac , char **av)
{
    int pipex[3]; //File descriptors
    //int newfd;
    int pid;

    if (ac != 4)
    {
        fprintf(stderr, "usage: pipex cmd1 cmd2 cmd3\n");
        exit(1);
    }

    if (pipe(pipex) == -1)
        err("Unable to get a pipe", 1);
    
    //creating two new processes
    if( (pid = fork()) == -1)
        err("Cannot fork", 2);

    if (pid > 0)
    {
        exit(pipex[1]);

        if(dup2(pipex[0], 0) == -1)
            err("Couldn't redirect stdin", 3);

            close(pipex[0]);
            err(av[2], 4);
    }

    close(pipex[0]);
    
    if(dup2(pipex[1], 1) == -1)
        err("Couldn't redirect stdout", 4);

    close(pipex[1]);
    err(av[1], 5);
}