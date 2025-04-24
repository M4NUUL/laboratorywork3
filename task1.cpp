#include <iostream>
#include <cmath> // для sqrt
#include <iomanip> // для вывода с точностью и для setw


using namespace std;

pair<float, float> fx(float x)
{ 
   if (x < 0)
   {
      return {x, -0.5*x};
   }
   else if (x >= 0 && x <= 2)
   {
      return {x, sqrt(4 - x*x) + 2};
   }
   else if (x > 2 && x < 4)
   {
      return {x, sqrt(4 - (x - 2)*(x - 2))};
   }
   return {x, -(x -4)/2};
}

int main() 
{
cout << "Через пробел введите x начальное, x конечное и шаг x: ";
int x_start, x_end;
float step;
cin >> x_start >> x_end >> step;
cout << fixed << setprecision(2);
cout << setw(8) << "x" << setw(10) << "y" << endl;
cout << "-------------------------" << endl;
for (float x = x_start; x <= x_end; x += step) 
{
   pair<float, float> result = fx(x);
   cout << setw(10) << result.first << setw(10) << result.second << endl;
}
return 0;
}