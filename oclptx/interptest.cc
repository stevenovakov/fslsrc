/*  Copyright (C) 2004
 *    Afshin Haidari
 *    Steve Novakov
 *    Jeff Taylor
 */
 
/* interptest.h
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
#include <vector>
#include <cmath>
#include <ctime>
#include <time.h>
#include <cstdlib>

#include "customtypes.h" 
 
//
// Declarations
// 
3DIntVolume CreateVoxelSpace(   int xrange = XN,
                                int yrange = YN,
                                int zrange = ZN
                            );
3DFloatVolume CreateFlowSpace(  3DFloatVolume voxel_space );                     
float3 FlowFunction( float3 coords, int NX, int NY, int NZ )
std::vector<float3> RandSeedSpace( float3 mins, float3 maxs );

 
 
//
// Simple integer voxel space, from 0,0,0 to N,N,N
// 
3DIntVolume CreateVoxelSpace(   int xrange = XN,
                                int yrange = YN,
                                int zrange = ZN
                            )
{
  
  3DIntVolume voxel_space;
  
  voxel_space.nx = XN;
  voxel_space.ny = YN;
  voxel_space.nz = ZN;  
  
  for(int i = 0; i < XN; i ++)
  {
        for(int j = 0; j < YN; j++)
        {
            for(int k = 0; k < ZN; k++)
            {
              
              voxel_space.v0.push_back(int3(i,j,k));
              voxel_space.v1.push_back(int3(i+1,j,k));
              voxel_space.v2.push_back(int3(i+1,j+1,k));
              voxel_space.v3.push_back(int3(i, j+1, k));
              voxel_space.v4.push_back(int3(i, j, k+1));
              voxel_space.v5.push_back(int3(i+1, j, k+1));
              voxel_space.v6.push_back(int3(i+1, j+1, k));
              voxel_space.v7.push_back(int3(i, j+1, k));
              
            }
        }
  }
  
  return voxel_space;  
}

3DFloatVolume CreateFlowSpace(  3DFloatVolume voxel_space )
{
  
  3DFloatVolume float_space;
  float_space.nx = voxel_space.nx;
  float_space.ny = voxel_space.ny;
  float_space.nz = voxel_space.nz;
  
  std::vector<float3>::iterator vit;
  
  for(vit = voxel_space.v0.begin(); vit != voxel_space.v0.end(); ++vit)
  {
      float_space.v0.push_back( FlowFunction(*vit),
                                float_space.nx,
                                float_space.ny, 
                                float_space.nz
                              );
  }
  for(vit = voxel_space.v1.begin(); vit != voxel_space.v1.end(); ++vit)
  {
      float_space.v1.push_back( FlowFunction(*vit),
                                float_space.nx,
                                float_space.ny, 
                                float_space.nz
                              );  }
  for(vit = voxel_space.v2.begin(); vit != voxel_space.v2.end(); ++vit)
  {
      float_space.v2.push_back( FlowFunction(*vit),
                                float_space.nx,
                                float_space.ny, 
                                float_space.nz
                              );  }
  for(vit = voxel_space.v3.begin(); vit != voxel_space.v3.end(); ++vit)
  {
      float_space.v3.push_back( FlowFunction(*vit),
                                float_space.nx,
                                float_space.ny, 
                                float_space.nz
                              );  }
  for(vit = voxel_space.v4.begin(); vit != voxel_space.v4.end(); ++vit)
  {
      float_space.v4.push_back( FlowFunction(*vit),
                                float_space.nx,
                                float_space.ny, 
                                float_space.nz
                              );  }
  for(vit = voxel_space.v5.begin(); vit != voxel_space.v5.end(); ++vit)
  {
      float_space.v5.push_back( FlowFunction(*vit),
                                float_space.nx,
                                float_space.ny, 
                                float_space.nz
                              );  }
  for(vit = voxel_space.v6.begin(); vit != voxel_space.v6.end(); ++vit)
  {
      float_space.v6.push_back( FlowFunction(*vit),
                                float_space.nx,
                                float_space.ny, 
                                float_space.nz
                              );  }
  for(vit = voxel_space.v7.begin(); vit != voxel_space.v7.end(); ++vit)
  {
      float_space.v7.push_back( FlowFunction(*vit),
                                float_space.nx,
                                float_space.ny, 
                                float_space.nz
                              );  }
  return voxel_space;  
}

float3 FlowFunction( float3 coords, int NX, int NY, int NZ )
{
  //
  // Right now its just like a "tree" from center of space to top
  //    
  
  float r = 1.0;
  float theta = std::atan(1.0) * (float) coords.z/ (float) NZ;
  float phi = 
    std::atan((float) (2*coords.y - NY)/ (float) (2*coords.x - NX));
  
  return float3( r*std::cos(phi)*std::sin(theta),
                  r*std::sin(phi)*std::sin(theta),
                  r*std::cos(theta)
                );  
}


std::vector<float3> RandSeedSpace( int n, float3 mins, float3 maxs )
{
  std::vector<float3> seed_set;
  float3 temp_point;
  
  srand( time(NULL) );
  
  for(int i = 0; i < n, i++)
  {
    temp_point.x = rand()%1000*(maxs.x - mins.x) + mins.x;
    temp_point.y = rand()%1000*(maxs.y - mins.y) + mins.y;
    temp_point.z = rand()%1000*(maxs.z - mins.z) + mins.z;

    seed_set.push_back(temp_pont);
  }
  
  return seed_set;
}