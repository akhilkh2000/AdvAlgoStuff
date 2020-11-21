#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9;


int gcd(int a , int b, int& x, int& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int x1, y1;
	int d = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return d;

}

int inv_euclid(int a, int b) {

	int x;
	int y;

	int res =  gcd(a, b, x, y);
	if (res != 1) {
		cout << "FML!";
		return -1;
	}

	x = (x % b + b) % b;
	return x;

}

int CRT(vector<int>a, vector<int>r, int n) {
	int totalProd = 1;
	for (int i = 0; i < n; i++)
		totalProd = totalProd * a[i];
	int ans = 0;

	//sum everything up
	for (int i = 0; i < n; i++) {
		int pp = totalProd / a[i];
		ans += (r[i] * inv_euclid(pp, a[i]) * pp);
	}

	return ans % totalProd; // to get the minimum
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("E:/SEM-4/DS,CP/IO/input.txt", "r", stdin);
	freopen("E:/SEM-4/DS,CP/IO/output.txt", "w", stdout);
#endif

	int n;
	cin >> n;

	vector<int>a(n);
	vector<int>r(n);

	for (int i = 0; i < n; i++) {
		cin >> a[i] >> r[i];
	}

	cout << CRT(a, r, n) % mod << endl;


}
