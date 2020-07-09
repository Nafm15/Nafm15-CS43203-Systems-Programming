/*CS-43203: Systems Programming
Name: Nafees Mahmood
Date: 2/28/2020
Assignment: Pong-final */

// Header functions for paddle

#ifndef PADDLE
#define PADDLE

struct bar{
    int upper;
    int lower;
    int len;
};

struct bar *create_bar(WINDOW *, int);
void place_bar(WINDOW *, struct bar *);
int move_bar(WINDOW *, struct bar*, int);
#endif

// Header functions for ball

#ifndef BALL
#define BALL

struct ball{
    int x, y;
    int xd, yd; //increment direction
    int xc, yc; //position count
    int xn, yn; //increment angle
    char sym;
};

struct ball *create_ball(WINDOW *);
void center_ball(WINDOW *, struct ball *);
int move_ball(WINDOW *, struct ball *, struct bar *);
int pong(struct bar *, int);
#endif

// Header functions for sleep and ticker (Alarm)

#ifndef ALARM
#define ALARM

void set_ticker(int);
void millisleep(int);
#endif

//Main function header

#ifndef MAIN
#define MAIN

void add_tick(int);
WINDOW *set_table(int width, int height, int x, int y);
WINDOW *set_scoreboard(int width, int height, int x, int y);
WINDOW *set_endzone(int width, int height, int x, int y);
void setup_signal();
void update_board(WINDOW *board, int lives, int time);

#endif
