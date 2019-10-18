// #15683. 감시
#include <stdio.h>

int R, C;
int map[10][10];
int dr[] = {0,1,0,-1};
int dc[] = {-1,0,1,0};
int zcnt, ccnt;
typedef struct st{
    int r, c, type, dir;
}CCTV;
CCTV cctv[8];
int sol;
int cinfo[6][5] = {
    {},
    {4, 0x1000, 0x0100, 0x0010, 0x0001},
    {2, 0x1010, 0x0101},
    {4, 0x1100, 0x0110, 0x0011, 0x1001},
    {4, 0x1110, 0x1101, 0x1011, 0x0111},
    {1, 0x1111}
};
int visited[10][10];
int t;
void Input(void)
{
    int i, j;

    scanf("%d %d", &R, &C);
    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            scanf("%d", &map[i][j]);
            if(map[i][j] == 0) zcnt++; 
            else if(map[i][j] < 6)
            {
                cctv[ccnt++] = (CCTV){i, j, map[i][j], 0};
            }
        }
    }
}

int Gamsi(void)
{
    int res = 0;
    int i, k;
    int tmp;
    int nr, nc;

    t++;
    for(i=0; i<ccnt; i++)
    {
        tmp = cctv[i].dir;

        for(k=0; k<4; k++)
        {
            if(tmp & 0x1)
            {
                nr = cctv[i].r;
                nc = cctv[i].c;
                while(nr>=0 && nc>=0 && nr<R && nc<C)
                {
                    if(map[nr][nc] == 6) break;
                    if(visited[nr][nc] != t) 
                    {
                        res++;
                        visited[nr][nc] = t;
                    }
                    nr += dr[k];
                    nc += dc[k];
                }
            }
            tmp = tmp >> 4;
        }
    }
    return res;
}

void DFS(int L)
{
    int res;
    int i;
    int typenum;

    if(L >= ccnt)
    {
        res = Gamsi();
        if(res > sol) sol = res;
	    return;
    }

    typenum = cctv[L].type;
    for(i=1; i<=cinfo[typenum][0]; i++)
    {
        cctv[L].dir = cinfo[typenum][i];
        DFS(L+1);
    }
}
int main(void)
{
    Input();
    DFS(0);
    printf("%d\n", zcnt - sol + ccnt);
    return 0;
}
