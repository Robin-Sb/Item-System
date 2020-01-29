#include "Ray_Caster.h"
#include <math.h>
#include <GLM/gtc/matrix_transform.hpp>


using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;

int Ray_Caster::cast_ray(double mouse_x, double mouse_y, int width, int height) {
	float x = (2.0f * mouse_x) / width - 1.0f;
	float y = 1.0f - (2.0f * mouse_y) / height;
	float z = 1.0f;
	vec3 ray_nds =  vec3(x, y, z);

	vec4 ray_clip = vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);

	vec4 ray_eye = inverse(projection_matrix) * ray_clip;
	ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
	vec3 inverse_ray_eye = (inverse(view_matrix) * ray_eye);
	vec3 ray_world = vec3(inverse_ray_eye.x, inverse_ray_eye.y, inverse_ray_eye.z);
	float length = sqrt(ray_world.x + ray_world.y + ray_world.z);
	ray_world = ray_world / length;
	for (int i = 0; i < cubes->size(); i++) {
		if (intersect_with_objects(ray_world, cubes->at(i))) {
			printf("intersected");
			return i;
		}
	}
	return -1;
}

bool Ray_Caster::intersect_with_objects(vec3 ray, Spawned_Cube* this_cube) {
	float tMin = 0.0f;
	// arbitrary high value
	float tMax = 1000000.0f;

	mat4 model_matrix = this_cube->get_model_matrix();
	vec3 upper_bound = vec3(1.0, 1.0, 1.0); 
	vec3 lower_bound = vec3(-1.0, -1.0, -1.0); 

	glm::vec3 OBBposition_worldspace(model_matrix[3].x, model_matrix[3].y, model_matrix[3].z);

	vec3 delta = OBBposition_worldspace - ray_origin;

	{
		vec3 x_axis(model_matrix[0].x, model_matrix[0].y, model_matrix[0].z);
		float e = glm::dot(x_axis, delta);
		float f = glm::dot(ray, x_axis);

		if (fabs(f) > 0.001f) { 
			float lower_intersect = (e + lower_bound.x) / f;
			float upper_intersect = (e + upper_bound.x) / f;
			if (lower_intersect > upper_intersect) {
				float w = lower_intersect; 
				lower_intersect = upper_intersect; 
				upper_intersect = w; 
			}

			if (upper_intersect < tMax)
				tMax = upper_intersect;
			if (lower_intersect > tMin)
				tMin = lower_intersect;
			if (tMax < tMin)
				return false;
		}
		else { 
			if (-e + lower_bound.x > 0.0f || -e + upper_bound.x < 0.0f)
				return false;
		}
	}

	{
		glm::vec3 yaxis(model_matrix[1].x, model_matrix[1].y, model_matrix[1].z);
		float e = glm::dot(yaxis, delta);
		float f = glm::dot(ray, yaxis);

		if (fabs(f) > 0.001f) {

			float lower_intersect = (e + lower_bound.y) / f;
			float upper_intersect = (e + upper_bound.y) / f;

			if (lower_intersect > upper_intersect) { 
				float w = lower_intersect; 
				lower_intersect = upper_intersect; 
				upper_intersect = w; 
			}

			if (upper_intersect < tMax)
				tMax = upper_intersect;
			if (lower_intersect > tMin)
				tMin = lower_intersect;
			if (tMin > tMax)
				return false;
		}
		else {
			if (-e + lower_bound.y > 0.0f || -e + upper_bound.y < 0.0f)
				return false;
		}
	}

	{
		glm::vec3 zaxis(model_matrix[2].x, model_matrix[2].y, model_matrix[2].z);
		float e = glm::dot(zaxis, delta);
		float f = glm::dot(ray, zaxis);

		if (fabs(f) > 0.001f) {

			float lower_intersect = (e + lower_bound.z) / f;
			float upper_intersect = (e + upper_bound.z) / f;

			if (lower_intersect > upper_intersect) { 
				float w = lower_intersect; 
				lower_intersect = upper_intersect; 
				upper_intersect = w; 
			}

			if (upper_intersect < tMax)
				tMax = upper_intersect;
			if (lower_intersect > tMin)
				tMin = lower_intersect;
			if (tMin > tMax)
				return false;
		}
		else {
			if (-e + lower_bound.z > 0.0f || -e + upper_bound.z < 0.0f)
				return false;
		}
	}
	return true;
}

void Ray_Caster::set_view_matrix(glm::mat4 _view_matrix) {
	view_matrix = _view_matrix;
}
void Ray_Caster::set_projection_matrix(glm::mat4 _projection_matrix) {
	projection_matrix = _projection_matrix;
}
void Ray_Caster::set_ray_origin(glm::vec3 _camera_position) {
	ray_origin = _camera_position;
}
void Ray_Caster::set_cubes(vector<Spawned_Cube*>* _cubes) {
	cubes = _cubes;
}
vector<Spawned_Cube*>* Ray_Caster::get_cubes() {
	return cubes;
}