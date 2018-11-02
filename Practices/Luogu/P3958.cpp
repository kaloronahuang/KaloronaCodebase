// P3958.cpp
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define ll long long

int n, h, r;

struct Point
{
    ll x, y, z;
    Point() {}
    Point(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Sphere
{
    Point center;
    ll radius;
    bool upperColliding;
    bool lowerColliding;
    int index;

    Sphere() {}
    Sphere(Point c, int radius);
};

double getDist(Point a, Point b);
bool checkCollide(Sphere s1, Sphere s2);
bool checkLowerCollide(Sphere s);
bool checkUpperCollide(Sphere s);

Sphere::Sphere(Point c, int radius)
{
    center = c;
    this->radius = radius;
}

double getDist(Point a, Point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

bool checkUpperCollide(Sphere s)
{
    if (s.center.z + s.radius >= h)
        return true;
    return false;
}

bool checkLowerCollide(Sphere s)
{
    if (s.center.z - s.radius <= 0)
        return true;
    return false;
}

bool checkCollide(Sphere s1, Sphere s2)
{
    if (getDist(s1.center, s2.center) <= s1.radius + s2.radius)
        return true;
    return false;
}

struct Batch
{
    vector<Sphere> spheres;
    vector<Sphere> upper;
    vector<Sphere> lower;
    int mem[100100];

    void MakeHeap()
    {
        for (int i = 0; i < n + 2; i++)
            mem[i] = i;
    }

    void UnionElement(int p, int q)
    {
        int p_parent = FindElement(p);
        int q_element = FindElement(q);
        if (p_parent != q_element)
            mem[p_parent] = q_element;
    }

    int FindElement(int p)
    {
        if (mem[p] != p)
            mem[p] = FindElement(mem[p]);
        return mem[p];
    }

    bool allFlag = true;
    bool goFlag = false;

    void initialize()
    {
        cin >> n >> h >> r;
        for (int i = 0; i < n; i++)
        {
            ll x, y, z;
            cin >> x >> y >> z;
            Sphere sss = Sphere(Point(x, y, z), r);
            sss.index = i;
            sss.upperColliding = checkUpperCollide(sss);
            sss.lowerColliding = checkLowerCollide(sss);
            if (sss.upperColliding && sss.lowerColliding)
                goFlag = true;
            if (sss.upperColliding)
                allFlag = false, upper.push_back(sss);
            if (sss.lowerColliding)
                lower.push_back(sss);
            spheres.push_back(sss);
        }
        return;
    }

    void preprocess()
    {
        MakeHeap();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;
                if (checkCollide(spheres[i], spheres[j]))
                    UnionElement(i, j);
            }
    }

    void Solve()
    {
        if (goFlag)
        {
            cout << "Yes" << endl;
            return;
        }
        if (allFlag)
        {
            cout << "No" << endl;
            return;
        }
        preprocess();
        for (int i = 0; i < upper.size(); i++)
            for (int j = 0; j < lower.size(); j++)
            {
                if (upper[i].index == lower[i].index)
                    continue;
                int resi = FindElement(upper[i].index), resj = FindElement(lower[j].index);
                if (resi != resj)
                    continue;
                cout << "Yes" << endl;
                return;
            }
        cout << "No" << endl;
    }
};

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        Batch b;
        b.initialize();
        b.Solve();
    }
    return 0;
}