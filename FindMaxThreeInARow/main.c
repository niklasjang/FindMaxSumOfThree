/*
2017.12.07 niklasjang
N x M 크기의 격자가 있고, 각 칸에 1부터 100 사이의 숫자가 써 있다.

좌우로, 또는 위아래로 연속한 세 칸의 합의 최대값을 구하는 프로그램을 작성하시오.

연속한 세 칸은 ㅡ, ㅣ, ㄱ, ㄴ, 또는 이들을 회전/대칭한 모양일 수 있다.

입력

첫 줄에는 격자의 크기를 나타내는 두 정수 N과 M이 주어진다. 모두 3 이상 100 이하이다.

다음 N 줄에는 격자의 한 줄을 나타내는 M개의 정수가 주어진다.

출력

연속한 세 칸의 합 중 최대값을 출력한다.

풀이 :
모든 노드에 대해서 길이가 3인 깊이우선 탐색을 진행한다.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct Node {
	int  value;  //사용자로부터 입력을 받은 값
	int  visited; //
}Node;

int getAbsolute(int num) {
	if (num >= 0) {
		return num;
	}
	else {
		return -1 * num;
	}
}

int DFS(Node** map,int N, int M, int a, int b,int _sum, int _count) {
	int sum = _sum;         
	int count = _count; // Root Node 외에 몇 개의 value가 더해졌는지 나타냄
	int sub_max = 0;

	
	printf("DFS is called.\n");
	printf("Root Node is <%d,%d>\n", a, b);
	printf("_sum is %d\n", _sum);
	printf("_count is %d\n", _count);
	printf("\n");


	//Root Node 방문
	printf("map[%d][%d].visit ==1\n", a, b);
	map[a][b].visited = 1;

	//전체노트 출력해보기
	printf("sum is %d, count is %d, sum_max is %d\n", sum, count, sub_max);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("<%d, %d> ",map[i][j].value, map[i][j].visited);
		}
		printf("\n");
	}
	printf("\n");

	

	for (int i = -1; i <= 1; i++) {      // -1 <= i <= +1
		for (int j = -1; j <= 1; j++) {  // -1 <= j <= +1
			// Root의 상하좌우일 때
			printf("Root <%d,%d> 's <i,j> is <%d,%d>\n",a,b, i, j);
			if (getAbsolute(i) + getAbsolute(j) == 1) {
				
				//접근 불가능한 인덱스 처리
				if (a + i < 0 || N - 1 < a + i || b + j < 0 || M - 1 < b + j) {
					//printf("불가능한 인덱스! <%d,%d>\n",a+i, b+j);
					continue;
				}
				//Root Node의 상하좌우 중 하나의 값이 아직 접근하지 않았다면
				if (map[a + i][b + j].visited == 0) {
					if (count == 0) {
						int last_ele = 0;
						sum += map[a + i][b + j].value;
						count += 1;
						map[a + i][b + j].visited = 1;
						//전체노트 출력해보기
						printf("sum is %d, count is %d, sum_max is %d\n", sum, count, sub_max);
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < M; j++) {
								printf("<%d, %d> ", map[i][j].value, map[i][j].visited);
							}
							printf("\n");
						}
						printf("\n");

						printf("\ncall procedure Root = <%d, %d>\n",a+i, b+j);
						last_ele = DFS(map, N, M, a+i, b + j, sum, count);
						sum += last_ele;
						if (sub_max < sum) {
							sub_max = sum;
						}
						sum -= last_ele;
						count -= 1;
						printf("last_ele is %d\n", last_ele);
						//전체노트 출력해보기
						printf("sum is %d, count is %d, sum_max is %d\n", sum, count, sub_max);
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < M; j++) {
								printf("<%d, %d> ", map[i][j].value, map[i][j].visited);
							}
							printf("\n");
						}
						printf("\n");
					}
					else if (count == 1) {
						map[a + i][b + j].visited = 1;
						count += 1;
						//전체노트 출력해보기
						printf("sum is %d, count is %d, sum_max is %d\n", sum, count, sub_max);
						for (int i = 0; i < N; i++) {
							for (int j = 0; j < M; j++) {
								printf("<%d, %d> ", map[i][j].value, map[i][j].visited);
							}
							printf("\n");
						}
						printf("Return %d\n", map[a + i][b + j].value);
						return map[a + i][b + j].value;
					}
				}
			}
		}
	}

	//방문기록 초기화
	printf("###방문 초기화~~~~~~####\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j].visited = 0;
		}
	}
	printf("이 DFS에서 최대합은 %d", sub_max);
	return sub_max;
}



int main(void) {
	int N = 0, M = 0;
	Node **map;
	int max = 0;
	//크기입력
	scanf_s("%d %d", &N, &M);
	
	//할당 및 초기화
	map = (Node**)malloc(N * sizeof(Node *));
	for (int i = 0; i < N; i++) {
		map[i] = (Node *)malloc(M * sizeof(Node));
		for (int j = 0; j < M; j++) {
			memset(&map[i][j], 0, sizeof(Node)); //Box의 값들을 0으로 초기화
		}
	}

	//입력
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < M; col++) {
			scanf_s("%d", &map[row][col].value);
		}
	}

	//map의 모든 노드들에 대해서 DFS 알고리즘을 실행
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("<%d,%d> 노드를 기준으로 DFS 실행!!\n",i,j);
			int sum_max = DFS(map, N, M, i, j, map[i][j].value, 0);
			if (max < sum_max) {
				max = sum_max;
			}
		}
	}*/
	int sum_max = DFS(map, N, M, 0, 0, map[0][0].value, 0);
	printf("@@@@@@@@@");
	printf("max is %d", sum_max);
	printf("@@@@@@@@@");

	//할당 해제
	for (int i = 0; i < N; i++) {
		free(map[i]);
	}
	free(map);
	
	//종료
	return 0;
}