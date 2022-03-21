#include <iostream>
#include <vector>

using namespace std;

int connect;
int result;
int board[13][13]; // 격자판
vector<pair<int, int>> process; // 프로세서

//상하좌우
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };

// 최솟값 반환
int Min(int a, int b) {
	return a < b ? a : b;
}

// 깊이우선 탐색 이용해서 백트래킹 시작
void DFS(int n, int level, int len, int cur_cnn) {
	// 탈출조건
	if (level == process.size()) {
		// 길이 변경 조건
		if (cur_cnn > connect) {
			result = len;
			connect = cur_cnn;
		}

		// 같을 경우
		else if (cur_cnn == connect)
			result = Min(result, len);

		return;
	}

	// 순차적으로 4방향 탐색
	for (int dir = 0; dir < 4; ++dir) {
		int ny = process[level].first;
		int nx = process[level].second;
		int cnt = 0; // 전선

		while (1) {
			ny += dy[dir];
			nx += dx[dir];
			cnt++; // 전선 카운트

			// 전선 또는 프로세서와 마주친다면
			if (board[ny][nx] == 1 || board[ny][nx] == 2) {
				cnt = 0;
				break; 
			}

			// 빈 공간이지만 외곽인 경우
			if (board[ny][nx] == 0 && (ny == 1 || nx == 1 || nx == n || ny == n)) 
				break;
		}

		// 전선을 설치 가능하면
		if (cnt > 0) {
			int ny = process[level].first;
			int nx = process[level].second;
			
			while (1) {
				ny += dy[dir];
				nx += dx[dir];

				// 범위 초과
				if (ny < 1 || nx < 1 || nx > n || ny > n) 
					break;

				board[ny][nx] = 2; // 전선 처리
			}

			// 호출
			DFS(n, level + 1, len + cnt, cur_cnn + 1);
			// 백트래킹을 위해
			ny = process[level].first;
			nx = process[level].second;

			while (1) {
				ny += dy[dir];
				nx += dx[dir];

				// 범위 초과
				if (ny < 1 || nx < 1 || nx > n || ny > n)
					break;

				board[ny][nx] = 0; // 빈 칸 처리
			}
		}
	}

	//이번엔 생략한 것 호출
	DFS(n, level + 1, len, cur_cnn);

	return;
}

int solution(int n) {
	int answer = 0;

	process.clear(); // 비우기
	//외각은 프로세서를 무시하고 프로세서 위치 확인
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (board[i][j] == 1) { // 프로세서 발견
				if (i == 1 || j == n || i == n || j == 1)
					continue;
				process.push_back({ i,j });
			}
		}
	}

	connect = 0; // 초기화
	result = 0x7fffffff; // 최소를 위한
	DFS(n, 0, 0, 0);
	answer = result;
	return answer;
}

int main(int argc, char** argv) {
	int test_case;
	int T;

	cin >> T;
	// 여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	for (test_case = 1; test_case <= T; ++test_case) {
		int n;

		cin >> n;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j)
				cin >> board[i][j];
		}

		// 답안 출력
		int ret = solution(n);
		cout << '#' << test_case << ' ' << ret << '\n';
	}
	return 0; // 정상종료시 반드시 0을 리턴해야합니다.
}