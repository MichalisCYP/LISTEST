#include <iostream>
using namespace std;

void normalStreakCheck(uint32_t xp, uint32_t &prevXp, pair<uint32_t, uint32_t> &highestStreakPair, int &streak)
{
    if (xp > prevXp)
    {
        streak++;
        if (xp > highestStreakPair.second)
        {
            highestStreakPair.first++;
            highestStreakPair.second = xp;
        }
        if (streak > highestStreakPair.first)
        {
            highestStreakPair.first = streak;
        }
    }
    else
    {
        streak = 1;
    }
    prevXp = xp;
}

void premiumStreakCheck(uint32_t &xp, uint32_t &prevPremiumXp, pair<uint32_t, uint32_t> &highestPremiumStreakPair, int &premiumStreak, bool &breakAvailable)
{
    if (xp > prevPremiumXp)
    // if a streak or a break is available, meaning the comparison may fail, so we can give the break
    {
        premiumStreak++;
        if (xp > highestPremiumStreakPair.second)
        // the iTh experience is higher than the highest pair experience, which continues the steak
        {
            highestPremiumStreakPair.first++;
            highestPremiumStreakPair.second = xp;
        }
        if (premiumStreak > highestPremiumStreakPair.first) //  there is a new streak which has become higher (by 1)
        {
            highestPremiumStreakPair.first = premiumStreak;
            highestPremiumStreakPair.second = xp;
        }
        prevPremiumXp = xp;
    }
    else if (breakAvailable) // ignore this element and give a break
    {
        // set streaks to zero to make sure the streak continues
        prevPremiumXp = 0;
        highestPremiumStreakPair.second = 0;
        breakAvailable = false;
    }
    else // no more breaks, streak resets
    {
        premiumStreak = 1; // premium streak is reset
        breakAvailable = true;
        prevPremiumXp = xp;
    }
}

int main()
{
    uint32_t n;

    cin >> n;
    uint32_t xp; // temp experience
    uint32_t prevXp, prevPremiumXp;

    cin >> xp;

    prevXp = xp;
    pair<uint32_t, uint32_t> highestStreakPair(1, xp); // holds the highest streak and its last experience vale
    int streak = 1;                                    // start from one since we inserted the first xp

    bool breakAvailable = true;
    prevPremiumXp = xp;
    pair<uint32_t, uint32_t> highestPremiumStreakPair(1, xp); // holds the highest premium streak and its last experience vale
    int premiumStreak = 1;                                    // start from one since we inserted the first xp

    for (int i = 1; i < n; i++)
    {
        cin >> xp;
        normalStreakCheck(xp, prevXp, highestStreakPair, streak);
        premiumStreakCheck(xp, prevPremiumXp, highestPremiumStreakPair, premiumStreak, breakAvailable);
    }
    cout << highestStreakPair.first << " " << highestPremiumStreakPair.first << endl;
    return 0;
}