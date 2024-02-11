#include <iostream>
#include <stack>
#include <sstream>
using namespace std;
string reverseString(string &enteredString)
{

    istringstream wordStream(enteredString); // treat entered string as a stream, which automatically ignores spaces

    // we are going to be using a stack, since it is Last In First out, it is ideal for this task!
    stack<string> wordStack;

    string word;
    while (wordStream >> word)
    {
        wordStack.push(word);
    }

    if (wordStack.size() > 100000) // 10^5=100000
    {
        return "Maximum number of words reached.";
    }
    else if (wordStack.size() < 1)
    {
        return "No words entered.";
    }

    string reversed = "";
    while (!wordStack.empty())
    {
        reversed += wordStack.top() + " ";
        wordStack.pop();
    }
    reversed.pop_back(); // remove the last " " space

    return reversed;
}

int main()
{
    string enteredString;
    getline(cin, enteredString);

    if (enteredString.length() > 1000000 || enteredString.length() < 1) // 10^6=1000000
    {
        cout << "String out of bounds.";
        return 0;
    }
    cout << reverseString(enteredString);
    return 0;
}