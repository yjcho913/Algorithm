// #14442. 벽 부수고 이동하기2
#if 01
int R, C, K;
int map[1010][1010];
int WALL = 1000000;
typedef struct st{
	int r, c;
}ROBOT;
ROBOT QUE[10000000];
int WP, RP;
int visited[1010][1010];
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };

void Input(void)
{
	int i, j;
	char tmp[1010];

	scanf("%d %d %d", &R, &C, &K);

	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= C; j++)
		{
			visited[i][j] = 11000000;
		}
	}

	for (i = 1; i <= R; i++)
	{
		scanf("%s", tmp + 1);
		for (j = 1; j <= C; j++)
		{
			map[i][j] = tmp[j] - '0';
		}
	}

	for (i = 0; i <= R + 1; i++)
	{
		map[i][0] = map[i][C + 1] = 2;
	}

	for (j = 0; j <= C + 1; j++)
	{
		map[0][j] = map[R + 1][j] = 2;
	}

	map[R][C] = 4;
}

int BFS(void)
{
	ROBOT out;
	int k;
	int nr, nc;
	int tmp;

	QUE[WP++] = (ROBOT){ 1, 1 };
	visited[1][1] = 1;

	while (WP > RP)
	{
		out = QUE[RP++];
		tmp = visited[out.r][out.c] + 1;

		for (k = 0; k < 4; k++)
		{
			nr = out.r + dr[k];
			nc = out.c + dc[k];

			if (map[nr][nc] == 2) continue;
			if (map[nr][nc] == 4) return visited[out.r][out.c] % WALL + 1;

			if (map[nr][nc] == 0)
			{
				if (tmp >= visited[nr][nc]) continue;
				QUE[WP++] = (ROBOT){ nr, nc };
				visited[nr][nc] = tmp;
			}
			else
			{
				if (visited[out.r][out.c] >= WALL * K) continue;
				if (tmp + WALL >= visited[nr][nc]) continue;
				QUE[WP++] = (ROBOT){ nr, nc };
				visited[nr][nc] = tmp + WALL;
			}
		}
	}
	return -1;
}

int main(void)
{
	Input();
	if (R == 1 && C == 1) printf("1\n");
	else printf("%d\n", BFS());
	return 0;
}
#endif
