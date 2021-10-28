#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class PartA
{
  private:
    vector <double> v1;
    vector <double> v2;
    vector <double> v3;

    string out_file;

  public:

    PartA(string in_file, string out_f)
    {
      ifstream in_f(in_file);

      while (!in_f.eof() ){

        double value;
    

        in_f >> value;
        v1.push_back(value);
        in_f >> value;
        v2.push_back(value);
        in_f >> value;
        v3.push_back(value);

      }
      in_f.close();

      out_file = out_f;

      write_file();
    }

    void write_file()
    {
      //outfile
      ofstream out(out_file);


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
          out << "System Underdetermined" << endl;

        }
        else{
          out << "System Inconsistent" << endl;
        }
        
        //calculate a solution
        double u_two = 1;

        double u_one = - A_prime[0][1]/A_prime[0][0];

        //normalize
        
        
        double length = sqrt(pow(u_one,2) + pow(u_two,2));

        out << fixed << setprecision(4) << u_one/length << " " << u_two/length << endl;

        //print normalized vector

    
      } 

      //compute u vector
      else {
       //back substitution to find vector components for solution
      double u_two = b_prime[1]/A_prime[1][1];

      double u_one = (1/A_prime[0][0]) * (b_prime[0] - u_two * A_prime[0][1]);

      out << fixed << setprecision(4) <<  u_one << " "<< u_two << endl;
      out << "Only Trivial Solution exists" << endl;
      }
      out.close();
    }
};

int main()
{

  PartA input_1 = PartA("pa3_input_1.txt", "tdiehl_output_A_1.txt");
  PartA input_2 = PartA("pa3_input_2.txt", "tdiehl_output_A_2.txt");
  PartA input_3 = PartA("pa3_input_3.txt", "tdiehl_output_A_3.txt");
  PartA input_4 = PartA("pa3_input_4.txt", "tdiehl_output_A_4.txt");
  PartA input_5 = PartA("pa3_input_5.txt", "tdiehl_output_A_5.txt");
  
}
  
