/*  Copyright (C) 2004
 *    Afshin Haidari
 *    Steve Novakov
 *    Jeff Taylor
 */
 
/* oclptxhandler.cc
 *
 *
 * Part of 
 *    oclptx
 * OpenCL-based, GPU accelerated probtrackx algorithm module, to be used
 * with FSL - FMRIB's Software Library
 *
 * This file is part of oclptx.
 * 
 * oclptx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * oclptx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with oclptx.  If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


#define __CL_ENABLE_EXCEPTIONS 
// adds exception support from CL libraries
// define before CL headers inclusion

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "oclptxhandler.h"

//
// Assorted Functions Declerations
//

std::string oclErrorStrings(cl_int error);

//*********************************************************************
//
// OclPtxHandler Constructors/Destructors
//
//*********************************************************************

//
// Constructor(s)
//
OclPtxHandler::OclPtxHandler(
  std::string ocl_routine
)
{  
  this->ocl_routine_name = ocl_routine;
  
  this->ocl_profiling = true;
  this->interpolation_complete = true;
}

//
// Destructor
//
OclPtxHandler::~OclPtxHandler()
{
  std::cout<<"~OclPtxHandler\n";
	// no pointer data elements at the moment...
}


//*********************************************************************
//
// OclPtxHandler Thread Management
//
//*********************************************************************

//
//
//
void OclPtxHandler::PTStart()
{
  this->interpolation_complete = false;
  
  
}


//
//
//
void OclPtxHandler::ThreadController()
{
  while(!(this->interpolation_complete))
  {
    
    //
    // One while/for loop for thread CREATION/QUEUEING/EXECUTION
    //
    
    //
    // One while/for loop for thread collection/joining
    //
    
    //if(termination_condition)
    // this->interpolation_complete = true;
    
  }

}


//*********************************************************************
//
// OclPtxHandler OpenCL Interface
//
//*********************************************************************

//
//
//
void OclPtxHandler::OclInit()
{
  
	cl::Platform::get(&(this->ocl_platforms));
	
	cl_context_properties conProp[3] =
  {
		CL_CONTEXT_PLATFORM,
		(cl_context_properties) (this->ocl_platforms[0]) (),
		0
	};
	
	this->ocl_context = cl::Context(CL_DEVICE_TYPE_GPU, conProp);
  // GPU DEVICES ONLY, FOR CPU, (don't use CPU unless informed, not
  // quite the same physical interface):
	//this->oclContext = cl::Context(CL_DEVICE_TYPE_CPU, conProp);
  
	this->ocl_devices = this->ocl_context.getInfo<CL_CONTEXT_DEVICES>();
							
  this->NewCLCommandQueues();

}

//
//
//
void OclPtxHandler::NewCLCommandQueues()
{
  
  this->ocl_device_queues.clear();
	
	for( int k = 0; k < this->ocl_devices.size(); k++ )
  {

		std::cout<<"Create CommQueue, Kernel, Device: "<<k<<"\n";
		if(this->ocl_profiling)
    {
			this->ocl_device_queues.push_back(  cl::CommandQueue(
                                            this->ocl_context,
                                            this->ocl_devices[k],
                                            CL_QUEUE_PROFILING_ENABLE
                                          )
                                        );
		}
		else
    {
			this->ocl_device_queues.push_back(  cl::CommandQueue(
                                            this->ocl_context,
                                            this->ocl_devices[k]
                                          )
                                        );	
		}
  }
					
  
}

//
//
//
cl::Program OclPtxHandler::CreateProgram()
{
  
  this->ocl_kernel_set.clear();  
  
  // Read Source
	
	std::string line_str, kernel_source;
	
	std::ifstream source_file;
	
  if( this->ocl_routine_name == "oclptx" )
  {
    
    line_str = "prngmethods.cl";
    source_file.open(line_str.c_str());
    
    std::getline(source_file, line_str);
    
    while(source_file){
      
      kernel_source += line_str + "\n";
    
      std::getline(source_file, line_str);
    
    }
    
    source_file.close();
    
    line_str = "interpolate.cl";
    source_file.open(line_str.c_str());
    
    std::getline(source_file, line_str);
    
    while(source_file){
      
      kernel_source += line_str + "\n";
    
      std::getline(source_file, line_str);
    
    }
    
    source_file.close();
  }
  else if( this->ocl_routine_name == "prngtest" )
  {
    
    line_str = "prngmethods.cl";
    source_file.open(line_str.c_str());
    
    std::getline(source_file, line_str);
    
    while(source_file){
      
      kernel_source += line_str + "\n";
    
      std::getline(source_file, line_str);
    
    }
    
    source_file.close();
    
    line_str = "prngtest.cl";
    source_file.open(line_str.c_str());
    
    std::getline(source_file, line_str);
    
    while(source_file){
      
      kernel_source += line_str + "\n";
    
      std::getline(source_file, line_str);
    
    }
    
    source_file.close();    
    
  }
  //TODO
  // no else  because we will check for routine_name at init
	//
  
  //
  // Build Program files here
  //

	cl::Program::Sources prog_source(  
              1,
              std::make_pair(kernel_source.c_str(), kernel_source.length())
              );
              
	source_file.close();	
	
	cl::Program array_program(this->ocl_context, prog_source);
	
	try{
		array_program.build(this->ocl_devices);
	}
	catch(cl::Error err){
		
    // TODO 
    //  dump all error logging to logfile
    //
    
		if( oclErrorStrings(err.err()) != "CL_SUCCESS")
    {
			std::cout<<"ERROR: " << err.what() <<
        " ( " << oclErrorStrings(err.err()) << ")\n";
			std::cin.get();
		
			for(std::vector<cl::Device>::iterator dit = this->ocl_devices.begin();
        dit != this->ocl_devices.end(); dit++)
      {
			
				std::cout<<"BUILD OPTIONS: \n" << 
          array_program.getBuildInfo<CL_PROGRAM_BUILD_OPTIONS>(*dit) <<
           "\n";
				std::cout<<"BUILD LOG: \n" << 
          array_program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(*dit) <<"\n";
			}
		}
	}
  
  //
  // Compile Kernels from Program
  //
  if( this->ocl_routine_name == "oclptx" )
  {
    this->ocl_kernel_set.push_back(cl::Kernel(  array_program, 
                                                "InterpolateKernel",
                                                NULL
                                              ));
  }
  else if( this->ocl_routine_name == "oclptx" )
  {
    this->ocl_kernel_set.push_back(cl::Kernel(  array_program, 
                                                "PrngTestKernel",
                                                NULL
                                              ));
  }
  
}

//*********************************************************************
//
// OclPtxHandler Tractography
//
//*********************************************************************





//*********************************************************************
//
// Assorted Functions
//
//*********************************************************************

//
// Matches OCL error codes to their meaning.
//
std::string oclErrorStrings(cl_int error)
{
	
  //
  // redeclaration on each call obviously not efficient, but had some 
  // problems putting this as a global variable, revisit later
  //
	std::string error_string[] = 
  {
        "CL_SUCCESS",
        "CL_DEVICE_NOT_FOUND",
        "CL_DEVICE_NOT_AVAILABLE",
        "CL_COMPILER_NOT_AVAILABLE",
        "CL_MEM_OBJECT_ALLOCATION_FAILURE",
        "CL_OUT_OF_RESOURCES",
        "CL_OUT_OF_HOST_MEMORY",
        "CL_PROFILING_INFO_NOT_AVAILABLE",
        "CL_MEM_COPY_OVERLAP",
        "CL_IMAGE_FORMAT_MISMATCH",
        "CL_IMAGE_FORMAT_NOT_SUPPORTED",
        "CL_BUILD_PROGRAM_FAILURE",
        "CL_MAP_FAILURE",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "CL_INVALID_VALUE",
        "CL_INVALID_DEVICE_TYPE",
        "CL_INVALID_PLATFORM",
        "CL_INVALID_DEVICE",
        "CL_INVALID_CONTEXT",
        "CL_INVALID_QUEUE_PROPERTIES",
        "CL_INVALID_COMMAND_QUEUE",
        "CL_INVALID_HOST_PTR",
        "CL_INVALID_MEM_OBJECT",
        "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR",
        "CL_INVALID_IMAGE_SIZE",
        "CL_INVALID_SAMPLER",
        "CL_INVALID_BINARY",
        "CL_INVALID_BUILD_OPTIONS",
        "CL_INVALID_PROGRAM",
        "CL_INVALID_PROGRAM_EXECUTABLE",
        "CL_INVALID_KERNEL_NAME",
        "CL_INVALID_KERNEL_DEFINITION",
        "CL_INVALID_KERNEL",
        "CL_INVALID_ARG_INDEX",
        "CL_INVALID_ARG_VALUE",
        "CL_INVALID_ARG_SIZE",
        "CL_INVALID_KERNEL_ARGS",
        "CL_INVALID_WORK_DIMENSION",
        "CL_INVALID_WORK_GROUP_SIZE",
        "CL_INVALID_WORK_ITEM_SIZE",
        "CL_INVALID_GLOBAL_OFFSET",
        "CL_INVALID_EVENT_WAIT_LIST",
        "CL_INVALID_EVENT",
        "CL_INVALID_OPERATION",
        "CL_INVALID_GL_OBJECT",
        "CL_INVALID_BUFFER_SIZE",
        "CL_INVALID_MIP_LEVEL",
        "CL_INVALID_GLOBAL_WORK_SIZE",
    };
    
    return error_string[ -1*error];
}


//EOF