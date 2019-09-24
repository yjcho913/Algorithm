// #12100. 2048(Easy)
#if 01
#include <stdio.h>
#define MAX (22)

int N;
unsigned short map[11][MAX][MAX];
unsigned short max;

void Input(void)
{
	int i, j;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%hd", &map[0][i][j]);
			if (map[0][i][j] > max) max = map[0][i][j];
		}
	}
}

void Circulate_Blocks(int L)
{
	unsigned short tmp[MAX][MAX];
	int i, j;

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			tmp[j][N - i + 1] = map[L - 1][i][j];
		}
	}

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			map[L - 1][i][j] = tmp[i][j];
		}
	}
}

int Move_Blocks(int L)
{
	int WP;
	int i, j;
	unsigned short prev = -1;
	int max = 0;

	for (i = 1; i <= N; i++)
	{
		WP = 1;
		prev = -1;
		for (j = 1; j <= N; j++)
		{
			if (!map[L - 1][i][j]) continue;
			if (map[L - 1][i][j] == prev)
			{
				map[L][i][WP - 1] <<= 1;
				prev = -1;
			}
			else
			{
				map[L][i][WP++] = map[L - 1][i][j];
				prev = map[L - 1][i][j];
			}
			if (map[L][i][WP - 1] > max) max = map[L][i][WP - 1];
		}

		for (j = WP; j <= N; j++)
		{
			map[L][i][j] = 0;
		}
	}

	return max;
}

void DFS(int L, int m)
{
	int i;
	int tmp;

	if (m << (6 - L) <= max) return;
	if (L > 5)
	{
		max = m;
		return;
	}

	DFS(L + 1, Move_Blocks(L));
	for (i = 0; i<3; i++)
	{
		Circulate_Blocks(L);
		DFS(L + 1, Move_Blocks(L));
	}
}

int main(void)
{
	Input();
	DFS(1, max);
	printf("%d\n", max);
}
#endif
