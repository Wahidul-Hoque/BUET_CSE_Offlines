#include <bits/stdc++.h>
using namespace std;

int globalAlignment(string a, string b, int m, int n, int match, int mismatch, int gap, vector<vector<int>> &dp)
{
    if (m == 0)
        return n * gap;
    if (n == 0)
        return m * gap;
    if (dp[m][n] != -1)
        return dp[m][n];
    int score;
    if (a[m - 1] == b[n - 1])
    {
        score = globalAlignment(a, b, m - 1, n - 1, match, mismatch, gap, dp) + match;
    }
    else
    {
        int mis = globalAlignment(a, b, m - 1, n - 1, match, mismatch, gap, dp) + mismatch;
        int gapa = globalAlignment(a, b, m - 1, n, match, mismatch, gap, dp) + gap;
        int gapb = globalAlignment(a, b, m, n - 1, match, mismatch, gap, dp) + gap;
        score = max({mis, gapa, gapb});
    }
    return dp[m][n] = score;
}
void traceGlobal(string a, string b, int match, int mismatch, int gap, vector<vector<int>> &dp)
{
    int m = a.size();
    int n = b.size();
    string alignedx = "", alignedy = "";
    while (m > 0 && n > 0)
    {
        if (a[m - 1] == b[n - 1])
        {
            alignedx = a[m - 1] + alignedx;
            alignedy = b[n - 1] + alignedy;
            m--;
            n--;
        }
        else if (dp[m - 1][n] + gap == dp[m][n])
        {
            alignedx = a[m - 1] + alignedx;
            alignedy = "-" + alignedy;
            m--;
        }
        else if (dp[m][n - 1] + gap == dp[m][n])
        {
            alignedy = b[n - 1] + alignedy;
            alignedx = "-" + alignedx;
            n--;
        }
        else
        {
            alignedx = a[m - 1] + alignedx;
            alignedy = b[n - 1] + alignedy;
            m--;
            n--;
        }
    }
    while (m > 0)
    {
        alignedx = a[m - 1] + alignedx;
        alignedy = "-" + alignedy;
        m--;
    }
    while (n > 0)
    {
        alignedy = b[n - 1] + alignedy;
        alignedx = "-" + alignedx;
        n--;
    }
    cout << alignedx << endl
         << alignedy << endl;
}
int localAlignment(string a, string b, int m, int n, int match, int mismatch, int gap, vector<vector<int>> &dp)
{
    if (m == 0)
        return 0;
    if (n == 0)
        return 0;
    if (dp[m][n] != -1)
        return dp[m][n];
    int score = 0;
    if (a[m - 1] == b[n - 1])
    {
        score = localAlignment(a, b, m - 1, n - 1, match, mismatch, gap, dp) + match;
    }
    else
    {
        int mis = localAlignment(a, b, m - 1, n - 1, match, mismatch, gap, dp) + mismatch;
        int gapa = localAlignment(a, b, m - 1, n, match, mismatch, gap, dp) + gap;
        int gapb = localAlignment(a, b, m, n - 1, match, mismatch, gap, dp) + gap;
        score = max({0, mis, gapa, gapb});
    }
    return dp[m][n] = score;
}

void traceLocal(string a, string b, int match, int mismatch, int gap, vector<vector<int>> &dp)
{
    int m = a.size();
    int n = b.size();
    string alignedx = "", alignedy = "";
    int maxscore = 0, maxi, maxj;
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (dp[i][j] > maxscore)
            {
                maxscore = dp[i][j];
                maxi = i;
                maxj = j;
            }
        }
    }
    int i = maxi, j = maxj;
    while (i > 0 && j > 0 && dp[i][j] > 0)
    {
        if (a[i - 1] == b[j - 1])
        {
            alignedx = a[i - 1] + alignedx;
            alignedy = b[j - 1] + alignedy;
            i--;
            j--;
        }
        else if (dp[i - 1][j] + gap == dp[i][j])
        {
            alignedx = a[i - 1] + alignedx;
            alignedy = "-" + alignedy;
            i--;
        }
        else if (dp[i][j - 1] + gap == dp[i][j])
        {
            alignedy = b[j - 1] + alignedy;
            alignedx = "-" + alignedx;
            j--;
        }
        else
        {
            alignedx = a[i - 1] + alignedx;
            alignedy = b[j - 1] + alignedy;
            i--;
            j--;
        }
    }

    cout << alignedx << endl
         << alignedy << endl
         << "Maximum Score: " << maxscore << endl;
}

int main()
{
    string a, b;
    int match_score, mismatch_penalty, gap_penalty;
    cout << "Enter first sequence: ";
    cin >> a;
    cout << "Enter second sequence: ";
    cin >> b;
    cout << "Enter match score: ";
    cin >> match_score;
    cout << "Enter mismatch penalty: ";
    cin >> mismatch_penalty;
    cout << "Enter gap penalty: ";
    cin >> gap_penalty;
    int m = a.size();
    int n = b.size();
    vector<vector<int>> dpGlobal(m + 1, vector<int>(n + 1, -1));
    vector<vector<int>> dpLocal(m + 1, vector<int>(n + 1, -1));
    int globalAns = globalAlignment(a, b, m, n, match_score, mismatch_penalty, gap_penalty, dpGlobal);
    int localAns = localAlignment(a, b, m, n, match_score, mismatch_penalty, gap_penalty, dpLocal);
    cout << "Global Alignment:\n";
    traceGlobal(a, b, match_score, mismatch_penalty, gap_penalty, dpGlobal);
    cout << "Maximum Score: " << globalAns << endl;
    cout << endl;
    cout << "Local Alignment:\n";
    traceLocal(a, b, match_score, mismatch_penalty, gap_penalty, dpLocal);
}