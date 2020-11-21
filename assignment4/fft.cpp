#include<bits/stdc++.h>
using namespace std;
typedef complex<double> cd;



void fillComplex(vector<cd>& w, int n) {
    for (int i = 0; i < n; i++)
    {
        double alpha = 2 * M_PI * i / n;
        w[i] = cd(cos(alpha), sin(alpha));
    }
}

void fillFFt(vector<cd>&y, vector<cd>&y0, vector<cd>&y1, vector<cd>& w, int n) {
    for (int k = 0; k < n / 2; k++)
    {
        y[k] = y0[k] + w[k] * y1[k];
        y[k + n / 2] = y0[k] - w[k] * y1[k];
    }
}

void fillInvFft(vector<cd>&y, vector<cd>&y0, vector<cd>&y1, vector<cd>& w, int n) {
    for (int k = 0; k < n / 2; k++)
    {
        y[k] = y0[k] + y1[k] / w[k];            ///w[k]^-1
        y[k + n / 2] = y0[k] - y1[k] / w[k];
    }
}
vector<cd> fft(vector<cd>& a)
{
    int n = a.size();
    if (n == 1)
        return vector<cd>(1, a[0]);
    vector<cd> w(n);            ///complex roots
    vector<cd> A0(n / 2), A1(n / 2);
    fillComplex(w, n);


    for (int i = 0; i < n / 2; i++)
    {
        A1[i] = a[i * 2 + 1];   ///Odd coefficients
        A0[i] = a[i * 2];       ///Even coefficients

    }
    //recursion
    vector<cd> y0 = fft(A0);
    vector<cd> y1 = fft(A1);
    vector<cd> y(n);

    fillFFt(y, y0, y1, w, n);

    return y;
}
vector<cd> ifft(vector<cd>& a)      ///Inverse FFT
{
    int n = a.size();
    if (n == 1)
        return vector<cd>(1, a[0]);
    vector<cd> w(n);
    fillComplex(w, n);
    vector<cd> A0(n / 2), A1(n / 2);

    for (int i = 0; i < n / 2; i++)
    {
        A0[i] = a[i * 2];
        A1[i] = a[i * 2 + 1];
    }
    vector<cd> y0 = ifft(A0);
    vector<cd> y1 = ifft(A1);
    vector<cd> y(n);

    fillInvFft(y, y0, y1, w, n);

    return y;
}

vector<cd> invfft(vector<cd>&a)         ///last step of inverse fft
{   ///divide each element by n
    a = ifft(a);
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        a[i] = a[i] / cd(n);
    }
    return a;
}
vector<cd> mulfft(vector<cd>&a)         ///doubles the quantity of terms by adding n high-order
{
    auto n = a.size();                   ///So we can obtain the right quantity of terms as a result
    for (auto i = 0; i < n; i++)
    {
        a.push_back(0);
    }
    return fft(a);
}

void mult(vector<cd>&a, vector<cd>&b, vector<cd>&c)
{
    int sizeofA = a.size();
    int sizeofB = b.size();
    int maxSize = max(sizeofA, sizeofB);
    c.resize(maxSize);
    for (int i = 0; i < maxSize; i++)
    {
        c[i] = a[i] * b[i];
    }

}


void solvePoly(vector<cd>a, vector<cd>b) {
    vector<cd> c;
    a = mulfft(a);

    b = mulfft(b);

    mult(a, b, c);
    c = invfft(c);
    // cout << endl << "Vector c: " << endl;
    for (int i = 0; i < c.size(); i++)
    {
        cout << lround(real(c[i])) << " ";
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("E:/SEM-4/DS,CP/IO/input.txt", "r", stdin);
    freopen("E:/SEM-4/DS,CP/IO/output.txt", "w", stdout);
#endif

    int n;
    cin >> n;




    vector<cd> a(n);
    vector<cd>b(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    //std::vector<cd> a(x, x + sizeof x / sizeof x[0]);
    //vector<cd> a{9,-10,7,6};
    // int y[n];
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    solvePoly(a, b);

    return 0;
}
