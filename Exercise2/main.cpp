#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <iomanip>

using namespace std;
using namespace Eigen;

int main()
{
    //il file data.txt contiene (un valore per riga): dimensione della matrice quadrata A,
    //elementi della matrice A ordinati per riga, elementi del vettore B, elementi del vettore exactSolution.
    string filename = "data.txt";
    ifstream ifstr(filename);
    if(ifstr.fail())
    {
        std::cerr << "File not found" << std::endl;
        return 2;
    }
    unsigned int iter = 0;
    unsigned int i;
    while (ifstr>>i)
    {
        iter++;
        cout << "\nDataset " << iter << endl;

        MatrixXd A = MatrixXd::Zero(i, i);
        for (unsigned int r = 0; r < i; r++)
        {
            for (unsigned int c = 0; c < i; c++)
            {
                ifstr >> A(r,c);
            }
        }

        VectorXd b = VectorXd::Zero(i);
        for (unsigned int c = 0; c < i; c++)
        {
            ifstr >> b(c);
        }
        //cout << setprecision(15) << scientific << A << endl;
        //cout << setprecision(15) << scientific << b << endl;

        //exact solution
        VectorXd exactSolution = VectorXd::Zero(i);
        for (unsigned int c = 0; c < i; c++)
        {
            ifstr >> exactSolution(c);
        }
        //cout << "Exact solution: " << setprecision(15) << scientific << exactSolution << endl;

        //PALU solution
        VectorXd x1 = A.fullPivLu().solve(b);
        //cout << "PALU solution: x1 = " << setprecision(15) << scientific << x1 << endl;

        double errRel1 = (exactSolution - x1).norm() / exactSolution.norm();
        cout << "PALU Relative Error: " << setprecision(15) << scientific <<errRel1 << endl;

        //QR solution
        VectorXd x2 = A.householderQr().solve(b);
        //cout << "QR solution: x2 = " << setprecision(15) << scientific << x2 << endl;

        double errRel2  = (exactSolution - x2).norm() / exactSolution.norm();
        cout << "QR Relative Error: " << setprecision(15) << scientific <<errRel2 << endl;
    }
    ifstr.close();


    return 0;
}
