// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12
#include <iostream>
using std::boolalpha;
using std::cout;
#include <vector>
using std::vector;
#include <algorithm>
using std::any_of;
#include <numeric> // for std::accumulate
#include <range/v3/all.hpp>

int main() {
  using namespace ranges;
  cout << "Perfect Numbers"<< std::endl;
  auto is_perfect = [](int n) {
    auto divisors = views::iota(1) | views::take_while([n](int i) { return i <= n / 2; }) |
                    views::filter([n](int i) { return n % i == 0; });
    int sum = accumulate(divisors, 0);
    return sum == n;
  };
  auto perfect_view = views::iota(1) | views::filter(is_perfect) | views::take(4);
  int n = 0;
  for (auto perfect_number : perfect_view) {
    n++;
    cout << perfect_number << " is a perfect number" << std::endl;
    if(n >= 4)
      break;
  }
  return 0;
}