/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<cstring> 

using namespace std;

int n, result;
int board[20][20];
bool visited[20][20]; // 방문리스트
bool numbers[101]; // 디저트 종류

// 마름모 방향
const int dy[4] = { -1,-1,1,1 };
const int dx[4] = { -1,1,-1,1 };

int Max(int a, int b) {
	return a > b ? a : b;
}

// 범위판단
bool in_Range(int y, int x) {
	return y >= 0 && x >= 0 && y < n && x < n;
}

// 깊이우선탐색
void DFS(int cy, int cx, int sy, int sx, int d, int cnt, int level) {
	// 마지막은 sy, sx에 가야하므로
	if (cnt > 4)
		return;

	for (int dir = 0; dir < 4; ++dir) {
		int ny = cy + dy[dir];
		int nx = cx + dx[dir];

		// 범위 내
		if (in_Range(ny, nx)) {
			// 방문한 곳이면
			if (visited[ny][nx]) {
				// 돌아올떄가 되었으면
				if (cnt >= 3 && level >= 4) {
					if (ny == sy && nx == sx) {
						result = Max(result, level);
						return;
					}
				}
			}

			// 미방문이면
			else {
				if (!numbers[board[ny][nx]]) {
					visited[ny][nx] = 1;
					numbers[board[ny][nx]] = 1;

					// 현재 같은 방향으로 진행하면
					if (dir == d)
						DFS(ny, nx, sy, sx, d, cnt, level + 1);
					else
						DFS(ny, nx, sy, sx, dir, cnt + 1, level + 1);

					visited[ny][nx] = 0;
					numbers[board[ny][nx]] = 0;
				}
			}
		}
	}

	return;
}

int solution(void) {
	int answer = 0;
	// 초기화
	memset(visited, 0, sizeof(visited));
	memset(numbers, 0, sizeof(numbers));
	result = -1; 

	// 백트래킹
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j < n - 1; ++j) {
			visited[i][j] = 1;
			numbers[board[i][j]] = 1;

			int ny = i + dy[3];
			int nx = j + dx[3];

			// 이동이 가능하다면
			if (in_Range(ny, nx) && !numbers[board[ny][nx]]) {
				visited[ny][nx] = 1;
				numbers[board[ny][nx]] = 1;

				DFS(ny, nx, i, j, 3, 1, 2);

				visited[ny][nx] = 0;
				numbers[board[ny][nx]] = 0;
			}
			
			visited[i][j] = 0;
			numbers[board[i][j]] = 0;
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
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
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
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
