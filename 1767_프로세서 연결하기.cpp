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
#include<vector>

using namespace std;

int n, connect, result;
int board[12][12];
vector<pair<int, int>> process;

// 상하좌우
const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,-1,1 };

// 최소값 반환
int Min(int a, int b) {
	return a < b ? a : b;
}

void DFS(int len, int cur_cnn, int level) {
	// 탈출 조건
	if (level == process.size()) {
		if (cur_cnn > connect) {
			result = len;
			connect = cur_cnn;
		}

		else if (cur_cnn == connect)
			result = Min(result, len);
		return;
	}

	for (int dir = 0; dir < 4; ++dir) {
		int ny = process[level].first;
		int nx = process[level].second;
		int cnt = 0; // 전선

		// 전선 설치
		while (1) {
			ny += dy[dir];
			nx += dx[dir];
			cnt++; // 카운트

			// 전선 또는 프로세서와 만남
			if (board[ny][nx] == 1 || board[ny][nx] == 2) {
				cnt = 0;
				break;
			}

			// 빈공간이지만 외곽인 경우
			if (board[ny][nx] == 0 && (ny == 0 || nx == 0 || ny == n - 1 || nx == n - 1))
				break;
		}

		// 설치가 가능한 경우
		if (cnt > 0) {
			ny = process[level].first;
			nx = process[level].second;

			while (1) {
				ny += dy[dir];
				nx += dx[dir];

				// 범위초과
				if (ny < 0 || nx < 0 || ny >= n || nx >= n)
					break;

				board[ny][nx] = 2;
			}

			DFS(len + cnt, cur_cnn + 1, level + 1);
			ny = process[level].first;
			nx = process[level].second;

			while (1) {
				ny += dy[dir];
				nx += dx[dir];

				// 범위초과
				if (ny < 0 || nx < 0 || ny >= n || nx >= n)
					break;

				board[ny][nx] = 0;
			}
		}

	}

	// 이번엔 생략한 것 호출
	DFS(len, cur_cnn, level + 1);
	return;
}

int solution(void) {
	int answer = 0;
	result = 1e9;
	connect = 0; // 초기화
	process.clear(); // 시작전 비우기

	// 가장 자리 제외
	for (int i = 1; i < n - 1; ++i) {
		for (int j = 1; j < n - 1; ++j) {
			if (board[i][j] == 1)
				process.push_back({ i,j }); // 좌표
		}
	}

	// 백트래킹 시작
	DFS(0, 0, 0);
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
	//freopen("input.txt", "r", stdin);
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
