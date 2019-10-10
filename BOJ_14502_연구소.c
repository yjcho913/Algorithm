// #14502. 연구소
#if 01
int N, M;
int map[10][10];
int vr[10], vc[10];
int er[64], ec[64];
int ecnt;
int vcnt;
int wcnt = 3;
int sol = 64;

typedef struct st{
	int r, c;
}POS;
POS QUE[8 * 8];
int WP, RP;
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };

void InQueue(int r, int c)
{
	QUE[WP].r = r;
	QUE[WP++].c = c;
}

POS OutQueue(void)
{
	return QUE[RP++];
}

void Input(void)
{
	int i, j;
	scanf("%d %d", &N, &M);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2)
			{
				vr[vcnt] = i;
				vc[vcnt++] = j;
			}
			else if (map[i][j]) wcnt++;
			else
			{
				er[ecnt] = i;
				ec[ecnt++] = j;
			}
		}
	}

	for (i = 0; i <= N + 1; i++)
	{
		map[i][0] = map[i][M + 1] = 1;
	}
	
	for (j = 0; j <= M + 1; j++)
	{
		map[0][j] = map[N + 1][j] = 1;
	}
}

int BFS(void)
{
	int visited[10][10] = { 0 };
	int i;
	int nr, nc;
	int tmp = vcnt;
	POS out;

	WP = RP = 0;
	for (i = 0; i < vcnt; i++)
	{
		InQueue(vr[i], vc[i]);
		visited[vr[i]][vc[i]] = 1;
	}

	while (WP > RP)
	{
		out = OutQueue();

		for (i = 0; i < 4; i++)
		{
			nr = out.r + dr[i];
			nc = out.c + dc[i];
			if (map[nr][nc] || visited[nr][nc]) continue;
			visited[nr][nc] = 1;
			if (++tmp >= sol) return sol;
			InQueue(nr, nc);
		}
	}
	return tmp;
}

void DFS(int L, int idx)
{
	int i, tmp;

	if (L == 3)
	{
		sol = BFS();
		return;
	}

	for (i = idx; i < ecnt; i++)
	{
		map[er[i]][ec[i]] = 1;
		DFS(L + 1, i + 1);
		map[er[i]][ec[i]] = 0;
	}
}

int main(void)
{
	Input();
	DFS(0, 0);
	printf("%d\n", N*M - wcnt - sol);
	return 0;
}
#endif
