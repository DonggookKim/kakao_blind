// kakao_blind.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

// Headers for RESTful API
//#include <cpprest/http_listener.h>              // HTTP server
//#include <cpprest/json.h>                       // JSON library
//#include <cpprest/uri.h>                        // URI library
//#include <cpprest/ws_client.h>                  // WebSocket client
//#include <cpprest/containerstream.h>            // Async streams backed by STL containers
//#include <cpprest/interopstream.h>              // Bridges for integrating Async streams with STL and WinRT streams
//#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
//#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios
// Namespace for RESTful API
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

//using namespace web::http::experimental::listener;          // HTTP server
//using namespace web::experimental::web_sockets::client;     // WebSockets client
//using namespace web::json;                                  // JSON library

int main()
{
	auto fileStream = std::make_shared<ostream>();

	// Open stream to output file.
	pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
	{
		*fileStream = outFile;

		// Create http_client to send the request.
		http_client client(U("http://www.bing.com/"));

		// Build request URI and start the request.
		uri_builder builder(U("/search"));
		builder.append_query(U("q"), U("cpprestsdk github"));
		return client.request(methods::GET, builder.to_string());
	})

		// Handle response headers arriving.
		.then([=](http_response response)
	{
		printf("Received response status code:%u\n", response.status_code());

		// Write response body into the file.
		return response.body().read_to_end(fileStream->streambuf());
	})

		// Close the file stream.
		.then([=](size_t)
	{
		return fileStream->close();
	});

	// Wait for all the outstanding I/O to complete and handle any exceptions
	try
	{
		requestTask.wait();
	}
	catch (const std::exception &e)
	{
		printf("Error exception:%s\n", e.what());
	}

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

