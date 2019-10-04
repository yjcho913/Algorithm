// #15685. 드래곤 커브
#if 01
char map[101][101];
char dirs[1025];
short WP;
int N;
char dr[] = { 0, -1, 0, 1 };
char dc[] = { 1, 0, -1, 0 };
char chd[] = { 1, 2, 3, 0 };

void Get_Sol(void)
{
	int r, c, d, g;
	int j;

	scanf("%d %d %d %d", &c, &r, &d, &g);

	map[r][c] = 1;
	dirs[WP++] = d;
	r += dr[d];
	c += dc[d];
	map[r][c] = 1;

	while (g--)
	{
		for (j = WP - 1; j >= 0; j--)
		{
			d = chd[dirs[j]];
			r += dr[d];
			c += dc[d];
			map[r][c] = 1;
			dirs[WP++] = d;
		}
	}
}

int Get_Cnt(void)
{
	int i, j;
	int cnt = 0;

	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 100; j++)
		{
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1]) cnt++;
		}
	}
	return cnt;
}

int main(void)
{
	scanf("%d", &N);
	while (N--)
	{
		WP = 0;
		Get_Sol();
	}

	printf("%d\n", Get_Cnt());
}
#endif
