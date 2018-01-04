#pragma once

#ifndef __CONTAINER_MACRO__
#define __CONTAINER_MACRO__

#define MAP_DELEGATE [&](auto& Key, auto& Value)
#define MAP_FILTER [&](auto& Key, auto& Value)

#define LIST_DELEGATE [&](auto& Element)
#define LIST_FILTER [&](auto& Element)

#define SET_DELEGATE [&](auto& Element)
#define SET_FILTER [&](auto& Element)

#endif

