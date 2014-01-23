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


#ifndef OCLPTX_CUSTOMTYPES_H_
#define OCLPTX_CUSTOMTYPES_H_


struct float8
{
	//Constructors
	float8() {};
	float8(float a) : s0(a), s1(a), s2(a), s3(a),
                    s4(a), s5(a), s6(a), s7(a) {}
	float8(float x, float y, float z, float w,
    float a, float b, float c, float d) : s0(x), s1(y), s2(z),
      s3(w), s4(a), s5(b), s6(c), s7(d) {}
 
	//Struct Data
	float s0, s1, s2, s3, s4, s5, s6, s7;
 
	//Operator Overrides
	float8 operator*(float x) const
  { 
      return float8(s0*x, s1*x, s2*x, s3*x, s4*x, s5*x, s6*x, s7*x); 
  }
	float8 operator+(const float8& a) const
  {
    return float8(s0+a.s0, s1+a.s1, s2+a.s2, s3+a.s3,
      s4+a.s4, s5+a.s5, s6+a.s6, s7+a.s7);
  }
};


struct float4
{
	//Constructors
	float4() {};
	float4(float a) : s0(a), s1(a), s2(a), s3(a) {}
	float4(float x, float y, float z, float w): s0(x), s1(y),
                                                    s2(z), s3(w) {}
 
	//Struct Data
	float s0, s1, s2, s3;
 
	//Operator Overrides
	float4 operator*(float x) const 
  {
    return float4(s0*x, s1*x, s2*x, s3*x); 
  }
	float4 operator+(const float4& a) const 
  { 
    return float4(s0+a.s0, s1+a.s1, s2+a.s2, s3+a.s3); 
  }
};


struct float3
{
	//Constructors
	float2() {};
	float2(float s) : x(s), y(s), z(s) {}
	float2(float s1, float s2, float s3) : x(s1), y(s2), z(s3) {}

	//Struct Data
	float x, y, z;
 
	//Operator Overrides
	float3 operator*(float s) const { return float3(x*s, y*s, z*s); }
	float3 operator+(const float3& a) const
  {
    return float3(x+a.x, y+a.y, z+a.z); 
  }
};

struct float2
{
	//Constructors
	float2() {};
	float2(float s) : x(s), y(s) {}
	float2(float x, float y) : x(x), y(y) {}

	//Struct Data
	float x, y;
 
	//Operator Overrides
	float2 operator*(float s) const { return float2(x*s, y*s); }
	float2 operator+(const float2& a) const 
  { 
    return float2(x+a.x, y+a.y); 
  }
};


struct int3
{
	//Constructors
	int3() {};
	int3(int s) : x(s), y(s), z(s) {}
	int3(int s1, int s2, int s3) : x(s1), y(s2), z(s3) {}

	//Struct Data
	int x, y, z;
 
	//Operator Overrides
	int3 operator*(int s) const { return int3(x*s, y*s, z*s); }
	int3 operator+(const int3& a) const
  {
    return int3(x+a.x, y+a.y, z+a.z); 
  }
};


struct 3DIntVolume
{
  //Constructors
  3DIntVolume(){};
  
  std::vector<int3> v0, v1, v2, v3, v4, v5, v6, v7;
  int nx, ny, nz;  
  
}

struct 3DFloatVolume
{
  //Constructors
  3DFloatVolume(){};
  
  std::vector<float3> v0, v1, v2, v3, v4, v5, v6, v7;
  int nx, ny, nz;  
  
}

#endif