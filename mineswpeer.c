#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char tip_comanda,coloana;
    int rand;
} comanda_joc;

const int lungime_maxima_sir = 30000;
void print (int h, int w, char t[h][w])
{

    int i,j;
    char Start_Leg_Col='A',Finish_Leg_Col='A';
    printf("  ");
    for(i=0; i<w; i++)
    {
        if(Start_Leg_Col=='Z')
        {
            Start_Leg_Col='a';
        }
        printf("%c",Start_Leg_Col);
        Start_Leg_Col++;
    }
    printf("\n");
    for(i=0; i<h; i++)
    {
        for(j=0; j<w; j++)
        {
            if(j==0)
            {
                printf("%d ",i+1);
            }
            printf("%c",t[i][j]);
            if(j==w-1)
            {
                printf(" %d",i+1);
            }
        }
        printf("\n");
    }
    printf("  ");
    for(i=0; i<w; i++)
    {
        if(Finish_Leg_Col=='Z')
        {
            Finish_Leg_Col='a';
        }
        printf("%c",Finish_Leg_Col);
        Finish_Leg_Col++;
    }

}

void initializare(char h,char w,char t[h][w])
{
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
            t[i][j]='0';
    }

}


void create(int nr_bombs,char cols[],int rows[],int h, int w, char t[h][w])
{
    int i,j;
    initializare(h,w,t);

    for(i=0; i<nr_bombs; i++)
    {
        int row = rows[i]-1;
        int col = cols[i]-'A';
        if(row >= h || col >= w || row <0 || col < 0){
            continue;
        }
        t[row][col]='X';
        if(rows[i]-2>=0)
        {
            if(cols[i]-'A'-1>=0)
            {
                if(t[rows[i]-2][cols[i]-'A'-1]!='X')t[rows[i]-2][cols[i]-'A'-1]++;
            }
            if(t[rows[i]-2][cols[i]-'A']!='X') t[rows[i]-2][cols[i]-'A']++;
            if(cols[i]-'A'+1<w)
            {
                if(t[rows[i]-2][cols[i]-'A'+1]!='X')t[rows[i]-2][cols[i]-'A'+1]++;
            }

        }
        if(cols[i]-'A'-1>=0)
        {
            if(t[rows[i]-1][cols[i]-'A'-1]!='X') t[rows[i]-1][cols[i]-'A'-1] ++;
        }
        if(cols[i]-'A'+1<w)
        {
            if(t[rows[i]-1][cols[i]-'A'+1]!='X')t[rows[i]-1][cols[i]-'A'+1]++;
        }
        if(rows[i]<h)
        {
            if(cols[i]-'A'-1>=0)
            {
                if(t[rows[i]][cols[i]-'A'-1]!='X') t[rows[i]][cols[i]-'A'-1]++;
            }
            if(t[rows[i]][cols[i]-'A']!='X')t[rows[i]][cols[i]-'A']++;
            if(cols[i]-'A'+1<w)
            {
                if(t[rows[i]][cols[i]-'A'+1]!='X')t[rows[i]][cols[i]-'A'+1]++;
            }
        }
    }

    for(i=0; i<h; i++)
    {
        for(j=0; j<w; j++)
            if(t[i][j]=='0') t[i][j]='.';
    }

}

char** init_state(int h,int w)
{
    char** st=(char **) malloc(h*sizeof(char*));
    for(int i=0; i<h; i++)
        *(st+i)=(char *)malloc(w*sizeof(char));

    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
            *(*(st+i)+j)='?';
    }
    return st;
}

int discover(int i,int j,int h,int w, char t[h][w],char** s)
{
    if(i<0) return -2;
    if(j<0) return -2;
    if(i>=h) return -2;
    if(j>=w) return -2;
    if(t[i][j]=='X') return -1;
    if( *(*(s+i)+j)=='.') return 0;
    if(isdigit(t[i][j])>0)
    {
        *(*(s+i)+j)='.';
        return 1;
    }
    if(t[i][j]=='.')
    {
        *(*(s+i)+j)='.';

        discover(i-1,j,h,w,t,s);
        discover(i-1,j+1,h,w,t,s);
        discover(i+1,j-1,h,w,t,s);
        discover(i+1,j,h,w,t,s);
        discover(i+1,j+1,h,w,t,s);
        discover(i,j-1,h,w,t,s);
        discover(i,j+1,h,w,t,s);
        discover(i-1,j-1,h,w,t,s);
        return 2;
    }

}

//void afisare(int h,int w,char** s)
//{
//    for(int i=0; i<h; i++)
//    {
//        for(int j=0; j<w; j++)
//            printf("%c",*(*(s+i)+j));
//        printf("\n");
//    }
//}

void mark(int i, int j, int h, int w, char** s)
{
    int ok1=0,ok2=0;
    if(i>=0 && i<h) ok1=1;
    if(j>=0 && j<w) ok2=1;
    if(ok1*ok2==1)
    {
        if(s[i][j]=='?') s[i][j]='!';
        else if(s[i][j]=='!') s[i][j]='?';

    }

}

void player_view(int h, int w, char t[h][w], char** s)
{


    char Start_Leg_Col='A',Finish_Leg_Col='A';
    printf("  ");
    for(int i=0; i<w; i++)
    {
        if(Start_Leg_Col=='Z')
        {
            Start_Leg_Col='a';
        }
        printf("%c",Start_Leg_Col);
        Start_Leg_Col++;
    }
    printf("\n");
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            if(j==0)
            {
                printf("%d ",i+1);
            }
            if(s[i][j]=='.')
                printf("%c",t[i][j]);
            else printf("%c",s[i][j]);
            if(j==w-1)
            {
                printf(" %d",i+1);
            }
        }
        printf("\n");
    }
    printf("  ");
    for(int i=0; i<w; i++)
    {
        if(Finish_Leg_Col=='Z')
        {
            Finish_Leg_Col='a';
        }
        printf("%c",Finish_Leg_Col);
        Finish_Leg_Col++;
    }


}

