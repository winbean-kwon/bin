// DFS BFS 구현


#include <stdio.h>

int n; // 정점의 총 갯수
int map[30][30], visit[30]; // 인접 행렬과 방문 여부를 나타내는 배열
//----------------DFS-----------------------------------------------

int a; // 입력될 정수의 갯수
int rear, front; // 전단과 후단을 나타내는 변수
int map2[30][30], queue[30], visit2[30]; // 인접 행렬과 큐와 방문 배열
//----------------BFS-----------------------------------------------

void DFS(int v)
{
	int i;
	visit[v] = 1; // 정점 v를 방문했다고 표시
	for (i = 1; i <= n; i++)
	{
		if (map[v][i] == 1 && !visit[i]) // v와 i가 연결됐고, if 정점 i를 방문하지 않았다면
		{
			printf("%d에서 %d로 이동\n", v, i);
			// i에서 다시 DFS를 시작
			DFS(i);
		}
	}
}

void BFS(int v5)
{
	int i2;
	visit2[v5] = 1; // v를 방문했다고 표시
	printf("%d에서 시작\n", v5);
	queue[rear++] = v5; // 큐에 v를 삽입, 후단을 1 증가시킴
	while (front < rear) // 후단이 전단과 같거나 작으면 루프 탈출
	{
		// 큐의 첫번째에 있는 데이터를 제외하고 제외된 값을 가져오며, 전단 1 증가
		v5 = queue[front++];
		for (i2 = 1; i2 <= a; i2++)
		{
			// 정점 v와 정점 i가 만나고, 정점 i를 방문하지 않은 상태일 경우
			if (map2[v5][i2] == 1 && !visit2[i2])
			{
				visit2[i2] = 1; // 정점 i를 방문했다고 표시
				printf("%d에서 %d로 이동\n", v5, i2);
				queue[rear++] = i2; // 큐에 i를 삽입하고 후단을 1 증가시킴
			}
		}
	}
}

int main()
{
	int start; // 시작 정점
	int v1, v2; //인접행렬에 넣을 행,열의 입력값

	scanf_s("%d%d", &n, &start); //정점의 갯수와 시작정점을 입력

	while (1) //인접행렬
	{
		scanf_s("%d%d", &v1, &v2);
		if (v1 == -1 && v2 == -1) break; // -1과 -1이 입력되면 무한 루프 탈출
		map[v1][v2] = map[v2][v1] = 1; // 정점 v1과 정점 v2가 연결되었다고 표시
	}
	DFS(start);


	int start2; // 시작 정점을 나타내는 변수
	int v3, v4;
	scanf_s("%d%d", &a, &start2);
	while (1)
	{
		scanf_s("%d%d", &v3, &v4);
		if (v3 == -1 && v4 == -1) break;
		map2[v3][v4] = map2[v4][v3] = 1;
	}
	BFS(start);
	return 0;
}
