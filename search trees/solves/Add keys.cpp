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

#define F first
#define S second
#define mp make_pair
#define NAME "bridge"
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

const int N = 131111;

struct Node {
	Node* left;
	Node* right;
	int pr, sz, value, cnt_z;
};

typedef pair<Node*, Node*> pn;

Node* Empty = new Node({ NULL, NULL, 0, 0, 0, 0 });
Node* root = Empty;

void upd(Node* v) {
	if (v == Empty) {
		return;
	}
	v->sz = v->left->sz + v->right->sz + 1;
	v->cnt_z = v->left->cnt_z + v->right->cnt_z + (v->value == 0);
}

Node* merge(Node* l, Node* r) {
	if (l == Empty) {
		upd(r);
		return r;
	}
	if (r == Empty) {
		upd(l);
		return l;
	}
	if (l->pr > r->pr) {
		l->right = merge(l->right, r);
		upd(l);
		return l;
	}
	r->left = merge(l, r->left);
	upd(r);
	return r;
}

pn split(Node* v, int k) {
	if (v == Empty) {
		return{ Empty, Empty };
	}
	if (v->left->sz >= k) {
		pn fsplit = split(v->left, k);
		v->left = fsplit.second;
		upd(fsplit.first);
		upd(v);
		return{ fsplit.first, v };
	}
	pn fsplit = split(v->right, k - v->left->sz - 1);
	v->right = fsplit.first;
	upd(fsplit.second);
	upd(v);
	return{ v, fsplit.second };
}

vector<int> ans;
void calc(Node* v) {
	if (v == Empty) {
		return;
	}
	calc(v->left);
	ans.push_back(v->value);
	calc(v->right);
}

void print(Node* v) {
	if (v == Empty) {
		return;
	}
	print(v->left);
	cout << v->value << " ";
	print(v->right);
}

int leftest_zero(Node* v, int sz = 0) {
	if (v->cnt_z == 0) {
		return -1;
	}
	if (v->left->cnt_z > 0) {
		return leftest_zero(v->left, sz);
	}
	if (v->value == 0) {
		return sz + v->left->sz + 1;
	}
	return leftest_zero(v->right, sz + v->left->sz + 1);
}

int main() {
#if _DEBUG
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
#else
	// freopen(NAME".in", "r", stdin);
	// freopen(NAME".out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	srand((int)time(NULL));
	// srand(172381);
	// cout.precision(20);
	// cout.setf(ios::fixed);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		Node* v = new Node({ Empty, Empty, rand(), 1, 0, 1 });
		root = merge(root, v);
	}
	for (int i = 0; i < n; ++i) {
		int ind;
		cin >> ind;
		pn fsplit = split(root, ind - 1);
		Node* v = new Node({ Empty, Empty, rand(), 1, i + 1, 0 });
		int id = leftest_zero(fsplit.second);
		if (id == -1) {
			root = merge(fsplit.first, merge(v, fsplit.second));
		} else {
			pn ssplit = split(fsplit.second, id - 1);
			pn tsplit = split(ssplit.second, 1);
			root = merge(merge(fsplit.first, v), merge(ssplit.first, tsplit.second));
		}
		// print(root);
		// cout << "\n";
	}
	calc(root);
	int end = (int)ans.size() - 1;
	while (end >= 0 && ans[end] == 0) {
		--end;
	}
	cout << end + 1 << "\n";
	for (int i = 0; i <= end; ++i) {
		cout << ans[i] << " ";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
