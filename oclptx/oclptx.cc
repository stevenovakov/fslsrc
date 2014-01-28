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

#include "interptest.cc"

//*********************************************************************
//
// Assorted Function Declerations
//
//*********************************************************************

// Ask Jeff about maybe a good library to deal with CLI argument parsing
// writing the custom function to parse argc/argv sucks so bad
//int argMapper(int argc, char*argv[]);


//*********************************************************************
//
// Main
//
//*********************************************************************

int main(int argc, char *argv[] )
{
  
  OclPtxHandler * ptx_handler;
  
  ptx_handler = new OclPtxHandler("interptest");
  
  //*******************************************************************
  // 
  //  TEST ROUTINE
  // 
  //*******************************************************************
  
  int XN = 20;
  int YN = 20;
  int ZN = 20;
  
  unsigned int nseeds = 100;
  unsigned int nsteps = 100;
  
  float3 mins;
  mins.x = 8.0;
  mins.y = 8.0;
  mins.z = 0.0;
  float3 maxs;
  maxs.x = 12.0;
  maxs.y = 12.0;
  maxs.z = 1.0;
  
  float dr = 0.1;  
  
  IntVolume voxel_space = CreateVoxelSpace( XN, YN, ZN);
  FloatVolume flow_space = CreateFlowSpace( voxel_space, dr);
  std::vector<unsigned int> seed_elem = RandSeedElem(  
    nseeds,
    mins,
    maxs,
    voxel_space
  );                  
  
  std::vector<float3> seed_space = RandSeedPoints(  nseeds, 
                                                    voxel_space,
                                                    seed_elem
                                                  );

  VolumeToFile(voxel_space, flow_space);
  
  PathsToFile(  ptx_handler->InterpolationTestRoutine(  voxel_space,
                                                        flow_space,
                                                        seed_space,
                                                        seed_elem,
                                                        nseeds,
                                                        nsteps,
                                                        dr
                                                      ),
                nseeds,
                nsteps
  );


  //*******************************************************************
  // 
  //  END TEST ROUTINE
  // 
  //*******************************************************************
  
  delete ptx_handler;
  
  std::cout<<"\n\nExiting...\n\n";
  return 0;
}

//*********************************************************************
//
// Assorted Functions
//
//*********************************************************************