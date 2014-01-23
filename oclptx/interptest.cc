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
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <time.h>
#include <cstdlib>

#include "customtypes.h" 
 
//
// Declarations
// 
IntVolume CreateVoxelSpace( int NX, int NY, int NZ );
FloatVolume CreateFlowSpace( FloatVolume voxel_space );                     
float3 FlowFunction( int3 coords, int NX, int NY, int NZ );
std::vector<float3> RandSeedSpace( int n, float3 mins, float3 maxs );
void VolumeToFile( IntVolume ivol, FloatVolume fvol );
 
 
//
// Simple integer voxel space, from 0,0,0 to N,N,N
// 
IntVolume CreateVoxelSpace( int NX, int NY, int NZ )
{
  
  IntVolume voxel_space;
  
  voxel_space.nx = NX;
  voxel_space.ny = NY;
  voxel_space.nz = NZ;  
  
  for(int i = 0; i < NX; i ++)
  {
        for(int j = 0; j < NY; j++)
        {
            for(int k = 0; k < NZ; k++)
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

FloatVolume CreateFlowSpace(  IntVolume voxel_space )
{
  
  FloatVolume flow_space;
  flow_space.nx = voxel_space.nx;
  flow_space.ny = voxel_space.ny;
  flow_space.nz = voxel_space.nz;
  
  std::vector<int3>::iterator vit;
  
  for(vit = voxel_space.v0.begin(); vit != voxel_space.v0.end(); ++vit)
  {
      flow_space.v0.push_back( FlowFunction( *vit,
                                              flow_space.nx,
                                              flow_space.ny, 
                                              flow_space.nz
                                            )
                              );
  }
  for(vit = voxel_space.v1.begin(); vit != voxel_space.v1.end(); ++vit)
  {
      flow_space.v1.push_back( FlowFunction( *vit,
                                              flow_space.nx,
                                              flow_space.ny, 
                                              flow_space.nz
                                            )
                              );
  }
  for(vit = voxel_space.v2.begin(); vit != voxel_space.v2.end(); ++vit)
  {
      flow_space.v2.push_back( FlowFunction( *vit,
                                              flow_space.nx,
                                              flow_space.ny, 
                                              flow_space.nz
                                            )
                              );
  }
  for(vit = voxel_space.v3.begin(); vit != voxel_space.v3.end(); ++vit)
  {
      flow_space.v3.push_back( FlowFunction( *vit,
                                              flow_space.nx,
                                              flow_space.ny, 
                                              flow_space.nz
                                            )
                              );
  }
  for(vit = voxel_space.v4.begin(); vit != voxel_space.v4.end(); ++vit)
  {
      flow_space.v4.push_back( FlowFunction( *vit,
                                              flow_space.nx,
                                              flow_space.ny, 
                                              flow_space.nz
                                            )
                              );
  }
  for(vit = voxel_space.v5.begin(); vit != voxel_space.v5.end(); ++vit)
  {
      flow_space.v5.push_back( FlowFunction( *vit,
                                              flow_space.nx,
                                              flow_space.ny, 
                                              flow_space.nz
                                            )
                              );
  }
  for(vit = voxel_space.v6.begin(); vit != voxel_space.v6.end(); ++vit)
  {
     flow_space.v6.push_back( FlowFunction( *vit,
                                            flow_space.nx,
                                            flow_space.ny, 
                                            flow_space.nz
                                          )
                            );
  }
  for(vit = voxel_space.v7.begin(); vit != voxel_space.v7.end(); ++vit)
  {
      flow_space.v7.push_back( FlowFunction( *vit,
                                              flow_space.nx,
                                              flow_space.ny, 
                                              flow_space.nz
                                            )
                              );
  }
  
  return flow_space;  
}

float3 FlowFunction( int3 coords, int NX, int NY, int NZ )
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
  
  for(int i = 0; i < n; i++)
  {
    temp_point.x = rand()%1000*(maxs.x - mins.x) + mins.x;
    temp_point.y = rand()%1000*(maxs.y - mins.y) + mins.y;
    temp_point.z = rand()%1000*(maxs.z - mins.z) + mins.z;

    seed_set.push_back(temp_point);
  }
  
  return seed_set;
}


void VolumeToFile( IntVolume vvol, FloatVolume fvol )
{
  
  int vsize = vvol.v0.size();
  int fsize = fvol.v0.size();
  
  std::ostringstream convert (std::ostringstream::ate);
  
  std::string volume_filename;
  std::string flow_filename;
  	
	
	time_t t = time(0);
	struct tm * now = localtime(&t);
	
	convert << "Test Data/" << now->tm_hour << ":" << now->tm_min <<
	":" << now->tm_sec << "_" << now->tm_yday <<
		"-" << ((int) now->tm_year) + 1900;
		
	volume_filename = convert.str() + "_VOL.dat";
  flow_filename = convert.str() + "_FLOW.dat";
  
  std::fstream volume_file;
	volume_file.open(volume_filename.c_str(), std::ios::app|std::ios::out);
  
  for(int i = 0; i < vsize; i ++)
  {
			
		volume_file<< vvol.v0.at(i).x <<"," << vvol.v0.at(i).y << "," <<
      vvol.v0.at(i).z << ",";
		volume_file<< vvol.v1.at(i).x <<"," << vvol.v1.at(i).y << "," <<
      vvol.v1.at(i).z << ",";
    volume_file<< vvol.v2.at(i).x <<"," << vvol.v2.at(i).y << "," <<
      vvol.v2.at(i).z << ",";
    volume_file<< vvol.v3.at(i).x <<"," << vvol.v3.at(i).y << "," <<
      vvol.v3.at(i).z << ",";
    volume_file<< vvol.v4.at(i).x <<"," << vvol.v4.at(i).y << "," <<
      vvol.v4.at(i).z << ",";
    volume_file<< vvol.v5.at(i).x <<"," << vvol.v5.at(i).y << "," <<
      vvol.v5.at(i).z << ",";  
		volume_file<< vvol.v6.at(i).x <<"," << vvol.v6.at(i).y << "," <<
      vvol.v6.at(i).z << ",";
    volume_file<< vvol.v7.at(i).x <<"," << vvol.v7.at(i).y << "," <<
      vvol.v7.at(i).z;
        
		if( i == vsize - 1)
			break;
		else
			volume_file <<"\n";
	}
  
  volume_file.close();
  
  
  std::fstream flow_file;
	flow_file.open(flow_filename.c_str(), std::ios::app|std::ios::out);
  
  for(int i = 0; i < vsize; i ++)
  {
			
		flow_file<< fvol.v0.at(i).x <<"," << fvol.v0.at(i).y << "," <<
      fvol.v0.at(i).z << ",";
		flow_file<< fvol.v1.at(i).x <<"," << fvol.v1.at(i).y << "," <<
      fvol.v1.at(i).z << ",";
    flow_file<< fvol.v2.at(i).x <<"," << fvol.v2.at(i).y << "," <<
      fvol.v2.at(i).z << ",";
    flow_file<< fvol.v3.at(i).x <<"," << fvol.v3.at(i).y << "," <<
      fvol.v3.at(i).z << ",";
    flow_file<< fvol.v4.at(i).x <<"," << fvol.v4.at(i).y << "," <<
      fvol.v4.at(i).z << ",";
    flow_file<< fvol.v5.at(i).x <<"," << fvol.v5.at(i).y << "," <<
      fvol.v5.at(i).z << ",";  
		flow_file<< fvol.v6.at(i).x <<"," << fvol.v6.at(i).y << "," <<
      fvol.v6.at(i).z << ",";
    flow_file<< fvol.v7.at(i).x <<"," << fvol.v7.at(i).y << "," <<
      fvol.v7.at(i).z;
        
		if( i == vsize - 1)
			break;
		else
			flow_file <<"\n";
	}
  
  flow_file.close();  
  
}