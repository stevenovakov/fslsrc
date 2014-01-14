/*  Copyright (C) 2004
 *    Afshin Haidari
 *    Steve Novakov
 *    Jeff Taylor
 */
 
/* oclptx.cc
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

#define __CL_ENABLE_EXCEPTIONS 
// adds exception support from CL libraries
// define before CL headers inclusion

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "oclptx.h"

//*********************************************************************
//
// Assorted Function Declerations
//
//*********************************************************************




//*********************************************************************
//
// Main
//
//*********************************************************************

int main(int argc, char *argv[] )
{
  
  OclPtxHandler * ptx_handler;
  ptx_handler = new OclPtxHandler();
  
  
  delete ptx_handler;
  
  std::cout<<"\n\nExiting...\n\n";
  return 0;
}

//*********************************************************************
//
// Assorted Functions
//
//*********************************************************************