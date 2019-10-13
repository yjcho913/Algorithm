// #16234. 인구 이동
#include <stdio.h>
#define ABS(x) ((x) > 0 ? (x) : -(x))

int map[52][52];
int N, L, R;
int visited[52][52];
int rlst[2500];
int clst[2500];
int pops;
int cnt;
typedef struct st{
    int r, c;
}POS;
POS QUE[2500];
int WP, RP;
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};
int flag = 1;

void InQ(POS p)
{
    QUE[WP++] = p;
}

POS OutQ(void)
{
    return QUE[RP++];
}

void Input(void)
{
    int i, j;

    scanf("%d %d %d", &N, &L, &R);
    for(i=1; i<=N; i++)
    {
        for(j=1; j<=N; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
}

void BFS(int r, int c, int t)
{
    int pop;
    POS out;
    int i;
    int nr, nc;
    int diff;

    cnt = 0;
    pops = map[r][c];
    WP = RP = 0;
    InQ((POS){r, c});
    visited[r][c] = t;
    rlst[cnt] = r;
    clst[cnt++] = c;
    
    while(WP > RP)
    {
        out = OutQ();
        for(i=0; i<4; i++)
        {
            nr = out.r + dr[i];
            nc = out.c + dc[i];
            if(visited[nr][nc] == t || map[nr][nc] == 0) continue;
            diff = ABS(map[nr][nc] - map[out.r][out.c]);
            if(diff < L || diff > R) continue;
            rlst[cnt] = nr;
            clst[cnt++] = nc;
            pops += map[nr][nc];
            flag = 0;
            visited[nr][nc] = t;
            InQ((POS){nr,nc});
        }
    }

    pop = pops / cnt;
    for(i=0; i<cnt; i++)
    {
        map[rlst[i]][clst[i]] = pop;
    }
}

int Get_Sol(void)
{
    int t = 1;
    int i, j;

    while(1)
    {
        for(i=1; i<=N; i++)
        {
            for(j=1; j<=N; j++)
            {
                if(visited[i][j] == t) continue;
                BFS(i, j, t);
            }
        }
        if(flag) return t-1;
        flag = 1;
        t++;
    }
}

int main(void)
{
    Input();
    printf("%d\n", Get_Sol());
    return 0;
}
