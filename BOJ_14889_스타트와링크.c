// #14889. 스타트와 링크
#if 01
#include <stdio.h>
#define ABS(x) ((x)>0?(x):-(x))

int stat[21][21];
int N;
int sol = 0x7fffffff;
int lst[11];

void Input(void)
{
	int i, j;

	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &stat[i][j]);
		}
	}
}

int Calc_Diff(void)
{
	int i, j;
	int oneteam = 0, zeroteam = 0;

	for (i = 1; i <= N; i++)
	{
		if (lst[i]) continue;

		for (j = i + 1; j <= N; j++)
		{
			if (lst[j]) continue;
			zeroteam += stat[i][j] + stat[j][i];
		}
	}

	for (i = 1; i <= N; i++)
	{
		if (lst[i] == 0) continue;

		for (j = i + 1; j <= N; j++)
		{
			if (lst[j] == 0) continue;
			oneteam += stat[i][j] + stat[j][i];
		}
	}
	return ABS(oneteam - zeroteam);
}

void DFS(int L, int sum, int idx)
{
	int tmp;
	int i, j, lim;

	if (L > N / 2)
	{
		tmp = Calc_Diff();
		if (tmp < sol) sol = tmp;
		return;
	}

	lim = N / 2 + L;
	for (i = idx; i <= lim; i++)
	{
		tmp = 0;
		lst[i] = 1;
		DFS(L + 1, sum + tmp, i + 1);
		lst[i] = 0;
	}
}

int main(void)
{
	Input();
	lst[1] = 1;
	DFS(2, 0, 2);
	printf("%d\n", sol);
	return 0;
}
#endif
