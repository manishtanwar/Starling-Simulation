#include "../include/properties.h"
#include<bits/stdc++.h>

#define cohesion_coeff 3.0
#define separation_coeff 7.0
#define alignment_coeff 0.5
#define inertia_coeff 0.1
#define boundary_repulsion_coeff 0.8
#define wall_coeff 50.0
#define wall_coeff_near 5.0
#define radius 40.0
#define no_of_neighbours 80
// #define radius 150.0
// #define no_of_neighbours 80

int dir[27][3];
int call_no = 0;

std::vector<int> give_neighbours(int n, std::vector<boid> v, std::vector<int> grid[12][12][12], int x1,int y1, int z1)
{
	std::vector< std::pair<float,int> > ans;
	int x2,y2,z2;
	for(int i=0;i<27;i++)
	{
		x2 = x1 + dir[i][0];
		y2 = y1 + dir[i][1];
		z2 = z1 + dir[i][2];
		if(x2 < 0 || x2 > 11) continue;
		if(y2 < 0 || y2 > 11) continue;
		if(z2 < 0 || z2 > 11) continue;
		for(auto z : grid[x2][y2][z2])
		{
			if(z == n) continue;
			float dist = v[z].position.distance(v[n].position);
			if(dist > radius) continue;
			ans.pb({dist,z});
		}
	}

	// for(int i=0;i<v.size(); i++)
	// {
	// 	if(i == n) continue;
	// 	float dist = v[i].position.distance(v[n].position);
	// 	if(dist > radius) continue;
	// 	ans.pb({dist,i});
	// }
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
		if(z == n) continue;
		tuple ith_position; ith_position = v[z].position; ith_position.shift_it(v[n].position);
		float ith_mag = -(1.0/ith_position.magnitude());
		ith_mag /= ith_position.magnitude();
		if(std::isinf(ith_mag)) continue;

		// if(std::isnan(ith_mag)) {std::cout<<"sep galat "<<'\n'; return avg_position;}
		// if(std::isnan(ith_position.x)) {std::cout<<"sep galat "<<'\n'; return avg_position;}
		// if(std::isnan(ith_position.y)) {std::cout<<"sep galat "<<'\n'; return avg_position;}
		// if(std::isnan(ith_position.z)) {std::cout<<"sep galat "<<'\n'; return avg_position;}

		// if(std::isnan(avg_position.x)) {std::cout<<"sep1 galat "<<'\n'; return avg_position;}
		// if(std::isnan(avg_position.y)) {std::cout<<"sep1 galat "<<'\n'; return avg_position;}
		// if(std::isnan(avg_position.z)) {std::cout<<"sep1 galat "<<'\n'; return avg_position;}
		
		// std::cout<<avg_position.x<<' '<<avg_position.y<<' '<<avg_position.z<<'\n';
		// std::cout<<ith_position.x<<' '<<ith_position.y<<' '<<ith_position.z<<'\n';
		// std::cout<<ith_mag<<'\n';
		avg_position = avg_position + ith_position*ith_mag;

		// if(std::isnan(avg_position.x)) {std::cout<<"sep21 galat "<<'\n';std::cout<<avg_position.x<<' '<<avg_position.y<<' '<<avg_position.z<<'\n';
		// std::cout<<ith_position.x<<' '<<ith_position.y<<' '<<ith_position.z<<'\n';
		// std::cout<<ith_mag<<'\n'; return avg_position;}
		// if(std::isnan(avg_position.y)) {std::cout<<"sep22 galat "<<'\n'; return avg_position;}
		// if(std::isnan(avg_position.z)) {std::cout<<"sep23 galat "<<'\n'; return avg_position;}
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
	int p,q; 
	
	xmi = v.position + ( (tuple (Xmin,0,0))*(-1.0));
	p = rand()%50; q = rand()%50;
	p = v.velocity.y/abs(v.velocity.y) * p;
	q = v.velocity.z/abs(v.velocity.z) * q;
	xmi = xmi + (tuple (0,p,q));

	if(xmi.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + xmi*(1.0/xmi.magnitude());
	if(xmi.magnitude() < wall_coeff_near && v.position.x > Xmin)
	avg_velocity = avg_velocity + xmi*(50.0/xmi.magnitude());
	else if(v.position.x < Xmin)
	avg_velocity = avg_velocity + xmi*(-50.0/xmi.magnitude());

	
	xmx = v.position + ( (tuple (Xmax,0,0))*(-1.0));
	p = rand()%50; q = rand()%50;
	p = v.velocity.y/abs(v.velocity.y) * p;
	q = v.velocity.z/abs(v.velocity.z) * q;
	xmx = xmx + (tuple (0,p,q));

	if(xmx.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + xmx*(1.0/xmx.magnitude());
	if(xmx.magnitude() < wall_coeff_near && v.position.x < Xmax)
	avg_velocity = avg_velocity + xmx*(50.0/xmx.magnitude());
	else if(v.position.x > Xmax)
	avg_velocity = avg_velocity + xmx*(-50.0/xmx.magnitude());

	tuple ymi,ymx;
	
	ymi = v.position + ( (tuple (0,Ymin,0))*(-1.0));
	p = rand()%50; q = rand()%50;
	p = v.velocity.x/abs(v.velocity.x) * p;
	q = v.velocity.z/abs(v.velocity.z) * q;
	ymi = ymi + (tuple (p,0,q));

	if(ymi.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + ymi*(1.0/ymi.magnitude());
	if(ymi.magnitude() < wall_coeff_near && v.position.y > Ymin)
	avg_velocity = avg_velocity + ymi*(50.0/ymi.magnitude());
	else if(v.position.y < Ymin)
	avg_velocity = avg_velocity + ymi*(-50.0/ymi.magnitude());

	ymx = v.position + ( (tuple (0,Ymax,0))*(-1.0));
	p = rand()%50; q = rand()%50;
	p = v.velocity.x/abs(v.velocity.x) * p;
	q = v.velocity.z/abs(v.velocity.z) * q;
	ymx = ymx + (tuple (p,0,q));

	if(ymx.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + ymx*(1.0/ymx.magnitude());
	if(ymx.magnitude() < wall_coeff_near && v.position.y < Ymax)
	avg_velocity = avg_velocity + ymx*(50.0/ymx.magnitude());
	else if(v.position.y > Ymax)
	avg_velocity = avg_velocity + ymx*(-50.0/ymx.magnitude());

	tuple zmi,zmx;
	zmi = v.position + ( (tuple (0,0,Zmin))*(-1.0));
	p = rand()%50; q = rand()%50;
	p = v.velocity.x/abs(v.velocity.x) * p;
	q = v.velocity.y/abs(v.velocity.y) * q;
	zmi = zmi + (tuple (p,q,0));

	if(zmi.magnitude() < wall_coeff)
	avg_velocity = avg_velocity + zmi*(1.0/zmi.magnitude());
	if(zmi.magnitude() < wall_coeff_near && v.position.z > Zmin)
	avg_velocity = avg_velocity + zmi*(50.0/zmi.magnitude());
	else if(v.position.z > Zmin)
	avg_velocity = avg_velocity + zmi*(-50.0/zmi.magnitude());
	

	zmx = v.position + ( (tuple (0,0,Zmax))*(-1.0));
	p = rand()%50; q = rand()%50;
	p = v.velocity.x/abs(v.velocity.x) * p;
	q = v.velocity.y/abs(v.velocity.y) * q;
	zmx = zmx + (tuple (p,q,0));

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

tuple change_it(std::vector<boid> &v)
{
	call_no++;
	tuple avg_force(0,0,0);
	for(int i=0;i<v.size(); i++)
	{
		if(std::isnan(v[i].position.x)) {std::cout<<"here "<<call_no<<'\n'; return avg_force;}
		if(std::isnan(v[i].position.y)) {std::cout<<"here "<<call_no<<'\n'; return avg_force;}
		if(std::isnan(v[i].position.z)) {std::cout<<"here "<<call_no<<'\n'; return avg_force;}
		if(std::isnan(v[i].velocity.x)) {std::cout<<"here "<<call_no<<'\n'; return avg_force;}
		if(std::isnan(v[i].velocity.y)) {std::cout<<"here "<<call_no<<'\n'; return avg_force;}
		if(std::isnan(v[i].velocity.z)) {std::cout<<"here "<<call_no<<'\n'; return avg_force;}
		
	}
	int gin=0;
	for(int i=-1;i<=1;i++)
	{
		for(int j=-1;j<=1;j++)
		{
			for(int k=-1;k<=1;k++){
				dir[gin][0] = i;
				dir[gin][1] = j;
				dir[gin++][2] = k;
			}
		}
	}

 	std::vector<int> neighbours;
	tuple cohesive_change, separation_change, alignment_change, total_change,boundary_force_change;
	std::vector<tuple> velocity_change;
	std::vector<int> grid[12][12][12];

	for(int i=0;i<v.size(); i++)
	{
		int x1,y1,z1;
		x1 = (int)((v[i].position.x + 240.0)/40.0);
		y1 = (int)((v[i].position.y + 240.0)/40.0);
		z1 = (int)((v[i].position.z + 240.0)/40.0);
		if(x1 < 0) x1 = 0;
		if(x1 > 11) x1 = 11;
		if(y1 < 0) y1 = 0;
		if(y1 > 11) y1 = 11;
		if(z1 < 0) z1 = 0;
		if(z1 > 11) z1 = 11;

		grid[x1][y1][z1].push_back(i);
	}


	for(int i=0;i<v.size(); i++)
	{
		int x1,y1,z1;
		x1 = (int)((v[i].position.x + 240.0)/40.0);
		y1 = (int)((v[i].position.y + 240.0)/40.0);
		z1 = (int)((v[i].position.z + 240.0)/40.0);
		if(x1 < 0) x1 = 0;
		if(x1 > 11) x1 = 11;
		if(y1 < 0) y1 = 0;
		if(y1 > 11) y1 = 11;
		if(z1 < 0) z1 = 0;
		if(z1 > 11) z1 = 11;

		neighbours = give_neighbours(i,v,grid,x1,y1,z1);
		
		cohesive_change = calc_cohesive(neighbours,i,v);
		separation_change = calc_separation(neighbours,i,v);
		// if(std::isnan(separation_change.x)) {std::cout<<"total me galat "<<call_no<<'\n'; return avg_force;}
		alignment_change = calc_alignment(neighbours,i,v);
		boundary_force_change = calc_boundary_force(v[i]);
		// boundary_force_change = tuple(0,0,0);

		total_change = cohesive_change * cohesion_coeff + separation_change * separation_coeff + alignment_change * alignment_coeff
		+ boundary_force_change * boundary_repulsion_coeff;
		// if(std::isnan(total_change.x)) {std::cout<<"total me galat "<<call_no<<'\n'; return avg_force;}
		total_change = total_change * inertia_coeff;
		velocity_change.pb(total_change);
		// if(i == 0)
		// return avg_force;
	}


	for(int i=0;i<v.size();i++)
	{
		tuple new_vel = v[i].velocity;
		// if(std::isnan(new_vel.x)) {std::cout<<"here212 "<<call_no<<'\n'; return avg_force;}
		// if(std::isnan(new_vel.y)) {std::cout<<"here2 "<<call_no<<'\n'; return avg_force;}
		// if(std::isnan(new_vel.z)) {std::cout<<"here3 "<<call_no<<'\n'; return avg_force;}
		velocity_change[i] = velocity_change[i] * (-1);
		new_vel.shift_it(velocity_change[i]);
		// if(std::isnan(new_vel.x)) {std::cout<<"here213 "<<call_no<<'\n'; return avg_force;}
		// if(std::isnan(new_vel.y)) {std::cout<<"here2 "<<call_no<<'\n'; return avg_force;}
		// if(std::isnan(new_vel.z)) {std::cout<<"here3 "<<call_no<<'\n'; return avg_force;}
		float velmg = new_vel.magnitude();

		// if(std::isnan(new_vel.x)) {std::cout<<"here21 "<<call_no<<'\n'; return avg_force;}
		// if(std::isnan(new_vel.y)) {std::cout<<"here2 "<<call_no<<'\n'; return avg_force;}
		// if(std::isnan(new_vel.z)) {std::cout<<"here3 "<<call_no<<'\n'; return avg_force;}

		if(velmg > vel_MAX)
			new_vel = new_vel * ( vel_MAX / new_vel.magnitude() );

		avg_force = avg_force + ( new_vel + v[i].velocity*(-1.0) )*(1.0/0.03);

		// if(std::isnan(new_vel.x)) {std::cout<<"here1 "<<call_no<<'\n'; return avg_force;}
		// if(std::isnan(new_vel.y)) {std::cout<<"here2 "<<call_no<<'\n'; return avg_force;}
		// if(std::isnan(new_vel.z)) {std::cout<<"here3 "<<call_no<<'\n'; return avg_force;}

		v[i].velocity = new_vel;
		// std::cout<<v[i].velocity.x<<' '<<v[i].velocity.y<<' '<<v[i].velocity.z<<'\n';
	}
	// std::cout<<std::setprecision(25);
	// std::cout<<avg_force.x<<' '<<avg_force.y<<' '<<avg_force.z<<'\n';
	avg_force = avg_force * ( 70.0/(v.size() * 1000.0) );

	// avg_force = avg_force * ( 1.0/v.size() );
	// std::cout<<avg_force.x<<' '<<avg_force.y<<' '<<avg_force.z<<'\n';
	return avg_force;
}
