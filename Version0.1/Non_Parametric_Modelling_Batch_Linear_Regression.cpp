#include <iostream>
#include <time.h>
#include <ctime>
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
    if(argc<4)
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
    xte_file = argv[2];
    ytr_file = argv[3];
    yte_file = argv[4];

    try
    {
        gMat2D<T> Xtr, Xte, ytr, yte, pred_mat, error_mat, empty;
        // load data from file
        Xtr.readCSV(xtr_file);
        Xte.readCSV(xte_file);
        ytr.readCSV(ytr_file);
        yte.readCSV(yte_file);
	int row = ytr.rows();
	int test_row = yte.rows();
	int x_row = Xte.rows();
	int info = row + x_row;
	
	std::cout << " =========== Information of data set ============" << std::endl <<std::endl;
	std::cout << " rows for training :" <<row << "rows for testing :"<< test_row <<std::endl;
	std::cout << " total rows size :" <<info <<std::endl;
	std::string operation0, operation1,operation2,operation3,operation4,operation5,operation6,operation7;
	int choice;
	int option1,option2,option3,option4,option5,option6,option7;
	std::cout << "========================================================================================"<< std::endl
        << " Enter choice for regression to be done : " << std::endl
        << " 1 --> Linear regression" << std::endl
        << " 2 --> Using kernel (linear,rbf,chisquaredkernel)" << std::endl
        << " Default --> Any key" << std::endl
        << "========================================================================================" << std::endl << std::endl;
	std::cin >> choice;
	if (choice == 1)
	{
	std::cout << " You are using Linear Regression " << std::endl << std::endl;
	std::cout << "=====================================================" <<std::endl <<std::endl;
	std::cout << " You are using split:ho " << std::endl;
	operation0 = "split:ho";
	
	std::cout << "========================================================================================"<< std::endl
        << " Enter option to be done for parameter selection : " << std::endl
        << " 1 --> paramsel:fixlambda : for linear case" << std::endl
        << " 2 --> paramsel:loocvprimal : for linear case" << std::endl
        << " 3 --> paramsel:hoprimal : for linear case" << std::endl
        << " Default --> Any key (paramsel:fixlambda) " << std::endl
        << "========================================================================================" << std::endl << std::endl;
	std::cin >> option1;
	switch (option1)
	{
	  case 1 :
	    operation1 = "paramsel:fixlambda";
	    std::cout << " you specified parameter as fixlambda " <<std::endl;
	    break;
	  case 2 :
	    operation1 = "paramsel:loocvprimal";
	    std::cout << " you specified parameter as loocvprimal " <<std::endl;
	    break;
	  case 3 :
	    operation1 = "paramsel:hoprimal";
	    std::cout << " you specified parameter as hoprimal " <<std::endl;
	    break;
	  default :
	    operation1 = "paramsel:fixlambda";
	    std::cout << " defaults parameter is fixlambda " <<std::endl;
	    break;
	} 
	std::cout << "========================================================================================"<< std::endl
        << " Enter option to be done for optimizer: " << std::endl
        << " 1 --> optimizer:rlsprimal" << std::endl
        << " Default --> Any key (optimizer:rlsauto) " << std::endl
        << "========================================================================================" << std::endl << std::endl;
	std::cin >> option2;
	switch (option2)
	{
	  case 1 :
	    operation2 = "optimizer:rlsprimal";
	    std::cout << " you specified optimizer as rlsprimal " <<std::endl;
	    break;
	  default :
	    operation2 = "optimizer:rlsauto";
	    std::cout << " default optimizer is rlsauto " <<std::endl;
	    break;
	} 
	std::cout << "========================================================================================"<< std::endl
        << " Enter option to be done for predicting labels: " << std::endl
        << " 1 --> pred:primal" << std::endl
        << " Default --> Any key (pred:primal) " << std::endl
        << "========================================================================================" << std::endl << std::endl;
	std::cin >> option3;
	switch (option3)
	{
	  case 1 :
	    operation3 = "pred:primal";
	    std::cout << " you specified prediction as primal " <<std::endl;
	    break;
	  default :
	    operation3 = "pred:primal";
	    std::cout << " default prediction is primal " <<std::endl;
	    break;
	} 
	std::cout << "========================================================================================"<< std::endl
        << " Enter option to be done for prediction performance: " << std::endl
        << " 1 --> pref:rmse" << std::endl
        << " default --> pref:macroavg" << std::endl
        << "========================================================================================" << std::endl << std::endl;
	std::cin >> option4;
	switch (option4)
	{
	  case 1 :
	    operation4 = "perf:rmse";
	    std::cout << " specified performance measure as rmse " <<std::endl;
	    break;
	  default :
	    operation4 = "perf:macroavg";
	    std::cout << " default performance measure is macroavg " <<std::endl;
	    break;
	} 
	operation5 = "perf:macroavg";
	}
	else if(choice == 2) 
	{
	std::cout << " You are using kernel (linear,rbf,chisquaredkernel) " << std::endl << std::endl;
	std::cout << "============================================="<<std::endl <<std::endl;
	std::cout << " You are using split:ho " << std::endl;
	operation0 = "split:ho";
	std::cout << "========================================================================================"<< std::endl
        << " Enter option to be done for parameter selection : " << std::endl
        << " 1 --> paramsel:fixlambda/loocvprimal/hoprimal : for kernel case" << std::endl
        << " 2 --> paramsel:hodual : for kernel case" << std::endl
        << " 3 --> paramsel:siglam : for kernel case" << std::endl
        << " 4 --> paramsel:siglamho : for kernel case" << std::endl
        << " Default --> Any key (paramsel:loocvprimal) " << std::endl
        << "========================================================================================" << std::endl << std::endl;
	std::cin >> option1;
	switch (option1)
	{
	  case 1 :
	    operation1 = "paramsel:fixsiglam";
	    std::cout << " you specified parameter as fixsiglam " <<std::endl;
	    break;
	  case 2 :
	    operation1 = "paramsel:hodual";
	    std::cout << " you specified parameter as hodual " <<std::endl;
	    break;
	  case 3 :
	    operation1 = "paramsel:siglam";
	    std::cout << " you specified parameter as siglam " <<std::endl;
	    break;
	  case 4 :
	    operation1 = "paramsel:siglamho";
	    std::cout << " you specified parameter as siglamho " <<std::endl;
	    break;
	  default :
	    operation1 = "paramsel:loocvprimal";
	    std::cout << " defaults parameter is loocvprimal " <<std::endl;
	    break;
	}
	std::cout << "========================================================================================"<< std::endl
        << " Enter option to be done for kernel: " << std::endl
        << " 1 --> kernel:rbf" << std::endl
        << " 2 --> kernel:chisquaredkernel" << std::endl
        << " Default --> Any key (kernel:linear) " << std::endl
        << "========================================================================================" << std::endl << std::endl;
	std::cin >> option2;
	switch (option2)
	{
	  case 1 :
	    operation2 = "kernel:rbf";
	    std::cout << " you specified kernel as rbf " <<std::endl;
	    break;
	  case 2 :
	    operation2 = "kernel:chisquared";
	    std::cout << " you specified kernel as chisquaredkernel " <<std::endl;
	    break;
	  default :
	    operation2 = "kernel:linear";
	    std::cout << " default kernel is linear " <<std::endl;
	    break;
	} 
	std::cout << "========================================================================================"<< std::endl
        << " Enter option to be done for optimizer: " << std::endl
        << " 1 --> optimizer:rlsprimal" << std::endl
        << " 2 --> optimizer:rlsdual" << std::endl
        << " Default --> Any key (optimizer:rlsauto) " << std::endl
        << "========================================================================================" << std::endl << std::endl;
	std::cin >> option3;
	switch (option3)
	{
	  case 1 :
	    operation3 = "optimizer:rlsprimal";
	    std::cout << " you specified optimizer as rlsprimal " <<std::endl;
	    break;
	  case 2 :
	    operation3 = "optimizer:rlsdual";
	    std::cout << " you specified optimizer as rlsdual " <<std::endl;
	    break;
	  default :
	    operation3 = "optimizer:rlsauto";
	    std::cout << " default optimizer is rlsauto " <<std::endl;
	    break;
	} 
	
	std::cout << "======================================" << std::endl;
	std::cout << " You are using traintest for predkernel" <<std::endl <<std::endl;
	operation4 = "predkernel:traintest";
	std::cout << "========================================================================================"<< std::endl
        << " Enter option to be done for predicting labels: " << std::endl
        << " 1 --> pred:primal" << std::endl
        << " 2 --> pred:dual" << std::endl
        << " Default --> Any key (pred:primal) " << std::endl
        << "========================================================================================" << std::endl << std::endl;
	std::cin >> option5;
	switch (option5)
	{
	  case 1 :
	    operation5 = "pred:primal";
	    std::cout << " you specified prediction as primal " <<std::endl;
	    break;
	  case 2 :
	    operation5 = "pred:dual";
	    std::cout << " you specified prediction as dual " <<std::endl;
	    break;
	  default :
	    operation5 = "pred:primal";
	    std::cout << " default prediction is primal " <<std::endl;
	    break;
	} 
	std::cout << "========================================================================================"<< std::endl
        << " Enter option to be done for prediction performance: " << std::endl
        << " 1 --> perf:rmse" << std::endl
        << " Default --> Any key (perf:macroavg) " << std::endl
        << "========================================================================================" << std::endl << std::endl;
	std::cin >> option6;
	switch (option6)
	{
	  case 1 :
	    operation6 = "perf:rmse";
	    std::cout << " specified performance measure as rmse " <<std::endl;
	    break;
	  default :
	    operation6 = "perf:macroavg";
	    std::cout << " default performance measure is macroavg " <<std::endl;
	    break;
	} 
	operation7 = "perf:macroavg";
	}
	
	else {
	  std::cout << " You are using Default(Linear with default sequence) " << std::endl;
	  operation0 = "split:ho";
	  operation1 = "kernel:linear";
	  operation2 = "paramsel:siglam";
	  operation3 = "optimizer:rlsdual";
	  operation4 = "pred:dual";
	  operation5 = "perf:rmse";
	  //operation5 = "perf:macroavg";
	  //operation6 = "perf:prerec";
	  
	}
	
	int start_s=clock();
        // specify the task sequence
        OptTaskSequence *seq = new OptTaskSequence();
	if(choice==2)
	  *seq << operation0 << operation1 << operation2 << operation3 << operation4 << operation5 << operation6 << operation7;
	else
          //*seq << operation1 << operation2 << operation3 << operation4 << operation5; // << operation6;
          *seq << operation0 << operation1 << operation2 << operation3 << operation4 << operation5; // << operation6;
	
	std::cout << "========================================" << std::endl;
	std::cout << "Specified Task Sequence :" << std::endl;
	std::cout << *seq << std::endl <<std::endl; 


        GurlsOptionsList * process = new GurlsOptionsList("processes", false);
	

        // defines instructions for training process
        OptProcess* process1 = new OptProcess();
	if (choice==2)
	*process1 << GURLS::computeNsave << GURLS::computeNsave <<GURLS::computeNsave <<GURLS::computeNsave << GURLS::ignore << GURLS::ignore << GURLS::ignore <<GURLS::ignore;
        else
	//*process1 << GURLS::computeNsave <<GURLS::computeNsave <<GURLS::computeNsave << GURLS::ignore << GURLS::ignore;	  
	*process1 << GURLS::computeNsave << GURLS::computeNsave <<GURLS::computeNsave <<GURLS::computeNsave << GURLS::ignore << GURLS::ignore;
	process->addOpt("one", process1);

        // defines instructions for testing process
        OptProcess* process2 = new OptProcess();
	if (choice==2)
	  if(operation2 == "kernel:linear")
        *process2 << GURLS::load << GURLS::load << GURLS::load << GURLS::load << GURLS::load << GURLS::computeNsave << GURLS::computeNsave;
	  else
	*process2 << GURLS::load << GURLS::load << GURLS::load << GURLS::load << GURLS::computeNsave << GURLS::computeNsave << GURLS::computeNsave << GURLS::computeNsave;
	else
	//*process2 << GURLS::load << GURLS::load <<GURLS::load << GURLS::computeNsave << GURLS::computeNsave;
	*process2 << GURLS::load << GURLS::load << GURLS::load <<GURLS::load << GURLS::computeNsave << GURLS::computeNsave;
        process->addOpt("two", process2);

        // build an options' structure
        GurlsOptionsList* opt = new GurlsOptionsList("Non_Parametric_Modelling_Batch_Linear_Regression", true);
	opt->addOpt("seq", seq);
	opt->addOpt("processes", process);
	// for changing holdouts/split portions
	float value_for_splitportions;
	std::cout << "Enter your own choice to split proportion between training and validation set :"<<std::endl <<std::endl;
	std::cout << " *Caution it should be between 0 to 1 like 0.1,0.2....1 " <<std::endl <<std::endl;
	std::cin >> value_for_splitportions;
	std::cout << std::endl;
	opt->removeOpt("hoproportion");
	opt->addOpt("hoproportion",new OptNumber(value_for_splitportions));
	opt->removeOpt("hoperf");
	opt->addOpt("hoperf", new OptString("rmse"));
	int value_for_nholdouts;
	std::cout << "Enter your own choice to split the data to used for holdout cross validations :" <<std::endl <<std::endl;
	std::cout << " *Caution it should be between 1 to 10 like 1,2,3...10 " <<std::endl <<std::endl;
	std::cin >> value_for_nholdouts;
	std::cout << std::endl;
	opt->removeOpt("nholdouts");
	opt->addOpt("nholdouts",new OptNumber(value_for_nholdouts));
	// for experiments 
// 	opt->removeOpt("nsigma");
// 	opt->addOpt("nsigma",new OptNumber(3));
// 	opt->removeOpt("nlambda");
// 	opt->addOpt("nlambda", new OptNumber(3));
        GURLS G;

        string jobId0("one");
        string jobId1("two");

        // run gurls for training
        G.run(Xtr, ytr, *opt, jobId0);
	try{
           const gMat2D<T> &opti = opt->getOptValue<OptMatrix<gMat2D<T> > >("optimizer");
           std::cout << "\n" << opti.getSize() << std::endl << std::endl;
       }
       catch(std::exception &){
           std::cout << "Not computed" << std::endl<< std::endl;
       }
       int stop_s=clock();
       double time_train = (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
        std::cout << "time (seconds) for training: " << time_train/1000  << std::endl << std::endl;
	int start_s1=clock();


        // run gurls for testing
        G.run(Xte, yte, *opt, jobId1);
	
	// for displaying error output for performance measure
	std::cout << std::endl;
	std::cout << "************ Printing Resutlts ***********" <<std::endl << std::endl;
	std::cout << "Macroaverage performance: ";
       try{
           const gMat2D<T> &acc = opt->getOptValue<OptMatrix<gMat2D<T> > >("perf.acc");
           std::cout << "\n" << acc << std::endl << std::endl;
       }
       catch(std::exception &){
           std::cout << "Not computed" << std::endl<< std::endl;
       }

       std::cout << "Precision recall performance: ";
       try{
           const gMat2D<T> &ap = opt->getOptValue<OptMatrix<gMat2D<T> > >("perf.precrec");
           std::cout << "\n" << ap << std::endl << std::endl;
       }
       catch(std::exception &){
           std::cout << "Not computed" << std::endl << std::endl;
       }

       std::cout << "RMSE performance: ";
       try{
           const gMat2D<T> &rmse = opt->getOptValue<OptMatrix<gMat2D<T> > >("perf.rmse");
           std::cout << "\n" << rmse.operator/(test_row) << std::endl << std::endl;
       }
       catch(std::exception &){
           std::cout << "Not computed" << std::endl << std::endl;
       }
       std::cout << "************ Printed Resutlts ***********" <<std::endl << std::endl;
        //GurlsOption *nholdouts = opt->getOpt("nholdouts");
	//GurlsOption *hoproportion = opt->getOpt("hoproportion");
// 	std::cout << " ---- Changed nholdouts ---- " <<std::endl << std::endl; 
// 	std::cout <<" nholdouts :" << *nholdouts <<std::endl << std::endl;;
// 	std::cout << " ---- Changed splitportions ---- " <<std::endl << std::endl; 
// 	std::cout <<" split portions :" << *hoproportion << std::endl << std::endl;;
// 	
	std::cout << " ================= Printing All ================" <<std::endl << std::endl;
	opt->printAll();
	std::cout << " ================= Printed All ================" <<std::endl << std::endl;
	int stop_s1=clock();
	double time_test = (stop_s1-start_s1)/double(CLOCKS_PER_SEC)*1000;
        std::cout << "time (seconds) for testing: " << time_test/1000 << std::endl << std::endl;
	

    }
    catch (gException& e)
    {
        cout << e.getMessage() << endl;
        return EXIT_FAILURE;
    }
   
    return EXIT_SUCCESS;
 

}
