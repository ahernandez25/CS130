#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
#include<algorithm>

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
	vec3 id;
	vec3 is;
	vec3 ia;
	vec3 r;
	vec3 l;

 	double max1;
	for(int i = 0; i < world.lights.size(); i++){
	    
	    l = (world.lights[i]->position - intersection_point).normalized();
	    
	    Ray shadow_ray;
	    Hit hit = {NULL, 0, 0};
	    
	    
	    vec3 light_dist = world.lights[i]->position - intersection_point; 
	    
		if(world.enable_shadows == true){
		    shadow_ray.endpoint = intersection_point;
	    	    shadow_ray.direction = l;
	    
	   
	    	    hit = world.Closest_Intersection(shadow_ray);
	    	}

	    if(hit.dist < light_dist.magnitude() && hit.dist >= small_t){
	        continue;

	     } 

	    //DIFFUSE
	    if(dot(normal,l) > 0){
			max1 =dot(normal, l); 
	    }else{
	        max1 = 0;
	    }

	    id += color_diffuse * world.lights[i]->Emitted_Light(world.lights[i]->position - intersection_point) * max1;

	    //SPECULAR
	    r = (-l) + (2 * dot(l,normal) * normal);
 	    if(dot(-ray.direction,r) > 0){
                        max1 =dot(-ray.direction,r);
            }else{
                max1 = 0;
            }
	    is += color_specular * world.lights[i]->Emitted_Light(world.lights[i]->position - intersection_point) * pow(max1,specular_power);         

	    //ia += (specular_power*world.lights[i]->Emitted_Light(world.lights[i]->position - intersection_point)) * color_ambient;


	}//end for

	ia = world.ambient_color * world.ambient_intensity * color_ambient;


	color = id + is + ia;
    return color;
}
