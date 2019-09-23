// #2105. 디저트 카페
#if 01
#include <stdio.h>
#define MAX (25)
#define INF (0x7fff0000)

int N;
int map[MAX][MAX];
int max;
int dr[4] = { 1, 1, -1, -1 };
int dc[4] = { -1, 1, 1, -1 };
int visited[101];
int ret;
int left, right;
int cr, cc;
int nr, nc;
int tr, tc;
int chk = 1;

void Input(void)
{
	int i, j;
	scanf("%d", &N);
	for (i = 0; i<N; i++)
	{
		for (j = 0; j<N; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
}

int Check_Opposite(void)
{
	int i, j;

	tr = cr;
	tc = cc;
	for (i = 0; i < left; i++)
	{
		tr += dr[2];
		tc += dc[2];
		if (tr < 0 || tc < 0 || tr >= N || tc >= N) return 0;
		if (visited[map[tr][tc]] >= chk) return 0;
		visited[map[tr][tc]] = chk;
	}

	for (i = 0; i < right; i++)
	{
		tr += dr[3];
		tc += dc[3];
		if (tr < 0 || tc < 0 || tr >= N || tc >= N) return 0;
		if (visited[map[tr][tc]] >= chk) return 0;
		visited[map[tr][tc]] = chk;
	}
	return 1;
}

void DFS(int L)
{
	if (L == 3)
	{
		if ((left + right) * 2 > max)
		{
			ret = (Check_Opposite()) ? (right + left) * 2 : -1;
			if (ret > max) max = ret;
			chk++;
		}
		return;
	}

	nr = cr + dr[L - 1];
	nc = cc + dc[L - 1];
	if (nr < 0 || nc < 0 || nr >= N || nc >= N) return;
	if (visited[map[nr][nc]] >= chk) return;

	cr = nr;
	cc = nc;
	visited[map[cr][cc]] = INF;

	if (L == 1) left++;
	else right++;

	DFS(L);
	DFS(L + 1);

	if (L == 1) left--;
	else right--;

	visited[map[cr][cc]] = 0;
	cr -= dr[L - 1];
	cc -= dc[L - 1];
}

int main(void)
{
	int t, T;
	int i, j;

	scanf("%d", &T);
	for (t = 1; t <= T; t++)
	{
		Input();
		max = -1;
		for (i = 0; i < N - 1; i++)
		{
			if ((N - i - 1) * 2 <= max) break;
			for (j = 1; j < N - 1; j++)
			{
				cr = i;
				cc = j;
				right = left = 0;
				DFS(1);
				if (max == (N - i - 1) * 2) break;
			}
			if (max == (N - i - 1) * 2) break;
		}
		printf("#%d %d\n", t, max);
	}
}
#endif
