#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  ifstream in_file("testfile.txt");

  vector <double> v1;
  vector <double> v2;
  vector <double> v3;

  while (!in_file.eof() ){

    double value;
    

    in_file >> value;
    v1.push_back(value);
    in_file >> value;
    v2.push_back(value);
    in_file >> value;
    v3.push_back(value);

  }
  double S[2][2] = { {1,0}, { 0 - (v1[1]/v1[0]), 1} };

  double A[2][2] = { {v1[0],v2[0]}, {v1[1],v2[1]} };

  double x1 = S[0][0] * A[0][0] + S[0][1] * A[1][0];
  double x2 = S[0][0] * A[0][1] + S[0][1] * A[1][1];

  double x3 = S[1][0] * A[0][0] + S[1][1] * A[1][0];
  double x4 = S[1][0] * A[0][1] + S[1][1] * A[1][1];

  double A_prime[2][2] = { {x1,x2}, {x3,x4}};
  double b_prime[2] = {S[0][0] * v3[0] + 
                       S[0][1] * v3[1], 
                       S[1][0] * v3[0] + 
                       S[1][1] * v3[1]};

  cout << A_prime[0][0] << " " << A_prime[0][1] << endl;
  cout << A_prime[1][0] << " " << A_prime[1][1] << endl;
  cout << " = " << endl;
  cout << b_prime[0] << "\n" << b_prime[1] << endl;

  double u_two = b_prime[1]/A_prime[1][1];
  double u_one = (1/A_prime[0][0]) * (b_prime[0] - u_two * A_prime[0][1]);

  double u[2] = {u_one, u_two}; 

  cout << "u_one: " << u_one << "\nu_two: "<< u_two << endl;
}
