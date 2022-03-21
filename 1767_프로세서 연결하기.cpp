#include <iostream>
#include <vector>

using namespace std;

int connect;
int result;
int board[13][13]; // ������
vector<pair<int, int>> process; // ���μ���

//�����¿�
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };

// �ּڰ� ��ȯ
int Min(int a, int b) {
	return a < b ? a : b;
}

// ���̿켱 Ž�� �̿��ؼ� ��Ʈ��ŷ ����
void DFS(int n, int level, int len, int cur_cnn) {
	// Ż������
	if (level == process.size()) {
		// ���� ���� ����
		if (cur_cnn > connect) {
			result = len;
			connect = cur_cnn;
		}

		// ���� ���
		else if (cur_cnn == connect)
			result = Min(result, len);

		return;
	}

	// ���������� 4���� Ž��
	for (int dir = 0; dir < 4; ++dir) {
		int ny = process[level].first;
		int nx = process[level].second;
		int cnt = 0; // ����

		while (1) {
			ny += dy[dir];
			nx += dx[dir];
			cnt++; // ���� ī��Ʈ

			// ���� �Ǵ� ���μ����� ����ģ�ٸ�
			if (board[ny][nx] == 1 || board[ny][nx] == 2) {
				cnt = 0;
				break; 
			}

			// �� ���������� �ܰ��� ���
			if (board[ny][nx] == 0 && (ny == 1 || nx == 1 || nx == n || ny == n)) 
				break;
		}

		// ������ ��ġ �����ϸ�
		if (cnt > 0) {
			int ny = process[level].first;
			int nx = process[level].second;
			
			while (1) {
				ny += dy[dir];
				nx += dx[dir];

				// ���� �ʰ�
				if (ny < 1 || nx < 1 || nx > n || ny > n) 
					break;

				board[ny][nx] = 2; // ���� ó��
			}

			// ȣ��
			DFS(n, level + 1, len + cnt, cur_cnn + 1);
			// ��Ʈ��ŷ�� ����
			ny = process[level].first;
			nx = process[level].second;

			while (1) {
				ny += dy[dir];
				nx += dx[dir];

				// ���� �ʰ�
				if (ny < 1 || nx < 1 || nx > n || ny > n)
					break;

				board[ny][nx] = 0; // �� ĭ ó��
			}
		}
	}

	//�̹��� ������ �� ȣ��
	DFS(n, level + 1, len, cur_cnn);

	return;
}

int solution(int n) {
	int answer = 0;

	process.clear(); // ����
	//�ܰ��� ���μ����� �����ϰ� ���μ��� ��ġ Ȯ��
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (board[i][j] == 1) { // ���μ��� �߰�
				if (i == 1 || j == n || i == n || j == 1)
					continue;
				process.push_back({ i,j });
			}
		}
	}

	connect = 0; // �ʱ�ȭ
	result = 0x7fffffff; // �ּҸ� ����
	DFS(n, 0, 0, 0);
	answer = result;
	return answer;
}

int main(int argc, char** argv) {
	int test_case;
	int T;

	cin >> T;
	// ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	for (test_case = 1; test_case <= T; ++test_case) {
		int n;

		cin >> n;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j)
				cin >> board[i][j];
		}

		// ��� ���
		int ret = solution(n);
		cout << '#' << test_case << ' ' << ret << '\n';
	}
	return 0; // ��������� �ݵ�� 0�� �����ؾ��մϴ�.
}