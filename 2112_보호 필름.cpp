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

int result;
int D, W, K;
int board[13][20];
int cboard[13][20];
int row[20];

int Min(int a, int b) {
	return a < b ? a : b;
}

// 통과되는 체크
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
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
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
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}