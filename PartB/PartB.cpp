#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class PartB
{
  private:
    double A[6];
    double A2x2[4];
    string in_string;
    string out_string;

    //used for testing
    void check_array(double A[4]){

      cout << A[0] << " " << A[1] << "\n" << A[2] << " " << A[3] << endl;

    }

    //will store data in A, S * mat format
    void mult2x2(double A_prime[4], double mat[4], double S[4]){

      A_prime[0] = S[0] * mat[0] + S[1] * mat[2];
      A_prime[1] = S[0] * mat[1] + S[1] * mat[3];

      A_prime[2] = S[2] * mat[0] + S[3] * mat[2];
      A_prime[3] = S[2] * mat[1] + S[3] * mat[3];
    }

    //length of a vector
    double calc_length(double a, double b){

      double length = sqrt(pow(a,2) + pow(b,2));
      return length;
    }

    //checks to see if the matrix are identical checks if they are nearly the same number
    bool is_same_mat(double mat1[4], double mat2[4]){
      int val1 = 0;


      for (int i = 0; i<4; i++){
        if ( abs(mat1[i] - mat2[i]) < .1){
          val1++;
      }

      }
      if (val1 == 4){
        return true;
      }
      else{
        return false;
    }
  }
  
  public:
    PartB(string in, string out){
      int i = 0;

    //Read file and store in A
    ifstream in_file(in);
    ofstream out_file(out);

    while (!in_file.eof()){

      double temp;

      in_file >> temp;
      A[i] = temp;

      i++;

      }//while

    A2x2[0] = A[0];
    A2x2[1] = A[1];
    A2x2[2] = A[3];
    A2x2[3] = A[4];
    //coeffient on lambda squared will always be 1
  double a = 1;

  //coeffiecient on lambda opposite of the sum of the diagonals
  double b = - (A[0] + A[4]);

  //coefficient on constant will be the product of diagonals minus the product
  //of anti diagonals
  double c = A[0] * A[4] - A[1] * A[3];

  

  //calculate roots
  //root one is dominant
  double root1 = (-b + sqrt(pow(b,2) - 4*a*c))/2.0;
  double root2 = (-b - sqrt(pow(b,2) - 4*a*c))/2.0;
  
  if (isnan(-root1) && isnan(-root2)){
    out_file <<  "No real eigenvalues"<< endl;
  }
  else{

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
    //find r1 and r2 using mat1 and mat2

    //gauss elimination to mat1 and mat2

    //calculate sheer matrix
    double S1[4];
    double S2[4];

    S1[0] = 1;
    S2[0] = 1;

    S1[1] = 0;
    S2[1] = 0;

    S1[2] = - (mat1[2]/mat1[0]);
    S2[2] = - (mat2[2]/mat2[0]);

    S1[3] = 1;
    S2[3] = 1;

  
    //multiply sheer matrix by mat and mat2 
    double A_prime1[4];
    double A_prime2[4];

    mult2x2(A_prime1, mat1, S1);
   mult2x2(A_prime2, mat2, S2);


 

  //back substitution
  double u11 =  1;
  double u12 = - A_prime1[0]/A_prime1[1];
  double length1 = calc_length(u11, u12);

  double u21 = -1;
  double u22 =  A_prime2[0]/A_prime2[1];
  double length2 = calc_length(u21, u22);

  double R[4] = {u11/length1, u21/length2, u12/length1, u22/length2};
  

  double R_t[4] = {R[0],R[2],R[1], R[3]};
  double lambda[4] = {root1, 0, 0 , root2};

  double test[4];
  double test1[4];
  mult2x2(test, R_t, lambda);
  mult2x2(test1, test, R);
  

  out_file << fixed << setprecision(4) << lambda[0] << " " << lambda[1] << "\n" << lambda[2] << " " << lambda[3] << endl;
  out_file << R[0] << " " << R[1] << "\n" << R[2] << " " << R[3] << endl;
  out_file << test1[0] <<" " << test1[1] << "\n" << test1[2] << " " << test1[3] << endl;

  if (is_same_mat(test1, A2x2) ){
    out_file << "1" <<endl;
  }
  else{
    out_file << "0"<< endl;
  }
  }
    }//constructor

};

int main() 
{

  PartB input_1 = PartB("pa3_input_1.txt", "tdiehl_output_B_1.txt");
  PartB input_2 = PartB("pa3_input_2.txt", "tdiehl_output_B_2.txt");
  PartB input_3 = PartB("pa3_input_3.txt", "tdiehl_output_B_3.txt");
  PartB input_4 = PartB("pa3_input_4.txt", "tdiehl_output_B_4.txt");
  PartB input_5 = PartB("pa3_input_5.txt", "tdiehl_output_B_5.txt");
}
