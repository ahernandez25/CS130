#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    	Hit hit;
	float discriminant;
	
	float a = dot(ray.direction, ray.direction);
	float b = dot(ray.direction, (ray.endpoint-center)) * 2;
	float c = dot((ray.endpoint - center), (ray.endpoint - center)) - (radius * radius);



	//discriminant = pow(dot(ray.direction, ray.endpoint - center),2) - 
	//	dot(ray.direction, ray.direction)*(dot(ray.endpoint - center, ray.endpoint - center)
	//		- pow(radius, 2));
	
	discriminant = (b*b) -( 4 * a * c);
//std::cout << "\ndisc: " << discriminant;
	if (discriminant < 0) {
		hit.object = NULL;
		hit.dist = 0;
		hit.part = 0;	
	}
	else if(discriminant == 0) {
		hit.object = this;
		hit.dist = -b/(2*a);
		hit.part = 0;
	
	}else{ 

		float t1, t2;
		
		t1 = (-b - sqrt(discriminant)) / 2*a;
		t2 = (-b + sqrt(discriminant)) / 2*a;
 		
		if((t1 < small_t) && (t2 < small_t)){
			hit.object = NULL;
			hit.dist = 0;
			hit.part = 0;
		} else if((t1 < small_t) && (t2 > small_t)){
			hit.object = this;
			hit.dist = t2;
			hit.part = 0;
		} else if((t1 > small_t) && (t2 < small_t)){
			hit.dist = t1;
			hit.object = this;
			hit.part = 0;
		}else {
			if(t1 < t2){
				hit.dist = t1;
				hit.object = this;
				hit.part = 0;
			} else if(t1 > t2){
				hit.dist = t2;
				hit.object = this;
				hit.part = 0;
			} else{
				hit.dist = t1;
				hit.object = this;
				hit.part = 0;
			}

		} 	
	}
    return hit;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    normal = point - center;
	
    return normal.normalized();
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
