#include<bits/stdc++.h>
using namespace std;


int longestCommonPrefix(string s, int idx, int n) {
	//preprocess hash values of string s
	vector<long long>hash(n, 0);
	vector<long long >power(n, 0);


	const int p = 31; //prime number
	const int m = 1e9 + 7; // modulo value
	power[0] = 1;
	for (int i = 1; i < n; i++)
		power[i] = (power[i - 1] * p) % m ;
	//first char hash value
	hash[0] = ((s[0] - 'a' + 1) * power[0]) ;

	//hash[0] = s[0] - 'a' + 1;+ 1) * power) % m;
	//power = (power * p) ;

	for (int i = 1; i < n; i++) {

		hash[i] = (hash[i - 1] + (s[i] - 'a' + 1) * power[i]) % m;

		//cout << hash[i] << "  " << s[i] - 'a' + 1 << " " << power[i] << endl;
	}

	// for (auto x : hash) {
	// 	cout << x << endl;
	// }

	cout << (hash[2]*power[4]) % m << endl;
	cout << (hash[6] - hash[3]) % m << endl;


	bool left = false;
	int low, high;
	if (idx <= n - idx) {
		low = 0;
		high = idx - 1;
		left = true;
	} else {
		low = idx;
		high = n - 1;
	}

	int hash_main, hash_temp;
	if (left) {
		hash_main = 0;
		hash_temp = hash[high];
	} else {
		hash_main = hash[low - 1];
		hash_temp = 0;
	}
	//binary search
	int maxLen = 0;
	while (low <= high) {
		int mid = low + (high - low) / 2; //to prevent overflow
		if (left) {
			if ((hash[mid] - hash_main) == (hash[mid + idx] - hash_temp)) {
				maxLen = mid + 1;
				low = mid + 1;
			} else {
				high = mid - 1;
			}

		}
		else {
			if ((hash[mid] - hash_main) == (hash[mid - idx] - hash_temp)) {
				cout << "mid: " << mid << endl;
				maxLen = mid - idx + 1;
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		}



	}

	return maxLen;
}


int main()
{
#ifndef ONLINE_JUDGE
	freopen("/media/akhil/Work/SEM-4/DS,CP/IO/input.txt", "r", stdin);
	freopen("/media/akhil/Work/SEM-4/DS,CP/IO/output.txt", "w", stdout);
#endif

	int l;
	string A;
	cin >> l;
	cin >> A;
	int q;
	cin >> q;
	int i;
	while (q--) {
		cin >> i;
		int lcp = longestCommonPrefix(A, i, l);
		cout << lcp << endl;
	}
}