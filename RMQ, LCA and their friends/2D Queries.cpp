#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

typedef unsigned int u_int;

const u_int N = (1 << 17);
u_int q, a, b, f[N];

struct Node {
	Node* left;
	Node* right;
	vector<u_int> arr;
};

Node* Empty = new Node({ NULL, NULL, {} });

void my_merge(vector<u_int> const &arr1, vector<u_int> const &arr2, vector<u_int> &res) {
	size_t n = arr1.size(), m = arr2.size();
	for (size_t i = 0, j = 0, k = 0; i < n || j < m; ++k) {
		if (i < n && j < m) {
			if (arr1[i] < arr2[j]) {
				res[k] = arr1[i++];
			} else {
				res[k] = arr2[j++];
			}
		} else {
			if (i < n) {
				res[k] = arr1[i++];
			} else {
				res[k] = arr2[j++];
			}
		}
	}
}

Node* build(u_int const &l, u_int const &r) {
	if (l + 1 == r) {
		return new Node({ Empty, Empty, {f[l]} });
	}
	u_int mid = (l + r) >> 1;
	Node* new_left = build(l, mid);
	Node* new_right = build(mid, r);
	vector <u_int> new_arr(r - l);
	my_merge(new_left->arr, new_right->arr, new_arr);
	return new Node({ new_left, new_right, new_arr });
}

u_int ans(Node* v, u_int l, u_int r, u_int x, u_int y, u_int lb, u_int rb) {
	if (lb >= r || rb <= l) {
		return 0;
	}
	if (l <= lb && r >= rb) {
		vector<u_int>::iterator left = lower_bound(v->arr.begin(), v->arr.end(), x);
		vector<u_int>::iterator right = upper_bound(v->arr.begin(), v->arr.end(), y);
		return (u_int)((right - v->arr.begin()) - (left - v->arr.begin()));
	}
	u_int mid = (lb + rb) >> 1;
	return ans(v->left, l, r, x, y, lb, mid) + ans(v->right, l, r, x, y, mid, rb);
}

u_int cur = 0;
inline u_int nextRand17() {
	cur = cur * a + b;
	return cur >> 15;
}

inline u_int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}

int main() {
	cin >> q >> a >> b;
	for (u_int i = 0; i < N; ++i) {
		f[i] = nextRand24();
	}
	Node* root = build(0, N);
	u_int res = 0;
	for (u_int i = 0; i < q; ++i) {
		u_int l = nextRand17();
		u_int r = nextRand17();
		if (l > r) {
			swap(l, r);
		}
		u_int x = nextRand24();
		u_int y = nextRand24();
		if (x > y) {
			swap(x, y);
		}
		u_int cur = ans(root, l, r + 1, x, y, 0, N);
		res += cur;
		b += cur;
	}
	cout << res;
	// cerr << clock() * 1. / CLOCKS_PER_SEC;
}
