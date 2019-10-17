// #16988. Baaaaaaaaaduk2 (Easy)
#if 01
#include <stdio.h>

int R, C;
int pan[22][22];
int visited[22][22];
typedef struct st{
	int r, c;
}POS;
POS QUE[400];
int WP, RP;
int dr[] = { 1, -1, 0, 0 };
int dc[] = { 0, 0, 1, -1 };

POS ones[400];
int onecnt;
POS twos[400];
int twocnt;

void Input(void)
{
	int i, j;

	scanf("%d %d", &R, &C);
	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= C; j++)
		{
			scanf("%d", &pan[i][j]);
			if (pan[i][j] == 2)
			{
				twos[twocnt++] = (POS){ i, j };
			}
		}
	}

	for (i = 0; i <= R + 1; i++)
	{
		pan[i][0] = pan[i][C + 1] = 1;
	}
	for (j = 0; j <= C + 1; j++)
	{
		pan[0][j] = pan[R + 1][j] = 1;
	}
}

void Search_Ones(void)
{
	int i, j;

	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= C; j++)
		{
			if (pan[i][j] != 0) continue;
			if (pan[i][j + 1] == 2 || pan[i][j - 1] == 2 || pan[i + 1][j] == 2 || pan[i - 1][j] == 2) ones[onecnt++] = (POS){ i, j };
		}
	}
}

int FFBFS(void)
{
	static int t;
	int res = 0;
	int cnt;
	POS out;
	int k, i;
	int nr, nc;
	int exit = 0;

	WP = RP = 0;
	t++;

	for (i = 0; i < twocnt; i++)
	{
		if (visited[twos[i].r][twos[i].c] == t) continue;
		cnt = 1;
		exit = 0;
		visited[twos[i].r][twos[i].c] = t;
		QUE[WP++] = (POS){ twos[i].r, twos[i].c };
		
		while (WP > RP)
		{
			out = QUE[RP++];

			for (k = 0; k < 4; k++)
			{
				nr = out.r + dr[k];
				nc = out.c + dc[k]; 
				if (visited[nr][nc] == t || pan[nr][nc] == 1) continue;
				if (pan[nr][nc] == 0)
				{
					exit = 1;
					continue;
				}
				cnt++;
				visited[nr][nc] = t;
				QUE[WP++] = (POS){ nr, nc };
			}
		}
		if (exit) cnt = 0;
		res += cnt;
	}
	return res;
}

int Get_Sol(void)
{
	int i, j;
	int sol = 0;
	int tmp;

	for (i = 0; i < onecnt; i++)
	{
		pan[ones[i].r][ones[i].c] = 1;

		for (j = i + 1; j < onecnt; j++)
		{
			pan[ones[j].r][ones[j].c] = 1;
			tmp = FFBFS();
			if (tmp > sol) sol = tmp;
			pan[ones[j].r][ones[j].c] = 0;
		}

		pan[ones[i].r][ones[i].c] = 0;
	}

	return sol;
}

int main(void)
{
	Input();
	Search_Ones();
	printf("%d\n", Get_Sol());
	return 0;
}
#endif
