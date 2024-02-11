#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int max(int a, int b)
{
    return a > b ? a : b;
}

int longestStreak(int xp[], int n, vector<int> &subsequence)
{
    int longestSubsequence[n];                           // stores the longest subsequence for each element
    fill(longestSubsequence, longestSubsequence + n, 1); // All elements are set to 1
    vector<int> previousIndex(n, -1);                    // To store the index of previous element in subsequence

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++) // iterate until i
        {
            if (xp[j] < xp[i])
            {
                // the lis at i will be at least the lis at j + 1 (+itself)
                // or stays the same if the subsequence is already bigger
                if (longestSubsequence[j] + 1 > longestSubsequence[i])
                {
                    longestSubsequence[i] = longestSubsequence[j] + 1;
                    previousIndex[i] = j;
                }
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
            maxIndex = i;
        }
    }

    // Reconstruct the subsequence
    while (maxIndex != -1)
    {
        subsequence.push_back(maxIndex);
        maxIndex = previousIndex[maxIndex];
    }

    reverse(subsequence.begin(), subsequence.end()); // Reverse to get correct order
    return max;
}

int longestPremiumStreak(int xp[], int n, vector<int> &subsequence)
{
    int longest = 0;
    int count = 0;
    bool usedPremium = false;

    for (int i = 0; i < subsequence.size(); i++)
    {
        if (i > 0 && xp[subsequence[i]] <= xp[subsequence[i - 1]])
        {
            // If current XP is not strictly greater than previous
            if (!usedPremium)
            {
                // If premium protection is available, use it
                usedPremium = true;
                count++;
            }
        }
        else
        {
            // If current XP is strictly greater than previous, increment count
            count++;
        }

        // Update longest streak
        longest = max(longest, count);
    }

    return longest;
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

    vector<int> subsequence;
    int normalStreak = longestStreak(xp, n, subsequence);

    int premiumStreak = longestPremiumStreak(xp, n, subsequence);

    cout << normalStreak << " " << premiumStreak << endl;

    return 0;
}
