#include "../include/properties.h"
#include<bits/stdc++.h>

#define cohesion_coeff 0.1
#define separation_coeff 0.001
#define alignment_coeff 0.5
#define inertia_coeff 0.1
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
	tuple cohesive_change, separation_change, alignment_change, total_change;
	std::vector<tuple> velocity_change;

	for(int i=0;i<v.size(); i++)
	{
		neighbours = give_neighbours(i,v);
		cohesive_change = calc_cohesive(neighbours,i,v);
		separation_change = calc_separation(neighbours,i,v);
		alignment_change = calc_alignment(neighbours,i,v);

		total_change = cohesive_change * cohesion_coeff + separation_change * separation_coeff + alignment_change * alignment_coeff;
		total_change = total_change * inertia_coeff;
		velocity_change.pb(total_change);
	}
	for(int i=0;i<v.size();i++)
	{
		velocity_change[i] = velocity_change[i] * (-1);
		v[i].velocity.shift_it(velocity_change[i]);
	}
}
