#include "BKA_Light_Builder.h"

BKA_Light_Builder::BKA_Light_Builder() {
	light_ambient_color = glm::vec3(1.0f, 0.5f, 0.25f);
	light_ambient_intensity = 0.5f;
}

BKA_Light_Builder::BKA_Light_Builder(glm::vec3 ambient_light_color, GLfloat ambient_light_intensity) {
	light_ambient_color = ambient_light_color;
	light_ambient_intensity = ambient_light_intensity;
}

void BKA_Light_Builder::activate_scene_light(GLfloat ambient_light_color_location, GLfloat ambient_light_intensity_location) {
	glUniform3f(ambient_light_color_location, light_ambient_color.x, light_ambient_color.y, light_ambient_color.z);
	glUniform1f(ambient_light_intensity_location, light_ambient_intensity);
}