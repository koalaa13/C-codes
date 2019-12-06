#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <queue>
#include <algorithm>
#include <stack>
#include <ctime>
#include <cassert>
#include <complex>
#include <stdlib.h>
#include <limits>
// #pragma comment(linker, "/STACK:256000000")
using namespace std;

#define mp make_pair
#define NAME "kth"
/* #define FAST_ALLOCATOR_MEMORY 2e8
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
inline void* operator new(size_t n) {
char* res = allocator_memory + allocator_pos;
allocator_pos += n;
assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
return (void*)res;
}
inline void operator delete(void*)noexcept {}
// inline void * operator new [] ( size_t ) { assert(0); }
// inline void operator delete [] ( void * ) { assert(0); }
#endif */

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int N = 16;

vector<vector<pair<int, int>>> layers(10);

void build() {
	for (int i = 0; i < N; i += 2) {
		layers[0].push_back({ i, i + 1 });
	}
	//
	for (int i = 0; i < N; i += 4) {
		for (int l = i, r = i + 3; l < r; ++l, --r) {
			layers[1].push_back({ l, r });
		}
	}
	//
	layers[2] = layers[0];
	//
	for (int i = 0; i < N; i += 8) {
		for (int l = i, r = i + 7; l < r; ++l, --r) {
			layers[3].push_back({ l, r });
		}
	}
	//
	for (int i = 0; i < N; i += 4) {
		layers[4].push_back({ i, i + 2 });
		layers[4].push_back({ i + 1, i + 3 });
	}
	//
	layers[5] = layers[0];
	//
	for (int l = 0, r = 15; l < r; ++l, --r) {
		layers[6].push_back({ l, r });
	}
	//
	for (int i = 0; i < 4; ++i) {
		layers[7].push_back({ i, i + 4 });
	}
	for (int i = 8; i < 12; ++i) {
		layers[7].push_back({ i, i + 4 });
	}
	//
	layers[8] = layers[4];
	//
	layers[9] = layers[0];
}

int main() {
#if SOLVE
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
#else
	// freopen(NAME".in", "r", stdin);
	// freopen(NAME".out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	// srand((unsigned int)time(NULL));
	// cout.precision(20);
	// cout.setf(ios::fixed);

	build();
	int n, m = 0, k = 0;
	cin >> n;
	for (int i = 0; i < 10; ++i) {
		vector<pair<int, int>> layer;
		for (pair<int, int> j : layers[i]) {
			if (j.first < n && j.second < n) {
				layer.push_back(j);
			}
		}
		if (layer.size()) {
			m += (int)layer.size();
			k++;
		}
	}
	cout << n << " " << m << " " << k << "\n";
	for (int i = 0; i < 10; ++i) {
		vector<pair<int, int>> layer;
		for (pair<int, int> j : layers[i]) {
			if (j.first < n && j.second < n) {
				layer.push_back(j);
			}
		}
		if (layer.size()) {
			cout << layer.size() << " ";
			for (pair<int, int> j : layer) {
				cout << j.first + 1 << " " << j.second + 1 << " ";
			}
			cout << "\n";
		}
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
