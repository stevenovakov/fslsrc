/*  Copyright (C) 2004
 *    Afshin Haidari
 *    Steve Novakov
 *    Jeff Taylor
 */
 
/* customtypes.h
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
#include <thread>
#include <mutex>


#ifndef OCLPTX_CUSTOMTYPES_H_
#define OCLPTX_CUSTOMTYPES_H_


struct float8
{
  float s0, s1, s2, s3, s4, s5, s6, s7;
};


struct float4
{
  float s0, s1, s2, s3;
};


struct float3
{
  float x, y, z;
};

struct float2
{
  float x, y;
};


struct int3
{
  int x, y, z;
};



struct IntVolume
{
  std::vector<int3> vol;
  int nx, ny, nz;  
  // Access x, y, z:
  //                var_name.vol[z*(ny*nx) + y*8*nx + 8*x + v]
};

struct FloatVolume
{
  std::vector<float3> vol;
  int nx, ny, nz;
  // Access x, y, z:
  //                var_name.vol[z*(ny*nx) + y*8*nx + 8*x + v]
};

//struct MutexWrapper {
    //std::mutex m;
    //MutexWrapper() {}
    //MutexWrapper(MutexWrapper const&) {}
    //MutexWrapper& operator=(MutexWrapper const&) { return *this; }
//};

#endif