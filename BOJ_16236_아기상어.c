// # 16236. 아기 상어
#include <stdio.h>

int N;
int map[22][22];
int fcnt;   // 전체 물고기 수
int ecnt;   // 성장 전 먹은 물고기 수
int sw = 2;     // 상어 크기
int sr, sc; // 상어 위치
typedef struct st1{
    int r, c, w;
}FISH;
FISH afish[20*20];  // 물고기 위치 담아놓은 배열

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1 ,0 ,0};
int WP, RP;
typedef struct st2{
    int r, c;
}POS;
POS QUE[20*20];

void InQueue(int r, int c)
{
    QUE[WP].r = r;
    QUE[WP++].c = c;
}

POS OutQueue(void)
{
    return QUE[RP++];
}

void Input(void)
{
    int i, j;
    scanf("%d", &N);
    for(i=1; i<=N; i++)
    {
        for(j=1; j<=N; j++)
        {
            scanf("%d", &map[i][j]);
            if(map[i][j] == 9)
            {
                sr = i, sc = j;
                map[i][j] = 0;
            }
            else if(map[i][j])
            {
                afish[fcnt].r = i;
                afish[fcnt].c = j;
                afish[fcnt++].w = map[i][j];
            }
        }
    }

    for(i=0; i<=N+1; i++)
    {
        map[i][0] = map[i][N+1] = map[0][i] = map[N+1][i] = 100;
    }
}

int BFS(void)
{
    int visited[22][22] = {0};
    POS out;
    int i, nr, nc;
    int min = 499, minidx;
    int tmp;

    WP = RP = 0;
    visited[sr][sc] = 1;
    InQueue(sr,sc);
    
    while(WP>RP)
    {
        out = OutQueue();
        for(i=0; i<4; i++)
        {
            nr = out.r + dr[i];
            nc = out.c + dc[i];
            if(visited[nr][nc] || map[nr][nc] > sw) continue;
            visited[nr][nc] =  visited[out.r][out.c] + 1;
            InQueue(nr, nc);
        }
    }

    for(i=0; i<fcnt; i++)
    {
        if(afish[i].w >= sw) continue;
        tmp = visited[afish[i].r][afish[i].c];
        if(tmp && tmp < min)
        {
            min = visited[afish[i].r][afish[i].c];
            minidx = i;
        }
    }

    if(min == 499) return 0;

    sr = afish[minidx].r;
    sc = afish[minidx].c;
    map[sr][sc] = 0;
    afish[minidx].w = 30;
    return min - 1;
}

int Get_Sol(void)
{
    int i;
    int minidx, min;
    int tmp;
    int time = 0;

    while(1)
    {
        tmp = BFS();
        if(tmp == 0) break;
        time += tmp;

        if(++ecnt == sw)
        {
            sw++;
            ecnt = 0;
        }
        if(sw*(sw-1)/2 - 1  + ecnt == fcnt) break;
    }
    return time;
}

int main(void)
{
    Input();
    printf("%d\n", Get_Sol());
    return 0;
}
