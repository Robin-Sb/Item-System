#pragma once
#include "BKA_Texture_Cube.h"

BKA_Utils bka_utils;

BKA_Texture_Cube::BKA_Texture_Cube()
{
	cube_texture_handle = 0;
	uniform_projection = 0;
	uniform_model = 0;
	uniform_view = 0;
	uniform_ambient_light_color = 0;
	uniform_ambient_light_intensity = 0;
}

BKA_Texture_Cube::BKA_Texture_Cube(std::vector<std::string> polygon_locations)
{
	////BKA_Light_Builder scene_sunlight;
	////scene_sunlight = BKA_Light_Builder(glm::vec3(0.35f, 0.6f, 1.0f), 0.375f);
	cube_material = new BKA_Material_Builder();
	cube_material->create_default_material_from_file("Shader_Root/Cubemap/Cube/bka_cube.vertex", "Shader_Root/Cubemap/Cube/bka_cube.fragment");

	uniform_projection = cube_material->get_uniform_projection();
	uniform_view = cube_material->get_uniform_view();
	uniform_model = cube_material->get_uniform_model();

	//uniform_ambient_light_color = cube_material->get_uniform_ambient_light_color();
	//uniform_ambient_light_intensity = cube_material->get_uniform_ambient_light_intensity();

	glGenTextures(1, &cube_texture_handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_texture_handle);

	GLint cube_texture_width, cube_texture_height, cube_texture_bitdepth;

	for (size_t i = 0; i < 6; i++) {
		unsigned char* texture_data = stbi_load(polygon_locations[i].c_str(), &cube_texture_width, &cube_texture_height, &cube_texture_bitdepth, 0);
		if (!texture_data) {

			printf("Keine Texturdaten vorhanden. %s/n wurde nicht gefunden.", polygon_locations[i].c_str());
			return;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, cube_texture_width, cube_texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		stbi_image_free(texture_data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void BKA_Texture_Cube::use_cube_texture(glm::mat4 view_matrix, glm::mat4 projection_matrix) {
	cube_material->use_default_material();

	glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));
	glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(view_matrix));

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(bka_utils.simple_rotation()), glm::vec3(-0.125f, 1.0f, -1.0f));
	model = glm::scale(model, glm::vec3(0.25f));
	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

	//model = glm::mat4();
	//model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 0));
	//model = glm::rotate(model, glm::radians(bka_standard_utils.simple_rotation()), glm::vec3(-0.125f, 1.0f, -1.0f));
	//model = glm::scale(model, glm::vec3(0.2f));
	//glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
	//list_bka_objects[1]->render_bka_objects();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_texture_handle);
}

void BKA_Texture_Cube::unload_cube_texture() {

	cube_material->unload_default_material();
}

BKA_Texture_Cube::~BKA_Texture_Cube() {

}