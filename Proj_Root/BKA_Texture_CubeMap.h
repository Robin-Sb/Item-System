#pragma once
#include <vector>
#include <string>
#include <GL/glew.h>
#include "stb_image.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "BKA_Object_Builder.h"
#include "BKA_Material_Builder.h"

class BKA_Texture_CubeMap {
public:
	BKA_Texture_CubeMap();

	BKA_Texture_CubeMap(std::vector<std::string> polygon_locations);

	void draw_dome(glm::mat4 view_matrix, glm::mat4 projection_matrix);

	~BKA_Texture_CubeMap();
private:
	BKA_Object_Builder* dome_mesh;
	BKA_Material_Builder* dome_material;

	GLuint dome_texture_handle;
	GLuint uniform_projection;
	GLuint uniform_view;
};