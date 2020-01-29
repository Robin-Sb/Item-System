#pragma once
#define GLM_FORCE_CTOR_INIT

#include <stdio.h>
#include <vector>
#include "BKA_Texture_CubeMap.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "BKA_Window.h"
#include "BKA_Camera_Builder.h"
#include "BKA_Texture_Sampler.h"
#include "BKA_Texture_Cube.h"
#include "Inventory_Sampler.h"
#include "Item_Spawner.h"
#include "BKA_Material_Builder.h"



BKA_Window main_window;
BKA_Utils bka_standard_utils;
BKA_Camera_Builder main_camera;

BKA_Texture_CubeMap dome;
BKA_Texture_Sampler default_texture;
BKA_Texture_Cube material_cube_01;

std::vector<BKA_Object_Builder*> list_bka_objects;
std::vector<BKA_Material_Builder> list_bka_materials;

Item_Spawner spawner;
Ray_Caster ray_caster;

const char* vertex_shader = "Shader_Root/shader.vertex";
const char* fragment_shader = "Shader_Root/shader.fragment";


BKA_Object_Builder* create_bka_default_object() {
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
	BKA_Object_Builder* bka_default_cube_01 = new BKA_Object_Builder();
	bka_default_cube_01->create_bka_objects(vertices, indices, sizeof(vertices), sizeof(indices));
	return bka_default_cube_01;
}

BKA_Material_Builder* create_material() {
	BKA_Material_Builder* cube_material = new BKA_Material_Builder();
	cube_material->create_default_material_from_file("Shader_Root/os_shader.vertex", "Shader_Root/os_shader.fragment");
	return cube_material;
}

std::vector<std::string> get_dome_polygons () {
	std::vector<std::string> dome_polygons;
	dome_polygons.push_back("Texture_Root/CubeMap/peaks_lf.tga");
	dome_polygons.push_back("Texture_Root/CubeMap/peaks_rt.tga");
	dome_polygons.push_back("Texture_Root/CubeMap/peaks_up.tga");
	dome_polygons.push_back("Texture_Root/CubeMap/peaks_dn.tga");
	dome_polygons.push_back("Texture_Root/CubeMap/peaks_bk.tga");
	dome_polygons.push_back("Texture_Root/CubeMap/peaks_ft.tga");
	return dome_polygons;
}

void drawItems() {
	glm::mat4 ortho = glm::ortho(-(GLfloat)main_window.getbufferwidth() / 2, (GLfloat)main_window.getbufferwidth() / 2, (GLfloat)main_window.getbufferheight() / 2, -(GLfloat)main_window.getbufferheight() / 2, 0.1f, 150.0f);

	BKA_Material_Builder* cube_material = create_material();
	cube_material->use_default_material();
	GLfloat uniform_model = cube_material->get_uniform_model();
	GLfloat uniform_view = cube_material->get_uniform_view();
	GLfloat uniform_projection = cube_material->get_uniform_projection();
	GLfloat uniform_cube_colour = cube_material->get_uniform_cube_colour();

	vector<Item> items = inventory.get_all_items();
	glm::mat4 model(1.0f);

	float base_transform_width = -(main_window.getbufferwidth() / 2 - main_window.getbufferwidth() / 10);
	float transform_bonus = 0.0;

	for (int i = 0; i < items.size(); i++) {
		Item this_item = items[i];
		std::array<float,4> color = this_item.color;
		GLfloat cube_colour[4] = { color[0], color[1], color[2], color[3] };

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(base_transform_width + transform_bonus, main_window.getbufferheight()/2 - main_window.getbufferheight()/8, 0.0));
		transform_bonus += main_window.getbufferwidth() / 8;
		model = glm::scale(model, glm::vec3(50.0, 50.0, 1.0));
		glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(ortho));
		glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4fv(uniform_cube_colour, 1, cube_colour);
		create_bka_default_object()->render_bka_objects();
	}
}

void draw_HUD() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);

	drawItems();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

int main() {
	main_window = BKA_Window(1024, 768);
	main_window.bka_window_init();
	spawner.spawn_items();
	main_camera = BKA_Camera_Builder(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 1.0f, 0.08f);
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)main_window.getbufferwidth() / (GLfloat)main_window.getbufferheight(), 0.1f, 150.0f);
	ray_caster.set_projection_matrix(projection);
	default_texture = BKA_Texture_Sampler("Texture_Root/factory_wall_diff_4k.jpg");
	default_texture.load_texture();
	dome = BKA_Texture_CubeMap(get_dome_polygons());


	while (!main_window.bka_window_close()) {
		glfwPollEvents();
		glfwSetInputMode(main_window.get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		GLfloat delta_time = bka_standard_utils.get_delta_time();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);

		glm::mat4 view_matrix = main_camera.calculate_view_matrix();

		dome.draw_dome(view_matrix, projection);
		spawner.render_spawned_cubes(view_matrix, projection);

		ray_caster.set_view_matrix(view_matrix);
		ray_caster.set_ray_origin(main_camera.get_camera_position());
		ray_caster.set_cubes(spawner.get_cubes());
		main_window.set_ray_caster(ray_caster);

		main_camera.interaction_keyboard(main_window.get_keys(), delta_time);
		main_camera.interaction_mouse(main_window.get_movement_x(), main_window.get_movement_y());

		draw_HUD();
		glfwSetInputMode(main_window.get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		main_window.bka_window_doublebuffering();
	}
}