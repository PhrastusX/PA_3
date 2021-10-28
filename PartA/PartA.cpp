#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

int main()
{


  ifstream in_file("testfile.txt");

  //input vectors
  vector <double> v1;
  vector <double> v2;
  vector <double> v3;

  //reads file
  while (!in_file.eof() ){

    double value;
    

    in_file >> value;
    v1.push_back(value);
    in_file >> value;
    v2.push_back(value);
    in_file >> value;
    v3.push_back(value);

  }
  //shear matrix with -c/a in bottom left corner 
  double S[2][2] = { {1,0}, { 0 - (v1[1]/v1[0]), 1} };

  //build A matrix from input vectors
  double A[2][2] = { {v1[0],v2[0]}, {v1[1],v2[1]} };

  //find first row in A` matrix
  double x1 = S[0][0] * A[0][0] + S[0][1] * A[1][0];
  double x2 = S[0][0] * A[0][1] + S[0][1] * A[1][1];

  //find second row in A` matrix
  double x3 = S[1][0] * A[0][0] + S[1][1] * A[1][0];
  double x4 = S[1][0] * A[0][1] + S[1][1] * A[1][1];

  //fill in solutions from above process
  double A_prime[2][2] = { {x1,x2}, {x3,x4}};

  //multiply the shear matrix by b vector
  double b_prime[2] = {S[0][0] * v3[0] + 
                       S[0][1] * v3[1], 
                       S[1][0] * v3[0] + 
                       S[1][1] * v3[1]};

  //test to see if the system is Undertermined or Inconsistent
  //executes if vectors in A are linearally dependent
  if (A_prime[1][0] == 0 && A_prime[1][1] == 0){
    
    if (b_prime[1] == 0){
      cout << "System Underdetermined" << endl;

    }
    else{
      cout << "System Inconsistent" << endl;
    }
    cout << "non trivial solution exists" << endl;
    //calculate a solution
    double u_two = 1;

    double u_one = - A_prime[0][1]/A_prime[0][0];

    //normalize
    cout << u_one << endl;
    cout << u_two << endl;
    double length = sqrt(pow(u_one,2) + pow(u_two,2));

    cout << fixed << setprecision(4) << u_one/length << " " << u_two/length << endl;

    //print normalized vector

    
  } 

  //compute u vector
  else {
    //back substitution to find vector components for solution
  double u_two = b_prime[1]/A_prime[1][1];

  double u_one = (1/A_prime[0][0]) * (b_prime[0] - u_two * A_prime[0][1]);

  //store solution
  double u[2] = {u_one, u_two}; 

  cout << fixed << setprecision(4) << "u_one: " << u_one << "\nu_two: "<< u_two << endl;
  cout << "Only Trivial Solution exists" << endl;
}


}
  
