#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    pid_t pid1, pid2;
    int rv;
    int status1, status2;
    int stop;
    int i=1;
        switch(pid1=fork()) 
       {
        case -1:
            perror("fork1");
            exit(1);
        case 0:
           printf("It is child\n");
           printf("my pid is %d \n", getpid());
           printf("my ppid is %d \n", getppid());
           scanf("%d", &rv);
           exit(rv);
        default:
            printf("It is parent");
            printf("my pid is %d \n", getpid());
            printf("my child pid is %d \n", pid1);
            printf("wait for my child\n");
            waitpid(pid1, &status1,0);
            printf("PARENT: exit status of my child is %d\n",
                   WEXITSTATUS(rv));
        }
            system("ls -l");
            switch(pid2=fork())
           {
            case -1:
                 perror("fork2");
                 exit(1);
            case 0:
                 printf("I will open a new terminal\n");
                 execl("/bin/bash", "bash", "-c", "gnome-terminal", (char *) 0);
exit(0);
            default:
                // int i=1;
                 waitpid(pid2, &status2, 0);
                 printf("parent of fork2");
                 setsid();
		 daemon(0, 0);
                 printf("kill me, if you want, my pid is: %d\n", getpid());
		 while (1)
                     {
                      printf("%d", i++);
                      sleep(1);
                     }
                       
            
            }
           //printf("Do you want to stop this program?\n");
           //scanf("%c", &stop);
           //if ( stop=='y')
           //kill(, -9);
       

    return 0;
}
