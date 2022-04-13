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

#include<iostream>
#include<cstring>

using namespace std;

int board[8][8];
int visited[8][8];
int path = 0;

// 상하좌우
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };

// 최댓값 반환
int Max(int a, int b) {
	return a > b ? a : b;
}

// 깊이우선탐색
void DFS(int n, int k, int y, int x, bool flag, int level) {
	path = Max(path, level); // 교체
	for (int dir = 0; dir < 4; ++dir) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n)
			continue;

		if (visited[ny][nx] == 1)
			continue;

		// 깍지 않아도 되는 경우
		if (board[ny][nx] < board[y][x]) {
			visited[ny][nx] = 1;
			DFS(n, k, ny, nx, flag, level + 1);
			visited[ny][nx] = 0;
		}

		// 깍아야 하는 경우
		else if (flag == 0 && board[ny][nx] >= board[y][x]) {
			// 최소한으로 깎는다
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
			visited[i][j] = 0; // 방문리스트 초기화
		}
	}
	
	// 높은 봉우리에서 시작
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// 발견
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
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
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
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}