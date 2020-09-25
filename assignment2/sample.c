#include<bits/stdc++.h>
using namespace std;

int maxi = 0;
void LPSArray(char* pat, int M, int* lps);

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    LPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j > maxi)
            maxi = i - j;
        if (j == M) {
            //printf("Found pattern at index %d ", i - j);
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    printf("%d\n", maxi);
}

// Fills lps[] for given patttern pat[0..M-1]
void LPSArray(char* pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
char* r_operation(char* q, int n)
{
    char* temp;
    temp = (char*)malloc(sizeof(char) * n);
    printf("enetered here %s\n", q);
    strcat(temp, q);
    printf("enetered here %s\n", temp);
    strcat(temp, q);
    printf("enrterd here %s\n", temp);
    return temp;
}
// Driver program to test above function
int main()
{
//    char q[] = "assadadadaskaassadadadaska";
//    char p[] = "daskaa";
#ifndef ONLINE_JUDGE
    freopen("/media/akhil/Work/SEM-4/DS,CP/IO/input.txt", "r", stdin);
    freopen("/media/akhil/Work/SEM-4/DS,CP/IO/output.txt", "w", stdout);
#endif
    int n;
    printf("Enter the length of string\n");
    scanf("%d", &n);
    char q[n];
    scanf("%s", q);
    char qt[n];
    strcpy(qt, r_operation(q, n));
    char p[n];
    scanf("%s", p);
    printf("%s\n", p);
    KMPSearch(p, qt);
    return 0;
}