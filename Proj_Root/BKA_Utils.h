#pragma once
#include <GL/glew.h>

class BKA_Utils
{
public:
	BKA_Utils();

	float simple_movement();

	float simple_rotation();

	float simple_scaling();

	GLfloat get_delta_time();

	~BKA_Utils();

private:

	bool direction;
	float object_offset;
	float object_max_offset;
	float object_speed;
	float rotation_speed;
	GLfloat delta_time;
	GLfloat last_time_step;
};