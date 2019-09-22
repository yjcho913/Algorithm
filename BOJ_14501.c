// #14501. 퇴사
#if 01
#define MAX (18)

int N;
int T[MAX], P[MAX];
int max;

void Input(void)
{
	int i;

	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%d %d", &T[i], &P[i]);
	}
}

void DFS(int D, int profit)
{
	if (profit > max) max = profit;
	if (D >= N) return;
	if (D + T[D] <= N) DFS(D + T[D], profit + P[D]);
	DFS(D + 1, profit);
}

int main(void)
{
	Input();
	DFS(0, 0);
	printf("%d\n", max);
}
#endif
