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

void printMap(Node** map, int N, int M) {
	//전체노트 출력해보기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("<%d, %d> ", map[i][j].value, map[i][j].visited);
		}
		printf("\n");
	}
	printf("\n");

}

int DFS(Node** map,int N, int M, int a, int b,int _sum, int _count) {
	int sum = _sum;     // <a,b>를 기준으로 깊이우선탐색을 했을 때 가장 큰 연속된 세 수의 합       
	int count = _count; // Root Node 외에 몇 개의 value가 더해졌는지 나타냄
	int sub_max = 0;    // Root Node의 4방향 중 한 방향에서 찾은 최대값?????????


	//Root Node 방문
	map[a][b].visited = 1;

	printMap(map, N, M);
	

	for (int i = -1; i <= 1; i++) {      // -1 <= i <= +1
		for (int j = -1; j <= 1; j++) {  // -1 <= j <= +1
			//printf("Root <%d,%d> 's <i,j> is <%d,%d>\n",a,b, i, j);

			if (getAbsolute(i) + getAbsolute(j) == 1) {// Root의 상하좌우일 때
				if (a + i < 0 || N - 1 < a + i || b + j < 0 || M - 1 < b + j) continue; //접근 불가능한 인덱스 처리
				
				//Root Node의 상하좌우 중 하나의 값이 아직 접근하지 않았다면
				if (map[a + i][b + j].visited == 0) {
					printf("<%d,%d> -> <%d,%d> successed", a, b, a + i, b + j);
					if (count == 0) {//하나의 값을 더한 후 그곳에서 DFS를 call 해야하면
						map[a + i][b + j].visited = 1;
						sum += map[a + i][b + j].value;
						count += 1;
						

						printf("ncall procedure Root = <%d, %d>\n",a+i, b+j);
						int sub_sub_max = 0; //마지막 깊이에서 return된 값
						sub_sub_max = DFS(map, N, M, a+i, b + j, sum, count);
						count -= 1; //상하좌우 중 한 방향으로 가치지기가 끝나면 count -1
						sum -= map[a + i][b + j].value; //이동해서 가치지기가 다시 시작했던 값을 빼준다. 
						printf("sub_sub_max is %d\n", sub_sub_max);
						if (sub_max < sub_sub_max) {
							sub_max = sub_sub_max;
						}
					}
					else if (count == 1) {//하나의 값만 더 더하면 되면
						map[a + i][b + j].visited = 1;
						if (getAbsolute(a + i) + getAbsolute(b + j) == 2) {//시작 Root 노드에 대해서 대각선이면
							map[a + i][b + j].visited = 0;
						}
						sum += map[a + i][b + j].value;
						printf("세 개의 합은 %d\n", sum);
						if (sub_max < sum) {
							sub_max = sum;
						}
						if (i == 1 && j == 0) {//사방을 다 확인했으면 return
							return sub_max;
						}
						sum -= map[a + i][b + j].value;
					}
				}
				else {
					printf("<%d,%d> -> <%d,%d> failed",a,b, a + i, b + j);
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
	printf("이 DFS에서 최대합은 %d\n\n", sub_max);
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
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("<%d,%d> 노드를 기준으로 DFS 실행!!\n", i, j);
			int sum_max = DFS(map, N, M, i, j, map[i][j].value, 0);
			if (max < sum_max) {
				max = sum_max;
			}
		}
	}
	printf("@@@@@@@@@\n");
	printf("max is %d\n", max);
	printf("@@@@@@@@@\n");

	//할당 해제
	for (int i = 0; i < N; i++) {
		free(map[i]);
	}
	free(map);
	
	//종료
	return 0;
}