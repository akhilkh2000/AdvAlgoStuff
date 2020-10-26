// A Dynamic Programming based C++ program to find minimum
// number operations to convert str1 to str2
#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

bool compareChars(char c1, char c2) {
	return toupper(c1) == toupper(c2);
}

int computeCost(int insertOp, int deleteOp, int replaceOp, int c1, int c2) {
	int insertCost = (insertOp + c2 - 'A' + 1) % mod;
	int deleteCost = (deleteOp + c1 - 'A' + 1) % mod;
	int replaceCost = (replaceOp + abs(c1 - c2)) % mod;


	return min(insertCost, min(deleteCost, replaceCost));
}
int editDistDP(string str1, string str2)
{
	int m = str1.size();
	int n = str2.size();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
	dp[0][0] = 0;
	for (int i = 1; i <= m; i++) {

		dp[i][0] = (dp[i - 1][0] + toupper(str1[i - 1]) - 'A' + 1) % mod; //second string is empty so we have to delete
		//cout << dp[i][0] << endl;
	}

	for (int j = 1; j <= n; j++) {
		dp[0][j] = (dp[0][j - 1] + toupper(str2[j - 1]) - 'A' + 1) % mod; //first string is empty so we have insert
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

			else {
				// dp[i][j] = (1 + min(dp[i][j - 1], // Insert
				//                     dp[i - 1][j])) % mod; // Replace
				int insertOp = dp[i][j - 1];
				int deleteOp = dp[i - 1][j];
				int replaceOp = dp[i - 1][j - 1];
				dp[i][j] = computeCost(insertOp, deleteOp, replaceOp, toupper(c1), toupper(c2)) % mod;
			}
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

