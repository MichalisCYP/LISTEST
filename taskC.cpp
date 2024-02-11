#include <iostream>
#include <algorithm>
using namespace std;
int max(int a, int b)
{
    return a > b ? a : b;
}

int longestPremiumStreak(int xp[], int n)
{
    
}

int longestStreak(int xp[], int n)
{
    int longestSubsequence[n];                           // stores the longest subsequence for each element
    fill(longestSubsequence, longestSubsequence + n, 1); // All elements are set to 1
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++) // iterate until i
        {
            if (xp[j] < xp[i])
            {
                // the lis at i will be at least the lis at j + 1 (+itself)
                // or stays the same if the subsequence is already bigger
                longestSubsequence[i] = max(longestSubsequence[j] + 1, longestSubsequence[i]);
            }
        }
    }

    int max = 0;
    int maxIndex;
    for (int i = 0; i < n; i++)
    {
        if (longestSubsequence[i] > max)
        {
            max = longestSubsequence[i];
        }
    }
    return max;
}

int main()
{
    int n;
    cin >> n;
    int xp[n];

    for (int i = 0; i < n; i++)
    {
        cin >> xp[i];
    }
    int normalStreak = longestStreak(xp, n);
    cout << normalStreak << " " << longestPremiumStreak(xp, n);
    return 0;
}
