/* CS-43203: Systems Programming
Name: Nafees Mahmood
Assignment: sttyl-final */

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <unistd.h>

#ifndef FD
#define FD 0
#endif

/* -------------- Speed Functions ------------- */

struct speed{speed_t constant; char* name; };

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
    if(cfsetospeed(ttyopts, baud[i].constant) == -1)
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
    else if(c == VERASE)
    {
        printf("^?");
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

void a_in(struct attribute *row, struct termios *ttyopts, int on);
void a_out(struct attribute *row, struct termios *ttyopts, int on);
void a_local(struct attribute *row, struct termios *ttyopts, int on);
void p_in(struct attribute *row, struct termios *ttyopts);
void p_out(struct attribute *row, struct termios *ttyopts);
void p_local(struct attribute *row, struct termios *ttyopts);

struct attribute attribute_table[] = {
    { ICRNL, "icrnl", p_in, a_in },
    { ONLCR, "onlcr", p_out, a_out },
    { OLCUC, "olcuc", p_out, a_out },
    { ECHO, "echo", p_local, a_local },
    { ECHOE, "echoe", p_local, a_local },
    { ICANON, "icanon", p_local, a_local },
    { ISIG, "isig", p_local, a_local },
    { 0, NULL, 0, 0 },
};

//check the other attributes
int is_attribute(char *av)
{
    int i;
    for(i = 0; attribute_table[i].name; ++i){
        if(strcmp(attribute_table[i].name, av) == 0){
            return i;
        }
    }
    return -1;
}

void set_attribute(struct termios *ttyopts, int i, int on)
{
    attribute_table[i].setter(attribute_table+i, ttyopts, on);
}

//Mask a terminal device attribute on or off within the temporary termios structure, and set the structure
void a_opt(struct attribute *row, struct termios *ttyopts, tcflag_t *flag_p, int on)
{
    if(on == 1){
        *flag_p |= row->constant;
    }
    else{
        *flag_p &= ~(row->constant);
    }
    if(tcsetattr(FD, TCSANOW, ttyopts) == -1){
        perror("tcsetattr");
        exit(1);
    }
}

//Set device attribute settings
void a_in(struct attribute *row, struct termios *ttyopts, int on)
{
    a_opt(row, ttyopts, &ttyopts->c_iflag, on);
}

void a_out(struct attribute *row, struct termios *ttyopts, int on)
{
    a_opt(row, ttyopts, &ttyopts->c_oflag, on);
}

void a_local(struct attribute *row, struct termios *ttyopts, int on)
{
    a_opt(row, ttyopts, &ttyopts->c_lflag, on);
}

//Print each of the terminal device attributes stored in the termios structure with each respective function in the attribute_table
void print_attribute( struct termios *ttyopts )
{
	int i;
	for(i = 0; attribute_table[i].name; ++i) {
		attribute_table[i].printer(&attribute_table[i], ttyopts);
		printf(" ");
	}
	printf("\n");
}

void p_opt(struct attribute *row, int flag)
{
    if(flag & row->constant){
        printf(row->name);
    }
    else{
        printf("-%s", row->name);
    }
}

//Print whether an option stored in the termios structure is on or off using the stty syntax
void p_in(struct attribute *row, struct termios *ttyopts)
{
    p_opt(row, ttyopts->c_iflag);
}

void p_out(struct attribute *row, struct termios *ttyopts)
{
    p_opt(row, ttyopts->c_oflag);
}

void p_local(struct attribute *row, struct termios *ttyopts)
{
    p_opt(row, ttyopts->c_lflag);
}

/* ------------- Main -----------*/

int check_speed(struct termios *ttyopts, char *av);
int check_special(struct termios *ttyopts, char *av, char *next);
int check_attribute(struct termios *ttyopts, char *av);
void set_atgvs(struct termios *ttyopts, int ac, char *av[]);
void print_all(struct termios *ttyopts);
void set_argvs(struct termios *ttyopts, int ac, char *av[]);

static char *program_name;

int main(int ac, char **av)
{
    struct termios ttyopts;

    program_name = av[0];

    if(tcgetattr(FD, &ttyopts) == -1){
        perror("tcgetattr of stdin");
        exit(1);
    }

    if(ac <= 1){
        print_all(&ttyopts);
    }
    else{
        set_argvs(&ttyopts, ac, av);
    }

    exit(0);
}

//print all the terminal device settings
void print_all(struct termios *ttyopts)
{
    print_speed(ttyopts);
    print_special(ttyopts);
    print_attribute(ttyopts);
}

//Matching each argument variable parameter with available settings
void set_argvs(struct termios *ttyopts, int ac, char *av[])
{
    int i;
    for(i = 1; i < ac; ++i){
        if(check_speed(ttyopts, av[i]) == 0){
            continue;
        }
        else if(check_special(ttyopts, av[i], av[i+1]) == 0){
            ++i;
            continue;
        }
        else if(check_attribute(ttyopts, av[i]) == 0){
            continue;
        }
        else{
            fprintf(stderr, "%s: Invalid argument `%s' \n", program_name, av[i]);
        }
    }
}

int check_speed(struct termios *ttyopts, char *av)
{
    int i = is_speed(av);
    if(i != -1){
        set_speed(ttyopts, i);
        return 0;
    }
    else{
        return -1;
    }
}

int check_special(struct termios *ttyopts, char *av, char *next)
{
    int i = is_special(av);
    if(i != -1){
        if(next == NULL){
            fprintf(stderr, "%s: Missing argument to `erase' \n", program_name);
            exit(1);
        }
        if(set_special(ttyopts, i, next) == -1){
            fprintf(stderr, "%s: Invalid integer argument `%s' \n", program_name, next);
            exit(1);
        }
        return 0;
    }
    return -1;
}

int check_attribute(struct termios *ttyopts, char *av)
{
    int on = 1;
    if(av[0] == '-'){
        on = 0;
        ++av;
    }
    int i = is_attribute(av);
    if(i != -1){
        set_attribute(ttyopts, i, on);
        return 0;
    }
    return -1;
}