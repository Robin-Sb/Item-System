#pragma once
#include <GL/glew.h>
#include <GLM/glm.hpp>

class BKA_Light_Builder {
public:
	BKA_Light_Builder(glm::vec3 ambient_light_color, GLfloat ambient_light_intensity);
	void activate_scene_light(GLfloat ambient_light_color_location, GLfloat ambient_light_intensity_location);
	BKA_Light_Builder();
private:
	glm::vec3 light_ambient_color;
	GLfloat light_ambient_intensity;
};