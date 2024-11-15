#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minesweeper.h"

void fill_x(int nr_bombs, char cols[], int rows[],int h, int w, char t[h][w])
{
    int i,pc;
    for(i=0; i<nr_bombs; i++)
    {
        pc = cols[i] - 'A';
        t[rows[i]-1][pc] = 'X';
    }
}

void fill_nr(int h, int w,  char t[h][w])
{
    int i,j,c;
    for(i=0; i<h; i++)
    {
        for(j=0; j<w; j++)
        {
            c = 0;
            if(t[i][j]=='X')
            {
                continue;
            }
            if(i!=0 && t[i-1][j-1]=='X')
            {
                c++;
            }
            if(i!=0 && t[i-1][j]=='X')
            {
                c++;
            }
            if(i!=0 && j!=w-1 && t[i-1][j+1]=='X')
            {
                c++;
            }
            if(j!=0 &&t[i][j-1]=='X')
            {
                c++;
            }
            if(j !=w-1 && t[i][j+1]=='X')
            {
                c++;
            }
            if(i!=h-1 && j!=0 && t[i+1][j-1]=='X')
            {
                c++;
            }
            if(i!=h-1 && t[i+1][j]=='X')
            {
                c++;
            }
            if(i!=h-1 && j!=w-1 && t[i+1][j+1] == 'X')
            {
                c++;
            }
            if( c == 0 )
            {
                t[i][j] = '.';
            }
            else
            {
                t[i][j] = '0' + c;
            }

        }
    }
}


void create(int nr_bombs, char cols[], int rows[], int h, int w, char t[h][w])
{
    fill_x(nr_bombs, cols, rows, h, w, t);
    fill_nr(h,w,t);
}

char** init_state(int h, int w)
{
    char** a = calloc(h, sizeof(char*));
    for(int i=0; i<h; i++)
    {
        a[i] = calloc(w, sizeof(char));
    }
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            a[i][j] = '?';
        }
    }
    return a;
}

void discover_point(int i, int j, int h, int w, char t[h][w], char** s)
{
    if(t[i][j]=='X')
    {
        return;
    }
    if (i>=h || j>=w )
    {
        return;
    }
    if( i<0 || j<0)
    {
        return;
    }
    if( s[i][j] != '?' )
    {
        return;
    }
    s[i][j] = '.';
    if(t[i][j] =='.')
    {
        discover_point(i-1,j-1,h,w,t,s);
        discover_point(i-1,j,h,w,t,s);
        discover_point(i-1,j+1,h,w,t,s);
        discover_point(i,j-1,h,w,t,s);
        discover_point(i,j+1,h,w,t,s);
        discover_point(i+1,j-1,h,w,t,s);
        discover_point(i+1,j,h,w,t,s);
        discover_point(i+1,j+1,h,w,t,s);
    }
}
int discover(int i, int j, int h, int w, char t[h][w], char** s)
{
    if(i>=h || j>=w)
    {
        printf("Dimensiunile nu exista");
        return -2;
    }
    if(t[i][j]=='X' && s[i][j] != '!')
    {
        printf("Aici bomba");
        return -1;
    }
    if (s[i][j] == '.' || s[i][j] == '!')
    {
        return 0;
    }
    discover_point(i,j,h,w,t,s);
    return 1;
}

void mark(int i, int j, int h, int w, char** s)
{
     if (i>=h || j>=w )
    {
        return;
    }
    if( i<0 || j<0)
    {
        return;
    }
    if( s[i][j] == '!' )
    {
        s[i][j] = '?';
        return;
    }
    if( s[i][j] != '?' )
    {
        return;
    }
    s[i][j]='!';
}
void player_view(int h, int w, char t[h][w], char** s)
{
    for( int i = 0; i< h; i++)
    {
        for(int j=0; j<w; j++)
        {
            if(s[i][j] == '.')
            {
                printf("%c",t[i][j]);
            }
            else
            {
                printf("%c",s[i][j]);
            }
        }
        if(i == 0)
        {
            printf("\t Legenda:");
        }
        if( i == 1 )
        {
            printf("\t ? - pozitie nedescoperita");
        }
        if(i == 2)
        {
            printf("\t ! - pozitie marcata");
        }
        printf("\n");
    }

}

void Play(int h, int w, char t[h][w], char** s, int nr_bombs)
{
    int ok = 1, win, i,j, marked;
    struct command c;
    marked = 0;
    int diff_ch = 'A'-'a'; //conversie litera mica in litera mare
    while(ok!=-1) //in discover returneaza -1 la aici bomba
    {
        win = 0;
        for(i=0;i<h;i++)
        {
            for(j=0;j<w;j++)
            {
                if(s[i][j]=='?')
                {
                    win = 1;
                }
            }
        }
        if(win == 0 && marked == nr_bombs)
        {
            printf("Ai castigat!!!");
            ok = -1;
            continue;
        }
        if(ok!=-2 && ok!=0)
        {
            player_view(h,w,t,s);
        }
        printf("\n");
        printf("Tip comanda: ");
        scanf("\n%c", &c.type);
        printf("Coloana: ");
        scanf("\n%c", &c.col);
        printf("Randul: ");
        scanf("\n%d",&c.row);

        if(c.col>='a' && c.col <='z')
        {
            c.col = c.col+diff_ch;
        }
        if(c.col>='A' && c.col <='Z')
        {
            j = c.col - 'A';
        }
        else
        {
            printf("Coloana nu este valida\n");
            ok = 0;
            continue;
        }
        if(c.type == '.')
        {
            ok = discover(c.row-1,j,h,w,t,s);
            continue;
        }
        if(c.type == '!' && s[c.row-1][j] == '?')
        {
            mark(c.row-1,j,h,w,s);
            marked++;
            ok = 1;
            continue;
        }
        if(c.type == '!' && s[c.row-1][j] == '!')
        {
            mark(c.row-1,j,h,w,s);
            marked--;
            ok = 1;
            continue;
        }
        ok=0;
    }

}


