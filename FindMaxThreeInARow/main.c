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

void printMap(Node** map, int N, int M) {
	//��ü��Ʈ ����غ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("<%d, %d> ", map[i][j].value, map[i][j].visited);
		}
		printf("\n");
	}
	printf("\n");

}

int DFS(Node** map,int N, int M, int a, int b,int _sum, int _count) {
	int sum = _sum;     // <a,b>�� �������� ���̿켱Ž���� ���� �� ���� ū ���ӵ� �� ���� ��       
	int count = _count; // Root Node �ܿ� �� ���� value�� ���������� ��Ÿ��
	int sub_max = 0;    // Root Node�� 4���� �� �� ���⿡�� ã�� �ִ밪?????????


	//Root Node �湮
	map[a][b].visited = 1;

	printMap(map, N, M);
	

	for (int i = -1; i <= 1; i++) {      // -1 <= i <= +1
		for (int j = -1; j <= 1; j++) {  // -1 <= j <= +1
			//printf("Root <%d,%d> 's <i,j> is <%d,%d>\n",a,b, i, j);

			if (getAbsolute(i) + getAbsolute(j) == 1) {// Root�� �����¿��� ��
				if (a + i < 0 || N - 1 < a + i || b + j < 0 || M - 1 < b + j) continue; //���� �Ұ����� �ε��� ó��
				
				//Root Node�� �����¿� �� �ϳ��� ���� ���� �������� �ʾҴٸ�
				if (map[a + i][b + j].visited == 0) {
					printf("<%d,%d> -> <%d,%d> successed", a, b, a + i, b + j);
					if (count == 0) {//�ϳ��� ���� ���� �� �װ����� DFS�� call �ؾ��ϸ�
						map[a + i][b + j].visited = 1;
						sum += map[a + i][b + j].value;
						count += 1;
						

						printf("ncall procedure Root = <%d, %d>\n",a+i, b+j);
						int sub_sub_max = 0; //������ ���̿��� return�� ��
						sub_sub_max = DFS(map, N, M, a+i, b + j, sum, count);
						count -= 1; //�����¿� �� �� �������� ��ġ���Ⱑ ������ count -1
						sum -= map[a + i][b + j].value; //�̵��ؼ� ��ġ���Ⱑ �ٽ� �����ߴ� ���� ���ش�. 
						printf("sub_sub_max is %d\n", sub_sub_max);
						if (sub_max < sub_sub_max) {
							sub_max = sub_sub_max;
						}
					}
					else if (count == 1) {//�ϳ��� ���� �� ���ϸ� �Ǹ�
						map[a + i][b + j].visited = 1;
						if (getAbsolute(a + i) + getAbsolute(b + j) == 2) {//���� Root ��忡 ���ؼ� �밢���̸�
							map[a + i][b + j].visited = 0;
						}
						sum += map[a + i][b + j].value;
						printf("�� ���� ���� %d\n", sum);
						if (sub_max < sum) {
							sub_max = sum;
						}
						if (i == 1 && j == 0) {//����� �� Ȯ�������� return
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

	//�湮��� �ʱ�ȭ
	printf("###�湮 �ʱ�ȭ~~~~~~####\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j].visited = 0;
		}
	}
	printf("�� DFS���� �ִ����� %d\n\n", sub_max);
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
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("<%d,%d> ��带 �������� DFS ����!!\n", i, j);
			int sum_max = DFS(map, N, M, i, j, map[i][j].value, 0);
			if (max < sum_max) {
				max = sum_max;
			}
		}
	}
	printf("@@@@@@@@@\n");
	printf("max is %d\n", max);
	printf("@@@@@@@@@\n");

	//�Ҵ� ����
	for (int i = 0; i < N; i++) {
		free(map[i]);
	}
	free(map);
	
	//����
	return 0;
}