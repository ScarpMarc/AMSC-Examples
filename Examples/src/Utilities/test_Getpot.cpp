/*
 * test_Getpot.cpp
 *
 *  Created on: Aug 15, 2022
 *      Author: forma
 */
#include <iostream>
#include <fstream>
#include <string>
#include "GetPot"
void printHelp()
{
  std::cout<< "test_Getpot. A code that shows some GetPot parsing tools\n";
  std::cout<< "some data is read form the file \"data.pot\"\n";
  std::cout<< "Synopsis:\n test_Getpot [-h --help] [-f filename]\n";
  std::cout<< "filename: file to read (default \"data.pot\")\n";
}
int main(int argc, char** argv)
{
  GetPot cl(argc, argv);
  // Test possible options
    if(cl.search(2, "-h", "--help"))
      {
        printHelp();
        return 0;
      }
    // Reading options from command line
    std::string filename = cl.follow("data.pot", "-p");
    // Read a GetPot formatted data file
    GetPot     ifile(filename.c_str());

    // The last argument is the default value and also
    // determines the type of the returned data
    // Th edefault value is used if the file doesn not specify the parameter
    auto h  = ifile("problemData/h",0.01);
    auto y0 = ifile("problemData/y0",0.01);
    std::string solverType = ifile("solverData/solver","Beuler");
    std::string nonLinearSolver = ifile("solverData/nonLinearSolver","broyden");
    auto maxIt = ifile("solverData/parameters/maxIt",100u);
    auto tol = ifile("solverData/parameters/tol",1.e-8);

    std::cout<<"Values read from "<<filename<<":\n";
    std::cout<<"h="<<h<<"\ty0="<<y0<<std::endl;
    std::cout<<"solverType= "<<solverType<<"\tnonLinearSolver="<<nonLinearSolver<<std::endl;
    std::cout<<"max n. Iter.="<<maxIt<<"\ttolerance="<<tol<<std::endl;

}



