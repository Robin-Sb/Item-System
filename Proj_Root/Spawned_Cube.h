#pragma once
#include "BKA_Object_Builder.h"
#include "Item.h"
#include <GLM/glm.hpp>

class Spawned_Cube {
public:
	Spawned_Cube();

	void set_cube_object(BKA_Object_Builder* cube_object);
	void set_item(Item _item);
	void set_scale(glm::vec3 _scale);
	void set_translate(glm::vec3 _translate);
	void set_model_matrix(glm::mat4 _model_matrix);
	void set_rotate(glm::f32 _angle, glm::vec3 _rotate);
	Item get_item();
	glm::mat4 get_model_matrix();
	glm::vec3 get_scale();
	glm::vec3 get_translate();
	glm::vec3 get_rotate();
	glm::f32 get_angle();
	BKA_Object_Builder* get_cube_object();
	int get_id();

private:
	BKA_Object_Builder* object;
	Item item;
	glm::vec3 translate;
	glm::vec3 scale;
	glm::vec3 rotate;
	glm::f32 angle;
	glm::mat4 model_matrix;
	int id;
};