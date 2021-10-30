#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>

using namespace std;
void check_array(double A[4]);
int main() 
{

  double A[6];
  int i = 0;

  //Read file and store in A
  ifstream in_file("testfile.txt");

  while (!in_file.eof()){

    double temp;

    in_file >> temp;
    A[i] = temp;

    i++;

  }

  //make a 2x2 matrix
  double A2x2[4];
  A2x2[0] = A[0];
  A2x2[1] = A[1];
  A2x2[2] = A[3];
  A2x2[3] = A[4];

  for (int i = 0; i < 4; i++){
    cout << A2x2[i] << endl;
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

  //find the eigen vectors
  double mat1[4];
  double mat2[4];

  //fill mat 1 with dominant eigen vector and mat2 with non
  for(int i = 0; i < 4; i++){
    
    if (i == 1 || i == 2){
      mat1[i] = A2x2[i];
      mat2[i] = A2x2[i];
    } 
    else{
      mat1[i] = (A2x2[i] - root1);
      mat2[i] = (A2x2[i] - root2);
    }
   

  }
  cout << mat2[0] << " " << mat2[1] << "\n" << mat2[2] << " " << mat2[3] << endl;

  //find r1 and r2 using mat1 and mat2

  //gauss elimination to mat1 and mat2

  //calculate sheer matrix
  double S1[4];
  double S2[4];

  S1[0] = 1;
  S2[0] = 1;

  S1[1] = 0;
  S2[1] = 0;

  S1[2] = - mat1[2]/mat1[0];
  S2[2] = - mat2[2]/mat2[2];

  S1[3] = 1;
  S2[3] = 1;

  cout << S2[0] << " " << S2[1] << "\n" << S2[2] << " " << S2[3] << endl;

  //multiply sheer matrix by mat and mat2 
  double A_prime1[4];
  double A_prime2[4];

  A_prime1[0] = S1[0] * mat1[0] + S1[1] * mat1[2];
  A_prime1[1] = S1[0] * mat1[1] + S1[1] * mat1[3];

  A_prime1[2] = S1[2] * mat1[0] + S1[3] * mat1[2];
  A_prime1[3] = S1[2] * mat1[1] + S1[3] * mat1[3];

  check_array(A_prime1);

}

void check_array(double A[4]){
  cout << A[0] << " " << A[1] << "\n" << A[2] << " " << A[3] << endl;
}
