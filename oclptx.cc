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

void SimpleInterpolationTest();



//*********************************************************************
//
// Main
//
//*********************************************************************

int main(int argc, char *argv[] )
{
  
  //Test Routine
  SimpleInterpolationTest();

  
  std::cout<<"\n\nExiting...\n\n";
  return 0;
}

//*********************************************************************
//
// Assorted Functions
//
//*********************************************************************


void SimpleInterpolationTest()
{
  
  OclPtxHandler * ptx_handler;
  
  ptx_handler = new OclPtxHandler("interptest");
  
  //*******************************************************************
  // 
  //  TEST ROUTINE
  // 
  //*******************************************************************
  
  unsigned int XN = 20;
  unsigned int YN = 20;
  unsigned int ZN = 20;
  
  unsigned int nseeds = 200;
  unsigned int nsteps = 200;
  
  std::cout<<"\n\nInterpolation Test\n"<<"\n";
  std::cout<<"\tSeeds :" << nseeds << " Steps:" << nsteps <<"\n";
  std::cout<<"\tXN: " << XN << " YN: " << YN << " ZN: " << ZN <<"\n";
  std::cout<<"\n\n";
  
  float3 mins;
  mins.x = 8.0;
  mins.y = 8.0;
  mins.z = 0.0;
  float3 maxs;
  maxs.x = 12.0;
  maxs.y = 12.0;
  maxs.z = 1.0;
  
  float4 min_bounds;
  min_bounds.x = 0.0;
  min_bounds.y = 0.0;
  min_bounds.z = 0.0;
  min_bounds.t = 0.0;
  
  float4 max_bounds;
  max_bounds.x = 20.0;
  max_bounds.y = 20.0;
  max_bounds.z = 20.0;
  max_bounds.t = 0.0;
  
  float dr = 0.1;  
  
  FloatVolume voxel_space = CreateVoxelSpace( XN, YN, ZN,
    min_bounds, max_bounds);
    
  float3 setpts;
  setpts.z = max_bounds.z - min_bounds.z;
  setpts.y = (max_bounds.y + min_bounds.y)/2.0;  
  setpts.x = (max_bounds.x + min_bounds.x)/2.0;  
    
  FloatVolume flow_space = CreateFlowSpace( voxel_space, dr, setpts);
  std::vector<unsigned int> seed_elem = RandSeedElem(  
    nseeds,
    mins,
    maxs,
    voxel_space
  );                  
  
  std::vector<float4> seed_space = RandSeedPoints(  nseeds, 
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
                                                        dr,
                                                        min_bounds,
                                                        max_bounds
                                                      ),
                nseeds,
                nsteps
  );

  
  
  delete ptx_handler;
  
}