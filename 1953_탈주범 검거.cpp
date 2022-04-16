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
#include<queue>
#include<cstring>

using namespace std;

int n, m, r, c, l;
int board[50][50][4];
bool visited[50][50]; // 방문리스트

// 파이브 연결
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

// 북동남서
const int dy[4] = { -1,0,1,0 };
const int dx[4] = { 0,1,0,-1 };

// 너비우선탐색
int BFS(void) {
	int result = 0;
	queue<pair<int, int>> que;

	que.push({ r,c }); // 탈주범 위치
	visited[r][c] = 1;

	l--; // 탈주범은 한시간 뒤 맨홀에 들어감
	result++;

	while (l--) {
		int size = que.size();

		// 현재 시간대에 갈수 있는 곳 판단
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

				// 현재와 다음이 뚫여 있다면
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
	// 체크리스트 초기화
	memset(visited, 0, sizeof(visited));
	answer = BFS();

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
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}