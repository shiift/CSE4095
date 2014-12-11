#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct BoardTag {
    int row;
    int col;
    char** src;
} Board;

typedef struct BoardTracker {
    Board* b0;
    Board* b1;
} BoardTracker;

typedef struct ThreadVars {
    BoardTracker* bt;
    int row;
    pthread_barrier_t* bar;
} ThreadVars;

Board* makeBoard(int r,int c)
{
    Board* p = (Board*)malloc(sizeof(Board));
    p->row = r;
    p->col = c;
    p->src = (char**)malloc(sizeof(char*)*r);
    int i;
    for(i=0;i<r;i++)
        p->src[i] = (char*)malloc(sizeof(char)*c);
    return p;
}
void freeBoard(Board* b)
{
    int i;
    for(i=0;i<b->row;i++)
        free(b->src[i]);
    free(b->src);
    free(b);
}

Board* readBoard(char* fName)
{
    int row,col,i,j;
    FILE* src = fopen(fName,"r");
    fscanf(src,"%d %d\n",&row,&col);
    Board* rv = makeBoard(row,col);
    for(i=0;i<row;i++) {
        for(j=0;j<col;j++) {
            char ch = fgetc(src);
            rv->src[i][j] = ch == '*';
        }
        char skip = fgetc(src);
        while (skip != '\n') skip = fgetc(src);
    }
    fclose(src);   
    return rv;
}

void saveBoard(Board* b,FILE* fd)
{
    int i,j;
    for(i=0;i<b->row;i++) {
        fprintf(fd,"|");
        for(j=0;j < b->col;j++) 
            fprintf(fd,"%c",b->src[i][j] ? '*' : ' ');
        fprintf(fd,"|\n");
    }
}

void printBoard(Board* b)
{
    printf("\033\143");  /* this is to clear the terminal */
    saveBoard(b,stdout);
}

int liveNeighbors(int i,int j,Board* b)
{
    const int pc = (j-1) < 0 ? b->col-1 : j - 1;
    const int nc = (j + 1) % b->col;
    const int pr = (i-1) < 0 ? b->row-1 : i - 1;
    const int nr = (i + 1) % b->row;
    int xd[8] = {pc , j , nc,pc, nc, pc , j , nc };
    int yd[8] = {pr , pr, pr,i , i , nr , nr ,nr };
    int ttl = 0;
    int k;
    for(k=0;k < 8;k++)
        ttl += b->src[yd[k]][xd[k]];
    return ttl;
}

void evolveBoard(Board* src, Board* out, int row)
{
    static int rule[2][9] = {
        {0,0,0,1,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0}
    };
    int i,j;
    i = row;
    for(j=0;j<src->col;j++) {
        int ln = liveNeighbors(i,j,src);
        int c  = src->src[i][j];
        out->src[i][j] = rule[c][ln];
    }
}

void runThread(ThreadVars* tv){
    int i;
    for(i = 0; i < 1000; i++){
        pthread_barrier_wait(tv->bar);
        evolveBoard(tv->bt->b0, tv->bt->b1, tv->row);
        pthread_barrier_wait(tv->bar);
    }
    free(tv);
    return;
}

int main(int argc,char* argv[])
{
    Board* life1 = readBoard(argv[1]);
    Board* life2 = makeBoard(life1->row,life1->col);
    int g;
    pthread_t tids[life1->row];
    BoardTracker* bt = calloc(1, sizeof(BoardTracker));
    bt->b0 = life1;
    bt->b1 = life2;

    pthread_barrier_t* bar = calloc(1, sizeof(pthread_barrier_t));
    pthread_barrier_init(bar,NULL,life1->row+1);

    for(g=0; g<life1->row; g++){
        ThreadVars* tv = calloc(1, sizeof(ThreadVars));
        tv->bt = bt;
        tv->row = g;
        tv->bar = bar;
        pthread_create(&tids[g], NULL, (void*(*)(void*))runThread, (void *)tv);
    }
    for(g=0;g < 1000;g++) {
        bt->b0 = g & 0x1 ? life2 : life1;
        bt->b1 = g & 0x1 ? life1 : life2;
        pthread_barrier_wait(bar);
        printBoard(bt->b0);
        usleep(100000);
        pthread_barrier_wait(bar);
    }
    for(g=0; g < life1->row; g++){
        pthread_join(tids[g], NULL);
    }
    printBoard(bt->b1);
    FILE* final = fopen("finalMT.txt","w");
    saveBoard(bt->b1,final);
    fclose(final);
    pthread_barrier_destroy(bar);
    free(bar);
    free(bt);
    freeBoard(life1);
    freeBoard(life2);
    return 0;
}
