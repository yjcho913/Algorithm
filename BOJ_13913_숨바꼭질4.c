// #13913. 숨바꼭질 4
#include <stdio.h>

int SOO, DONG;
int QUE[100001];
int visited[100001];
int prev[100001];
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
            prev[out - 1] = out;
			QUE[WP++] = out - 1;
		}

        if(out < DONG)
		{
            if (out <= 99999 && visited[out + 1] == 0)
            {
                visited[out + 1] = visited[out] + 1;
                prev[out + 1] = out;
                QUE[WP++] = out + 1;
            }
            if (out <= 50000 && visited[out * 2] == 0)
            {
                visited[out * 2] = visited[out] + 1;
                prev[out * 2] = out;
                QUE[WP++] = out * 2;
            }
        }
	}
}

void Print_Path(int i)
{
    if(i != SOO) Print_Path(prev[i]);
    printf("%d ", i);
}

int main(void)
{
	scanf("%d %d", &SOO, &DONG);
	printf("%d\n", BFS());
    Print_Path(DONG);
	return 0;
}
