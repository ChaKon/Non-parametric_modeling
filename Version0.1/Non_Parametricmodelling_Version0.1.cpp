#include <iostream>
#include <string>

#include "gurls++/recrlswrapper.h"
#include "gurls++/rlsprimal.h"
#include "gurls++/primal.h"
using namespace gurls;
typedef double T;

// size of first batch to be used for initialization
const unsigned long n0 = 100;
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

    gMat2D<T> Xtr_tot, Xte_tot, ytr_tot;

    std::string XtrFileName = std::string(argv[1]) + "Xtr.txt";
    std::string XteFileName = std::string(argv[1]) + "Xte.txt";
    std::string ytrFileName = std::string(argv[1]) + "ytr.txt";
    // to check file path in debug mode
    std::cout << " File path for XtrFileName :" << XtrFileName << std::endl;
    std::cout << " File path for XteFileName :" << XteFileName << std::endl;
    std::cout << " File path for ytrFileName :" << ytrFileName << std::endl;
    


    RecursiveRLSWrapper<T> wrapper("Non_Parametricmodelling_version0.1");

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
	
	gMat2D<T> Xtr(n0, d);
        gMat2D<T> ytr(n0, t);
	std::cout <<" Size of Xtr :" <<Xtr.getSize() <<std::endl;
	std::cout <<" Size of ytr :" <<ytr.getSize() <<std::endl;

        unsigned long *rows = new unsigned long [n0];
        for(unsigned long i=0; i<n0; ++i)
            rows[i] = i;
        subMatrixFromRows(Xtr_tot.getData(), n, d, rows, n0, Xtr.getData());
        subMatrixFromRows(ytr_tot.getData(), n, t, rows, n0, ytr.getData());
	std::cout<< " row element :"<< ytr << std::endl;
	////////////////////////// specifying the task sequence ////////////////////////////
	OptTaskSequence *seq = new OptTaskSequence();
	*seq << "split:ho" << " paramsel:hoprimal" <<"Optimizer:RLSPrimalRecInit";
	GurlsOptionsList * process = new GurlsOptionsList("processes", true);
	/////////////////////// for training process instructions /////////////////////////
	OptProcess* process1 = new OptProcess();
        *process1 << GURLS::computeNsave << GURLS::computeNsave << GURLS::computeNsave;
        process->addOpt("one",process1);
	GurlsOptionsList* opt = new GurlsOptionsList("Non_Parametricmodelling_version0.1",true);
	opt->addOpt("seq", seq);
	opt->addOpt("processes", process);
	std::cout << "====================" << std::endl;
	std::cout << " Opt structure specified by user : " << *opt << std::endl;
	//GurlsOptionsList:recursiveRLS:seq;
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
	    std::cout << " Wrapper getOpt : " << wrapper.getOpt() << std::endl;
        }

	
	
	
	return EXIT_SUCCESS;
    }
    catch (gException& e)
    {
        std::cout << e.getMessage() << std::endl;
        return EXIT_FAILURE;
    }
}
