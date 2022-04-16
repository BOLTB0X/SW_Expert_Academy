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

int n, result;
int board[20][20];
bool visited[20][20];
bool number[101];

// �밢������
const int dy[4] = {-1,-1, 1,1};
const int dx[4] = { -1,1,-1,1 };

int Max(int a, int b) {
	return a > b ? a : b;
}

// ��Ʈ��ŷ
void DFS(int y, int x, int sy, int sx, int d, int line, int level) {
	// Ż�� ����
	if (line > 4)
		return;

	for (int dir = 0; dir < 4; ++dir) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny >= 0 && nx >= 0 && ny < n && nx < n) {
			if (visited[ny][nx] == 1) {
				if (line >= 3 && level >= 4) {
					if (ny == sy && nx == sx) {
						result = Max(result, level);
						return;
					}
				}
			}

			else {
				if (!number[board[ny][nx]]) {
					visited[ny][nx] = 1;
					number[board[ny][nx]] = 1;

					if (dir == d)
						DFS(ny, nx, sy, sx, d, line, level + 1);
					else
						DFS(ny, nx, sy, sx, dir, line + 1, level + 1);
					visited[ny][nx] = 0;
					number[board[ny][nx]] = 0;
				}
			}
		}
	}

	return;
}

int solution(void) {
	int answer = 0;
	// �ʱ�ȭ
	memset(visited, 0, sizeof(visited));
	memset(number, 0, sizeof(number));
	result = -1;

	// Ž�� ����
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j < n - 1; ++j) {
			visited[i][j] = 1;
			number[board[i][j]] = 1;

			int ny = i + dy[3];
			int nx = j + dx[3];

			if (ny>= 0 && nx >=0 && ny < n && nx < n) {
				if (!number[board[ny][nx]]) {
					visited[ny][nx] = 1;
					number[board[ny][nx]] = 1;
					DFS(ny, nx, i, j, 3, 1, 2);
					visited[ny][nx] = 0;
					number[board[ny][nx]] = 0;
				}
			}
			visited[i][j] = 0;
			number[board[i][j]] = 0;
		}
	}
	
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
	//freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
		cin >> n;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cin >> board[i][j];
		}

		int ret = solution();
		cout << '#' << test_case << ' ' << ret << '\n';
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}