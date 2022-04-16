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
#include<queue>
#include<cstring>

using namespace std;

int n, m, r, c, l;
int board[50][50][4];
bool visited[50][50]; // �湮����Ʈ

// ���̺� ����
bool pipe[8][4] = {
	{0,0,0,0},
	{1,1,1,1}, // 1
	{1,0,1,0}, // 2
	{0,1,0,1}, // 3
	{1,1,0,0}, // 4
	{0,1,1,0}, // 5
	{0,0,1,1}, // 6
	{1,0,0,1}  // 7
};

// �ϵ�����
const int dy[4] = { -1,0,1,0 };
const int dx[4] = { 0,1,0,-1 };

// �ʺ�켱Ž��
int BFS(void) {
	int result = 0;
	queue<pair<int, int>> que;

	que.push({ r,c }); // Ż�ֹ� ��ġ
	visited[r][c] = 1;

	l--; // Ż�ֹ��� �ѽð� �� ��Ȧ�� ��
	result++;

	while (l--) {
		int size = que.size();

		// ���� �ð��뿡 ���� �ִ� �� �Ǵ�
		for (int i = 0; i < size; ++i) {
			int cy = que.front().first;
			int cx = que.front().second;
			que.pop();

			for (int dir = 0; dir < 4; ++dir) {
				int ny = cy + dy[dir];
				int nx = cx + dx[dir];

				if (ny < 0 || nx < 0 || ny >= n || nx >= m)
					continue;

				if (visited[ny][nx] == 1)
					continue;

				// ����� ������ �տ� �ִٸ�
				if (board[cy][cx][dir] == 1 && board[ny][nx][(dir + 2) % 4] == 1) {
					visited[ny][nx] = 1;
					que.push({ ny,nx });
					result++;
				}
			}
		}
	}

	return result;
}

int solution(void) {
	int answer = 0;
	// üũ����Ʈ �ʱ�ȭ
	memset(visited, 0, sizeof(visited));
	answer = BFS();

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
		int tmp;
		cin >> n >> m >> r >> c >> l;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> tmp;
				for (int k = 0; k < 4; ++k)
					board[i][j][k] = pipe[tmp][k];
			}
		}
		int ret = solution();
		cout << '#' << test_case << ' ' << ret << '\n';
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}