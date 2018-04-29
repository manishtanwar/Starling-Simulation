#include "../include/properties.h"
#include<bits/stdc++.h>

#define cohesion_coeff 0.01
#define separation_coeff 50.0
#define alignment_coeff 0.1
#define inertia_coeff 0.1
#define boundary_repulsion_coeff 0.05
#define wall_coeff 50.0
#define wall_coeff_near 5.0
#define radius 30.0
#define no_of_neighbours 6

std::vector<int> give_neighbours(int n, std::vector<boid> v)
{
	std::vector< std::pair<float,int> > ans;
	for(int i=0;i<v.size(); i++)
	{
		if(i == n) continue;
		float dist = v[i].position.distance(v[n].position);
		if(dist > radius) continue;
		ans.pb({dist,i});
	}
	std::sort(ans.begin(), ans.end());
	std::vector<int> ans1;
	int size_of = ans.size();
	size_of = std::min(no_of_neighbours,size_of);
	for(int i=0;i<size_of;i++)
	{
		ans1.pb(ans[i].second);
	}
	return ans1;
}

tuple calc_cohesive(std::vector<int> neighbours, int n, std::vector<boid> v)
{
	tuple avg_position;
	if(neighbours.size() == 0) return avg_position; // avg_position is zero
	
	for(auto z : neighbours)
	{
		avg_position = avg_position + v[z].position;
	}
	avg_position = avg_position * ((float)1.0/neighbours.size());
	avg_position.shift_it(v[n].position);
	return avg_position;
}

tuple calc_separation(std::vector<int> neighbours, int n, std::vector<boid> v)
{
	tuple avg_position;
	if(neighbours.size() == 0) return avg_position; // avg_position is zero
	
	for(auto z : neighbours)
	{
		tuple ith_position; ith_position = v[z].position; ith_position.shift_it(v[n].position);
		float ith_mag = -1.0/ith_position.magnitude();
		avg_position = avg_position + v[z].position*ith_mag;
	}
	return avg_position;
}

