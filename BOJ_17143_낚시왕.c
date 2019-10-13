// #17143. 낚시왕
#include <stdio.h>

int R, C, M;
int arr1[110][110];
int arr2[110][110];
int (*write)[110];
int (*read)[110];
void * tmp;
int sol;
int nfish;
int sw[5] = {0, 2, 1, 4, 3};
int dd[5] = {0, -1, 1, 1, -1};

typedef struct st{
    int r, c, w, d, v;
}SHARK;
SHARK QUE[1100000];
int WP, RP;

void InQ(SHARK q)
{
    QUE[WP++] = q;
}

SHARK OutQ(void)
{
    return QUE[RP++];
}

void Input(void)
{
    int r, c, v, d, w;
    int i;
    
    write = arr1;
    read = arr2;
    
    scanf("%d %d %d", &R, &C, &M);
    for(i=0; i<M; i++)
    {
        scanf("%d %d %d %d %d", &r, &c, &v, &d, &w);
        InQ((SHARK){r, c, w, d, v});
        read[r][c] = w;
    }
}

void Move_Shark(void)
{
    int lim = WP;
    int nr, nc, nd, nv;
    SHARK out;

    while(RP < lim)
    {
        out = OutQ();
        if(out.w != read[out.r][out.c]) continue;
        read[out.r][out.c] = 0;
        nd = out.d;
        // 상하 이동
        if(nd <= 2)
        {
            nv = out.v % (2*(R-1));
            nr = out.r + dd[nd] * nv;
            nc = out.c;
            while(1)
            {
                if(nr < 1)
                {
                    nd = sw[nd];
                    nr = 2-nr;
                }
                else if(nr > R)
                {
                    nd = sw[nd];
                    nr = 2*R - nr;
                }
                else if(nr == 1 || nr == R)
                {
                    nd = sw[nd];
                    break;
                }
                else break;
            }
        }

        // 좌우 이동
        else
        {
            nv = out.v % (2*(C-1));
            nr = out.r;
            nc = out.c + (dd[nd] * nv);
            while(1)
            {
                if(nc < 1)
                {
                    nd = sw[nd];
                    nc = 2-nc;
                }
                else if(nc > C)
                {
                    nd = sw[nd];
                    nc = 2*C - nc;
                }
                else if(nc == 1 || nc == C)
                {
                    nd = sw[nd];
                    break;
                }
                else break;
            }
        }

        if(out.w <= write[nr][nc]) continue;
        write[nr][nc] = out.w;
        InQ((SHARK){nr, nc, out.w, nd, out.v});
    }
    tmp = write;
    write = read;
    read = tmp;
}

int Get_Weight(int i)
{
    int j, tmp;
    for(j=1; j<=R; j++)
    {
        if(read[j][i])
        {
            nfish++;
            tmp = read[j][i];
            read[j][i] = 0;
            return tmp;
        }
    }
    return 0;
}

int main(void)
{
    int i;

    Input();
    for(i=1; i<=C; i++)
    {
        sol += Get_Weight(i);
        if(nfish == M)  break;
        Move_Shark();
    }
    printf("%d\n", sol);
}