//VVVVVVVVVVVVVVVVVVVVVV   rezolvare tema 12   VVVVVVVVVVVVVVVVVVVVV//



typedef struct
{
    int rez_comenzi;
    unsigned long long int hhash;
} result;

void readNextTest( FILE *fp,int *h, int*w,int *numbombs,int rows[],char cols[],char commands[])
{
    int pos,pos2;
    fgets (commands, lungime_maxima_sir, fp);
    sscanf(commands,"%d %d %d %n ",h,w,numbombs,&pos);
    sscanf(commands+pos," %s%n",cols,&pos2);
    pos+=pos2;

    for(int i=0; i<*numbombs; i++)
    {
        sscanf(commands+pos,"%d%n",rows +i,&pos2);
        pos+=pos2;

    }

    fgets (commands, lungime_maxima_sir, fp);
}

void dezalocare(int *rows,char *cols,comanda_joc* commands)
{
    free(rows);
    free(cols);
    free(commands);
}

comanda_joc* comenzi(char commandsString[],int *nr_comenzi,comanda_joc commands[])
{
    const int max_nr_commands = 101;
    *nr_comenzi = 0;
    char *p = commandsString;
    int z,x;
    char s1[200]="",c;
    char* k;
    while(p < commandsString + strlen(commandsString) && ((*nr_comenzi) < max_nr_commands))
    {
        z= sscanf(p," %c%d",&c,&x);

        if(z==2)
        {
            commands[*nr_comenzi].tip_comanda='.';
            commands[*nr_comenzi].rand=x;
            commands[*nr_comenzi].coloana=c;
            sprintf(s1,"%d",x);
            k=strstr(p,s1);
            (*nr_comenzi)++;
        }

        else
        {
            z = sscanf(p," !%c%d",&c,&x);
            if(z == 2)
            {
                commands[*nr_comenzi].tip_comanda='!';
                commands[*nr_comenzi].rand=x;
                commands[*nr_comenzi].coloana=c;
                sprintf(s1,"%d",x);
                k=strstr(p,s1);
                (*nr_comenzi)++;
            }
            else
            {
                break;
            }

        }
        p=k+strlen(s1);


    }

    return commands;

}
int convert(char c)
{
    if(c>='A' && c<='Z')
        return c-'A';
    if(c>='a' && c<='z')
        return c-'a'+26;
    return -1;
}

unsigned long long int dispersie(int h,int w,char** s)
{
    unsigned long long p=1;
    unsigned long long rez=0;
    unsigned long long a;
    for(int i=0; i<=h-1; i++)
    {
        for(int j=0; j<=w-1; j++)
        {
            a = (unsigned long long )s[i][j];
            rez=rez+a*p;
            p*=5;
        }


    }
    return rez;
}

int finishGame(int h, int w,char t[h][w], char **s){
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++){
            if(t[i][j] !='X' && s[i][j] !='.'){
                return 0;
            }
        }

    }
    return 1;
}

void dezalocate(int h, char **s){
    for(int i = 0; i < h; i ++){
        free(s[i]);
    }
    free(s);
}


result solve_problem(int nr_bombs,char cols[],int rows[],int h,int w,comanda_joc commands[],int nr_comenzi)
{
    result r;
    char t[h][w];
    create(nr_bombs,cols,rows,h,w,t);
    char **s = init_state(h,w);

    int lost=0;
    int win = 1;


    for(int nr_comanda=0; nr_comanda<nr_comenzi; nr_comanda++)
    {
        if(finishGame(h,w,t,s) == 1){
            break;
        }


        comanda_joc command = commands[nr_comanda];
        int i = command.rand-1;
        int j = convert(command.coloana);
        if(i >= h || j >= w || i <0 || j < 0){
            continue;
        }
        if(command.tip_comanda == '!')
        {
            mark(i,j,h,w,s);
        }
        else
        {
            if(t[i][j]=='X')
            {
                lost=1;
                break;
            }
            discover(i,j,h,w,t,s);
        }
    }

    win = finishGame(h,w,t,s) == 1;
    r.hhash=dispersie(h,w,s);

    if(lost==1) r.rez_comenzi=-1;
    else if(win==1) r.rez_comenzi=1;
    else r.rez_comenzi=0;

    dezalocate(h,s);
    return r;
}

void run_tests()
{

    FILE *fp = fopen("minesweeper.in", "r");
    FILE *out_file = fopen("minesweeper.out", "w");
    int nr_bombs=2;
    char cols[5300];
    int rows[5300];
    int h=3,w=6,nrteste;
    char **t ;
    char** s;
    char x[lungime_maxima_sir];
    fgets (x, lungime_maxima_sir, fp);
    sscanf(x,"%d",&nrteste);


    for (int test=0; test<nrteste; test++)
    {
        readNextTest(fp,&h,&w,&nr_bombs,rows,cols,x);
        int nr_commands=0;
        comanda_joc commands[101];
        comenzi(x,&nr_commands,commands);
        result r=solve_problem(nr_bombs,cols,rows,h,w,commands,nr_commands);
        fprintf(out_file,"%d %llu\n",r.rez_comenzi,r.hhash);
    }

    fclose(fp);
    fclose(out_file);
}

