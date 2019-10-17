// #1726. 로봇
#if 01
#include <stdio.h>

int map[102][102];
int visited[5][102][102];
int R, C;
typedef struct st{
	int d, r, c;
}ROBOT;
ROBOT QUE[100 * 100 * 30 * 5];
int WP, RP;
ROBOT dest;
int dr[] = { 0, 0, 0, 1, -1 };
int dc[] = { 0, 1, -1, 0, 0 };
int ldd[] = { 0, 4, 3, 1, 2 };
int rdd[] = { 0, 3, 4, 2, 1 };

void Input(void)
{
	int i, j;

	scanf("%d %d", &R, &C);
	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= C; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}

	scanf("%d %d %d", &QUE[WP].r, &QUE[WP].c, &QUE[WP].d);
	scanf("%d %d %d", &dest.r, &dest.c, &dest.d);
	visited[QUE[0].d][QUE[0].r][QUE[0].c] = 1;

	for (i = 1; i <= R; i++)
	{
		map[i][0] = map[i][C + 1] = 1;
	}

	for (j = 1; j <= C; j++)
	{
		map[0][j] = map[R + 1][j] = 1;
	}
}

int BFS(void)
{
	ROBOT out;
	int nr, nc, nd;
	int i;

	WP = 1;
	while (WP > RP)
	{
		out = QUE[RP++];
		if (out.r == dest.r && out.c == dest.c && out.d == dest.d) return visited[out.d][out.r][out.c] - 1;

		nd = out.d;
		nr = out.r;
		nc = out.c;

		for (i = 1; i <= 3; i++)
		{
			nr += dr[nd];
			nc += dc[nd];
			if (map[nr][nc]) break;
			if(visited[nd][nr][nc]) continue;
			QUE[WP++] = (ROBOT){ nd, nr, nc };
			visited[nd][nr][nc] = visited[nd][out.r][out.c] + 1;
		}

		nd = ldd[out.d];
		if (visited[nd][out.r][out.c] == 0)
		{
			QUE[WP++] = (ROBOT){ nd, out.r, out.c };
			visited[nd][out.r][out.c] = visited[out.d][out.r][out.c] + 1;
		}

		nd = rdd[out.d];
		if (visited[nd][out.r][out.c] == 0)
		{
			QUE[WP++] = (ROBOT){ nd, out.r, out.c };
			visited[nd][out.r][out.c] = visited[out.d][out.r][out.c] + 1;
		}
	}
}

int main(void)
{
	Input();
	printf("%d\n", BFS());
	return 0;
}
#endif
