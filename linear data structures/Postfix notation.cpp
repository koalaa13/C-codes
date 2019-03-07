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
#define NAME "postfix"
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

const int trash = numeric_limits<int>::min();

struct cell {
	int val;
	cell* prev;
	cell() {
		this->val = 0;
		this->prev = NULL;
	}
	cell(int v, cell* prev) {
		this->val = v;
		this->prev = prev;
	}
};

struct mystack {
	cell* head;
	mystack() {
		this->head = new cell();
	}
	mystack(cell* head) {
		this->head = head;
	}
	bool empty() {
		return this->head->prev == NULL;
	}
	void push(int v) {
		cell* new_head = new cell({ v, this->head });
		this->head = new_head;
	}
	void pop() {
		if (!empty()) {
			cell* new_head = this->head->prev;
			delete[] this->head;
			this->head = new_head;
		}
	}
	int top() {
		if (!empty()) {
			return this->head->val;
		}
		return trash;
	}
	int top_pop() {
		if (!empty()) {
			int res = this->head->val;
			pop();
			return res;
		}
		return trash;
	}
};

inline void conv(mystack* a, mystack *b) {
	while (!b->empty()) {
		a->push(b->top());
		b->pop();
	}
}

struct myqueue {
	mystack* f;
	mystack *b;
	myqueue() {
		this->f = new mystack();
		this->b = new mystack();
	}
	myqueue(mystack* f, mystack* b) {
		this->f = f;
		this->b = b;
	}
	void push(int v) {
		b->push(v);
	}
	void pop() {
		if (f->empty()) {
			conv(f, b);
		}
		f->pop();
	}
	int front() {
		if (f->empty()) {
			conv(f, b);
		}
		return f->top();
	}
};

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

	char c;
	mystack st;
	while (cin >> c) {
		if (c == '+') {
			int a = st.top_pop();
			int b = st.top_pop();
			st.push(a + b);
			continue;
		}
		if (c == '-') {
			int a = st.top_pop();
			int b = st.top_pop();
			st.push(b - a);
			continue;
		}
		if (c == '*') {
			int a = st.top_pop();
			int b = st.top_pop();
			st.push(a * b);
			continue;
		}
		st.push(c - '0');
	}
	cout << st.top_pop();

	//cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}