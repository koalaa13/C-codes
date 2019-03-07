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
//#pragma comment(linker, "/STACK:256000000")
using namespace std;

#define mp make_pair
#define NAME "stack2"
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

struct cell {
	int val;
	cell* prev;
};

struct mystack {
	cell* head;
	mystack(cell* head) {
		this->head = head;
	}
	void push(int v){
		cell* new_head = new cell({ v, this->head });
		this->head = new_head;
	}
	void pop() {
		if (this->head->prev != NULL) {
			cell* new_head = this->head->prev;
			delete[] this->head;
			this->head = new_head;
		}
	}
	int top() {
		return this->head->val;
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

	//cell* head = new cell({0, NULL});
	mystack st(new cell({ 0, NULL }));
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		char t;
		cin >> t;
		if (t == '+') {
			int v;
			cin >> v;
			st.push(v);
		}
		else {
			cout << st.top() << "\n";
			st.pop();
		}
	}

	//cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}