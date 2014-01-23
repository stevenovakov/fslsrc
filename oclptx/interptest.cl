/*  Copyright (C) 2004
 *    Afshin Haidari
 *    Steve Novakov
 *    Jeff Taylor
 */
 
/* interptest.cl
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
 
/*
 * OCL KERNEL COMPILATION - APPEND ORDER
 * 
 * Append parsed files in this order in one container
 * before compiling kernel for runtime:
 * 
 *      prngmethods.cl
 *      interptest.cl
 *
 */
 
 
 
__kernel void InterpolateKernel(
                                  __global int3* v0,
                                  __global int3* v1,
                                  __global int3* v2,
                                  __global int3* v3,
                                  __global int3* v4,
                                  __global int3* v5,
                                  __global int3* v6,
                                  __global int3* v7,
                                  __global float3* f0, 
                                  __global float3* f1,
                                  __global float3* f2,
                                  __global float3* f3,
                                  __global float3* f4,
                                  __global float3* f5,
                                  __global float3* f6,
                                  __global float3* f7,
                                  unsigned int nx, 
                                  unsigned int ny, 
                                  unsigned int nz,
                                  unsigned int n_steps                                 
                                )
{
  unsigned int glIDx = get_global_id(0);
  unsigned int glIDy = get_global_id(1);
  unsigned int glIDz = get_global_id(2);
  
  unsigned int globalX = get_global_size(0);
  unsigned int globalY = get_global_size(1);
  unsigned int globalZ = get_global_size(2);

}