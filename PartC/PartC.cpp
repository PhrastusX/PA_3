#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>

using namespace std;
class PartC
{
    public:
    PartC(string in, string out){
        //read three points in
    vector <double> a;
    vector <double> b;
    vector <double> c;
    double area;

    ifstream in_file(in);
    ofstream out_file(out);

    while (!in_file.eof()){
        double temp;
        in_file >> temp;
        a.push_back(temp);
        in_file >> temp;
        b.push_back(temp);
        in_file >> temp;
        c.push_back(temp);
}

    //compute area of triangle formed by points *first line of output file*

    area = abs( (a[0] * (b[1] - c[1]) + b[0] * (c[1] - a[1]) + c[0] * (a[1] - b[1]) ) /2);

    out_file << fixed << setprecision(4) << area << endl;

    //first two point make a line

    //find vector perpendicular to a - b
    vector <double> vect_ab;
    vect_ab.push_back(b[0] - a[0]);
    vect_ab.push_back(b[1] - a[1]);

    double vect_perp[2] = {-vect_ab[1], vect_ab[0]}; 
    double vect_parallel[2] = {vect_ab[0], vect_ab[1]};

    double length_vect_perp = sqrt(pow(vect_perp[0], 2) + pow(vect_perp[1], 2) );
    double length_vect_parallel = sqrt(pow(vect_parallel[0], 2) + pow(vect_parallel[1], 2) );

    //find the distance between point c and the a - b line *second line of output*
    double implicit_c = - (vect_perp[0]*a[0] + vect_perp[1]*a[1]);



    double distance = abs((vect_perp[0] * c[0] + vect_perp[1] * c[1] + implicit_c) / length_vect_perp);

    out_file << distance << endl;

    //find the foot point of the line *third line of output*

    double vect_w[2] = {c[0] - a[0] , c[1] - a[1]};

    //dot product of v * w divided by length of v^2
    double t = (vect_parallel[0]*vect_w[0] + vect_parallel[1]*vect_w[1])/pow(length_vect_parallel, 2);

    out_file << a[0] + t * vect_parallel[0] << " " << a[1] + t * vect_parallel[1] << endl;

    }
};
int main(){

    PartC input_1 = PartC("pa3_input_1.txt", "tdiehl_output_C_1.txt");
    PartC input_2 = PartC("pa3_input_2.txt", "tdiehl_output_C_2.txt");
    PartC input_3 = PartC("pa3_input_3.txt", "tdiehl_output_C_3.txt");
    PartC input_4 = PartC("pa3_input_4.txt", "tdiehl_output_C_4.txt");
    PartC input_5 = PartC("pa3_input_5.txt", "tdiehl_output_C_5.txt");


}