#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    Ray reflected_color;
    vec3 r;
    vec3 color_reflected;
    vec3 color_intersect;
    vec3 v = -ray.direction;

    r =  (-v) + (2 * dot(v,normal) * normal);
    reflected_color.endpoint = intersection_point;
    reflected_color.direction = r.normalized();
    
    color_reflected = reflectivity * world.Cast_Ray(reflected_color, recursion_depth++ );
    color_intersect = (1 - reflectivity) * shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);

    color = color_reflected + color_intersect; 
 
    return color;
}
