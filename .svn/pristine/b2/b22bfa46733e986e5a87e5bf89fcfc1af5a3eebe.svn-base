/*CS-43203: Systems Programming
Name: Nafees Mahmood
Date: 2/28/2020
Assignment: Pong-final */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <curses.h>
#include <ncurses.h>
#include <sys/times.h>
#include <sys/time.h>
#include <stdint.h>

#include "pong.h"

#define PCOL 0
#define MAXNUM 3
#define MARGIN 3
#define LIFE_TOTAL 3


/* -------------Functions for the paddle------------- */
struct bar *create_bar(WINDOW *table, int height)
{
    struct bar *p;

    p = malloc(sizeof(struct bar));
    p->lower = 2;
    p->upper = 2 + height;
    place_bar(table, p);
    return p;
}

void place_bar(WINDOW * table, struct bar *paddle)
{
    int i;
    for(i = paddle->lower; i <= paddle->upper; ++i)
    {
        mvwaddch(table, i, PCOL, ACS_BLOCK);
    }
    wrefresh(table);
}

int move_bar(WINDOW *table, struct bar *paddle, int direct)
{
    if(direct == -1)
    {
        if((paddle->upper + 1) > table->_maxy)
        {
            return 0;
        }
        else
        {
            mvwaddch(table, paddle->lower, PCOL, ' ');
            ++paddle->upper;
            ++paddle->lower;
            mvwaddch(table, paddle->upper, PCOL, ACS_BLOCK);
            wrefresh(table);
            return -1;
        }
    }

    if(direct == 1)
    {
        if((paddle->lower -1) < (table->_begy + table->_yoffset))
        {
            return 0;
        }
        else
        {
            mvwaddch(table, paddle->upper, PCOL, ' ');
            --paddle->upper;
            --paddle->lower;
            mvwaddch(table, paddle->lower, PCOL, ACS_BLOCK);
            wrefresh(table);
            return 1;
        }
    }
    return 0;
}

/*---------------Functions for the ball--------------- */
struct ball *create_ball(WINDOW *table)
{
    struct ball *p;
    
    p = malloc(sizeof(struct ball));
    p->sym = '0';
    center_ball(table, p);

    return p;
}

void center_ball(WINDOW *table, struct ball *ppb)
{
    ppb->x = LINES / 2;
    ppb->y = COLS / 2;
    ppb->xd = ppb->yd = -1;
    ppb->yc = ppb->yn = 1;
    ppb->xc = ppb->xn = 3;
    mvwaddch(table, ppb->x, ppb->y, '0');
    wmove(table, 0, 0);
    wrefresh(table);
}

int move_ball(WINDOW *table, struct ball *ppb, struct bar *paddle)
{
    mvwaddch(table, ppb->x, ppb->y, ' ');  //Removes the ball
    
    if((ppb->y + ppb->yd) == table->_maxy) //Switches direction if at bottom
        ppb->yd = -1;

    if((ppb->y + ppb->yd) == table->_begy) //Switch direction if at top
        ppb->yd = 1;

    if(ppb->yc > 0) 
    {
        ppb->y += ppb->yd; //Moves the ball along the y-axis
        --ppb->yc;
    }

    //Switch direction if at paddle
    if((ppb->x + ppb->xd) == table->_maxx)
    {
        if(pong(paddle, ppb->y) == 0)
        {
            return 0;
        }
        ppb->xd = -1;
    }

    //Switch direction if at left side
    if((ppb->x + ppb->xd) == table->_begx)
        ppb->xd = 1;
    
    //Move the ball along x-axis
    if(ppb->xc > 0)
    {
        ppb->x += ppb->xd;
        --ppb->xc;
    }

    //If next point reached, keep going
    if(ppb->yc == 0 && ppb->xc == 0)
    {
        ppb->yc = ppb->yn;
        ppb->xc = ppb->xn;
        move_ball(table, ppb, paddle);
    }

    mvwaddch(table, ppb->x, ppb->y, ppb->sym);
    wrefresh(table);
    return 1;
}

int pong(struct bar *paddle, int x)
{
    if(paddle->lower < x && x < paddle->upper)
        return 1;

    else
        return 0;
}

/*---------------Functions for the Alarm---------- */

//converting milliseconds to micro seconds
void set_ticker(int n_msecs)
{
    struct itimerval new_timeset, old_timeset;
    long n_sec, n_usecs;

    n_sec = n_msecs/1000;
    n_usecs = (n_msecs % 1000) * 1000L;

    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs; //new ticker value
    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;

    if(setitimer(ITIMER_REAL, &new_timeset, &old_timeset) != 0)
    {
        printf("Error with timer..errno=%d\n", errno);
        exit(1);
    }
}

