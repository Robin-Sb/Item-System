#include "Spawned_Cube.h"

int _id = 0;

Spawned_Cube::Spawned_Cube() {
	object = 0;
	item = Item();
	translate = glm::vec4(0);
	scale = glm::vec4(1);
	id = _id;
	_id++;
}

void Spawned_Cube::set_cube_object(BKA_Object_Builder* cube_object) {
	object = cube_object;
};

void Spawned_Cube::set_item(Item _item) {
	item = _item;
}

void Spawned_Cube::set_scale(glm::vec3 _scale) {
	scale = _scale;
}

void Spawned_Cube::set_translate(glm::vec3 _translate) {
	translate = _translate;
}

void Spawned_Cube::set_model_matrix(glm::mat4 _model_matrix) {
	model_matrix = _model_matrix;
}

void Spawned_Cube::set_rotate(glm::f32 _angle, glm::vec3 _rotate) {
	rotate = _rotate;
	angle = _angle;
}

glm::f32 Spawned_Cube::get_angle() {
	return angle;
}

glm::vec3 Spawned_Cube::get_rotate() {
	return rotate;
}

glm::mat4 Spawned_Cube::get_model_matrix() {
	return model_matrix;
}
glm::vec3 Spawned_Cube::get_scale() {
	return scale;
}

glm::vec3 Spawned_Cube::get_translate() {
	return translate;
}

Item Spawned_Cube::get_item() {
	return item;
}

BKA_Object_Builder* Spawned_Cube::get_cube_object() {
	return object;
}

int Spawned_Cube::get_id() {
	return id;
}