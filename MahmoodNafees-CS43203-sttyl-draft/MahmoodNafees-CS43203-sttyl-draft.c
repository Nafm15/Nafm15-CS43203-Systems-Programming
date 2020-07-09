/* CS-43203: Systems Programming
/* Name: Nafees Mahmood
/* Assignment: sttyl-draft 
/* This is incomplete. Still working on it, so please review it accordingly I guess */

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdef.h>


/* -------------- Speed Functions ------------- */

struct speed{speed_t constant, char* name;};

struct speed baud[] = {
    {B0, "0"},
    {B50, "50"},
    {B75, "75"},
    {B110, "110"},
    {B134, "134"},
    {B150, "150"},
	{ B200, "200"},
	{ B300, "300"},
	{ B600, "600"},
	{ B1200, "1200"},
	{ B1800, "1800"},
	{ B2400, "2400"},
	{ B4800, "4800"},
	{ B9600, "9600"},
	{ B19200, "19200"},
	{ B38400, "38400"},
	{ B57600, "57600"},
	{ B115200, "115200"},
	{ B230400, "230400"},
    {0, NULL}
};

//check baud speed
int is_speed(char *av)
{
    int i;
    for(i = 0; baud[i].name; i++)
    {
        if(strcmp(baud[i].name, av) == 0)
        {
            return i;
        }
    }
    return -1;
}

//set baud speed
void set_speed(struct termios *ttyopts, int i)
{
    if(cfsetospeed, baud[i].constant) == -1)
    {
        perror("cfsetospeed");
        exit(1);
    }
    if(tcsetattr(FD, TCSANOW, ttyopts) == -1)
    {
        perror("tcsetattr");
        exit(1);
    }
}

//print baud speed
void print_speed(struct termios *ttyopts)
{
    int cfospeed = cfgetospeed(ttyopts);
    int i;
    for(i = 0; baud[i].name; i++)
    {
        if(cfospeed == baud[i].constant)
        {
            printf("speed %s baud; \n", baud[i].name);
        }
    }
}

/* -------------------- Special (Erase, Kill) Functions ---------------- */

struct special {tcflag_t constant; char *name;};

struct special special_table[] = {
    {VINTR, "intr"},
    {VERASE, "erase"},
    {VKILL, "kill"},
    {0, NULL}
};

//check special character
int is_special(char *av)
{
    int i;
    for(i = 0; special_table[i].name; ++i)
    {
        if(strcmp(special_table[i].name, av) == 0)
        {
            return i;
        }
    }
    return -1;
}

//Set the input character to the element in the input termios special character array. Return 0 for success and -1 for failure
int set_special(struct termios *ttyopts, int i, char *c)
{
    if(isascii(*c) == 0)
    {
        return -1;
    }

    ttyopts->c_cc[special_table[i].constant] = *c;
    if(tcsetattr(FD, TCSANOW, ttyopts) == -1)
    {
        perror("tcsetattr");
        exit(1);
    }
    return 0;
}

void print_character(int c)
{
    if(isprint(c) != 0)
    {
        putchar(c);
    }
    else if(c == DEL)
    {
        printf("^");
    }
    else if(iscntrl(c) != 0)
    {
        printf("^%c", c-1+'A');
    }
}

//printing all special characters
void print_special(struct termios *ttyopts)
{
    int i;
    for(i = 0; special_table[i].name; ++i)
    {
        printf(special_table[i].name);
        printf(" = ");
        print_character(ttyopts->c_cc[special_table[i].constant]);
        printf(";");
    }
    printf("\n");
}

/* ------------------- Other Attributes ----------------- */

struct attribute{
    tcflag_t constant;
    char *name;
    void(*printer)(struct attribute *, struct termios *);
    void(*setter)(struct attribute *, struct termios *, int);
};

