#pragma once
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class BKA_Camera_Builder {
private:
	glm::vec3 camera_position;
	glm::vec3 front_direction;
	glm::vec3 right_direction;
	glm::vec3 up_direction;
	glm::vec3 world_up_direction;

	GLfloat yaw;
	GLfloat pitch;
	GLfloat speed_movement;
	GLfloat speed_turning;
	GLfloat rotation_angle;
	GLfloat camera_path_radius;

	void update_values();

public: 
	BKA_Camera_Builder();
	BKA_Camera_Builder(glm::vec3 initial_camera_position, glm::vec3 initial_up_direction, GLfloat initial_yaw, GLfloat initial_pitch, GLfloat initial_speed_movement, GLfloat initial_speed_turn);

	void interaction_keyboard(bool* keys, GLfloat delta_time);
	void interaction_mouse(GLfloat change_x_position, GLfloat change_y_position);

	glm::mat4 calculate_view_matrix();
	glm::vec3 get_camera_position();
};