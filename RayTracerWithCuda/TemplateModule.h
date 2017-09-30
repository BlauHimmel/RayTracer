#pragma once

#ifdef INCLUDE_TEMPLATE
	#define INCLUDE_ARRAY
	#define INCLUDE_MAP
	#define INCLUDE_SET
#endif 

#ifdef INCLUDE_ARRAY
#define __INCLUDE_ARRAY
	#include "Array.h"
	#include "ArrayList.h"
	#include "LinkedList.h"
	#include "PriorityQueue.h"
	#include "Queue.h"
	#include "Stack.h"
#endif 

#ifdef INCLUDE_MAP
#define __INCLUDE_MAP
	#include "HashMap.h"
	#include "TreeMap.h"
#endif 

#ifdef INCLUDE_SET
#define __INCLUDE_SET
	#include "HashSet.h"
	#include "TreeSet.h"
#endif 

