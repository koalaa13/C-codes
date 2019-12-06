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
//#pragma comment(linker, "/STACK:256000000")
using namespace std;

#define mp make_pair
#define NAME "queuemin2"
/*#define FAST_ALLOCATOR_MEMORY 2e8
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
#endif*/

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

int INF = numeric_limits<int>::max();

struct myvector {
	int sz, free_ind, *arr;
	myvector() {
		sz = 1;
		free_ind = 0;
		arr = new int[1];
	}
	myvector(int m) {
		sz = m;
		free_ind = 0;
		arr = new int[m];
	}
	bool empty() {
		return !free_ind;
	}
	int size() {
		return free_ind;
	}
	void push_back(int v) {
		if (free_ind < sz) {
			arr[free_ind++] = v;
		}
	}
	void pop_back() {
		if (!empty()) {
			free_ind--;
		}
	}
	int back() {
		if (!empty()) {
			return arr[free_ind - 1];
		}
		return INF;
	}
};

struct myqueue {
	myvector* f;
	myvector* f_min;
	myvector* b;
	myvector* b_min;
	myqueue() {
		f = new myvector();
		f_min = new myvector();
		b = new myvector();
		b_min = new myvector();
	}
	myqueue(int m) {
		f = new myvector(m);
		f_min = new myvector(m);
		b = new myvector(m);
		b_min = new myvector(m);
	}
	void push(int v) {
		b->push_back(v);
		b_min->push_back(min(b_min->back(), v));
	}
	void pop() {
		if (f->empty()) {
			while (!b->empty()) {
				f->push_back(b->back());
				f_min->push_back(min(f_min->back(), b->back()));
				b->pop_back();
				b_min->pop_back();
			}
		}
		f->pop_back();
		f_min->pop_back();
	}
	int front() {
		if (f->empty()) {
			while (!b->empty()) {
				f->push_back(b->back());
				f_min->push_back(min(f_min->back(), b->back()));
				b->pop_back();
				b_min->pop_back();
			}
		}
		return f->back();
	}
	int size() {
		return f->size() + b->size();
	}
	int get_min() {
		return min(f_min->back(), b_min->back());
	}
};

inline int get(myqueue &q, const int &m) {
	if (q.size() < m) {
		return 0;
	}
	if (q.size() > m) {
		q.pop();
	}
	return q.get_min();
}

int main() {
#if SOLVE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#else
	freopen(NAME".in", "r", stdin);
	freopen(NAME".out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//srand(time(NULL));
	//cout.precision(20);
	//cout.setf(ios::fixed);

	int n, m, k, a, b, c, ls[2];
	ll sum = 0;
	cin >> n >> m >> k >> a >> b >> c;
	myqueue q(m + 1);
	for (int i = 0; i < k; ++i) {
		int v;
		cin >> v;
		q.push(v);
		sum += get(q, m);
		if (i < 2) {
			ls[i] = v;
		}
		else {
			ls[0] = ls[1];
			ls[1] = v;
		}
	}
	for (int i = k; i < n; ++i) {
		int y = a * ls[0] + b * ls[1] + c;
		q.push(y);
		sum += get(q, m);
		ls[0] = ls[1];
		ls[1] = y;
	}
	cout << sum;
	
	//cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}