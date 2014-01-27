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

// maybe 'better' to declare inline function instead of macro
#define CIRCTOCART(invec){\  
  float3 xyz;\
  xyz.s1 = sincos(invec.s1, &xyz.s0 ); \
  xyz.s2 = 0;\
  xyz = xyz* invec.s0 * sin( invec.s2 );\
  xyz.s2 = invec.s0 * cos(invec.s2);\
  invec = xyz;\
}

 
// Flow List, Vertex List
// Access x, y, z vertex:
//                var_name.vol[z*(ny*nx*8) + y*nx*8 + x*8 + v]
 
__kernel void InterpolateTestKernel(
                                  __global int3* vertex_list, //R
                                  __global float3* flow_list, //R 
                                  __global float3* seed_list, //R
                                  __global unsigned int* seed_elem,//RW
                                  unsigned int nx, 
                                  unsigned int ny, 
                                  unsigned int nz,
                                  float dx,
                                  float dy, 
                                  float dz,
                                  unsigned int n_steps,
                                  __global float3* path_storage //W
                                )
{
  //unsigned int glIDx = get_global_id(0);
  ////unsigned int glIDy = get_global_id(1);
  ////unsigned int glIDz = get_global_id(2);
  
  ////unsigned int globalX = get_global_size(0);
  ////unsigned int globalY = get_global_size(1);
  ////unsigned int globalZ = get_global_size(2);
  
  //unsigned int current_elem = seed_elem[glIDx];
  //float3 particle_pos = seed_list[glIDx];
  
  //float3 flow_dir; //dr, phi, theta
  //float3 temp_pos; //dx, dy, dz
  
  //int d_elem_x;
  //int d_elem_y;
  //int d_elem_z;
  
  //float ox = ((float) nx) * dx;
  //float oy = ((float) ny) * dy;
  //float oz = ((float) nz) * dz;
  
  //float xmin, xmax;
  //float ymin, ymax;
  //float zmin, zmax;
  
  //unsigned int steps_left = 0;
  //unsigned int current_step = 0;
  
  //path_storage[glIDx*n_steps] = particle_pos;
  
  //while(current_step < n_steps)
  //{
    ////
    //// Current elem limits
    ////
    //xmin = (float) vertex_list[8*current_elem].s0;
    //xmax = xmin + dx;
    
    //ymin = (float) vertex_list[8*current_elem].s1;
    //ymax = ymin + dy;
    
    //zmin = (float) vertex_list[8*current_elem].s2;
    //zmax = zmin + dz;
    
    //// pick vertex
    //// just gonna pick the lowest one (v0)

    //// generate next step
    //flow_dir = flow_list[8*current_elem]; //+0 (lowest x,y,z)
    
    ////
    //// condititions to proceed
    ////
    ////  is step out of total volume (first, break)
    ////  are we transitioning to a new elem
    //// 
     
    //CIRCTOCART( flow_dir );
    //temp_pos = particle_pos + flow_dir;
    
    //if( temp_pos.x - (float) ox > 0.0 || temp_pos.x < 0.0 ||
    //temp_pos.y - (float) oy > 0.0 || temp_pos.y < 0.0 ||
    //temp_pos.z - (float) oz > 0.0 || temp_pos.z < 0.0 )
      //break;
    
    //d_elem_x = 0;
    //d_elem_y = 0;
    //d_elem_z = 0;
    
    ////
    //// If statements suck. Find some way to do this with projections?
    ////
    //if( xmin - temp_pos.x > 0)
      //d_elem_x = -1;
    //else if( temp_pos.x - xmax > 0)
      //d_elem_x = 1;
    
    //if( ymin - temp_pos.y > 0)
      //d_elem_y = -1;
    //else if( temp_pos.y - ymax > 0)
      //d_elem_y = 1;
      
    //if( zmin - temp_pos.z > 0)
      //d_elem_z = -1;
    //else if( temp_pos.z - zmax > 0)
      //d_elem_z = 1;
    
    //current_elem = (unsigned int) ((int)current_elem +
      //(d_elem_z*8*((int) ny*nx)) + (d_elem_y*8*((int) nx)) +
        //(d_elem_x*8));    
    
    //// add to path_storage
    
    //particle_pos = temp_pos;
    //path_storage[glIDx*n_steps + current_step] = particle_pos;
    
    //// proceed    
    //current_step = current_step + 1;
  //}
  
  //// Idle Loop
  //while(current_step < n_steps)
  //{
    //path_storage[glIDx*n_steps + current_step]=(float3)(0.0, 0.0, 0.0);
    //current_step = current_step + 1;
  //}
  
  // All Done
}


//EOF