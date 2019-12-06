#include <iostream>
#include <vector>

using namespace std;

int r, n;

struct matrix {
	int a, b, c, d;
	matrix() {
		a = d = 1;
		b = c = 0;
	}
	matrix(int const &a1, int const &b1, int const &c1, int const &d1) {
		a = a1;
		b = b1;
		c = c1;
		d = d1;
	}
};

matrix E(1, 0, 0, 1);

inline matrix mul(matrix const &a, matrix const &b) {
	int a1 = (a.a * b.a + a.b * b.c) % r;
	int b1 = (a.a * b.b + a.b * b.d) % r;
	int c1 = (a.c * b.a + a.d * b.c) % r;
	int d1 = (a.c * b.b + a.d * b.d) % r;
	return matrix(a1, b1, c1, d1);
}

struct Node {
	Node* left;
	Node* right;
	matrix res;
};

Node* Empty = new Node({ NULL, NULL, E });

Node* build(int lb, int rb, vector<matrix> const &arr) {
	if (lb + 1 == rb) {
		return new Node({ Empty, Empty, arr[lb] });
	}
	int mid = (lb + rb) / 2;
	Node* left_ch = build(lb, mid, arr);
	Node* right_ch = build(mid, rb, arr);
	return new Node({ left_ch, right_ch, mul(left_ch->res, right_ch->res) });
}

matrix get_mul(Node* v, int l, int r, int lb, int rb) {
	if (lb >= r || rb <= l) {
		return E;
	}
	if (l <= lb && rb <= r) {
		return v->res;
	}
	int mid = (lb + rb) / 2;
	return mul(get_mul(v->left, l, r, lb, mid), get_mul(v->right, l, r, mid, rb));
}

int main() {
	// freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int m;
	cin >> r >> n >> m;
	vector<matrix> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i].a >> arr[i].b >> arr[i].c >> arr[i].d;
		arr[i].a %= r;
		arr[i].b %= r;
		arr[i].c %= r;
		arr[i].d %= r;
	}
	Node* root = build(0, n, arr);
	for (int i = 0; i < m; ++i) {
		int l, r;
		cin >> l >> r;
		matrix res = get_mul(root, l - 1, r, 0, n);
		cout << res.a << " " << res.b << "\n" << res.c << " " << res.d << "\n\n";
	}

	return 0;
}
