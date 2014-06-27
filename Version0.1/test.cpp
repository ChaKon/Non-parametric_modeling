#include <iostream>
#include <string>

#include "gurls++/rlswrapper.h"
#include "gurls++/rlsprimal.h"
#include "gurls++/primal.h"

using namespace gurls;
typedef double T;
int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(NULL)));

//    std::cout.precision(16);
//    std::cout.setf( std::ios::fixed, std::ios::floatfield);
//    std::cout.setf (std::cout.showpos);

    if(argc < 2 || argc > 3)
    {
        std::cout << "Usage: " << argv[0] << " <Version0.1 Data_Sets/ICUB_DATASET data directory>" << std::endl;
        return EXIT_SUCCESS;
    }
    gMat2D<T> Xtr, Xte, ytr;

    std::string XtrFileName = std::string(argv[1]) + "/Xtr.txt";
    std::string XteFileName = std::string(argv[1]) + "/Xte.txt";
    std::string ytrFileName = std::string(argv[1]) + "/ytr.txt";
    RLSWrapper<T> wrapper("test");
     try
    {
        // Load data files
        std::cout << "Loading data files..." << std::endl;
        Xtr.readCSV(XtrFileName);
        Xte.readCSV(XteFileName);
        ytr.readCSV(ytrFileName);
	
	std::cout << "Training model..." << std::endl;
        wrapper.train(Xtr, ytr);
	std::cout << "Testing..." << std::endl;
        gMat2D<T>* rec_result = wrapper.eval(Xte);
	std::cout << "Saving predictions matrix..." << std::endl;
        rec_result->saveCSV("results.txt");

        delete rec_result;

        return EXIT_SUCCESS;
    }
    catch (gException& e)
    {
        std::cout << e.getMessage() << std::endl;
        return EXIT_FAILURE;
    }
}

