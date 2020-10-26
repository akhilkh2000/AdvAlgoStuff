#include<bits/stdc++.h>
using namespace std;


void fillLpsArray(string p, int*lps, int n) {
	int len = 0;

	lps[0] = 0; // as first char has "" as longest prefix which is a suffix

	int i = 1;
	while (i < n) {
		if (p[i] == p[len]) {
			lps[i] = len + 1;
			//incrememnt previous longest prefix length and pointer
			len += 1;
			i += 1;

		} else {
			if (len == 0) {
				//we dont need to move len here as already 0
				lps[i] = 0;
				i++; //move ahead
			}
			else {
				//we have to consider previous overlapped len
				len = lps[len - 1]; //as till len-1 characters were matched
				//we dont increment i here to check current char with new len
			}
		}
	}
}
void kmpSearch(string p, string q, int &r, int n) {
	cout << q << endl;

	int len = 0; //longest prefix length
	int lps[n];
	fillLpsArray(p, lps, n);

	for (int i = 0; i < n; i++)
		cout << lps[i] << " ";
	cout << endl;
	int i = 0; //text pointer (for q)
	int j = 0;// pattern pointer(for p)

	while (i < 2 * n) {

		if (q[i] == p[j]) {
			i += 1;
			j += 1;
		} else {

			if (j != 0) {
				j = lps[j - 1]; //back to previoulsy matched prefix
				// cout << "J: " << j << endl;
				// cout << "len: " << len << endl;
				// cout << "i " << i << endl;
			}
			else
				i++;
		}



		//longer prefix found as a substring in text
		if (j > len) {
			// cout << len << " " << j << endl;
			len = j;
			r = i - j; // this is how many times we have to perform R swap to get (i-j)th  char to starting
		}





	}



}
int countR(string p, string q, int n) {
	int r  = 0;
	kmpSearch(p, q + q, r, n);
	return r;

}
int main()
{
// #ifndef ONLINE_JUDGE
// 	freopen("/media/akhil/Work/SEM-4/DS,CP/IO/input.txt", "r", stdin);
// 	freopen("/media/akhil/Work/SEM-4/DS,CP/IO/output.txt", "w", stdout);
// #endif


	int n;
	cin >> n;
	string P;
	string Q;
	cin >> P >> Q;
	//number of R operations
	int r = countR(P, Q, n);
	cout << r;
	// cout << P << Q << endl;


}