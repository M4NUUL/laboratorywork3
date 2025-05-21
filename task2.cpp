#include <iostream>
#include <Miller_test.h>

using namespace std;

int main()
{
   int n;
   int target;
   cout << "Enter digit to test: ";
   cin >> n;
   cout << "Enter target digit: ";
   cin >> target;
   int Miller_test_result = Miller_test(n, target);
   return 0;
}