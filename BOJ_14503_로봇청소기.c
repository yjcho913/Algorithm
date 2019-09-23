// #14503. 로봇 청소기
#if 01
#define MAX (55)

int N, M;
int cr, cc, cd;
int cleaned[MAX][MAX];
int map[MAX][MAX];
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void Input(void)
{
	int i, j;

	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &cr, &cc, &cd);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
}

int Get_Sol(void)
{
	int nd, nr, nc;
	int rot_num = 0;
	int sol = 1;
	int i, j;

	for (;;)
	{
		cleaned[cr][cc] = 1;

		nd = (cd + 3) % 4;
		nr = cr + dr[nd];
		nc = cc + dc[nd];
		if (!cleaned[nr][nc] && !map[nr][nc])
		{
			cr = nr;
			cc = nc;
			cd = nd;
			sol++;
			rot_num = 0;
			continue;
		}
		else
		{
			cd = nd;
			if (++rot_num < 4) continue;
			nd = (cd + 2) % 4;
			nr = cr + dr[nd];
			nc = cc + dc[nd];
			if (map[nr][nc]) return sol;
			cr = nr;
			cc = nc;
			rot_num = 0;
			continue;
		}
	}
}

int main(void)
{
	Input();
	printf("%d\n", Get_Sol());
}
#endif
