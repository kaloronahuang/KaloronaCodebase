#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#pragma region ADT
struct horizonal
{
    int pos = -1;
    int num = 0;
};

struct vertical
{
    int pos = -1;
    int num = 0;
};

bool comph(horizonal a, horizonal b)
{
    return a.num > b.num;
}

bool compv(vertical a, vertical b)
{
    return a.num > b.num;
}
#pragma endregion

int main()
{
    int M, N, K, L, D;
    cin >> M >> N >> K >> L >> D;
    vector<horizonal> hor;
    vector<vertical> ver;

    for (int i = 0; i < D; i++)
    {
        int x, y, w, z;
        cin >> x >> y >> w >> z;
        // judge the ver or hor;
        if (x == w)
        {
            // hor;
            // if it exist;
            bool isExt = false;
            for (int j = 0; j < hor.size(); j++)
                if (min(y, z) == hor[j].pos)
                {
                    isExt = true;
                    hor[j].num++;
                    break;
                }
            if (!isExt)
            {
                horizonal h;
                h.num = 1;
                h.pos = min(y, z);
                hor.push_back(h);
                //cout<<"hI added:"<<h.num<<" pos is:"<<h.pos;
            }
        }
        else
        {
            // hor;
            // if it exist;
            bool isExt = false;
            for (int j = 0; j < ver.size(); j++)
                if (min(x, w) == ver[j].pos)
                {
                    isExt = true;
                    ver[j].num++;
                    break;
                }
            if (!isExt)
            {
                vertical h;
                h.num = 1;
                h.pos = min(x, w);
                ver.push_back(h);
                //cout<<"vI added:"<<h.num<<" pos is:"<<h.pos;
            }
        }
    }
    sort(hor.begin(), hor.end(), comph);
    sort(ver.begin(), ver.end(), compv);

    // output;
    for (int i = 0; i < K; i++)
        cout << ver[i].pos << " ";
    cout << endl;
    for (int i = 0; i < L; i++)
        cout << hor[i].pos << " ";
    return 0;
}
