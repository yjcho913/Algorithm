// #17471. 게리맨더링
#if 01
#include <stdio.h>
#define ABS(x) ((x) > 0 ? (x): -(x))

int N;
int pops[11];
int links[11][11];
int popsum;
int lst[11];
int rcnt = 1;
int sol = 1000;
int QUE[10];
int WP, RP;

void Input(void)
{
	int i, j, num, tmp;

	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &pops[i]);
		popsum += pops[i];
	}
	
	for (i = 1; i <= N; i++)
	{
		scanf("%d", &links[i][0]);
		for (j = 1; j <= links[i][0]; j++)
		{
			scanf("%d", &links[i][j]);
		}
	}
}

int Is_Possible(void)
{
	int out;
	int visited[11] = { 0 };
	int i;
	int tmp;
	int tcnt = 0;

	WP = RP = 0;
	QUE[WP++] = 1;
	visited[1] = 1;
	tcnt = 1;
	while (WP > RP)
	{
		out = QUE[RP++];
		for (i = 1; i <= links[out][0]; i++)
		{
			tmp = links[out][i];
			if (visited[tmp] || lst[tmp] == 0) continue;
			visited[tmp] = 1;
			tcnt++;
			QUE[WP++] = tmp;
		}
	}
	if (tcnt != rcnt) return 0;


	WP = RP = 0;
	for (i = 2; i <= N; i++)
	{
		if (lst[i] == 0)
		{
			QUE[WP++] = i;
			tcnt = 1;
			visited[i] = 1;
			break;
		}
	}

	while (WP > RP)
	{
		out = QUE[RP++];
		for (i = 1; i <= links[out][0]; i++)
		{
			tmp = links[out][i];
			if (visited[tmp] || lst[tmp]) continue;
			visited[tmp] = 1;
			tcnt++;
			QUE[WP++] = tmp;
		}
	}
	if (tcnt != N - rcnt) return 0;
	return 1;
}

void DFS(int L, int sum)
{
	int tmp;
	int i;

	if (rcnt == N || sol == 0) return;

	if (L > N)
	{
		tmp = ABS(2 * sum - popsum);
		if (tmp < sol && Is_Possible()) sol = tmp;
		return;
	}

	rcnt++;
	lst[L] = 1;
	DFS(L + 1, sum + pops[L]);
	rcnt--;
	lst[L] = 0;

	DFS(L + 1, sum);
}

int main(void)
{
	Input();
	lst[1] = 1;
	DFS(2, pops[1]);
	printf("%d\n", (sol == 1000) ? -1 : sol);
	return 0;
}
#endif
