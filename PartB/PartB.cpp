#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

int main() 
{

  double A[6];
  int i = 0;

  ifstream in_file("testfile.txt");

  while (!in_file.eof()){

    double temp;

    in_file >> temp;
    A[i] = temp;

    i++;

  }
  for (int i = 0; i < 6; i++){
    cout << A[i] << endl;
  }

  //find the characteristic equation

  //coeffient on lambda squared will always be 1
  double a = 1;

  //coeffiecient on lambda opposite of the sum of the diagonals
  double b = - (A[0] + A[4]);

  //coefficient on constant will be the product of diagonals minus the product
  //of anti diagonals
  double c = A[0] * A[4] - A[1] * A[3];

  cout << a << " " << b << " " << c << endl;

  //calculate roots
  //root one is dominant
  double root1 = (-b + sqrt(pow(b,2) - 4*a*c))/2.0;
  double root2 = (-b - sqrt(pow(b,2) - 4*a*c))/2.0;

  cout << root1 << " " << root2 << endl;

  //find dominant eigen value

  //if absolute value of root1 is less than root 2 swap them
  if(abs(root1) < abs(root2)){
    double temp;
    temp = root1;
    root1 = root2;
    root2 = temp;
  }

  double mat1[4];
  double mat2[4];
  
  


}
