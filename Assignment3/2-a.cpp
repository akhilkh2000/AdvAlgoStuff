// A Dynamic Programming based C++ program to find minimum
// number operations to convert str1 to str2
#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

bool compareChars(char c1, char c2) {
	return toupper(c1) == toupper(c2);
}
int editDistDP(string str1, string str2)
{
	int m = str1.size();
	int n = str2.size();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
	for (int i = 1; i <= m; i++) {
		dp[i][0] = i; //second string is empty so we have to delete
	}

	for (int j = 1; j <= n; j++) {
		dp[0][j] = j; //first string is empty so we have insert
	}


	// Fill d[][] in bottom up manner
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			// If last characters are same, ignore last char
			// and recur for remaining string
			char c1 = str1[i - 1];
			char c2 = str2[j - 1];
			if (compareChars(c1, c2))
				dp[i][j] = dp[i - 1][j - 1];

			else
				dp[i][j] = (1 + min(dp[i][j - 1], // Insert
				                    dp[i - 1][j])) % mod; // Replace
		}
	}

	return dp[m][n];
}

// Driver program
int main()
{
#ifndef ONLINE_JUDGE
	freopen("E:/SEM-4/DS,CP/IO/input.txt", "r", stdin);
	freopen("E:/SEM-4/DS,CP/IO/output.txt", "w", stdout);
#endif
	// your code goes here
	string str1, str2;
	int t;
	cin >> t;
	while (t--) {
		cin >> str1 >> str2;
		cout << editDistDP(str1, str2) << endl;

	}


	return 0;
}

