#include <iostream>

using namespace std;

int main()
{
    int setNum;
    cin>>setNum;
    for(int index = 0;index<setNum;index++)
    {
        int leapNum;
        cin>>leapNum;
        int leap[leapNum];
        for(int in = 0;in<leapNum;in++)
        {
            cin>>leap[in];
        }
        
        bool strange = false;
        for(int i = 0;i<leapNum&&!strange;i++)
        {
            int total = 0;
            for(int j = 0;j<leapNum;j++)
            {
                if(j!=i)
                {
                    if(j == 0)
                        total = leap[j];
                    else
                        total ^= leap[j];
                }
            }
            if(total == leap[i])
                strange = true;
        }
        
        if(strange)
            cout<<"No";
        else
            cout<<"Yes";
    }
    return 0;
}
