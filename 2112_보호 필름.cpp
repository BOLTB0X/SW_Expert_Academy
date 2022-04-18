/////////////////////////////////////////////////////////////////////////////////////////////
// �⺻ �����ڵ�� ���� �����ص� ���� �����ϴ�. ��, ����� ���� ����
// �Ʒ� ǥ�� ����� ���� �ʿ�� �����ϼ���.
// ǥ�� �Է� ����
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int ���� 1�� �Է¹޴� ����
// cin >> b >> c;                       // float ���� 2�� �Է¹޴� ���� 
// cin >> d >> e >> f;                  // double ���� 3�� �Է¹޴� ����
// cin >> g;                            // char ���� 1�� �Է¹޴� ����
// cin >> var;                          // ���ڿ� 1�� �Է¹޴� ����
// cin >> AB;                           // long long ���� 1�� �Է¹޴� ����
/////////////////////////////////////////////////////////////////////////////////////////////
// ǥ�� ��� ����
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int ���� 1�� ����ϴ� ����
// cout << b << " " << c;               // float ���� 2�� ����ϴ� ����
// cout << d << " " << e << " " << f;   // double ���� 3�� ����ϴ� ����
// cout << g;                           // char ���� 1�� ����ϴ� ����
// cout << var;                         // ���ڿ� 1�� ����ϴ� ����
// cout << AB;                          // long long ���� 1�� ����ϴ� ����
/////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<cstring>

using namespace std;

int result;
int D, W, K;
int board[13][20];
int cboard[13][20];
int row[20];

int Min(int a, int b) {
	return a < b ? a : b;
}

// ����Ǵ� üũ
bool is_pass(void) {
	for (int i = 0; i < W; ++i) {
		int cur = board[0][i];
		int cnt = 1;

		for (int j = 1; j < D; ++j) {
			if (cnt == K)
				break;
			if (cur == board[j][i])
				cnt++;

			else {
				cur = board[j][i];
				cnt = 1;
			}
		}

		if (cnt < K)
			return 0;
	}

	return 1;
}

void DFS(int cur, int level) {
	if (level >= result)
		return;

	if (cur == D + 1) {
		memcpy(cboard, board, sizeof(cboard));
		for (int i = 0; i < D; ++i) {
			if (row[i] != -1) {
				for (int j = 0; j < W; ++j) {
					board[i][j] = row[i];
				}
			}
		}

		if (is_pass())
			result = Min(result, level);

		memcpy(board, cboard, sizeof(board));
		return;
	}

	row[cur] = -1;
	DFS(cur + 1, level);
	if (cur == D)
		return;

	row[cur] = 0;
	DFS(cur + 1, level + 1);
	row[cur] = 1;
	DFS(cur + 1, level + 1);

	return;
}

int solution(void) {
	int answer = 0;
	result = 20;
	memset(row, 0, 20);
	DFS(0, 0);
	
	answer = result;
	return answer;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   �Ʒ��� freopen �Լ��� input.txt �� read only �������� �� ��,
	   ������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸκ��� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	   //�������� �ۼ��� �ڵ带 �׽�Ʈ �� ��, ���Ǹ� ���ؼ� input.txt�� �Է��� ������ ��,
	   freopen �Լ��� �̿��ϸ� ���� cin �� ������ �� ǥ�� �Է� ��� ���Ϸκ��� �Է��� �޾ƿ� �� �ֽ��ϴ�.
	   ���� �׽�Ʈ�� ������ ������ �Ʒ� �ּ��� ����� �� �Լ��� ����ϼŵ� �����ϴ�.
	   freopen �Լ��� ����ϱ� ���ؼ��� #include <cstdio>, Ȥ�� #include <stdio.h> �� �ʿ��մϴ�.
	   ��, ä���� ���� �ڵ带 �����Ͻ� ������ �ݵ�� freopen �Լ��� ����ų� �ּ� ó�� �ϼž� �մϴ�.
	*/
	freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
		cin >> D >> W >> K;
		for (int i = 0; i < D; ++i) {
			for (int j = 0; j < W; ++j)
				cin >> board[i][j];
		}

		int ret = solution();
		cout << '#' << test_case << ' ' << ret << '\n';
		/////////////////////////////////////////////////////////////////////////////////////////////
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}