// #16985. Maaaaaaaaaze
#if 01
#include <stdio.h>

int map[7][4][7][7];
int visited[7][7][7];
int lst[7];
int dr[] = { 1, -1, 0, 0, 0, 0 };
int dc[] = { 0, 0, 1, -1, 0, 0 };
int dh[] = { 0, 0, 0, 0, 1, -1 };

typedef struct st{
	int h, r, c;
}POS;
POS QUE[1000];
int WP, RP;
int sol = 200;
int rot[1024][7];

void Input(void)
{
	int i, j, k;
	int tmp;
	
	for (i = 1; i <= 5; i++)
	{
		for (j = 1; j <= 5; j++)
		{
			for (k = 1; k <= 5; k++)
			{
				scanf("%d", &tmp);
				map[i][0][j][k] = map[i][1][k][6 - j] = map[i][2][6 - j][6 - k] = map[i][3][6 - k][j] = tmp;
			}
		}
	}
}

void Make_Rotate_Arr(void)
{
	int a, b, c, d, e;
	int cnt = 0;
	
	for (a = 0; a < 4; a++)
	{
		for (b = 0; b < 4; b++)
		{
			for (c = 0; c < 4; c++)
			{
				for (d = 0; d < 4; d++)
				{
					for (e = 0; e < 4; e++)
					{
						rot[cnt][1] = a;
						rot[cnt][2] = b;
						rot[cnt][3] = c;
						rot[cnt][4] = d;
						rot[cnt++][5] = e;
					}
				}
			}
		}
	}
}

int BFS(int r)
{
	static int t = 0;
	POS out;
	int k;
	int nr, nc, nh;

	t += 150;
	WP = RP = 0;
	visited[1][1][1] = t;
	QUE[WP++] = (POS) { 1, 1, 1 };

	while (WP > RP)
	{
		out = QUE[RP++];
		for (k = 0; k < 6; k++)
		{
			nr = out.r + dr[k];
			nc = out.c + dc[k];
			nh = out.h + dh[k];
			if(map[lst[nh]][rot[r][lst[nh]]][nr][nc] == 0 || visited[nh][nr][nc] >= t) continue;
			visited[nh][nr][nc] = visited[out.h][out.r][out.c] + 1;
			if (nh == 5 && nr == 5 && nc == 5) return visited[5][5][5] - visited[1][1][1];
			QUE[WP++] = (POS){ nh, nr, nc };
		}
	}
	return visited[5][5][5] - visited[1][1][1];
}

void Get_Sol(void)
{
	int a, b, c, d, e;
	int r;
	int res;
	int vfloor[6] = { 0 };

	for (a = 1; a <= 5; a++)
	{
		if (vfloor[a]) continue;
		vfloor[a] = 1;
		lst[1] = a;

		for (b = 1; b <= 5; b++)
		{
			if (vfloor[b]) continue;
			vfloor[b] = 1;
			lst[2] = b;

			for (c = 1; c <= 5; c++)
			{
				if (vfloor[c]) continue;
				vfloor[c] = 1;
				lst[3] = c;

				for (d = 1; d <= 5; d++)
				{
					if (vfloor[d]) continue;
					vfloor[d] = 1;
					lst[4] = d;

					for (e = 1; e <= 5; e++)
					{
						if (vfloor[e]) continue;
						lst[5] = e;
						for (r = 0; r < 1024; r++)
						{
							if (map[lst[1]][rot[r][lst[1]]][1][1] == 0 || map[lst[5]][rot[r][lst[5]]][5][5] == 0) continue;
							res = BFS(r);
							if (res > 0 && res < sol)
							{
								sol = res;
								if (sol == 12) return;
							}
						}
					}
					vfloor[d] = 0;
				}
				vfloor[c] = 0;
			}
			vfloor[b] = 0;
		}
		vfloor[a] = 0;
	}
}

int main(void)
{
	Input();
	Make_Rotate_Arr();
	Get_Sol();
	sol = (sol == 200) ? -1 : sol;
	printf("%d\n", sol);
	return 0;
}
#endif
