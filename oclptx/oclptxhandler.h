/*  Copyright (C) 2004
 *    Afshin Haidari
 *    Steve Novakov
 *    Jeff Taylor
 */
 
/* oclptxhandler.h
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

#ifndef  OCLPTX_OCLPTXHANDLER_H_
#define  OCLPTX_OCLPTXHANDLER_H_

#include <iostream>
#include <vector>

#define __CL_ENABLE_EXCEPTIONS
// adds exception support from CL libraries
// define before CL headers inclusion

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
 
class OclPtxHandler{
  
  public:
    
    OclPtxHandler(){};
    
    OclPtxHandler( std::string ocl_routine);
  
    ~OclPtxHandler();
    
    //
    // Thread Management
    //
    
    void PTStart();
    
    void ThreadController();
    
    //
    // OpenCL API Interface/Helper Functions
    //
    
    void OclInit();
    
    void NewCLCommandQueues();
    
    cl::Program CreateProgram();
    
    void PrepOclContainers();
    
    
    
    
  private:
  
    //
    // Containers
    //
  
    //
    // OpenCL Objects
    //
    cl::Context ocl_context;
    
    std::vector<cl::Platform> ocl_platforms;		
		
		std::vector<cl::Device> ocl_devices;
		
		std::vector<cl::CommandQueue> ocl_device_queues;
		
		std::vector<cl::Kernel> ocl_kernel_set;
		//Every compiled kernel is stored here.
		
		bool ocl_profiling;
		
		std::string ocl_routine_name;
		//
		// Various
		//
		
		bool interpolation_complete;

};
 
#endif

//EOF