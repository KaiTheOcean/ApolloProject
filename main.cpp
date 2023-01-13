//
//  main.cpp
//  W03Exercise
//
//  Created by Kaidi Zhang on 1/13/23.
//

#include <iostream>
using namespace std;

class Complex
{
public:
   double real;
   double imaginary;
   
   void display()
   {
      cout << real << " + " << imaginary << endl;
   }
   
   void set(double r, double i)
   {
      
   }
   
   double getReal()
   {
      
   }
   
   double getImaginary()
   {
      
   }
};

int main(int argc, const char * argv[])
{
   Complex c;
   c.real = 7.3;
   c.imaginary = 4.6;
   cout << "This is for c.real: " << c.real << endl;
   cout << "This is for c.imagniary: " << c.imaginary << endl;
   return 0;
}
