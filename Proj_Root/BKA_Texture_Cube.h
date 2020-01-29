#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include "stb_image.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "BKA_Material_Builder.h"
#include "BKA_Utils.h"
#include "BKA_Light_Builder.h"

class BKA_Texture_Cube
{
public:
	BKA_Texture_Cube();

	BKA_Texture_Cube(std::vector<std::string> polygon_locations);

	void use_cube_texture(glm::mat4 view_matrix, glm::mat4 projection_matrix);

	void unload_cube_texture();

	~BKA_Texture_Cube();

private:

	BKA_Material_Builder* cube_material;

	GLuint cube_texture_handle;
	GLuint uniform_projection;
	GLuint uniform_view;
	GLuint uniform_model;
	GLuint uniform_ambient_light_color;
	GLuint uniform_ambient_light_intensity;
};