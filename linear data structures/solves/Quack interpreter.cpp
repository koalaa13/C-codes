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
#define NAME "quack"
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

template <class T>
struct myvector {
	int sz, free_ind;
	T *arr;
	myvector() {
		sz = 1;
		free_ind = 0;
		arr = new T[1];
	}
	myvector(const int &m) {
		sz = m;
		free_ind = 0;
		arr = new T[m];
	}
	bool empty() {
		return !free_ind;
	}
	int size() {
		return free_ind;
	}
	void push_back(const T &v) {
		if (free_ind == sz) {
			T *copy = new T[free_ind];
			for (int i = 0; i < free_ind; ++i) {
				copy[i] = arr[i];
			}
			delete[] arr;
			sz *= 2;
			arr = new T[sz];
			for (int i = 0; i < free_ind; ++i) {
				arr[i] = copy[i];
			}
		}
		arr[free_ind++] = v;
	}
	void pop_back() {
		if (!empty()) {
			free_ind--;
			if (free_ind * 4 <= sz && sz >= 4) {
				T *copy = new T[free_ind];
				for (int i = 0; i < free_ind; ++i) {
					copy[i] = arr[i];
				}
				sz /= 2;
				delete[] arr;
				arr = new T[sz];
				for (int i = 0; i < free_ind; ++i) {
					arr[i] = copy[i];
				}
			}
		}
	}
	T back() {
		return arr[free_ind - 1];
	}
	T get(const int &i) {
		return arr[i];
	}
	void set(const int &i, const T &v) {
		if (free_ind < i) {
			arr[i] = v;
		}
	}
};

template <class Q>
struct myqueue {
	myvector<Q> *f;
	myvector<Q> *b;
	myqueue() {
		f = new myvector<Q>();
		b = new myvector<Q>();
	}
	void push(const Q &v) {
		b->push_back(v);
	}
	void pop() {
		if (f->empty()) {
			while (!b->empty()) {
				f->push_back(b->back());
				b->pop_back();
			}
		}
		f->pop_back();
	}
	Q front() {
		if (f->empty()) {
			while (!b->empty()) {
				f->push_back(b->back());
				b->pop_back();
			}
		}
		return f->back();
	}
	Q front_pop() {
		if (f->empty()) {
			while (!b->empty()) {
				f->push_back(b->back());
				b->pop_back();
			}
		}
		Q res = f->back();
		f->pop_back();
		return res;
	}
};

myqueue<int> q;
const int MOD = 65536;
const int MOD_C = 256;
const int alp = 26;
int rs[alp];

inline bool is_num(const char &c) {
	return c >= '0' && c <= '9';
}

inline int int_from_string(const string &s) {
	int res = 0;
	for (int i = (int)s.length() - 1, p = 1; i >= 0; --i, p *= 10) {
		res += (s[i] - '0') * p;
	}
	return res;
}

string substring(const string &s, const int &a, const int &b) {
	string res = "";
	for (int i = a; i < b; ++i) {
		res += s[i];
	}
	return res;
}

const ll MOD_H = 79997;
const ll p = 49991;

struct hashtable {
	myvector<pair<string, int>> table[MOD_H];
	ll get_hash(const string &s) {
		ll hash = 0, pp = 1;
		for (int i = 0; i < (int)s.size(); ++i, pp = (pp * p) % MOD_H) {
			hash = (hash + ((int)s[i] * pp) % MOD_H) % MOD_H;
		}
		return hash;
	}
	void add(const string &s, const int &key) {
		ll hash = get_hash(s);
		if (table[hash].empty()) {
			table[hash].push_back(make_pair(s, key));
		}
		else {
			int ind = -1;
			for (int i = 0; i < table[hash].size(); ++i) {
				if (table[hash].get(i).first == s) {
					ind = i;
					break;
				}
			}
			if (ind != -1) {
				table[hash].arr[ind].second = key;
			}
			else {
				table[hash].push_back(make_pair(s, key));
			}
		}
	}
	int get(const string &s) {
		ll hash = get_hash(s);
		for (int i = 0; i < table[hash].size(); ++i) {
			if (table[hash].get(i).first == s) {
				return table[hash].get(i).second;
			}
		}
		return -1;
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

	myvector<string> arr;
	hashtable labels;
	//map<string, int> labels;
	string s;
	int i = 0;
	while (cin >> s) {
		if (s[0] == ':') {
			labels.add(substring(s, 1, (int)s.size()), i);
			//labels[substring(s, 1, (int)s.size())] = i;
		}
		++i;
		arr.push_back(s);
	}
	arr.push_back("Q");
	i = 0; 
	for (;;) {
		s = arr.get(i);
		if (is_num(s[0])) {
			q.push(int_from_string(s));
			++i;
		}
		if (s[0] == '+') {
			int x = q.front_pop();
			int y = q.front_pop();
			q.push((x + y) % MOD);
			++i;
		}
		if (s[0] == '-') {
			int x = q.front_pop();
			int y = q.front_pop();
			q.push((x + MOD - y) % MOD);
			++i;
		}
		if (s[0] == '*') {
			ll x = (ll)q.front_pop();
			ll y = (ll)q.front_pop();
			q.push((int)((x * y) % MOD));
			++i;
		}
		if (s[0] == '/') {
			int x = q.front_pop();
			int y = q.front_pop();
			if (y == 0) {
				q.push(0);
			}
			else {
				q.push((x / y) % MOD);
			}
			++i;
		}
		if (s[0] == '%') {
			int x = q.front_pop();
			int y = q.front_pop();
			if (y == 0) {
				q.push(0);
			}
			else {
				q.push((x % y) % MOD);
			}
			++i;
		}
		if (s[0] == '>') {
			rs[s[1] - 'a'] = q.front_pop();
			++i;
		}
		if (s[0] == '<') {
			q.push(rs[s[1] - 'a'] % MOD);
			++i;
		}
		if (s[0] == 'P') {
			if (s.size() > 1) {
				cout << rs[s[1] - 'a'] << endl;
			}
			else {
				cout << q.front_pop() << endl;
			}
			++i;
		}
		if (s[0] == 'C') {
			if (s.size() > 1) {
				cout << (char)(rs[s[1] - 'a'] % MOD_C);
			}
			else {
				cout << (char)(q.front_pop() % MOD_C);
			}
			++i;
		}
		if (s == "Q") {
			return 0;
		}
		if (s[0] == ':') {
			++i;
		}
		if (s[0] == 'J') {
			i = labels.get(substring(s, 1, (int)s.size())) + 1;
			//i = labels[substring(s, 1, (int)s.size())] + 1;
		}
		if (s[0] == 'Z') {
			if (!rs[s[1] - 'a']) {
				i = labels.get(substring(s, 2, (int)s.size()));
				//i = labels[substring(s, 2, (int)s.size())];
			}
			++i;
		}
		if (s[0] == 'E') {
			if (rs[s[1] - 'a'] == rs[s[2] - 'a']) {
				i = labels.get(substring(s, 3, (int)s.size()));
				//i = labels[substring(s, 3, (int)s.size())];
			}
			++i;
		}
		if (s[0] == 'G') {
			if (rs[s[1] - 'a'] > rs[s[2] - 'a']) {
				i = labels.get(substring(s, 3, (int)s.size()));
				//i = labels[substring(s, 3, (int)s.size())];
			}
			++i;
		}
	}

	//cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}