/*
 * test_Getpot.cpp
 *
 *  Created on: Aug 15, 2022
 *      Author: forma
 */
#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include "GetPot"
void printHelp()
{
  std::cout<< "test_json. A code that shows some json parsing tools\n";
  std::cout<< "some data is read form the file \"data.pot\"\n";
  std::cout<< "Synopsis:\n test_json [-h --help] [-f filename]\n";
  std::cout<< "filename: file to read (default \"data.json\")\n";
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
    std::string filename = cl.follow("data.json", "-p");
    // open the json file
    std::ifstream jfile(filename.c_str());
    nlohmann::json jdata;
    jfile>>jdata;// load data in json object

    // The last argument is the default value and also
    // determines the type of the returned data
    // Th edefault value is used if the file doesn not specify the parameter
    auto h  = jdata["problemData"].value("h",0.001);
    auto y0 = jdata["problemData"].value("y0", 0.0);

    std::string solverType = jdata["solverData"].value("solver","Beuler");
    std::string nonLinearSolver = jdata["solverData"].value("nonLinearSolver","broyden");
    auto maxIt = jdata["solverData"]["parameters"].value("maxIt",100u);
    auto tol = jdata["solverData"]["parameters"].value("tol",1.e-8);

    std::cout<<"Values read from "<<filename<<":\n";
    std::cout<<"h="<<h<<"\ty0="<<y0<<std::endl;
    std::cout<<"solverType= "<<solverType<<"\tnonLinearSolver="<<nonLinearSolver<<std::endl;
    std::cout<<"max n. Iter.="<<maxIt<<"\ttolerance="<<tol<<std::endl;

}



