Package includes both matlab and c++ codes for Non-parametric modeling using GURLS. However first you need to install GURLS package with necessary dependencies from https://github.com/LCSL/GURLS. More detail information can be found on GURLS manual.

Detail explaination of Non-parametric modeling and theory behind this can be found from my thesis which is included in the package. 


How to install package:  ( On linux terminal)

Step 1 : Install all necessary dependencies including Gurls package. Please find the instruction on the manual of GURLS.

Step 2 : root to Non-parametric modeling package version 0.1
	######	cd Non_Parametric_Modelling/Version0.1 ######
Step 3 : make directory build
	#### mkdir build### 
	#### cd build ####
Step 4 : Now make it
	#### ccmake ../ ####
	#### make ####
Step 5 : run the code you want to test with dataset you want. 
	####./Non_Parametric_Modelling_Batch_Linear_Regression ../Data_Sets/ICUB_DATASET/Xtr_2psmall.txt ../Data_Sets/ICUB_DATASET/Xte_2psmall.txt ../Data_Sets/ICUB_DATASET/ytr_2psmall.txt ../Data_Sets/ICUB_DATASET/yte_2psmall.txt ####

Any problems with code or questions can be asked through email prabhukumar.chalikonda@gmail.com
