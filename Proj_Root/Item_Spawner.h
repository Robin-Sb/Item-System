#pragma once
#include "BKA_Object_Builder.h"
#include <vector>
#include <GLM/glm.hpp>
#include "BKA_Material_Builder.h"
#include "Spawned_Cube.h"
#include "BKA_Utils.h"

class Item_Spawner {
public:
	Item_Spawner();
	std::vector<BKA_Object_Builder*> spawn_items();
	void use_material(glm::mat4 view_matrix, glm::mat4 projection_matrix);
	void create_material();


	void set_cube_values(Spawned_Cube* cube);
	void render_spawned_cubes(glm::mat4 view_matrix, glm::mat4 projection_matrix);
	std::vector<Spawned_Cube*>* get_cubes();

private:
	BKA_Material_Builder* spawned_cube_material;
	std::vector<Spawned_Cube*>* actual_cubes;
	BKA_Utils bka_utils;

	GLuint uniform_projection;
	GLuint uniform_view;
	GLuint uniform_model;
	GLuint uniform_cube_colour;
};