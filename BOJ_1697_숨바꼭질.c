// #1697. 숨바꼭질
#if 01
#include <stdio.h>

int SOO, DONG;
int QUE[100001];
int visited[100001];
int WP, RP;

int BFS(void)
{
	int out;

	QUE[WP++] = SOO;
	visited[SOO] = 1;

	while (WP > RP)
	{
		out = QUE[RP++];
		if (out == DONG) return visited[DONG] - 1;

		if (out >= 1 && visited[out - 1] == 0)
		{
			visited[out - 1] = visited[out] + 1;
			QUE[WP++] = out - 1;
		}
		if (out <= 99999 && visited[out + 1] == 0)
		{
			visited[out + 1] = visited[out] + 1;
			QUE[WP++] = out + 1;
		}
		if (out <= 50000 && visited[out * 2] == 0)
		{
			visited[out * 2] = visited[out] + 1;
			QUE[WP++] = out * 2;
		}
	}
}
int main(void)
{
	scanf("%d %d", &SOO, &DONG);
	printf("%d\n", BFS());
	return 0;
}
#endif
