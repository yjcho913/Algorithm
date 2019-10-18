// #5427. 불
#if 01
#include <stdio.h>
#define MAX (1005)

int R, C;
char map[MAX][MAX];
int visited[MAX][MAX];
typedef struct st{
	int r, c;
}POS;
POS FQUE[MAX*MAX];
POS SQUE[MAX*MAX];
int FWP, FRP, SWP, SRP;
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
int sr, sc;

void Input(void)
{
	int i, j;

	scanf("%d %d", &C, &R);
	for (i = 0; i < R; i++)
	{
		scanf("%s", map[i]);
		for (j = 0; j < C; j++)
		{
			if (map[i][j] == '*') FQUE[FWP++] = (POS){ i, j };
			else if (map[i][j] == '@')
			{
				map[i][j] = '.';
				sr = i; sc = j;
			}
		}
	}
}

int BFS(void)
{
	static int t;
	int nr, nc;
	int TFWP, TSWP;
	int k;
	POS out;

	t += 1000000;
	visited[sr][sc] = t;
	SQUE[SWP++] = (POS){ sr, sc };

	while (1)
	{
		// 상근이 이동
		TSWP = SWP;
		while (TSWP > SRP)
		{
			out = SQUE[SRP++];
			if (map[out.r][out.c] == '*') continue;

			for (k = 0; k < 4; k++)
			{
				nr = out.r + dr[k];
				nc = out.c + dc[k];
				if (nr < 0 || nc < 0 || nr >= R || nc >= C) return visited[sr][sc] - visited[out.r][out.c] + 1;
				if (visited[nr][nc] >= visited[out.r][out.c] - 1 || map[nr][nc] != '.') continue;
				visited[nr][nc] = visited[out.r][out.c] - 1;
				SQUE[SWP++] = (POS){ nr, nc };
			}
		}

		if (SWP == SRP) return 0;

		// 불 이동
		TFWP = FWP;
		while (TFWP > FRP)
		{
			out = FQUE[FRP++];

			for (k = 0; k < 4; k++)
			{
				nr = out.r + dr[k];
				nc = out.c + dc[k];
				if (nr < 0 || nc < 0 || nr >= R || nc >= C || map[nr][nc] != '.') continue;
				map[nr][nc] = '*';
				FQUE[FWP++] = (POS){ nr, nc };
			}
		}
	}
}

int main(void)
{
	int T;
	int res;

	scanf("%d", &T);
	while (T--)
	{
		SWP = SRP = FWP = FRP = 0;
		Input();
		res = BFS();
		if (res <= 0) printf("IMPOSSIBLE\n");
		else printf("%d\n", res);
	}
	return 0;
}
#endif
