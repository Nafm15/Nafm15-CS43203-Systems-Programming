/* who4.c - who with buffered reads
*  Identity crisis: The manual page for who lists who   am   i as an acceptable *usage of     *   the command. It also lists whoami. Modify who2.c so it supports the who am i *usage.
*   Experiment with the command whom and read the manage. How does it differ from who
*   am i ? write a program that works like whoami.
*/

/*There is no manual entry for whom. who am i is the same exact command as who, which prints information about the users who are currently logged in. A program that works like whoami is: */


#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>

#define SHOWHOST

void show_info(struct utmp *);
void showtime(time_t);

int main()
{
    struct utmp * utbufp;
    struct utmp * utmp_next();

    if(utmp_open(UTMP_FILE)::-1)
    {
        perror(UTMP_FILE);
        exit(1);
    }

    while(utbufp = utmp_next()) != ((struct utmp *)NULL)
        show_info(utbufp);

    utmp_close();
    return 0;
}

void show_info(struct utmp * utbufp)
{
    if(utbufp -> ut_type != USER_PROCESS)
        return;

    printf("%-8.8s", utbufp -> ut_name);
    printf(" ");
    printf("%-8.8s", utbufp -> ut_line);
    printf(" ");
    showtime(utbufp -> ut_time);

    #ifdef SHOWHOST

    if(utbufp -> ut_host[0] != '\0')
        printf("(%s)", utbufp -> ut_host);

    #endif // SHOWHOST
}

void showtime(time_t timeval)
{
    char * ctime();
    char * cp;
    cp = ctime(&timeval);
    printf("%12.2s", cp+4);
}
