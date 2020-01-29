#pragma once
#include "glm/glm.hpp"
#include "Spawned_Cube.h"

class Ray_Caster {
public:
	int cast_ray(double mouse_x, double mouse_y, int width, int height);
	bool intersect_with_objects(glm::vec3 ray, Spawned_Cube* this_cube);

	void set_view_matrix(glm::mat4 _view_matrix);
	void set_projection_matrix(glm::mat4 _projection_matrix);
	void set_ray_origin(glm::vec3 _camera_position);
	void set_cubes(vector<Spawned_Cube*>* _cubes);
	vector<Spawned_Cube*>* get_cubes();
private:
	glm::mat4 view_matrix;
	glm::mat4 projection_matrix;
	glm::vec3 ray_origin;
	vector<Spawned_Cube*>* cubes;
};