tuple calc_boundary_force(boid v)
{
	// tuple avg_velocity;
	// tuple xmi,xmx;
	// xmi = v.position + ( (tuple (Xmin,0,0))*(-1.0));
	// if(xmi.magnitude() < wall_coeff)
	// avg_velocity = avg_velocity + xmi*(1.0/xmi.magnitude());
	// xmx = v.position + ( (tuple (Xmax,0,0))*(-1.0));
	// if(xmx.magnitude() < wall_coeff)
	// avg_velocity = avg_velocity + xmx*(1.0/xmx.magnitude());

	// tuple ymi,ymx;
	// ymi = v.position + ( (tuple (0,Ymin,0))*(-1.0));
	// if(ymi.magnitude() < wall_coeff)
	// avg_velocity = avg_velocity + ymi*(1.0/ymi.magnitude());
	// ymx = v.position + ( (tuple (0,Ymax,0))*(-1.0));
	// if(ymx.magnitude() < wall_coeff)
	// avg_velocity = avg_velocity + ymx*(1.0/ymx.magnitude());
	
	// tuple zmi,zmx;
	// zmi = v.position + ( (tuple (0,0,Zmin))*(-1.0));
	// if(zmi.magnitude() < wall_coeff)
	// avg_velocity = avg_velocity + zmi*(1.0/zmi.magnitude());
	// zmx = v.position + ( (tuple (0,0,Zmax))*(-1.0));
	// if(zmx.magnitude() < wall_coeff)
	// avg_velocity = avg_velocity + zmx*(1.0/zmx.magnitude());

	tuple avg_velocity;
	tuple xmi,xmx;
	xmi = v.position + ( (tuple (Xmin,0,0))*(-1.0));
	if(xmi.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + xmi*(1.0/xmi.magnitude());
	if(xmi.magnitude() < wall_coeff_near && v.position.x > Xmin)
	avg_velocity = avg_velocity + xmi*(50.0/xmi.magnitude());
	else if(v.position.x < Xmin)
	avg_velocity = avg_velocity + xmi*(-50.0/xmi.magnitude());


	xmx = v.position + ( (tuple (Xmax,0,0))*(-1.0));
	if(xmx.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + xmx*(1.0/xmx.magnitude());
	if(xmx.magnitude() < wall_coeff_near && v.position.x < Xmax)
	avg_velocity = avg_velocity + xmx*(50.0/xmx.magnitude());
	else if(v.position.x > Xmax)
	avg_velocity = avg_velocity + xmx*(-50.0/xmx.magnitude());

	tuple ymi,ymx;
	ymi = v.position + ( (tuple (0,Ymin,0))*(-1.0));
	if(ymi.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + ymi*(1.0/ymi.magnitude());
	if(ymi.magnitude() < wall_coeff_near && v.position.y > Ymin)
	avg_velocity = avg_velocity + ymi*(50.0/ymi.magnitude());
	else if(v.position.y < Ymin)
	avg_velocity = avg_velocity + ymi*(-50.0/ymi.magnitude());

	ymx = v.position + ( (tuple (0,Ymax,0))*(-1.0));
	if(ymx.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + ymx*(1.0/ymx.magnitude());
	if(ymx.magnitude() < wall_coeff_near && v.position.y < Ymax)
	avg_velocity = avg_velocity + ymx*(50.0/ymx.magnitude());
	else if(v.position.y > Ymax)
	avg_velocity = avg_velocity + ymx*(-50.0/ymx.magnitude());

	tuple zmi,zmx;
	zmi = v.position + ( (tuple (0,0,Zmin))*(-1.0));
	if(zmi.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + zmi*(1.0/zmi.magnitude());
	if(zmi.magnitude() < wall_coeff_near && v.position.z > Zmin)
	avg_velocity = avg_velocity + zmi*(50.0/zmi.magnitude());
	else if(v.position.z > Zmin)
	avg_velocity = avg_velocity + zmi*(-50.0/zmi.magnitude());
	

	zmx = v.position + ( (tuple (0,0,Zmax))*(-1.0));
	if(zmx.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + zmx*(1.0/zmx.magnitude());
	if(zmx.magnitude() < wall_coeff_near && v.position.z < Zmax)
	avg_velocity = avg_velocity + zmx*(50.0/zmx.magnitude());
	else if(v.position.z > Zmax)
	avg_velocity = avg_velocity + zmx*(50.0/zmx.magnitude());

	return avg_velocity;
}

tuple calc_alignment(std::vector<int> neighbours, int n, std::vector<boid> v)
{
	tuple avg_velocity;
	if(neighbours.size() == 0) return avg_velocity; // avg_position is zero
	
	for(auto z : neighbours)
	{
		avg_velocity = avg_velocity + v[z].velocity;
	}
	avg_velocity = avg_velocity * ((float)1.0/neighbours.size());
	return avg_velocity;
}

void change_it(std::vector<boid> &v)
{
	std::vector<int> neighbours;
	tuple cohesive_change, separation_change, alignment_change, total_change,boundary_force_change;
	std::vector<tuple> velocity_change;

	for(int i=0;i<v.size(); i++)
	{
		neighbours = give_neighbours(i,v);
		cohesive_change = calc_cohesive(neighbours,i,v);
		separation_change = calc_separation(neighbours,i,v);
		alignment_change = calc_alignment(neighbours,i,v);
		boundary_force_change = calc_boundary_force(v[i]);
		// boundary_force_change = tuple(0,0,0);

		total_change = cohesive_change * cohesion_coeff + separation_change * separation_coeff + alignment_change * alignment_coeff
		+ boundary_force_change * boundary_repulsion_coeff;
		total_change = total_change * inertia_coeff;
		velocity_change.pb(total_change);
	}
	for(int i=0;i<v.size();i++)
	{
		tuple new_vel = v[i].velocity;
		velocity_change[i] = velocity_change[i] * (-1);
		new_vel.shift_it(velocity_change[i]);
		float velmg = new_vel.magnitude();

		if(velmg > vel_MAX)
			new_vel = new_vel * ( vel_MAX / new_vel.magnitude() );

		v[i].velocity = new_vel;
	}
}
