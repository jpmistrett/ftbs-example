#include <iostream>
#include <string>
#include <set>
#include <list>
#include <algorithm>

struct vector 
{
	float x, y, z;
};

struct point_data {
	std::set<const vector*> points; // O(lg(n))
	std::set<const vector*>::iterator it; 
};

struct fixed_tightly_bounding_sphere 
{
	const vector *center;
	float radius;
	point_data *p;
};

void init_sphere(fixed_tightly_bounding_sphere *sphere, const vector *center) 
{
	sphere->center = center;
	sphere->radius = 0;
	sphere->p = NULL;
}

void insert_point(fixed_tightly_bounding_sphere *sphere, const vector *new_p);

void remove_point(fixed_tightly_bounding_sphere *sphere, const vector *delete_p);

void update_radius(fixed_tightly_bounding_sphere *sphere);

int main()
{
	std::string hold;

	fixed_tightly_bounding_sphere sphere;
	vector center = { 1.0f, 1.0f, 1.0f };
	vector p1 = { 3.0f, 3.0f, 3.0f };

	init_sphere(&sphere, &center);
	insert_point(&sphere, &p1);

	std::cin >> hold;
}

void insert_point(fixed_tightly_bounding_sphere *sphere, const vector *new_p)
{
	bool point_found = false;

	if (sphere->p == NULL)
	{
		sphere->p = new point_data;
	}

	//check each point and decide whether of not to insert based on x/y/z/ values rather than the pointer
	for (const vector* point : sphere->p->points)
	{
		if (new_p->x == point->x && new_p->y == point->y && new_p->z == point->z)
		{
			point_found = true;
			break;
		}
	}

	if (!point_found) 
	{
		sphere->p->points.insert(new_p);
		update_radius(sphere);
	}
}

void remove_point(fixed_tightly_bounding_sphere* sphere, const vector* delete_p)
{
	if (sphere->p == NULL)
	{
		sphere->p = new point_data;
	}

	//check each point and decide whether of not to remove based on x/y/z/ values rather than the pointer
	for (const vector* point : sphere->p->points)
	{

		if (delete_p->x == point->x && delete_p->y == point->y && delete_p->z == point->z)
		{
			sphere->p->it = sphere->p->points.find(point);
			sphere->p->points.erase(sphere->p->it);
			update_radius(sphere);
			break;
		}
	}
}

void update_radius(fixed_tightly_bounding_sphere* sphere)
{
	sphere->radius = 0;

	for (const vector* point : sphere->p->points)
	{
		float point_distance_to_center = 
			sqrt(pow(point->x - sphere->center->x, 2) + 
			pow(point->y - sphere->center->y, 2) + 
			pow(point->z - sphere->center->z, 2) * 1.0);

		if (point_distance_to_center > sphere->radius)
		{
			sphere->radius = point_distance_to_center;
		}
	}
}
