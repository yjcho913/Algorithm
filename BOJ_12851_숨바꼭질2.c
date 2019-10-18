// #12851. 숨바꼭질 2
#if 01
#include <stdio.h>

int SOO, DONG;
typedef struct st{
	int n, time;
}JEOM;
JEOM QUE[100002*30];
int cnts[100002];
int WP, RP;
int sol = 0x7fffffff;
int visited[100002];

void BFS(void)
{
	JEOM out;
    
	QUE[WP++] = (JEOM){ SOO, 1 };
    visited[SOO] = 1;

	while (WP > RP)
	{
		out = QUE[RP++];

        if(visited[out.n] && visited[out.n] < out.time) continue;
        if(out.time > 100001) continue;        
		if (out.n == DONG)
		{
			cnts[out.time]++;
			if (sol > out.time) sol = out.time;
			continue;
		}
		if (out.time >= sol) continue;

        visited[out.n] = out.time;

		if (out.n < DONG)
		{
			if (out.n <= 99999)
			{
				QUE[WP++] = (JEOM){ out.n + 1, out.time + 1 };
			}

			if (out.n <= 50000)
			{
				QUE[WP++] = (JEOM){ out.n * 2, out.time + 1 };
			}
		}

		if (out.n >= 1)
		{
			QUE[WP++] = (JEOM){ out.n - 1, out.time + 1 };
		}
	}
}

int main(void)
{
	scanf("%d %d", &SOO, &DONG);
    BFS();
	printf("%d\n%d\n", sol - 1, cnts[sol]);
	return 0;
}
#endif
