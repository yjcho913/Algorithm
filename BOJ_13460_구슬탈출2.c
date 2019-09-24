// #13460. 구슬 탈출2
#if 01
#include <stdio.h>
#define MAX (12)

int R, C;
int RR, RC, BR, BC;
char map[MAX][MAX];
int dr[] = { 1, 0, -1, 0 };
int dc[] = { 0, 1, 0, -1 };

typedef struct st{
	int rr, rc, br, bc, dir, cnt;
}BOARD;
BOARD QUE[1000000];
int WP, RP;

void InQueue(int rr, int rc, int br, int bc, int dir, int cnt)
{
	QUE[WP].rr = rr;
	QUE[WP].rc = rc;
	QUE[WP].br = br;
	QUE[WP].bc = bc;
	QUE[WP].dir = dir;
	QUE[WP++].cnt = cnt;
}

BOARD OutQueue(void)
{
	return QUE[RP++];
}

void Input(void)
{
	int i, j;
	scanf("%d %d", &R, &C);
	for (i = 0; i < R; i++)
	{
		scanf("%s", map[i]);
		for (j = 1; j < C - 1; j++)
		{
			if (map[i][j] == 'R')
			{
				RR = i;
				RC = j;
			}
			else if (map[i][j] == 'B')
			{
				BR = i;
				BC = j;
			}
		}
	}
}

int Move(BOARD *out, int di)
{
	int i, j, dd;
	int tbr, tbc, trr, trc;

	for (dd = 1; dd <= 4; dd += di)
	{
		i = (out->dir + dd) % 4;
		tbr = out->br;
		tbc = out->bc;
		while (1)
		{
			tbr += dr[i];
			tbc += dc[i];
			if (map[tbr][tbc] == '#' || map[tbr][tbc] == 'O') break;
		}
		if (map[tbr][tbc] == '#')
		{
			tbr -= dr[i];
			tbc -= dc[i];
		}
		else continue;

		trr = out->rr;
		trc = out->rc;
		while (1)
		{
			trr += dr[i];
			trc += dc[i];
			if (map[trr][trc] == 'O') return out->cnt + 1;
			else if (map[trr][trc] == '#')
			{
				trr -= dr[i];
				trc -= dc[i];
				break;
			}
		}

		if (trr == tbr && tbc == trc)
		{
			if ((out->rr - out->br)*dr[i] < 0 || (out->rc - out->bc)*dc[i] < 0)
			{
				trr -= dr[i];
				trc -= dc[i];
			}
			else
			{
				tbr -= dr[i];
				tbc -= dc[i];
			}
		}

		if (trr == out->rr && trc == out->rc && tbr == out->br && tbc == out->bc) continue;
		InQueue(trr, trc, tbr, tbc, i, out->cnt + 1);
	}
	return 0;
}

int BFS(void)
{
	int sol;
	BOARD out = { RR, RC, BR, BC, 0, 0 };
	WP = RP = 0;

	if (sol = Move(&out, 1)) return sol;
	while (WP > RP)
	{
		out = OutQueue();
		if (out.cnt > 9) return -1;
		if (sol = Move(&out, 2)) return sol;
	}
	return -1;
}

int main(void)
{
	Input();
	printf("%d\n", BFS());
}
#endif
