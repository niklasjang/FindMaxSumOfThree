/*
2017.12.07 niklasjang
N x M ũ���� ���ڰ� �ְ�, �� ĭ�� 1���� 100 ������ ���ڰ� �� �ִ�.

�¿��, �Ǵ� ���Ʒ��� ������ �� ĭ�� ���� �ִ밪�� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

������ �� ĭ�� ��, ��, ��, ��, �Ǵ� �̵��� ȸ��/��Ī�� ����� �� �ִ�.

�Է�

ù �ٿ��� ������ ũ�⸦ ��Ÿ���� �� ���� N�� M�� �־�����. ��� 3 �̻� 100 �����̴�.

���� N �ٿ��� ������ �� ���� ��Ÿ���� M���� ������ �־�����.

���

������ �� ĭ�� �� �� �ִ밪�� ����Ѵ�.

Ǯ�� :
��� ��忡 ���ؼ� ���̰� 3�� ���̿켱 Ž���� �����Ѵ�.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct Node {
	int  value;  //����ڷκ��� �Է��� ���� ��
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
	int count = _count; // Root Node �ܿ� �� ���� value�� ���������� ��Ÿ��
	int sub_max = 0;

	
	printf("DFS is called.\n");
	printf("Root Node is <%d,%d>\n", a, b);
	printf("_sum is %d\n", _sum);
	printf("_count is %d\n", _count);
	printf("\n");


	//Root Node �湮
	printf("map[%d][%d].visit ==1\n", a, b);
	map[a][b].visited = 1;

	//��ü��Ʈ ����غ���
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
			// Root�� �����¿��� ��
			printf("Root <%d,%d> 's <i,j> is <%d,%d>\n",a,b, i, j);
			if (getAbsolute(i) + getAbsolute(j) == 1) {
				
				//���� �Ұ����� �ε��� ó��
				if (a + i < 0 || N - 1 < a + i || b + j < 0 || M - 1 < b + j) {
					//printf("�Ұ����� �ε���! <%d,%d>\n",a+i, b+j);
					continue;
				}
				//Root Node�� �����¿� �� �ϳ��� ���� ���� �������� �ʾҴٸ�
				if (map[a + i][b + j].visited == 0) {
					if (count == 0) {
						int last_ele = 0;
						sum += map[a + i][b + j].value;
						count += 1;
						map[a + i][b + j].visited = 1;
						//��ü��Ʈ ����غ���
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
						//��ü��Ʈ ����غ���
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
						//��ü��Ʈ ����غ���
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

	//�湮��� �ʱ�ȭ
	printf("###�湮 �ʱ�ȭ~~~~~~####\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j].visited = 0;
		}
	}
	printf("�� DFS���� �ִ����� %d", sub_max);
	return sub_max;
}



int main(void) {
	int N = 0, M = 0;
	Node **map;
	int max = 0;
	//ũ���Է�
	scanf_s("%d %d", &N, &M);
	
	//�Ҵ� �� �ʱ�ȭ
	map = (Node**)malloc(N * sizeof(Node *));
	for (int i = 0; i < N; i++) {
		map[i] = (Node *)malloc(M * sizeof(Node));
		for (int j = 0; j < M; j++) {
			memset(&map[i][j], 0, sizeof(Node)); //Box�� ������ 0���� �ʱ�ȭ
		}
	}

	//�Է�
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < M; col++) {
			scanf_s("%d", &map[row][col].value);
		}
	}

	//map�� ��� ���鿡 ���ؼ� DFS �˰����� ����
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("<%d,%d> ��带 �������� DFS ����!!\n",i,j);
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

	//�Ҵ� ����
	for (int i = 0; i < N; i++) {
		free(map[i]);
	}
	free(map);
	
	//����
	return 0;
}