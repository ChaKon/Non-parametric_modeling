#include <iostream>
#include <time.h>
#include <string>
#include "gurls++/icholwrapper.h"
#include "gurls++/recrlswrapper.h"
#include "gurls++/randfeatswrapper.h"
#include "gurls++/kernelrlswrapper.h"
#include "gurls++/rlsprimal.h"
#include "gurls++/primal.h"
using namespace gurls;
typedef double T;

// size of first batch to be used for initialization
const unsigned long n0 = 100;
int main(int argc, char* argv[])
{
  int start_s=clock();  
  srand(static_cast<unsigned int>(time(NULL)));

//    std::cout.precision(16);
//    std::cout.setf( std::ios::fixed, std::ios::floatfield);
//    std::cout.setf (std::cout.showpos);

    if(argc < 2 || argc > 3)
    {
        std::cout << "Usage: " << argv[0] << " <Version0.1 Data_Sets/ICUB_DATASET data directory>" << std::endl;
        return EXIT_SUCCESS;
    }

    gMat2D<T> Xtr_tot, Xte_tot, ytr_tot;

    std::string XtrFileName = std::string(argv[1]) + "Xtr_toosmall.txt";
    std::string XteFileName = std::string(argv[1]) + "Xte_toosmall.txt";
    std::string ytrFileName = std::string(argv[1]) + "ytr_toosmall.txt";
    // to check file path in debug mode
    //std::cout << " File path for XtrFileName :" << XtrFileName << std::endl;
    //std::cout << " File path for XteFileName :" << XteFileName << std::endl;
    //std::cout << " File path for ytrFileName :" << ytrFileName << std::endl;
    


    RandomFeaturesWrapper<T> wrapper("Non_Parametric_Modelling_Batch_RandomFeatures");
    //RecursiveRLSWrapper<T> wrapper1("Non_Parametric_Modelling_Incremental");

    try
    {
        ///////////////////////////////// Load data files ////////////////////////////////
        std::cout << "Loading data files..." << std::endl;
        Xtr_tot.readCSV(XtrFileName);
        Xte_tot.readCSV(XteFileName);
        ytr_tot.readCSV(ytrFileName);


        
	////////////////////////////////// Initialize model ////////////////////////////
        std::cout << "Training model..." << std::endl;
	//GurlsOptionsList * wrapper.getOpt() = opt;
	std::cout << " wrapper using process :" << wrapper.getOpt() <<std::endl;
	wrapper.train(Xtr_tot, ytr_tot);
	//wrapper.setParam();
	
         // Test on independent test set
        std::cout << "Testing..." << std::endl;
        gMat2D<T>* rec_result = wrapper.eval(Xte_tot);
	std::cout << "============ Printing Something ===========" << std::endl << std::endl;
	std::cout << wrapper.getOpt() << std::endl << std::endl;
	std::cout << "============ Printed Something ===========" << std::endl << std::endl;
        std::cout << "Saving predictions matrix..." << std::endl;
        rec_result->saveCSV("rec_result.txt");

        delete rec_result;
	int stop_s=clock();
        std::cout << "time (milliseconds): " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl << std::endl;

	
	
	
	return EXIT_SUCCESS;
    }
    catch (gException& e)
    {
        std::cout << e.getMessage() << std::endl;
        return EXIT_FAILURE;
    }
}
