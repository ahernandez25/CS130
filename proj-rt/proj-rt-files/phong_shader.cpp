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
	vec3 r;
	vec3 l;

 	double max1;
	for(int i = 0; i < world.lights.size(); i++){
	    
	    l = (world.lights[i]->position - intersection_point).normalized();
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
		

	     

	}//end for




	color = id + is;
    return color;
}
