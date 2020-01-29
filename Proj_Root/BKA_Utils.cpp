#include "BKA_Utils.h"
#include <cmath>
#include <GLFW/glfw3.h>

BKA_Utils::BKA_Utils() {
	direction = true;
	object_max_offset = 1.0f;
	object_offset = 0.0f;
	object_speed = 0.05f;
	rotation_speed = 0.5f;
	delta_time = 0;
	last_time_step = 0;
}

float BKA_Utils::simple_movement() {

	if (direction) {

		object_offset += object_speed;
	}
	else {

		object_offset -= object_speed;
	}

	if (abs(object_offset) >= object_max_offset) {

		direction = !direction;
	}

	return object_offset;
}

float BKA_Utils::simple_rotation() {
	rotation_speed += 0.5;
	if (rotation_speed >= 360) {
		rotation_speed = 0.5f;
	}
	return rotation_speed;
}

GLfloat BKA_Utils::get_delta_time() {
	GLfloat time_step_now = glfwGetTime();
	delta_time = time_step_now - last_time_step;
	last_time_step = time_step_now;

	return delta_time;
}

BKA_Utils::~BKA_Utils() {

}