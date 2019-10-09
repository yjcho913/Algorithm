// #14500. 테트로미노
#include <stdio.h>

int N, M;
int map[500][500];
int nmax;

void Input(void)
{
    int i, j;
    scanf("%d %d", &N, &M);
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            scanf("%d", &map[i][j]);
            if(map[i][j] > nmax) nmax = map[i][j];
        }
    }
}

int Get_Sol(void)
{
    int i, j;
    int sum;
    int sol = 0;

    // 4*1
    for(j=0; j<M; j++)
    {
        if(N < 3) break;

        sum = map[0][j] + map[1][j] + map[2][j] + map[3][j];
        if(sum > sol) sol = sum;

        for(i=1; i<=N-4; i++)
        {
            sum += (-map[i-1][j] + map[i+3][j]);
            if(sum > sol) sol = sum;
        }
    }

    // 1*4
    for(i=0; i<N; i++)
    {
        if(M < 3) break;

        sum = map[i][0] + map[i][1] + map[i][2] + map[i][3];
        if(sum > sol) sol = sum;

        for(j=1; j<=M-4; j++)
        {
            sum += (-map[i][j-1] + map[i][j+3]);
            if(sum > sol) sol = sum;
        }
    }

    // 2*2
    for(i=0; i<=N-2; i++)
    {
        for(j=0; j<=M-2; j++)
        {
            if(map[i][j] + nmax*3 <= sol) continue;
            sum = map[i][j] + map[i][j+1] + map[i+1][j] + map[i+1][j+1];
            if(sum > sol) sol = sum;
        }
    }

    // 2*3
    for(i=0; i<=N-2; i++)
    {
        for(j=0; j<=M-3; j++)
        {
            sum = map[i][j] + map[i][j+1] + map[i][j+2];
            if(sum + nmax > sol) 
            {
                if(sum + map[i+1][j] > sol) sol = sum+map[i+1][j];
                if(sum + map[i+1][j+1] > sol) sol = sum+map[i+1][j+1];
                if(sum + map[i+1][j+2] > sol) sol = sum+map[i+1][j+2];
            }
            sum = map[i+1][j] + map[i+1][j+1] + map[i+1][j+2];
            if(sum + nmax > sol) 
            {
                if(sum + map[i][j] > sol) sol = sum+map[i][j];
                if(sum + map[i][j+1] > sol) sol = sum+map[i][j+1];
                if(sum + map[i][j+2] > sol) sol = sum+map[i][j+2];
            }
            sum = map[i][j] + map[i][j+1] + map[i+1][j+1] + map[i+1][j+2];
            if(sum > sol) sol = sum;
            sum = map[i+1][j] + map[i][j+1] + map[i+1][j+1] + map[i][j+2];
            if(sum > sol) sol = sum;
        }
    }

    // 3*2
    for(i=0; i<=N-3; i++)
    {
        for(j=0; j<=M-2; j++)
        {
            sum = map[i][j] + map[i+1][j] + map[i+2][j];
            if(sum + nmax > sol) 
            {
                if(sum + map[i][j+1] > sol) sol = sum+map[i][j+1];
                if(sum + map[i+1][j+1] > sol) sol = sum+map[i+1][j+1];
                if(sum + map[i+2][j+1] > sol) sol = sum+map[i+2][j+1];
            }
            sum = map[i][j+1] + map[i+1][j+1] + map[i+2][j+1];
            if(sum + nmax > sol) 
            {
                if(sum + map[i][j] > sol) sol = sum+map[i][j];
                if(sum + map[i+1][j] > sol) sol = sum+map[i+1][j];
                if(sum + map[i+2][j] > sol) sol = sum+map[i+2][j];
            }
            sum = map[i][j] + map[i+1][j] + map[i+1][j+1] + map[i+2][j+1];
            if(sum > sol) sol = sum;
            sum = map[i][j+1] + map[i+1][j] + map[i+1][j+1] + map[i+2][j];
            if(sum > sol) sol = sum;
        }
    }
    return sol;
}

int main(void)
{
    Input();
    printf("%d\n", Get_Sol());
    return 0;
}
