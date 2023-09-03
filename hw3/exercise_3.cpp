#include <iostream>
using namespace std;
//rhea samuel
//rss3488
int main()
{
    int count = 0; //amount of steps
    int final = 0; //compare amount of steps to previous amount of steps
    int ret = 0;  //value of number that can be altered
    for(int number = 1; number<=1000; number++)
    {
        count = 0; //reset the count for each number
        ret = number;
        while(ret!=1) //loop stops when number reaches 1
        {
            if(ret%2==0) //if it is even
            {
                ret = ret/2;
                count++;
            }
            else{
                ret = (ret*3)+1; //if it is odd
                count++;
            }
        }
        if(final<count) //if amount of steps is bigger for new number
        {
            final = count; //set new value
            cout << number << endl; //print out the number
        }
    }
   // cout << ret << endl;
    return 0;
}