#pragma once

#ifndef __GLOBAL_MACRO__
#define __GLOBAL_MACRO__

#ifdef _DEBUG
	#define DEBUG_ERROR(Message) std::_Debug_message(_T(Message), _T(__FILE__), __LINE__)
#else
	#define DEBUG_ERROR(Message)
#endif

#define PRINTF(...) printf(__VA_ARGS__)

#ifdef _MSC_VER
	#define FORCE_INLINE __forceinline
	#define INLINE __inline
#else 
	#define FORCE_INLINE inline
	#define INLINE inline
#endif

#define PLATFORM_API

#define HOST_FUNC

#define DEVICE_FUNC

#define GLOBAL_FUNC

#define HOST_DEVICE_FUNC

#endif