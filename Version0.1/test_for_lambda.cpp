#include <iostream>
#include <time.h>
#include "gurls++/norm.h"
#include "gurls++/gurls.h"
#include "gurls++/exceptions.h"
#include "gurls++/gmat2d.h"
#include "gurls++/options.h"
#include "gurls++/optlist.h"

#include "gurls++/gmath.h"


using namespace gurls;
using namespace std;

typedef double T; ///< Data type of the matrices elements

/**
  * Main function
  */
int main(int argc, char *argv[])
{
    string xtr_file, xte_file, ytr_file, yte_file;
    

    // check that all inputs are given
    if(argc<2)
    {
        std::cout << "========================================================================================"<< std::endl
        << " Wrong parameters number ("<<argc <<")." << std::endl
        << " Provide a valid path for training, test and output files using the following syntax:" << std::endl
        << " \n\n\t " << argv[0] << " xtr xte ytr yte" << std::endl
        << " example of usage ../../Data_Sets/ICUB_DATASETS/Xtr.txt ../../Data_Sets/ICUB_DATASETS/Xte.txt ../../Data_Sets/ICUB_DATASETS/ytr.txt ../../Data_Sets/ICUB_DATASETS/yte.txt" << std::endl
        << "========================================================================================" << std::endl << std::endl;
        return 0;
    }

    // get file names from input
    xtr_file = argv[1];
    //xte_file = argv[2];
    ytr_file = argv[2];
    //yte_file = argv[4];

    try
    {
        gMat2D<T> Xtr, Xte, ytr, yte,slambdas;
        // load data from file
        Xtr.readCSV(xtr_file);
        //Xte.readCSV(xte_file);
        ytr.readCSV(ytr_file);
        //yte.readCSV(yte_file);
	int row = ytr.rows();
	std::cout << " =========== Number of rows for training ============" << std::endl <<std::endl;
	std::cout << " rows of training :" <<row <<std::endl;
	std::cout << " ============Number of rows displaye d ==============" << std::endl <<std::endl;
	 OptTaskSequence *seq = new OptTaskSequence();
	 *seq << "paramsel:loocvprimal";
	 std::cout << "========================================" << std::endl;
	std::cout << "Specified Task Sequence :" << std::endl;
	std::cout << *seq << std::endl <<std::endl; 
	GurlsOptionsList * process = new GurlsOptionsList("processes", false);
	OptProcess* process1 = new OptProcess();
	*process1 << GURLS::computeNsave;
	process->addOpt("one", process1);
	GurlsOptionsList* apt = new GurlsOptionsList("test_for_lambda", true);
	apt->addOpt("seq", seq);
	apt->addOpt("processes", process);
	 GURLS G;

        string jobId0("one");

        // run gurls for training
	
        G.run(Xtr, ytr, *apt, jobId0);
	try{
           const gMat2D<T> &lambdas = apt->getOptValue<OptMatrix<gMat2D<T> > >("paramsel.lambdas");
	   const T *lmn = lambdas.getData();
	   std::cout <<" lmn lambda :" <<*lmn <<std::endl;
           std::cout << "lambda values: \n" << lambdas << std::endl << std::endl;
	   
       }
       catch(std::exception &){
           std::cout << "Not computed" << std::endl << std::endl;
       }
       double x;
       GurlsOption *y = apt->getOpt("singlelambda");
       //const gMat2D<T> &lambda = apt->getOptValue<OptFunction>("singlelambda");     
       std::cout << *y <<std::endl;

     
       
       std::cout << " ================= Printing All ================" <<std::endl << std::endl;
	apt->printAll();
	std::cout << " ================= Printed All ================" <<std::endl << std::endl;

	
    }
    catch (gException& e)
    {
        cout << e.getMessage() << endl;
        return EXIT_FAILURE;
    }
   
    return EXIT_SUCCESS;
 

}
