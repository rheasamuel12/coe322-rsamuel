#include <iostream>
#include <vector>
using namespace std;
//rhea samuel
//rss3488
void createVect(vector<int> vect) //function
{
    vector <int> odd; // odd vector
    vector <int> even; // even vector
    for(int x = 0; x<vect.size(); x++)
    {
        if(vect[x] %2 == 0)
        {
            even.push_back(vect[x]); //pushes even values to new vector
        }
        else{
            odd.push_back(vect[x]); //pushes odd values to new vector
        }
    }
    for(int x = 0; x<odd.size(); x++)
    {
        if(x!=odd.size()-1)
        {
            cout << odd[x] << ","; //prints out odd #s
        }
        else{
            cout << odd[x]; //last number with no comma
        }
    }
    cout << endl;
    for(int x =0; x<even.size(); x++)
    {
        if(x!=even.size()-1)
        {
            cout << even[x] << ","; //prints out even #s
        }
        else{
            cout << even[x]; //last number with no comma
        }
    }
    cout << endl;
};
int main()
{
    vector <int> input = {5,6,2,4,5}; //input
    createVect(input);

}