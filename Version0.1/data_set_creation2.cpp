#include <iostream>
#include <string>
#include "gurls++/gmat2d.h"

using namespace gurls;
using namespace std;
typedef double T; ///< Data type of the matrices elements
int main(int argc, char* argv[])
{
    typedef double T;

    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <Version0.1 Data_Sets/SILIVIO's_DATASET directory>" << std::endl;
        return EXIT_SUCCESS;
    }

    gMat2D<T> data, Xtr,Xte,ytr,yte;

    std::string datafilepath = std::string(argv[1]) + "/Y_data";
    std::cout<<datafilepath <<std::endl;

    try
    {
        //load the training data
        data.readCSV(datafilepath);
	int row = data.rows();
	int col = data.cols();
	std::cout<<row<<std::endl;
	std::cout<<col<<std::endl;
	std::ofstream results_file1;
	std::ofstream results_file2;
	std::ofstream results_file3;
	std::ofstream results_file4;
	results_file1.open("Xtr.txt");
	results_file2.open("Xte.txt");
	results_file3.open("ytr.txt");
	results_file4.open("yte.txt");
	
	int train_rows, test_rows;
	double Xtrain,Xtest,Ytrain,Ytest;
	train_rows = row*0.7;
	test_rows = row - train_rows;
	std::cout<<"train_rows  "<< train_rows<<std::endl;
	std::cout<<"test_rows   " << test_rows<<std::endl;
	// for X_data especially for the data set of Silivio's we have to do separetely
// 	// Xtr -- Training the data (1:12 columns) which is of 70% of data
// 	for (int i=0; i<=train_rows ; i++)
// 	{
// 	  if(i !=train_rows){
// 	  for (int j=0; j<=12 ; j++)
// 	  {
// 	    
// 	    if (j !=12)
// 	    {
// 	    Xtrain = data[i][j];
// 	    results_file1 << Xtrain << ",";
// 	    }
// 	    else
// 	    {
// 	      results_file1 << std::endl;
// 	    }
// 
// 	  }
// 	  }
// 	  else { results_file1 << std::endl; }
// 	}
// 	// Xte -- Testing of the data which is 30% (1:12 columns)
// 	for (int i=train_rows; i<=row ; i++)
// 	{
// 	  if(i !=row){
// 	  for (int j=0; j<=12 ; j++)
// 	  {
// 	    
// 	    if (j !=12)
// 	    {
// 	    Xtest = data[i][j];  
// 	    results_file2 << Xtest << ",";
// 	    }
// 	    else
// 	    {
// 	      results_file2 << std::endl;
// 	    }
// 
// 	  }
// 	  }
// 	  else { results_file2 << std::endl; }
// 	}
// 	// Ytr -- Training of the output which is of 70% (13:18 columns)
// 	for (int i=0; i<=train_rows ; i++)
// 	{
// 	  if(i !=train_rows){
// 	  for (int j=13; j<=18 ; j++)
// 	  {
// 	    
// 	    if (j !=18)
// 	    {
// 	    Ytrain = data[i][j];  
// 	    results_file3 << Ytrain << ",";
// 	    }
// 	    else
// 	    {
// 	      results_file3 << std::endl;
// 	    }
// 
// 	  }
// 	  }
// 	  else { results_file3 << std::endl; }
// 	}
// 	// Yte -- Testing of the output which is of 30% (13:18 columns)
// 	for (int i=train_rows; i<=row ; i++)
// 	{
// 	  if(i !=row){
// 	  for (int j=12; j<=18 ; j++)
// 	  {
// 	    
// 	    if (j !=18)
// 	    {
// 	    Ytest = data[i][j];  
// 	    results_file4 << Ytest << ",";
// 	    }
// 	    else
// 	    {
// 	      results_file4 << std::endl;
// 	    }
// 
// 	  }
// 	  }
// 	  else { results_file4 << std::endl; }
// 	}
// 	
	  for (int k=0; k<=train_rows ; k++)
	{
	  //results_file2 << y(k);
	  if (k !=train_rows)
	  {
	    for (int l=0;l<=1;l++)
	    {
	      if(l!=1)
	      {
	    //std::cout << k;
	    Ytrain = data[k][l];
	    results_file3 << Ytrain << std::endl;
	      }
	    }
	  }
	}
	  for (int k=train_rows; k<=row ; k++)
	{
	  //results_file2 << y(k);
	  if (k !=row)
	  {
	    for (int l=0;l<=1;l++)
	    {
	      if(l!=1)
	      {
	    //std::cout << k;
	    Ytest = data[k][l];
	    results_file4 << Ytest << std::endl;
	      }
	    }
	  }
	}
	
	
	return EXIT_SUCCESS;
	results_file1.close();
	results_file2.close();
	results_file3.close();
	results_file4.close();
    }
    catch (gException& e)
    {
        std::cout << e.getMessage() << std::endl;
        return EXIT_FAILURE;
    }
}
