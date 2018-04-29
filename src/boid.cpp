#include "../include/boid.h"
#define eps 0.000001
#include<bits/stdc++.h>


tuple::tuple(float x, float y, float z)
{
	this->x = x; this->y = y;	this->z = z;
}

tuple::tuple()
{
	this->x = 0; this->y = 0;	this->z = 0;
}

bool tuple::operator == (const tuple& rhs)
{
	return ( std::abs(x-rhs.x) < eps ) && ( std::abs(y-rhs.y) < eps ) && ( std::abs(z-rhs.z) < eps );
}

tuple tuple::operator + (const tuple& rhs)
{
	tuple ans(this->x,this->y,this->z);
	ans.x += rhs.x;
	ans.y += rhs.y;
	ans.z += rhs.z;
	return ans;
}

tuple tuple::operator * (const float& rhs)
{
	tuple ans(this->x,this->y,this->z);
	ans.x *= rhs;
	ans.y *= rhs;
	ans.z *= rhs;
	return ans;
}


float tuple::distance(tuple a)
{
	float dist = (a.x - this->x)*(a.x - this->x);
	dist += (a.y - this->y)*(a.y - this->y);
	dist += (a.z - this->z)*(a.z - this->z);
	dist = sqrt(dist);
	return dist;
}

float tuple::magnitude()
{
	tuple tmp(0,0,0);
	return this->distance(tmp);
}


bool tuple::operator < (const tuple& rhs)
{
	if( std::abs(x-rhs.x) > eps && x < rhs.x) return true;
	if( std::abs(x-rhs.x) > eps && x > rhs.x) return false;
	if( std::abs(y-rhs.y) > eps && y < rhs.y) return true;
	if( std::abs(y-rhs.y) > eps && y > rhs.y) return false;
	if( std::abs(z-rhs.z) > eps && z < rhs.z) return true;
	return false;
}

void tuple::shift_it(tuple ref_vertex)
{
	x -= ref_vertex.x; y -= ref_vertex.y; z -= ref_vertex.z;
}

void tuple::make_it_unit_vector()
{
	float mag = this->magnitude();
	this->x /= mag;
	this->y /= mag;
	this->z /= mag;
}

boid::boid(tuple position, tuple velocity)
{
	this->position = position;
	this->velocity = velocity;
}

boid::boid(tuple position)
{
	this->position = position;
	float x,y,z; 
	x = random_float(vel_MIN,vel_MAX);
	y = random_float(vel_MIN,vel_MAX);
	z = random_float(vel_MIN,vel_MAX);
	tuple velocity1(x,y,z);
	this->velocity = velocity1;
}

boid::boid()
{
	float x,y,z;
	x = random_float(Xmin,Xmax);
	y = random_float(Ymin,Ymax);
	z = random_float(Zmin,Zmax);	
	tuple position1(x,y,z);
	this->position = position1;
	x = random_float(vel_MIN,vel_MAX);
	y = random_float(vel_MIN,vel_MAX);
	z = random_float(vel_MIN,vel_MAX);
	tuple velocity1(x,y,z);
	this->velocity = velocity1;	
}

float random_float(int mi,int mx)
{
    int mx1= mx-mi;
    int a = rand()%100 + 1;
    float ans = ((float)a/100.0)*(float)mx1;
    ans += (float)mi;

    return ans;
}

tuple cross_product(tuple a, tuple b)
{
	float x,y,z;

	x = a.y * b.z - a.z * b.y;
	y = b.x * a.z - a.x * b.z;
	z = a.x * b.y - a.y * b.x;

	tuple ans(x,y,z);
	return ans;
}

float dot_product(tuple a, tuple b)
{
	float ans;
	ans = a.x*b.x + a.y*b.y + a.z*b.z;
	return ans;
}
