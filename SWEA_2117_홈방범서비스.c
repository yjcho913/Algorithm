// #2117. 홈 방범 서비스
#if 01
#include <stdio.h>
#define ABS(x) ((x)>0?(x):-(x))

int N;
int M;
int rs[400];
int cs[400];
int rmax, cmax;
int hcnt;

void Input(void)
{
	int i, j, num;
	scanf("%d %d", &N, &M);

	for (i = 0; i<N; i++)
	{
		for (j = 0; j<N; j++)
		{
			scanf("%d", &num);
			if (num)
			{
				rs[hcnt] = i;
				cs[hcnt++] = j;
				if (i > rmax) rmax = i;
				if (j > cmax) cmax = j;
			}
		}
	}
}

int Get_Sol(void)
{
	int cost[40];
	int i, j, h, hh;
	int sol = 1;

	for (i = 0; i <= rmax; i++)
	{
		for (j = 0; j <= cmax; j++)
		{
			if (sol == hcnt) return hcnt;

			for (h = 0; h < 2 * N; h++)
			{
				cost[h] = 0;
			}

			for (h = 0; h < hcnt; h++)
			{
				cost[ABS(i - rs[h]) + ABS(j - cs[h]) + 1]++;
			}

			for (h = 2; cost[h - 1] < hcnt; h++)
			{
				cost[h] += cost[h - 1];
			}

			for (hh = h - 1; cost[hh] > sol; hh--)
			{
				if (hh * hh + (hh - 1) * (hh - 1) <= M*cost[hh])
				{
					sol = cost[hh];
					break;
				}
			}
		}
	}
	return sol;
}

int main(void)
{
	int t, T;
	scanf("%d", &T);

	for (t = 1; t <= T; t++)
	{
		hcnt = 0;
		Input();
		printf("#%d %d\n", t, Get_Sol());
	}
	return 0;
}
#endif
