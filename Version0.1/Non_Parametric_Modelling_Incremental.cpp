#include <iostream>
#include <time.h>
#include <string>
#include "gurls++/icholwrapper.h"
#include "gurls++/recrlswrapper.h"
#include "gurls++/kernelrlswrapper.h"
#include "gurls++/rlsprimal.h"
#include "gurls++/primal.h"
using namespace gurls;
using namespace std;
typedef double T;

// size of first batch to be used for initialization
const unsigned long n0 = 2500;
int main(int argc, char* argv[])
{
  
//    std::cout.precision(16);
//    std::cout.setf( std::ios::fixed, std::ios::floatfield);
//    std::cout.setf (std::cout.showpos);

    if(argc < 2 || argc > 3)
    {
        std::cout << "Usage: " << argv[0] << " <Version0.1 Data_Sets/ICUB_DATASET data directory>" << std::endl;
        return EXIT_SUCCESS;
    }

    gMat2D<T> Xtr_tot, Xte_tot, ytr_tot;

    std::string XtrFileName = std::string(argv[1]) + "Xtr_100psmall.txt";
    std::string XteFileName = std::string(argv[1]) + "Xte_100psmall.txt";
    std::string ytrFileName = std::string(argv[1]) + "ytr_100psmall.txt";
    // to check file path in debug mode
    //std::cout << " File path for XtrFileName :" << XtrFileName << std::endl;
    //std::cout << " File path for XteFileName :" << XteFileName << std::endl;
    //std::cout << " File path for ytrFileName :" << ytrFileName << std::endl;
    


    RecursiveRLSWrapper<T> wrapper("Non_Parametric_Modelling_Incremental");
   
    //RecursiveRLSWrapper<T> wrapper1("Non_Parametric_Modelling_Incremental");
    try
    {
        ///////////////////////////////// Load data files ////////////////////////////////
        std::cout << "Loading data files..." << std::endl;
        Xtr_tot.readCSV(XtrFileName);
        Xte_tot.readCSV(XteFileName);
        ytr_tot.readCSV(ytrFileName);

        /////////////////////////////// Load first batch for parameter selection and initialization //////////////////////////
        const unsigned long n = Xtr_tot.rows();
        const unsigned long d = Xtr_tot.cols();
        const unsigned long t = ytr_tot.cols();
	std::cout << "n :" << n <<std::endl;
	std::cout << "d :" << d <<std::endl;
	std::cout << "t :" << t <<std::endl;
	int start_train=clock();  
	srand(static_cast<unsigned int>(time(NULL)));
	gMat2D<T> Xtr(n0, d);
        gMat2D<T> ytr(n0, t);
	std::cout <<" Size of Xtr :" <<Xtr.getSize() <<std::endl;
	std::cout <<" Size of ytr :" <<ytr.getSize() <<std::endl;

        unsigned long *rows = new unsigned long [n0];
        for(unsigned long i=0; i<n0; ++i)
            rows[i] = i;
        subMatrixFromRows(Xtr_tot.getData(), n, d, rows, n0, Xtr.getData());
        subMatrixFromRows(ytr_tot.getData(), n, t, rows, n0, ytr.getData());
	//std::cout<< " row element :"<< ytr << std::endl;
	wrapper.setSplitProportion(0.4);
	wrapper.setProblemType(gurls::GurlsWrapper< T >::REGRESSION);
	////////////////////////////////// Initialize model ////////////////////////////
        std::cout << "Training model..." << std::endl;
	//GurlsOptionsList * wrapper.getOpt() = opt;
	std::cout << " wrapper using process :" << wrapper.getOpt() <<std::endl;
	wrapper.train(Xtr, ytr);
	//wrapper.setParam();
	
	std::cout << " Sequence done in training :" << std::endl;
	std::cout<< " Opt info :" <<wrapper.getOpt()<<std::endl;
	
	///////////////////////////////// update estimator /////////////////////////////
	std::cout << "Updating estimator..." << std::endl;

        gVec<T> Xnew(d);
        gVec<T> ynew(t);
        for(unsigned long i=n0; i<n; ++i)
        {
            // Read a row from the file where the global training set is stored and update estimator
            getRow(Xtr_tot.getData(), n, d, i, Xnew.getData());
            getRow(ytr_tot.getData(), n, t, i, ynew.getData());
            // Update estimator with a new input pair
            wrapper.update(Xnew, ynew);
	    //std::cout << " Wrapper getOpt : " << wrapper.getOpt() << std::endl;
        }
        int stop_train=clock();
        double train_time = (stop_train-start_train)/double(CLOCKS_PER_SEC)*1000;
        std::cout << "time (seconds) for training: " << train_time/1000 << std::endl << std::endl;
         // Test on independent test set
         int start_test=clock();  
         srand(static_cast<unsigned int>(time(NULL)));
        std::cout << "Testing..." << std::endl;
        gMat2D<T>* rec_result = wrapper.eval(Xte_tot);
	    std::cout << "============ Printing Something ===========" << std::endl << std::endl;
	    std::cout << wrapper.getOpt() << std::endl << std::endl;
	    std::cout << "============ Printed Something ===========" << std::endl << std::endl;
        std::cout << "Saving predictions matrix..." << std::endl;
        rec_result->saveCSV("kernel1.txt");

        delete rec_result;
        int stop_test=clock();
        double test_time = (stop_test-start_test)/double(CLOCKS_PER_SEC)*1000;
        std::cout << "time (seconds) for testing: " << test_time/1000 << std::endl << std::endl;
	return EXIT_SUCCESS;
    }
    catch (gException& e)
    {
        std::cout << e.getMessage() << std::endl;
        return EXIT_FAILURE;
    }
}
