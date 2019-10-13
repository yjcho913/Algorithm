// #14888. 연산자 끼워넣기
#include <stdio.h>

int N;
int nums[12];
int nplus, nminus, nprod, ndiv;
int max = -0x7fffffff;
int min = 0x7fffffff;

void Input(void)
{
    int i;

    scanf("%d", &N);
    for(i=0; i<N; i++)
    {
        scanf("%d", &nums[i]);
    }
    scanf("%d %d %d %d", &nplus, &nminus, &nprod, &ndiv);
}

void DFS(int L, int res)
{
    if(L>=N)
    {
        if(res < min) min = res;
        if(res > max) max = res;
        return;
    }

    if(nplus)
    {
        nplus--;
        DFS(L+1, res + nums[L]);
        nplus++;
    }
    if(nminus)
    {
        nminus--;
        DFS(L+1, res - nums[L]);
        nminus++;
    }
    if(nprod)
    {
        nprod--;
        DFS(L+1, res * nums[L]);
        nprod++;
    }
    if(ndiv)
    {
        ndiv--;
        if(res < 0) DFS(L+1, -((-res) / nums[L]));
        else DFS(L+1, res / nums[L]);
        ndiv++;
    }
}

int main(void)
{
    Input();
    DFS(1, nums[0]);
    printf("%d\n%d\n", max, min);
}
