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
#include <list>
#include <unordered_map>
// #pragma comment(linker, "/STACK:256000000")
using namespace std;

#define F first
#define S second
#define mp make_pair
#define NAME "map"
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

vector<ll> mods, ps;
inline int rnd(const int &n) {
	return rand() % n;
}

inline string int_to_string(int n) {
	string s = "";
	if (n < 0) {
		s += '-';
		n = -n;
	}
	while (n > 0) {
		s += (char)((n % 10) + '0');
		n /= 10;
	}
	reverse(s.begin(), s.end());
	return s;
}

class hashtable {
	vector<vector<pair<string, string>>> table;
	ll MOD_H, p;

 public:
	hashtable() {
		MOD_H = mods[rnd((int)mods.size())];
		table.resize(MOD_H);
		p = ps[rnd((int)ps.size())];
	}

 public:
	ll get_hash(const string &s) {
		ll hash = 0, pp = 1;
		for (size_t i = 0; i < s.size(); ++i, pp = (pp * p) % MOD_H) {
			hash = (hash + ((int)s[i] * pp) % MOD_H) % MOD_H;
		}
		return hash;
	}

 public:
	int find(const string &s, const ll &hash) {
		auto it = table[hash].begin();
		for (size_t i = 0; i < table[hash].size(); ++i, ++it) {
			if (it->first == s) {
				return (int)i;
			}
		}
		return -1;
	}

 public:
	void add(const string &s, const string &key) {
		ll hash = get_hash(s);
		int ind = find(s, hash);
		if (ind == -1) {
			table[hash].push_back({ s, key });
		} else {
			table[hash][ind].second = key;
		}
	}

 public:
	void erase(const string &s) {
		ll hash = get_hash(s);
		int ind = find(s, hash);
		if (ind != -1) {
			table[hash].erase(table[hash].begin() + ind);
		}
	}

 public:
	bool exists(const string &s) {
		return find(s, get_hash(s)) != -1;
	}

 public:
	string get(const string &s) {
		ll hash = get_hash(s);
		for (pair<string, string> cur : table[hash]) {
			if (cur.first == s) {
				return cur.second;
			}
		}
		return "none";
	}
};

const int N = 1111111;
bool sieve[N];
inline void gen_sieve() {
	sieve[0] = sieve[1] = true;
	for (int i = 2; i < N; ++i) {
		if (sieve[i]) {
			continue;
		}
		sieve[i] = false;
		for (int j = 2 * i; j < N; j += i) {
			sieve[j] = true;
		}
	}
}
vector<ll> primes;
inline void gen_primes(const int &beg) {
	gen_sieve();
	for (int i = beg; i < N; ++i) {
		if (!sieve[i]) {
			primes.push_back(i);
		}
	}
}

inline void gen_mods_and_ps() {
	gen_primes(5e5 + 228 * 322);
	int mods_sz = rnd(10) + 1, ps_sz = rnd(8) + 1;
	vector<ll> buff(mods_sz + ps_sz);
	for (int i = 0; i < mods_sz + ps_sz; ++i) {
		buff[i] = primes[rnd((int)primes.size())];
	}
	sort(buff.begin(), buff.end());
	for (int i = 0; i < mods_sz + ps_sz; ++i) {
		if (i < ps_sz) {
			ps.push_back(buff[i]);
		} else {
			mods.push_back(buff[i]);
		}
	}
}

int main() {
#if SOLVE
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
#else
	freopen(NAME".in", "r", stdin);
	freopen(NAME".out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	// srand(time(NULL));
	// cout.precision(20);
	// cout.setf(ios::fixed);

	gen_mods_and_ps();
	hashtable my_hashtable = hashtable();
	string type;
	while (cin >> type) {
		if (type == "put") {
			string a, b;
			cin >> a >> b;
			my_hashtable.add(a, b);
		}
		if (type == "delete") {
			string a;
			cin >> a;
			my_hashtable.erase(a);
		}
		if (type == "get") {
			string a;
			cin >> a;
			cout << my_hashtable.get(a) << "\n";
		}
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