static void my_handler(int);

void millisleep(int n)
{
    signal(SIGALRM, my_handler); //set handler
    set_ticker(n); //set alarm timer
    pause(); //wait for sigalrm
}

static void my_handler(int s)
{
    set_ticker(0); //turn off ticker
}

/* --------------Main Function---------- */

void start();
void end();
int ticks = 0; //No. of signals

int main()
{
    WINDOW *table;
    WINDOW *board;
    WINDOW *endzone;
    struct bar *paddle;
    struct ball *ppb;
    struct tms st_time;
    int lives = LIFE_TOTAL;

    start();

    //create a surface and place the ball on it
    table = set_table(LINES - (MARGIN * 2), COLS - (MARGIN *2), MARGIN, MARGIN);
    ppb = create_ball(table);

    //create an endzone and place the paddle
    endzone = set_endzone(LINES - (MARGIN *2), 1, MARGIN - 1, COLS - MARGIN - 1);
    paddle = create_bar(endzone, LINES/4);

    //create the scoreboard
    board = set_scoreboard(1, COLS - (MARGIN *2), MARGIN - 1, MARGIN);

    setup_signal();

    if(times(&st_time) == -1) //Recording start time of game
    {
        perror("times");
        exit(EXIT_FAILURE);
    }

    int c;
    int j = KEY_UP;
    int k = KEY_DOWN;
    while((c = wgetch(table)) != 'Q')
    {
        if(c == ERR && errno != EINTR)
            break;
        
        if(c == j)
            move_bar(endzone, paddle, 1);

        if(c == k)
            move_bar(endzone, paddle, -1);
        
        while(ticks > 0)
        {
            if(move_ball(table, ppb, paddle) == 0)
            {
                if(--lives > 0)
                {
                    center_ball(table, ppb);
                    ticks = 0;
                }
                if(lives == 0)
                {
                    end();
                    printf("You have lost after %i attempts.\n", LIFE_TOTAL);
                    exit(EXIT_FAILURE);
                }
            }
            update_board(board, lives, st_time.tms_utime);
            --ticks;
        }
    }

    end();
    exit(EXIT_SUCCESS);
}

void update_board(WINDOW *board, int lives, int time)
{
    struct tms en_time;

    mvwprintw(board, 0, 0, "LIVES: %i", lives);
    times(&en_time);
    mvwprintw(board, 0, COLS/2, "Time: %j", (intmax_t)(en_time.tms_utime - time));
    wrefresh(board);
}

WINDOW *set_table(int width, int height, int x, int y)
{
    WINDOW *table;

    table = newwin(width, height, x, y);
    keypad(table, TRUE);
    wborder(table, ACS_VLINE, ' ', ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_HLINE, ACS_LLCORNER, ACS_HLINE);
    wrefresh(table);
    return table;
}

WINDOW *set_scoreboard(int width,  int height, int x, int y)
{
    WINDOW *board;
    board = newwin(width, height, x, y);
    wrefresh(board);
    return board;
}

WINDOW *set_endzone(int width, int height, int x, int y)
{
    WINDOW *endzone;

    endzone = newwin(width, height, x, y);
    wrefresh(endzone);
    return endzone;
}

void setup_signal()
{
    struct sigaction siginfo;

    signal(SIGINT, SIG_IGN); //ignore interrupts in game
    siginfo.sa_flags = 0;
    siginfo.sa_handler = add_tick;
    sigemptyset(&siginfo.sa_mask);
    sigaction(SIGALRM, &siginfo, NULL);
    set_ticker(1000/50); //set ball speed
}

void add_tick(int signal)
{
    ++ticks;
}

void start()
{
    if(initscr() == NULL)
    {
        fprintf(stderr, "initscr:failed to initialize curses");
        exit(EXIT_FAILURE);
    }

    noecho(); //disable echo of getch
    cbreak(); //disable line buffering
    halfdelay(1); //delay 1/10 of a second if no character input
    nonl(); //disable new line
    intrflush(NULL, FALSE);
    if(curs_set(0) == ERR)
    {
        fprintf(stderr, "curs_set:failed to set cursor to invisible");
        exit(EXIT_FAILURE);
    }
    srand(getpid());
}

void end()
{
    if(endwin() == ERR)
    {
        fprintf(stderr, "endwin:failed to restore terminal settings");
        exit(EXIT_FAILURE);
    }
}
