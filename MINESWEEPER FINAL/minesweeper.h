#ifndef MINESWEEPER_H_INCLUDED
#define MINESWEEPER_H_INCLUDED

struct command {
   char type;
   char col;
   int row;
};

void fill_x(int nr_bombs, char cols[], int rows[],int h, int w, char t[h][w]);

void fill_nr(int h, int w, char t[h][w]);

void create(int nr_bombs, char cols[], int rows[], int h, int w, char t[h][w]);

char** init_state(int h, int w);

void discover_point(int i, int j, int h, int w, char t[h][w], char** s);

int discover(int i, int j, int h, int w, char t[h][w], char** s);

void mark(int i, int j, int h, int w, char** s);

void player_view(int h, int w, char t[h][w], char** s);

void Play(int h, int w, char t[h][w], char** s, int nr_bombs);

#endif // MINESWEEPER_H_INCLUDED
