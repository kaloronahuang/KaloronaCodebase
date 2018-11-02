#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n;
    cin >> n;
    priority_queue<int> num_container;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        num_container.push(a);
    }
    vector<int> theRealCTN;
    int tep = -10000000;
    while (!num_container.empty())
    {
        int current = num_container.top();
        num_container.pop();
        if (tep == current)
            continue;
        theRealCTN.push_back(current);
        tep = current;
    }
    cout << theRealCTN.size() << endl;
    for (int i = theRealCTN.size() - 1; i > -1; i--)
        cout << theRealCTN[i] << " ";
    return 0;
}