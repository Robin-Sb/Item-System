#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "BKA_Texture_CubeMap.h"

BKA_Texture_CubeMap::BKA_Texture_CubeMap() {
	dome_texture_handle = 0;
	uniform_projection = 0;
	uniform_view = 0;
}

BKA_Texture_CubeMap::BKA_Texture_CubeMap(std::vector<std::string> polygon_locations) {
	dome_material = new BKA_Material_Builder();
	dome_material->create_default_material_from_file("Shader_Root/Cubemap/bka_cubemap.vertex", "Shader_Root/Cubemap/bka_cubemap.fragment");
	uniform_projection = dome_material->get_uniform_projection();
	uniform_view = dome_material->get_uniform_view();
	glGenTextures(1, &dome_texture_handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, dome_texture_handle);
	GLint cubemap_texture_width, cubemap_texture_height, cubemap_texture_bitdepth;

	for (size_t i = 0; i < 6; i++) {
		unsigned char* texture_data = stbi_load(polygon_locations[i].c_str(), &cubemap_texture_width, &cubemap_texture_height, &cubemap_texture_bitdepth, 0);
		if (!texture_data) {

			printf("Keine Texturdaten vorhanden. %s/n wurde nicht gefunden.", polygon_locations[i].c_str());
			return;
		}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, cubemap_texture_width, cubemap_texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
	stbi_image_free(texture_data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned int dome_indices[]{
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

	GLfloat dome_vertices[] = {

	 -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,	//0 Hinten links oben
	  -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,	//1 Hinten links unten
	  1.0f, 1.0f, -1.0f, 1.0f, 1.0f,	//2 Hinten rechts oben
	  1.0f, -1.0f, -1.0f, 1.0f, 0.0f,	//3 Hinten rechts unten

	 -1.0f, 1.0f, 1.0f,	0.0f, 1.0f,		//4 Vorne links oben
	  -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,	//5 Vorne links unten
	  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,		//6 Vorne rechts oben
	  1.0f, -1.0f, 1.0f, 1.0f, 0.0f		//7 Vorne rechts unten
	};

	dome_mesh = new BKA_Object_Builder();
	dome_mesh->create_bka_objects(dome_vertices, dome_indices, sizeof(dome_vertices), sizeof(dome_indices));
}

void BKA_Texture_CubeMap::draw_dome(glm::mat4 view_matrix, glm::mat4 projection_matrix) {
	view_matrix = glm::mat4(glm::mat3(view_matrix));
	glDepthMask(GL_FALSE);
	dome_material->use_default_material();

	glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));
	glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(view_matrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, dome_texture_handle);

	dome_mesh->render_bka_objects();

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDepthMask(GL_TRUE);
}

BKA_Texture_CubeMap::~BKA_Texture_CubeMap() {};
