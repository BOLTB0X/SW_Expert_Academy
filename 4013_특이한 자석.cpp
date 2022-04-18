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
#include<vector>
#include<queue>

using namespace std;

int k;
deque<int> gears[5];
vector<pair<int, int>> cmd;

void rotate_prepare(queue<pair<int,int>>& que, int idx, int dir) {
	int cidx = idx;
	int cd = dir;
	que.push({ cidx, cd });

	// ->
	while (1) {
		if (cidx == 4)
			break;

		cidx++;
		cd *= -1;

		// 극 이 다르면
		if (gears[cidx - 1][2] != gears[cidx][6])
			que.push({ cidx, cd });
		else
			break;
	}

	cidx = idx;
	cd = dir;

	// <-
	while (1) {
		if (cidx == 1)
			break;

		cidx--;
		cd *= -1;

		// 극 이 다르면
		if (gears[cidx + 1][6] != gears[cidx][2])
			que.push({ cidx, cd });
		else
			break;
	}

	return;
}

// 회전
void rotate_gear(queue<pair<int, int>>& que) {
	while (!que.empty()) {
		int cidx = que.front().first;
		int cd = que.front().second;
		que.pop();

		// 반시계방향
		if (cd == -1) {
			int tmp = gears[cidx][0];
			gears[cidx].pop_front();
			gears[cidx].push_back(tmp);
		}
		
		// 시계
		else if (cd == 1) {
			int tmp = gears[cidx][7];
			gears[cidx].pop_back();
			gears[cidx].push_front(tmp);
		}
	}

	return;
}

int solution(void) {
	int answer = 0;
	queue<pair<int, int>> que;

	for (auto& c : cmd) {
		int idx = c.first;
		int dir = c.second;

		rotate_prepare(que, idx, dir);
		rotate_gear(que);
		while (!que.empty())
			que.pop();
	}

	// 점수계산
	for (int i = 1, cnt = 1; i <= 4; ++i, cnt *= 2) {
		if (gears[i][0] == 1)
			answer += cnt;
	}

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
		cmd.clear();
		for (int i = 1; i <= 4; ++i) 
			gears[i].clear(); // 초기화
	
		cin >> k;
		int a, b;
		for (int i = 1; i <= 4; ++i) {
			for (int j = 0; j < 8; ++j) {
				cin >> a;
				gears[i].push_back(a);
			}
		}

		for (int i = 0; i < k; ++i) {
			cin >> a >> b;
			cmd.push_back({ a,b });
		}
		
		int ret = solution();
		cout << '#' << test_case << ' ' << ret << '\n';
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}