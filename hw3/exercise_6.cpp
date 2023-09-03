#include <iostream>
#include <vector>
using namespace std;
//rhea samuel
//rss3488
void createVect(vector<int> vect)
{
    vector <int> odd;
    vector <int> even;
    for(int x = 0; x<vect.size(); x++)
    {
        if(vect[x] %2 == 0)
        {
            even.push_back(vect[x]);
        }
        else{
            odd.push_back(vect[x]);
        }
    }
    for(int x = 0; x<odd.size(); x++)
    {
        if(x!=odd.size()-1)
        {
            cout << odd[x] << ",";
        }
        else{
            cout << odd[x];
        }
    }
    cout << endl;
    for(int x =0; x<even.size(); x++)
    {
        if(x!=even.size()-1)
        {
            cout << even[x] << ",";
        }
        else{
            cout << even[x];
        }
    }
    cout << endl;
};
int main()
{
    vector <int> input = {5,6,2,4,5};
    createVect(input);

}