#ifndef UGINE_TYPES_H
#define UGINE_TYPES_H

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
struct Vector2{
	double x, y;
};
struct Region{
	Vector2 p1, p2, p3, p4;
};

#endif