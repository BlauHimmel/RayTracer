#pragma once

#ifdef INCLUDE_MATH
	#define INCLUDE_MATRIX
	#define INCLUDE_VECTOR
#endif 

#ifdef INCLUDE_MATRIX
#define __INCLUDE_MATRIX
	#include "Matrix4f.h"
#endif 

#ifdef INCLUDE_VECTOR
#define __INCLUDE_VECTOR
	#include "Vector2f.h"
	#include "Vector3f.h"
	#include "Vector4f.h"
#endif 