//
//
////solution1
//int solution_1(string s) {
//	int answer = 0;
//
//	// 몇개 단위로 자를지 확인해야함
//	/*
//	2ababcdcd
//	abcabcdede -> 2abcdede
//
//	일단 brute force하게 접근해서, 전체 입력 길이 / 2 길이까지 하나씩 다 해보고 가장 짧게 되는지 확인해보기
//	*/
//	int length = s.length();
//	string stndString = "";
//	string matchString = "";
//
//	string zipString = "";
//	int ziplength = 0;
//	int min = length;
//	int cnt = 1;
//	for (int crop_length = 1; crop_length < length / 2; crop_length++) {
//		stndString = s.substr(0, crop_length);
//		cnt = 1;
//		for (int i = 1; i < (length / crop_length + 0.5) + 1; i++) {
//			matchString = s.substr(i*crop_length, crop_length);
//			// 압축 가능한 문구인 경우
//			if (stndString.compare(matchString) == 0) {
//				cnt++;
//			}
//			// 압축 불가능한 문구인 경우
//			else {
//				if (cnt == 1) {
//					zipString.append(stndString);
//				}
//				else {
//					zipString.append(to_string(cnt));
//					zipString.append(stndString);
//				}
//				stndString = s.substr(i*crop_length, crop_length);
//				if (stndString.length() < crop_length) {
//					zipString.append(stndString);
//					break;
//				}
//				cnt = 1;
//			}
//		}
//
//		ziplength = zipString.length();
//		if (min > ziplength) {
//			min = ziplength;
//		}
//		zipString = "";
//	}
//	answer = min;
//
//	return answer;
//}
//
////solution2
//bool good_string(string p) {
//	int len = p.length();
//	int cnt = 0;
//	for (int i = 0; i < len; i++) {
//		if (p[i] == '(') {
//			cnt++;
//		}
//		if (p[i] == ')') {
//			cnt--;
//		}
//		if (cnt < 0) {
//			return false;
//		}
//	}
//	return true;
//}
//string recur(string p) {
//	if (p.compare("") == 0) {
//		return "";
//	}
//	if (good_string(p)) {
//		return p;
//	}
//	string u, v;
//
//	int cnt = 0;
//	int plen = p.length();
//	for (int i = 0; i < plen; i++) {
//		if (p[i] == '(') {
//			cnt++;
//		}
//		if (p[i] == ')') {
//			cnt--;
//		}
//		if (i != 0 && cnt == 0) {
//			u = p.substr(0, i + 1);
//			v = p.substr(i + 1, plen - i);
//			break;
//		}
//	}
//
//	if (good_string(u)) {
//		string ret = u;
//		ret.append(recur(v));
//		return ret;
//	}
//	else {
//		string ret = "(";
//		ret.append(recur(v));
//		ret.append(")");
//		u = u.substr(1, u.length() - 2);
//		for (int i = 0; i < u.length(); i++) {
//			if (u[i] == '(') {
//				u[i] = ')';
//			}
//			else {
//				u[i] = '(';
//			}
//		}
//		ret.append(u);
//		return ret;
//	}
//
//}
//
////solution3
//int printV(vector<vector<int>> matrix) {
//	for (int i = 0; i < matrix.size(); i++) {
//		for (int j = 0; j < matrix[i].size(); j++) {
//			cout << matrix[i][j] << ' ';
//		}
//		cout << endl;
//	}
//	return 0;
//}
////오른쪽으로 90도 돌리기
//vector<vector<int>> rotate(vector<vector<int>> matrix) {
//	vector<vector<int>> ret = matrix;
//	for (int i = 0; i < ret.size(); i++) {
//		for (int j = 0; j < ret[i].size(); j++) {
//			ret[j][ret.size() - i - 1] = matrix[i][j];
//		}
//	}
//	return ret;
//}
//// a만큼 b만큼 이동하기
//vector<vector<int>> transpose(vector<vector<int>> matrix, int a, int b) {
//	vector<vector<int>> ret = matrix;
//	int tx, ty, ip;
//	for (int i = 0; i < ret.size(); i++) {
//		tx = i - a;
//		for (int j = 0; j < ret[i].size(); j++) {
//			ty = j - b;
//			if (tx > ret.size() - 1 || tx<0 || ty>ret[i].size() - 1 || ty < 0) {
//				ip = 0;
//			}
//			else {
//				ip = matrix[tx][ty];
//			}
//			ret[i][j] = ip;
//		}
//	}
//	return ret;
//}
//// 맞는 키인가 확인
//bool good_key(vector<vector<int>> key, vector<vector<int>> lock) {
//	for (int i = 0; i < lock.size(); i++) {
//		for (int j = 0; j < lock[i].size(); j++) {
//			if (lock[i][j] + key[i][j] != 1) {
//				return false;
//			}
//		}
//	}
//	return true;
//}
//
//bool solution3(vector<vector<int>> key, vector<vector<int>> lock) {
//	bool answer = true;
//	/*
//	Matrix를 조합했을때, 그 조합이 전체 꽉차게 만들수 있는지확인하면됨
//	key 크기를 lock크기로 강제로 늘리고, 나머지는 0을 채움. 그 후 노가다로 비교시키자
//	*/
//	vector<vector<int>> newKey = lock;
//	for (int i = 0; i < newKey.size(); i++) {
//		for (int j = 0; j < newKey[i].size(); j++) {
//			if (i > key.size() - 1 || j > key[0].size() - 1) {
//				newKey[i][j] = 0;
//			}
//			else {
//				newKey[i][j] = key[i][j];
//			}
//		}
//	}
//	int m = key.size();
//	int n = lock.size();
//	for (int rr = 0; rr < 4; rr++) {
//		vector<vector<int>> changedKey;
//		for (int i = -n + 1; i < n - 1; i++) {
//			for (int j = -n + 1; j < n - 1; j++) {
//				changedKey = transpose(newKey, i, j);
//				if (good_key(changedKey, lock)) {
//					return true;
//				}
//			}
//		}
//		newKey = rotate(newKey);
//	}
//	answer = false;
//	return answer;
//}
//
//
//
//// n미터 짜리 원 위에서 a점과 b점 사이의 거리
//int calculate_distance(int n, int a, int b) {
//	int ret = a - b;
//	if (ret < 0) {
//		ret = -ret;
//	}
//	if (ret > n - ret) {
//		ret = n - ret;
//	}
//	return ret;
//}
//// weak 위치 a부터 weak 위치 b까지의 커버할 수 있는 거리
//int calculate_weak_number(int n, int a, int b, vector<int> weak, int mode) {
//	// mode가 1이면 짧은 길이, mode가 0이면 긴쪽.
//	if (mode == 0) {
//		return b - a;
//	}
//	else {
//		return (weak.size() - (b - a) + 1);
//	}
//}
//
//int solution33(int n, vector<int> weak, vector<int> dist) {
//	int answer = 0;
//	int max = 0;
//	int sp, ep;
//	int distance;
//
//	int shortCover;
//	int longCover;
//	int mode = 0;
//	vector<int> re_weak;
//	for (int d = dist.size() - 1; d >= 0; d--) {
//		answer++;
//		for (int i = 0; i < weak.size(); i++) {
//			for (int j = i + 1; j < weak.size(); j++) {
//				//if (i == j)continue;
//				distance = calculate_distance(n, weak[i], weak[j]);
//				shortCover = -1;
//				longCover = -1;
//
//				if (distance <= dist[d]) {
//					shortCover = calculate_weak_number(n, i, j, weak, 0);
//				}
//				if (n - distance <= dist[d]) {
//					longCover = calculate_weak_number(n, i, j, weak, 1);
//				}
//				// 현재 이동가능 거리보다 작은 거리를 찾아서 커버치고 지우자
//				// 짧은 쪽으로 씌우자
//				if (shortCover > longCover) {
//					if (max < shortCover) {
//						max = shortCover;
//						sp = i;
//						ep = j;
//						mode = 0;
//					}
//				}
//				// 긴쪽으로 씌우자
//				else if (shortCover < longCover) {
//					if (max < longCover) {
//						max = longCover;
//						sp = i;
//						ep = j;
//						mode = 1;
//					}
//				}
//			}
//		}
//		// sp,ep사이에 있는 점들을 삭제
//		// 방향을 봐야겠네. 원에서 본 거리가 같으면 안쪽을 아니면 바깥쪽을 지움
//
//		if (mode == 0) { // 가까운 쪽으로 이동. 먼쪽 만 저장
//			distance = calculate_distance(n, weak[sp], weak[ep]); // 거리를 계산했는데
//			if (distance == weak[ep] - weak[sp]) { // 거리가 그냥 뺀거랑 같다면 -> 반환점 안지남
//				for (int i = 0; i < weak.size(); i++) {
//					if (i<sp || i>ep)
//						re_weak.emplace_back(weak[i]);
//				}
//			}
//			else { // 그게 아니면 반환점을 지나니까
//				for (int i = 0; i < weak.size(); i++) {
//					if (i > sp && i < ep)
//						re_weak.emplace_back(weak[i]);
//				}
//
//			}
//		}
//		else { // 먼쪽으로 이동. 가까운 쪽 만 저장
//			distance = calculate_distance(n, weak[sp], weak[ep]); // 거리를 계산했는데
//			if (distance == weak[ep] - weak[sp]) { // 거리가 그냥 뺀거랑 같다면 -> 반환점 안지남
//				for (int i = 0; i < weak.size(); i++) {
//					if (i > sp && i < ep)
//						re_weak.emplace_back(weak[i]);
//				}
//			}
//			else { // 그게 아니면 반환점을 지나니까
//				for (int i = 0; i < weak.size(); i++) {
//					if (i<sp || i>ep)
//						re_weak.emplace_back(weak[i]);
//				}
//
//			}
//
//		}
//
//		if (re_weak.empty()) {
//			break;
//		}
//		weak = re_weak;
//		re_weak = vector<int>();
//	}
//	return answer;
//}
//
//
//
//
//int map[100][100];
//int visit[100][100];
//int path_stack[1000];
//int min_path_stack[1000];
//int n;
//int minPath = 0x7ffffff;
//// 현재 위치에서 회전이 가능한가 확인
//bool rotatable(int x, int y) {
//	if (x + 1 > n || y + 1 > n) {
//		return false;
//	}
//	if (map[x][y] == 0 && map[x + 1][y] == 0 && map[x][y + 1] == 0 && map[x + 1][y + 1] == 0) {
//		return true;
//	}
//	return false;
//}
//
//int tracking(int x, int y, int time) {
//	if (time > minPath) {
//		return time;
//	}
//	if (x == n - 1 && y == n - 1) {
//		if (minPath > time) {
//			minPath = time;
//			for (int i = 0; i < time; i++) {
//				min_path_stack[i] = path_stack[i];
//			}
//		}
//		return time;
//	}
//	// 위 아래 왼쪽 오른쪽
//	visit[x][y] = 1;
//	if (x + 1 < n) {
//		if (map[x + 1][y] == 0 && visit[x + 1][y] == 0) {
//			path_stack[time] = 1;
//			tracking(x + 1, y, time + 1);
//		}
//	}
//	if (y + 1 < n) {
//		if (map[x][y + 1] == 0 && visit[x][y + 1] == 0) {
//			path_stack[time] = 2;
//			tracking(x, y + 1, time + 1);
//		}
//	}
//	if (x - 1 >= 0) {
//		if (map[x - 1][y] == 0 && visit[x - 1][y] == 0) {
//			path_stack[time] = 3;
//			tracking(x - 1, y, time + 1);
//		}
//	}
//	if (y - 1 >= 0) {
//		if (map[x][y - 1] == 0 && visit[x][y - 1] == 0) {
//			path_stack[time] = 4;
//			tracking(x, y - 1, time + 1);
//		}
//	}
//	visit[x][y] = 0;
//	return time;
//}
//
//int solution(vector<vector<int>> board) {
//	int answer = 0;
//	/*
//	back tracking?
//	// 경로를 먼저 찾고, 그 경로를 따라 갈때 회전해야하는 횟수를 더하는게 어떨까 싶음
//	// 시작점 기준은 1,0에서 N,N까지 가는거
//	*/
//	n = board.size();
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			map[i][j] = board[i][j];
//		}
//	}
//	tracking(0, 1, 0);
//
//	answer = minPath;
//	int normal_time = answer;
//	for (int i = 0; i < normal_time - 1; i++) {
//		if (min_path_stack[i] != min_path_stack[i + 1]) {
//			answer--;
//		}
//	}
//
//	return answer;
//}