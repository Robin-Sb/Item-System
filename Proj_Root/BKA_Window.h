#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Ray_Caster.h"


class BKA_Window
{
public:
	BKA_Window();
	BKA_Window(GLuint bka_w_width, GLuint bka_w_height);

	int bka_window_init();

	void bka_window_doublebuffering() { glfwSwapBuffers(bka_main_window); }

	bool bka_window_close() { return glfwWindowShouldClose(bka_main_window); }
	~BKA_Window();

	bool* get_keys() { return keys; };

	GLfloat get_movement_x();
	GLfloat get_movement_y();

	GLint getbufferwidth() { return bka_window_buffer_width; }
	GLint getbufferheight() { return bka_window_buffer_height; }

	void set_ray_caster(Ray_Caster ray_caster);

	Ray_Caster get_ray_caster();

	GLFWwindow* get_glfw_window();

private:
	GLuint bka_window_width;
	GLuint bka_window_height;
	GLint bka_window_buffer_width;
	GLint bka_window_buffer_height;

	bool keys[1024];
	GLfloat last_x_position;
	GLfloat last_y_position;
	GLfloat x_position_change;
	GLfloat y_position_change;
	bool mouse_first_movement;

	Ray_Caster ray_caster;

	void create_bka_callbacks();
	static void listener_keys_events(GLFWwindow* window, int key, int code, int action, int mode);
	static void listener_mouse_events(GLFWwindow* window, double new_position_x, double new_position_y);
	static void listener_mouse_clicks(GLFWwindow* window, int button, int action, int mods);

	GLFWwindow* bka_main_window;
};

void listener_keys_events(GLFWwindow* window, int key, int code, int action, int mode);
