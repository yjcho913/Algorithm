// #2382. 미생물 격리
#if 01
#include <stdio.h>
#define MAX (110)

int max[MAX][MAX];
int sum[MAX][MAX];
int N, M, K;
typedef struct st{
	int r, c, dir, cnt, time;
}MI;
MI QUE[1000000];
int WP, RP;
int dr[] = { 0, -1, 1, 0, 0 };
int dc[] = { 0, 0, 0, -1, 1 };
int Time = 0;
int chdir[] = { 0, 2, 1, 4, 3 };

void InQueue(int r, int c, int dir, int cnt, int time)
{
	QUE[WP].r = r;
	QUE[WP].c = c;
	QUE[WP].dir = dir;
	QUE[WP].cnt = cnt;
	QUE[WP++].time = time;
}

MI OutQueue(void)
{
	return QUE[RP++];
}

void Input(void)
{
	int i;

	WP = RP = 0;
	Time = 0;

	scanf("%d %d %d", &N, &M, &K);
	for (i = 0; i<K; i++)
	{
		scanf("%d %d %d %d", &QUE[WP].r, &QUE[WP].c, &QUE[WP].cnt, &QUE[WP].dir);
		QUE[WP++].time = 0;
	}
}

void Correct_Queue(void)
{
	int i;
	int r, c;

	RP--;
	for (i = RP; i<WP; i++)
	{
		r = QUE[i].r;
		c = QUE[i].c;

		if (QUE[i].cnt != max[r][c])
		{
			QUE[i].cnt = 0;
			continue;
		}
		QUE[i].cnt = sum[r][c];
		max[r][c] = sum[r][c] = 0;
		//	printf("r: %d   c: %d   cnt: %d   dir: %d   time: %d\n", QUE[i].r, QUE[i].c, QUE[i].cnt, QUE[i].dir, QUE[i].time);

	}
}

int Get_Sol(void)
{
	int sol = 0;
	MI out;
	int nr, nc;

	while (WP > RP)
	{
		out = OutQueue();
		//	printf("r: %d   c: %d   cnt: %d   dir: %d   time: %d\n", out.r, out.c, out.cnt, out.dir, out.time);
		if (out.time != Time)
		{
			Correct_Queue();
			Time++;
			out = OutQueue();
		}
		if (out.cnt == 0) continue;

		if (out.time == M)
		{
			sol += out.cnt;
			continue;
		}

		nr = out.r + dr[out.dir];
		nc = out.c + dc[out.dir];
		if (nr == 0 || nr == N - 1 || nc == 0 || nc == N - 1)
		{
			out.dir = chdir[out.dir];
			out.cnt /= 2;
			if (out.cnt == 0) continue;
		}

		sum[nr][nc] += out.cnt;
		if (out.cnt > max[nr][nc]) max[nr][nc] = out.cnt;
		else continue;

		InQueue(nr, nc, out.dir, out.cnt, out.time + 1);
	}
	return sol;
}

int main(void)
{
	int t, T;

	scanf("%d", &T);
	for (t = 1; t <= T; t++)
	{
		Input();
		printf("#%d %d\n", t, Get_Sol());
	}
}
#endif
