// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12

#include <iostream>
using std::cin;
using std::cout;

#include <vector>
#include <string>

template <typename T>   // creating template T
class namedvector
  : public std::vector<T> {
private:
  std::string _name;
public:
  namedvector
    ( std::string n,int s )
    : _name(n)
    ,std::vector<T>(s) {};
  auto name() {
    return _name; };
};

// Exercise 5
namespace geo { // namedspaced class geo
    template <typename T>
    class vector : public namedvector<T> {  // adding functionality of namedvector
    public:
        vector(std::string n, int s) : namedvector<T>(n, s) {}
    };
}
int main() {

  namedvector<float> fivetemp("five",5);
  cout << fivetemp.name()
       << ": "
       << fivetemp.size() << '\n';
  cout << "at zero: "
       << fivetemp.at(0) << '\n';
  
  using namespace geo;
  geo::vector<float> float4("four",4);
  cout << float4.name() << '\n';
  float4[1] = 3.14;
  cout << float4.at(1) << '\n';
  geo::vector<std::string> string3("three",3);
  string3.at(2) = "abc";
  cout << string3[2] << '\n';

  return 0;
}