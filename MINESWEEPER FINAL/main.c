#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minesweeper.h"

int main()
{
    int h, w;
    printf("Introduceti dimensiunile tablei: ");
    printf("h= ");
    scanf("%d", &h);
    printf("w= ");
    scanf("%d", &w);
    char t[h][w];
    char col[5];
    col[0] = 'B';
    col[1] = 'D';
    int row[5];
    row[0] = 1;
    row[1] = 2;
    create(2, col, row, h, w, t);
    char** s = init_state(h,w);
    int i, j;
    for(i=0; i<h; i++)
    {
        for(j=0; j<w; j++)
        {
            printf("%c", t[i][j]);
        }
        printf("\n");
    }
    printf("\n");

   
    int ok = 1;
      while(ok!=-1)
    {
        if(ok!=-2 && ok!=0)
        {
            for(i=0; i<h; i++)
            {
                for(j=0; j<w; j++)
                {
                    printf("%c", s[i][j]);
                }
                printf("\n");
            }
        }
        printf("\n");
        printf("i= ");
        scanf("%d", &i);
        printf("j= ");
        scanf("%d",&j);
        ok = discover(i,j,h,w,t,s);
    }
    */

    printf("\n");
    char input_command[1000] = "A1 !B2!B2 A1A1 a103";
    struct command v[100];
    int p = 0;
    int diff_ch = 'A'-'a';
    printf("%s\n", input_command);
    for(int i=0; i<strlen(input_command); i++)
    {
        if(input_command[i] >= 'a' && input_command[i] <= 'z')
        {
            input_command[i] = input_command[i]+diff_ch ;

        }
        if(input_command[i] >= 'A' && input_command[i] <= 'Z')
        {
            if( input_command[i-1] == '!' )
            {
                v[p].type = '!';
            }
            else
            {
                v[p].type = '.';
            }
            v[p].col = input_command[i];
            j = i+1;
            while(input_command[j] >= '0' && input_command[j] <= '9')
            {
                j++;
            }
            j--;
            if(input_command[j] == '0' && (isalpha(input_command[j+1]) || input_command[j+1] == '!'))
            {
                j--;
            }
            v[p].row = 0;
            for( int k=i+1; k<=j; k++)
            {
                v[p].row = v[p].row * 10 + (input_command[k] - '0');
            }
            p++;
clear:
            row; // se sterge valoarea din variabila row daca nu se introduce nimic bun sa nu fie pb
        }
    }
    for(i = 0; i < p; i++)
    {
        printf("%c %c %d\n", v[i].type, v[i].col, v[i].row);
    }

    Play(h,w,t,s,5);
    return 0;
}

