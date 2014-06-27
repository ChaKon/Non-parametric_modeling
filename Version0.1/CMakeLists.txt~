# Copyright: (C) 2014, Master Thesis
# Authors: Chalikonda Prabhu Kumar
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

cmake_minimum_required(VERSION 2.8.12.2)

#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
#include_directories(/usr/local/include/ /usr/local/)

PROJECT(Non_Parametric_Modelling)

set(Non_Parametric_Modelling_VERSION_MAJOR "0")
set(Non_Parametric_Modelling_VERSION_MINOR "1")
set(Non_Parametric_Modelling_VERSION_PATCH "0")
set(Non_Parametric_Modelling_VERSION "${Non_Parametric_Modelling_VERSION_MAJOR}.${Non_Parametric_Modelling_VERSION_MINOR}.${Non_Parametric_Modelling_VERSION_PATCH}")

FIND_PACKAGE(YARP)
FIND_PACKAGE(ICUB)
####
#FIND_PACKAGE(kdl_codyco)
#FIND_PACKAGE(orocos_kdl)
#FIND_PACKAGE(iDynTree)
####
#include_directories("${kdl_INCLUDE_DIRS}")
#FIND_PACKAGE(IDynTree)
FIND_PACKAGE(Gurls)


# add include directories
INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS} ${ICUB_INCLUDE_DIRS} ${Gurls_INCLUDE_DIRS})
#${kdl_codyco_INCLUDE_DIRS} ${orocos_kdl_INCLUDE_DIRS} ${Gurls_INCLUDE_DIRS})
#${kdl_INCLUDE_DIRS})
# add required linker flags
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ICUB_LINK_FLAGS}")      
#  1 Verification For Hello Icub tutorial
ADD_EXECUTABLE(helloworld helloworld.cpp)
# we now add the YARP and iCub libraries to our project.
TARGET_LINK_LIBRARIES(helloworld ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})

# 2 Verification For Gurls Tutorial
ADD_EXECUTABLE(GURLSloocvprimal GURLSloocvprimal.cpp)
TARGET_LINK_LIBRARIES(GURLSloocvprimal ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})

# 3 Data Set Creation
ADD_EXECUTABLE(data_set_creation data_set_creation.cpp)
TARGET_LINK_LIBRARIES(data_set_creation ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})

# 4 Data Set Creation2
ADD_EXECUTABLE(data_set_creation2 data_set_creation2.cpp)
TARGET_LINK_LIBRARIES(data_set_creation2 ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})

# 5 Non Parametric Modelling Batch
#ADD_EXECUTABLE(Non_Parametric_Modelling_Batch Non_Parametric_Modelling_Batch.cpp)
#TARGET_LINK_LIBRARIES(Non_Parametric_Modelling_Batch ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})

# 6 Non Parametric Modelling Incremental
ADD_EXECUTABLE(Non_Parametric_Modelling_Incremental Non_Parametric_Modelling_Incremental.cpp)
TARGET_LINK_LIBRARIES(Non_Parametric_Modelling_Incremental ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})

# 7 Non Parametric Modelling Version0.1
ADD_EXECUTABLE(Non_Parametricmodelling_Version0.1 Non_Parametricmodelling_Version0.1.cpp)
TARGET_LINK_LIBRARIES(Non_Parametricmodelling_Version0.1 ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})
# 8 Some tests
ADD_EXECUTABLE(test test.cpp)
TARGET_LINK_LIBRARIES(test ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})
# 9 Random features test
ADD_EXECUTABLE(RandomFeatures RandomFeatures.cpp)
TARGET_LINK_LIBRARIES(RandomFeatures ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})
# 10 Non-paramteric modeling complete code with lot of choices
ADD_EXECUTABLE(Non_Parametric_Modelling_Batch_Linear_Regression Non_Parametric_Modelling_Batch_Linear_Regression.cpp)
TARGET_LINK_LIBRARIES(Non_Parametric_Modelling_Batch_Linear_Regression ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})
# 11 batch with random features
ADD_EXECUTABLE(Batchwith_randomfeatures Batchwith_randomfeatures.cpp)
TARGET_LINK_LIBRARIES(Batchwith_randomfeatures ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})
# 12 test for lambda for parametric part
ADD_EXECUTABLE(test_for_lambda test_for_lambda.cpp)
TARGET_LINK_LIBRARIES(test_for_lambda ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})
# 13 recursiveRLS (incremental)
ADD_EXECUTABLE(recursiveRLS recursiveRLS.cpp)
TARGET_LINK_LIBRARIES(recursiveRLS ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})
# 14 Non parametric modeling batch with random features
ADD_EXECUTABLE(Non_Parametric_Modelling_Batch_RandomFeatures Non_Parametric_Modelling_Batch_RandomFeatures.cpp)
TARGET_LINK_LIBRARIES(Non_Parametric_Modelling_Batch_RandomFeatures ${YARP_LIBRARIES} ${ICUB_LIBRARIES} ${Gurls_LIBRARIES})






