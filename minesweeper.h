#ifndef MINESWEEPER_H
#define MINESWEEPER_H
void print(int h, int w, char t[h][w]);
void create(int nr_bombs, char cols[], int rows[], int h, int w, char t[h][w]);
char** init_state(int h, int w);
int discover(int i,int j,int h,int w,char t[h][w],char** s);
void mark(int i, int j, int h, int w, char** s);
void player_view(int h, int w, char t[h][w], char** s);
void run_tests();
#endif // MINESWEEPER_H




