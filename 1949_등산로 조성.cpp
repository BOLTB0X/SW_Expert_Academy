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

#include<iostream>
#include<cstring>

using namespace std;

int board[8][8];
int visited[8][8];
int path = 0;

// �����¿�
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };

// �ִ� ��ȯ
int Max(int a, int b) {
	return a > b ? a : b;
}

// ���̿켱Ž��
void DFS(int n, int k, int y, int x, bool flag, int level) {
	path = Max(path, level); // ��ü
	for (int dir = 0; dir < 4; ++dir) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n)
			continue;

		if (visited[ny][nx] == 1)
			continue;

		// ���� �ʾƵ� �Ǵ� ���
		if (board[ny][nx] < board[y][x]) {
			visited[ny][nx] = 1;
			DFS(n, k, ny, nx, flag, level + 1);
			visited[ny][nx] = 0;
		}

		// ��ƾ� �ϴ� ���
		else if (flag == 0 && board[ny][nx] >= board[y][x]) {
			// �ּ������� ��´�
			for (int h = 1; h <= k; ++h) {
				flag = 1;
				board[ny][nx] -= h;

				if (board[ny][nx] < board[y][x]) {
					visited[ny][nx] = 1;
					DFS(n, k, ny, nx, flag, level + 1);
					visited[ny][nx] = 0;
				}

				flag = 0;
				board[ny][nx] += h;
			}
		}
	}
	return;
}

int solution(int n, int k) {
	int answer = 0;
	path = 1;
	int max_height = -1;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			max_height = Max(max_height, board[i][j]);
			visited[i][j] = 0; // �湮����Ʈ �ʱ�ȭ
		}
	}
	
	// ���� ���츮���� ����
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// �߰�
			if (board[i][j] == max_height) {
				visited[i][j] = 1;
				DFS(n, k, i, j, 0, 1);
				visited[i][j] = 0;
			}
		}
	}

	answer = path;
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
	//freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		int n, k;

		cin >> n >> k;
		memset(board, 0, sizeof(board));
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cin >> board[i][j];
		}

		int ret = solution(n, k);
		cout << '#' << test_case << ' ' << ret << '\n';
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}