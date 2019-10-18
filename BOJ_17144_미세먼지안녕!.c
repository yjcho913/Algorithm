// #17144. 미세먼지 안녕!
#include <stdio.h>

int R, C, T;
int map1[55][55];
int map2[55][55];
int (* before)[55] = map1[0];
int (* after)[55] = map2[0];
int dr[] = {0,0,1,-1};
int dc[] = {1,-1,0,0};
int upac, downac;

void Input(void)
{
    int i, j;

    scanf("%d %d %d", &R, &C, &T);
    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            scanf("%d", &before[i][j]);
            if(before[i][j] == -1)
            {
                if(upac) downac = i;
                else upac = i;
            }
        }
    }
}

void Diffuse(void)
{
    int i, j, k;
    int tmp;
    int nr, nc;
    int (* tptr)[55];

    for(j=0; j<C; j++) after[0][j] = before[0][j];

    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            after[i+1][j] = before[i+1][j];
            if(before[i][j] <= 0) continue;
            tmp = before[i][j]/5;
            
            for(k=0; k<4; k++)
            {
                nr = i + dr[k];
                nc = j + dc[k];
                if(nr < 0 || nc < 0 || nr >= R || nc >= C || before[nr][nc] == -1) continue;
                after[nr][nc] += tmp;
                after[i][j] -= tmp;
            }
        }
    }

    tptr = after;
    after = before;
    before = tptr;
}

void Operate_AC(void)
{
    int i, j;
    
    for(i=upac-1; i>0; i--) before[i][0] = before[i-1][0];
    for(j=0; j<C-1; j++) before[0][j] = before[0][j+1];
    for(i=0; i<upac; i++) before[i][C-1] = before[i+1][C-1];
    for(j=C-1; j>=2; j--) before[upac][j] = before[upac][j-1];

    for(i=downac+1; i<R-1; i++) before[i][0] = before[i+1][0];
    for(j=0; j<C-1; j++) before[R-1][j] = before[R-1][j+1];
    for(i=R-1; i>downac; i--) before[i][C-1] = before[i-1][C-1];
    for(j=C-1; j>=2; j--) before[downac][j] = before[downac][j-1];
    before[upac][1] = before[downac][1] = 0;
}

int Calc_Dust(void)
{
    int i, j;
    int res = 0;

    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            if(before[i][j] == -1) continue;
            res += before[i][j];
        }
    }
    return res;
}

int main(void)
{
    Input();
    while(T--)
    {
        Diffuse();
        Operate_AC();
    }
    printf("%d\n", Calc_Dust());
    return 0;
}
