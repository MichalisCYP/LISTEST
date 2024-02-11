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
bool isInSubsequence(int target, vector<int> &subsequence)
{
    for (int i = 0; i < subsequence.size(); i++)
    {
        if (subsequence[i] == target)
        {
            return true;
        }
    }
    return false;
}

int longestPremiumStreak(int xp[], int n, vector<int> &subsequence, int count)
{
    bool protection = true;
    bool found = false;
    for (int i = 0; i < subsequence.size() - 1; i++)
    {
        // we are trying to find where protection can be applied

        // for each element in the subsequence
        // we check if the elements next or previous to it causes a protection
        // xp[subsequence[i]] is in subsequence and is ith element
        // lis index in xp array is subsequence[i]

        // if subsequence items are next to each other we skip the checks
        found = false;
        int index = subsequence[i];
        int protectionIndex;
        if (!(subsequence[i] == subsequence[i + 1] + 1))
        {
            for (int j = index; (j < n - 1 && !found); j++)
            {
                if (xp[index + 1] >= xp[index]) // causes normal lis to break
                {
                    protectionIndex = index + 1;
                    found = true;
                }
            }
        }

        if (found)
        {
            // if found, perform normal LIS on the subarray skipping the protection index
            int size = n - protectionIndex + 1;
            int subarray[size];
            for (int k = protection; k < size; k++)
            {
                subarray[k] = xp[k];
            }
            vector<int> subsequence2;
            count += longestStreak(subarray, size, subsequence2);
            for (int l = 0; l < subsequence2.size(); l++)
            {
                cout << "second subsequence:" << endl;
                cout << xp[subsequence2[l]] << " ";
            }
            break;
        }
    }

    return count;
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

    int premiumStreak = longestPremiumStreak(xp, n, subsequence, normalStreak);

    cout << normalStreak << " " << premiumStreak << endl;

    return 0;
}
