#include "Item_Spawner.h"
#include <stdlib.h> 
#include <time.h>
#include <random>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>


Item_Spawner::Item_Spawner()
{
	uniform_projection = 0;
	uniform_view = 0;
	uniform_model = 0;
	spawned_cube_material = 0;
	uniform_cube_colour = 0;
	actual_cubes = new vector<Spawned_Cube*>();
}


void Item_Spawner::create_material() {
	BKA_Material_Builder* cube_material = new BKA_Material_Builder();
	cube_material->create_default_material_from_file("Shader_Root/os_shader.vertex", "Shader_Root/os_shader.fragment");
	spawned_cube_material = cube_material;
}


std::vector<BKA_Object_Builder*> Item_Spawner::spawn_items() {
	std::vector<BKA_Object_Builder*> spawned_objects;
	GLfloat vertices[] = {
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,		//0 Hinten links oben
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,	//1 Hinten links unten
		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,		//2 Hinten rechts oben
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,		//3 Hinten rechts unten

		-1.0f, 1.0f, 1.0f,	0.0f, 1.0f,		//4 Vorne links oben
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,		//5 Vorne links unten
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,		//6 Vorne rechts oben
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f		//7 Vorne rechts unten
	};
	unsigned int indices[]{
		//Hinten
		0,1,2,
		1,2,3,
		//Vorne
		4,5,6,
		5,6,7,
		//Unten
		5,1,3,
		3,7,5,
		//Links
		1,5,0,
		5,4,0,
		//Oben
		4,0,2,
		2,4,6,
		//Rechts
		6,7,3,
		3,2,6
	};

	//for (int i = 0; i < 2; i++) {
	//	Spawned_Cube first_cube = Spawned_Cube();

	//	BKA_Object_Builder* first_spawned_cube = new BKA_Object_Builder();
	//	first_spawned_cube->create_bka_objects(vertices, indices, sizeof(vertices), sizeof(indices));
	//	spawned_objects.push_back(first_spawned_cube);

	//	first_cube.set_cube_object(first_spawned_cube);
	//	first_cube = set_cube_values(first_cube);

	//	actual_cubes.push_back(first_cube);
	//}

	Spawned_Cube* first_cube = new Spawned_Cube();

	BKA_Object_Builder* first_spawned_cube = new BKA_Object_Builder();
	first_spawned_cube->create_bka_objects(vertices, indices, sizeof(vertices), sizeof(indices));
	spawned_objects.push_back(first_spawned_cube);

	first_cube->set_cube_object(first_spawned_cube);
	set_cube_values(first_cube);

	actual_cubes->push_back(first_cube); 

	Spawned_Cube* second_cube = new Spawned_Cube();

	BKA_Object_Builder* second_spawned_cube = new BKA_Object_Builder();
	second_spawned_cube->create_bka_objects(vertices, indices, sizeof(vertices), sizeof(indices));
	spawned_objects.push_back(second_spawned_cube);

	second_cube->set_cube_object(first_spawned_cube);
	set_cube_values(second_cube);

	actual_cubes->push_back(second_cube);

	create_material();

	return spawned_objects;
}

auto get_random_int(int left_bound, int right_bound) {
	static std::random_device r;
	static std::default_random_engine e1(r());
	static std::uniform_int_distribution<int> uniform_dist(left_bound, right_bound);
	return uniform_dist(e1);
}

float get_random_float(int left_bound, int right_bound) {
	static std::random_device r;
	static std::default_random_engine e1(r());
	static std::uniform_real_distribution<float> uniform_dist(left_bound, right_bound);
	return uniform_dist(e1);
}

void Item_Spawner::set_cube_values(Spawned_Cube* cube) {
	Item item;
	int left_bound = 0;
	int randValue = get_random_int(left_bound, 9);
	GLfloat cube_colour[4];
	if (randValue < 5) {
		item.name = "first_type";
		item.color = { 1.0f, 0.25f, 0.65f, 1.0f };
	}
	else {
		item.name = "second_type";
		item.color = { 0.5f, 1.0f, 0.35f, 1.0f };
	}

	cube->set_item(item);

	static std::uniform_real_distribution<> uniform_dist_fl(0, 3);
	int right_bound_trans = 3;
	glm::vec3 trans = glm::vec3(get_random_float(left_bound, right_bound_trans), get_random_float(left_bound, right_bound_trans), get_random_float(left_bound, right_bound_trans));
	glm::vec3 scale = glm::vec3(get_random_float(left_bound, 1)/2);
	cube->set_scale(scale);
	cube->set_translate(trans);
}

void Item_Spawner::render_spawned_cubes(glm::mat4 view_matrix, glm::mat4 projection_matrix) {
	spawned_cube_material->use_default_material();
	uniform_model = spawned_cube_material->get_uniform_model();
	uniform_view = spawned_cube_material->get_uniform_view();
	uniform_projection = spawned_cube_material->get_uniform_projection();
	uniform_cube_colour = spawned_cube_material->get_uniform_cube_colour();

	glm::mat4 model(1.0f);

	for (int i = 0; i < actual_cubes->size(); i++) {
		Spawned_Cube* actual_cube = actual_cubes->at(i);
		std::array<float, 4> color = actual_cube->get_item().color;
		GLfloat cube_colour[4] = { color[0], color[1], color[2], color[3] };

		model = glm::mat4(1.0f);
		model = glm::translate(model, actual_cube->get_translate());  
		model = glm::rotate(model, glm::radians(bka_utils.simple_rotation()), glm::vec3(-0.125f, 1.0f, -1.0f));
		model = glm::scale(model, actual_cube->get_scale()); 
		actual_cube->set_model_matrix(model);
		glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));
		glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4fv(uniform_cube_colour, 1, cube_colour);
		BKA_Object_Builder* cube = actual_cube->get_cube_object();
		cube->render_bka_objects();
		//actual_cubes->erase(actual_cubes->begin() + i);
		//actual_cubes->insert(actual_cubes->begin() + i, actual_cube);
		
		//updated_cubes.push_back(actual_cube);
	}
	//actual_cubes = updated_cubes;
	spawned_cube_material->unload_default_material();
}

std::vector<Spawned_Cube*>* Item_Spawner::get_cubes() {
	return actual_cubes;
}