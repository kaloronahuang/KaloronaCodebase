// P1042.cpp
#include <iostream>
#include <vector>

using namespace std;

struct compSit
{
    int own = 0;
    int rival = 0;
};

int main()
{
    // I/O;
    string comp;
    while (true)
    {
        string res;
        getline(cin, res);
        comp += res;
        if (res.back() == 'E')
            break;
    }
    vector<compSit> ep;
    vector<compSit> twp;
    int lun = 0;
    compSit current;
    for (int x = 0; true; x++)
    {
        int res = (int)(x + 1) / 11;
        if (res > lun)
        {
            ep.push_back(current);
            current.own = 0;
            current.rival = 0;
            lun = res;
        }
        if (comp[x] == 'W')
            current.own++;
        if (comp[x] == 'L')
            current.rival++;
        if (comp[x] == 'E')
            break;
    }
    current.own = 0;
    current.rival = 0;
    lun = 0;
    for (int x = 0; true; x++)
    {
        int res = (int)(x + 1) / 21;
        if (res > lun)
        {
            twp.push_back(current);
            current.own = 0;
            current.rival = 0;
            lun = res;
        }
        if (comp[x] == 'W')
            current.own++;
        if (comp[x] == 'L')
            current.rival++;
        if (comp[x] == 'E')
            break;
    }
    for (int x = 0; x < ep.size(); x++)
        cout << ep[x].own << ":" << ep[x].rival << endl;
    for (int x = 0; x < twp.size(); x++)
        cout << twp[x].own << ":" << twp[x].rival << endl;
    int a;
    cin >> a;
    return 0;
}