#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <map>

using namespace std;

typedef unsigned int u_int;
vector<vector<vector<vector<u_int>>>> fs;
function<u_int(int, int, int, u_int)> functions[8];
int nx, ny, nz;

void internal_update(int f_id, int x, int y, int z, u_int d) {
	for (int i = x; i <= nx; i |= (i + 1)) {
		for (int j = y; j <= ny; j |= (j + 1)) {
			for (int k = z; k <= nz; k |= (k + 1)) {
				fs[f_id][i][j][k] += d;
			}
		}
	}
}

u_int f0(int x, int y, int z, u_int d) {
	return static_cast<u_int>(-d * (x - 1) * (y - 1) * (z - 1));
}

u_int f1(int x, int y, int z, u_int d) {
	return static_cast<u_int>(d * (x - 1) * (y - 1) + z * 0);
}

u_int f2(int x, int y, int z, u_int d) {
	return static_cast<u_int>(d * (x - 1) * (z - 1) + y * 0);
}

u_int f3(int x, int y, int z, u_int d) {
	return static_cast<u_int>(d * (1 - x) + z * 0 + y * 0);
}

u_int f4(int x, int y, int z, u_int d) {
	return static_cast<u_int>(d * (y - 1) * (z - 1) + x * 0);
}

u_int f5(int x, int y, int z, u_int d) {
	return static_cast<u_int>(d * (1 - y) + z * 0 + x * 0);
}

u_int f6(int x, int y, int z, u_int d) {
	return static_cast<u_int>(d * (1 - z) + y * 0 + x * 0);
}

u_int f7(int x, int y, int z, u_int d) {
	return static_cast<u_int>(d + x * 0 + y * 0 + z * 0);
}

void prec() {
	functions[0] = f0;
	functions[1] = f1;
	functions[2] = f2;
	functions[3] = f3;
	functions[4] = f4;
	functions[5] = f5;
	functions[6] = f6;
	functions[7] = f7;
}

void update_fenw(int f_id, int x1, int y1, int z1, int x2, int y2, int z2, u_int d) {
	internal_update(f_id, x1, y1, z1, functions[f_id](x1, y1, z1, d));
	internal_update(f_id, x2 + 1, y1, z1, -functions[f_id](x2 + 1, y1, z1, d));
	internal_update(f_id, x1, y2 + 1, z1, -functions[f_id](x1, y2 + 1, z1, d));
	internal_update(f_id, x1, y1, z2 + 1, -functions[f_id](x1, y1, z2 + 1, d));
	internal_update(f_id, x2 + 1, y2 + 1, z1, functions[f_id](x2 + 1, y2 + 1, z1, d));
	internal_update(f_id, x1, y2 + 1, z2 + 1, functions[f_id](x1, y2 + 1, z2 + 1, d));
	internal_update(f_id, x2 + 1, y1, z2 + 1, functions[f_id](x2 + 1, y1, z2 + 1, d));
	internal_update(f_id, x2 + 1, y2 + 1, z2 + 1, -functions[f_id](x2 + 1, y2 + 1, z2 + 1, d));
}

void update(int x1, int y1, int z1, int x2, int y2, int z2, u_int d) {
	for (int i = 0; i < 8; ++i) {
		update_fenw(i, x1, y1, z1, x2, y2, z2, d);
	}
}

u_int query(int x, int y, int z) {
	u_int res[8];
	for (int i = 0; i < 8; ++i) {
		res[i] = 0;
	}
	for (int p = 0; p < 8; ++p) {
		for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
			for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
				for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
					res[p] += fs[p][i][j][k];
				}
			}
		}
	}
	return res[0] + res[1] * z + res[2] * y + res[3] * y * z +
		res[4] * x + res[5] * x * z + res[6] * x * y + res[7] * x * y * z;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	prec();
	int q;
	cin >> nx >> ny >> nz >> q;
	vector<pair<int, char>> arr = { {nx, 'x'}, {ny, 'y'}, {nz, 'z'} };
	sort(arr.begin(), arr.end());
	nx = arr[0].first;
	ny = arr[1].first;
	nz = arr[2].first;
	fs.resize(8);
	for (int i = 0; i < 8; ++i) {
		fs[i].resize(nx + 1);
		for (int j = 0; j <= nx; ++j) {
			fs[i][j].resize(ny + 1);
			for (int k = 0; k <= ny; ++k) {
				fs[i][j][k].resize(nz + 1);
			}
		}
	}
	while (q--) {
		char type;
		int x1, x2, y1, y2, z1, z2;
		cin >> type >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
		map<char, pair<int, int>> m;
		m['x'] = { x1, x2 };
		m['y'] = { y1, y2 };
		m['z'] = { z1, z2 };
		x1 = m[arr[0].second].first;
		y1 = m[arr[1].second].first;
		z1 = m[arr[2].second].first;
		x2 = m[arr[0].second].second;
		y2 = m[arr[1].second].second;
		z2 = m[arr[2].second].second;
		if (type == 'a') {
			u_int d;
			cin >> d;
			update(x1 + 1, y1 + 1, z1 + 1, x2, y2, z2, d);
		} else {
			u_int ans0 = query(x2, y2, z2);
			u_int ans1 = query(x1, y2, z2);
			u_int ans2 = query(x2, y1, z2);
			u_int ans3 = query(x2, y2, z1);
			u_int ans4 = query(x1, y1, z2);
			u_int ans5 = query(x1, y2, z1);
			u_int ans6 = query(x2, y1, z1);
			u_int ans7 = query(x1, y1, z1);
			cout << ans0 - ans1 - ans2 - ans3 + ans4 + ans5 + ans6 - ans7 << "\n";
		}
	}
	return 0;
}
