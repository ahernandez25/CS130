#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

#include <iostream>

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    	Hit hit;
	Hit finalHit = {NULL, 0, 0};
	double  min_t;

	min_t = std::numeric_limits<double>::max();
//std::cout << "obj size: "  << objects.size() << "\n";	
	
	for (int i = 0; i < objects.size(); i++) {
		
//		std::cout << "\nIN FOR";
		hit = objects.at(i)->Intersection(ray, 1);
		if (debug_pixel)
		    std::cout << "Intersection: " << hit.dist << std::endl;
		
		if (hit.dist >= small_t && hit.dist < min_t) {
			finalHit.part = hit.part;
			finalHit.dist = hit.dist;
			finalHit.object = objects[i];
			min_t = finalHit.dist;
			if (debug_pixel)
			    std::cout << "Min: " << min_t << std::endl;
		}
	}
    return finalHit;
    
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
        Ray ray;
	ray.endpoint = camera.position;
        ray.direction = ( camera.World_Position(pixel_index) - camera.position ).normalized();


    	vec3 color=Cast_Ray(ray,1);

    	camera.Set_Pixel(pixel_index,Pixel_Color(color));

//std::cout << "\n\n**cast ray: = " << ray.endpoint << "dirL " << ray.direction << "\n\n";   

}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    Hit hit;
    hit = Closest_Intersection(ray);
 
//	std::cout << "object dist: " << hit.dist << std::endl;
  
    if(hit.object != NULL){
	 color = hit.object->material_shader->Shade_Surface(ray, ray.Point(hit.dist),
	 hit.object->Normal(ray.Point(hit.dist),0),
	 recursion_depth);
//	if (debug_pixel)
//		std::cout << hit.dist << std::endl;		
		//std::cout << color << std::endl;

   }else
    {
	vec3 blank;
	blank.fill(1);
	color = background_shader->Shade_Surface(ray, blank, blank.normalized(), recursion_depth);
    }

    return color;

   
}

void Render_World::Initialize_Hierarchy(){
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
