// #15686. 치킨 배달
#if 01
#define ABS(x) ((x)>0?(x):-(x))
#define DIST(i, j) (ABS(hr[i]-cr[j]) + ABS(hc[i]-cc[j]))
int hcnt, ccnt;
int hr[100], hc[100];
int cr[13], cc[13];
int min = 0x7fffffff;
int dist[100];
int N, M;

void Input(void)
{
	int i, j, num; 

	scanf("%d %d", &N, &M);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &num);
			if (num == 1)
			{
				hr[hcnt] = i;
				hc[hcnt++] = j;
			}
			else if (num == 2)
			{
				cr[ccnt] = i;
				cc[ccnt++] = j;
			}
		}
	}
	for (i = 0; i < hcnt; i++)
	{
		dist[i] = 0x7fffffff;
	}
}

void DFS(int L, int cidx)
{
	int i, j;
	int tdist[100];
	int d = 0;

	//for (i = 0; i < hcnt; i++) printf("%d ", dist[i]);
	//printf("\n");

	if (L > M)
	{
		for (i = 0; i < hcnt; i++) d += dist[i];
		if (d < min) min = d;
		return;
	}

	for (i = 0; i < hcnt; i++)
	{
		tdist[i] = dist[i];
	}

	for (i = cidx; i < ccnt - M + L; i++)
	{
		for (j = 0; j < hcnt; j++)
		{
			d = DIST(j, i);
			dist[j] = (d < tdist[j]) ? d : tdist[j];
		}
		DFS(L + 1, i + 1);
	}
}

int main(void)
{
	Input();
	DFS(1, 0);
	printf("%d\n", min);
	return 0;
}
#endif
