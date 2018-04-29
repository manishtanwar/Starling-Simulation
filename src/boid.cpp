#include "boid.h"
#define epsilon 0.000001
#include<iostream>


tuple::tuple(float x, float y, float z)
{
	this->x = x; this->y = y;	this->z = z;
}

tuple::tuple()
{
	this->x = 0; this->y = 0;	this->z = 0;
}

void tuple::printit()
{
	std::cout<<"tuple "<<x<<' '<<y<<' '<<z;
}

bool tuple::operator == (const tuple& rhs)
{
	return ( std::abs(x-rhs.x) < epsilon ) && ( std::abs(y-rhs.y) < epsilon ) && ( std::abs(z-rhs.z) < epsilon );
}


bool tuple::operator < (const tuple& rhs)
{
	if( std::abs(x-rhs.x) > epsilon && x < rhs.x) return true;
	if( std::abs(x-rhs.x) > epsilon && x > rhs.x) return false;
	if( std::abs(y-rhs.y) > epsilon && y < rhs.y) return true;
	if( std::abs(y-rhs.y) > epsilon && y > rhs.y) return false;
	if( std::abs(z-rhs.z) > epsilon && z < rhs.z) return true;
	return false;
}

void tuple::shift_it(tuple ref_vertex)
{
	x -= ref_vertex.x; y -= ref_vertex.y; z -= ref_vertex.z;
}