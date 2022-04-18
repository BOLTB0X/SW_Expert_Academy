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

		// �� �� �ٸ���
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

		// �� �� �ٸ���
		if (gears[cidx + 1][6] != gears[cidx][2])
			que.push({ cidx, cd });
		else
			break;
	}

	return;
}

// ȸ��
void rotate_gear(queue<pair<int, int>>& que) {
	while (!que.empty()) {
		int cidx = que.front().first;
		int cd = que.front().second;
		que.pop();

		// �ݽð����
		if (cd == -1) {
			int tmp = gears[cidx][0];
			gears[cidx].pop_front();
			gears[cidx].push_back(tmp);
		}
		
		// �ð�
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

	// �������
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
	   �Ʒ��� freopen �Լ��� input.txt �� read only �������� �� ��,
	   ������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸκ��� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	   //�������� �ۼ��� �ڵ带 �׽�Ʈ �� ��, ���Ǹ� ���ؼ� input.txt�� �Է��� ������ ��,
	   freopen �Լ��� �̿��ϸ� ���� cin �� ������ �� ǥ�� �Է� ��� ���Ϸκ��� �Է��� �޾ƿ� �� �ֽ��ϴ�.
	   ���� �׽�Ʈ�� ������ ������ �Ʒ� �ּ��� ����� �� �Լ��� ����ϼŵ� �����ϴ�.
	   freopen �Լ��� ����ϱ� ���ؼ��� #include <cstdio>, Ȥ�� #include <stdio.h> �� �ʿ��մϴ�.
	   ��, ä���� ���� �ڵ带 �����Ͻ� ������ �ݵ�� freopen �Լ��� ����ų� �ּ� ó�� �ϼž� �մϴ�.
	*/
	freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		cmd.clear();
		for (int i = 1; i <= 4; ++i) 
			gears[i].clear(); // �ʱ�ȭ
	
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
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}