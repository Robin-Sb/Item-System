#include "BKA_Window.h"
#include <stdio.h>
#include "Inventory_Sampler.h "

BKA_Window::BKA_Window()
{
	bka_window_buffer_height = 0;
	bka_window_buffer_width = 0;
	bka_window_height = 1024;
	bka_window_width = 768;

	x_position_change = 0.0f;
	y_position_change = 0.0f;
	mouse_first_movement = true;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
	last_x_position = 0.0;
	last_y_position = 0.0;
	x_position_change = 0.0;
	y_position_change = 0.0;
}



BKA_Window::BKA_Window(GLuint bka_w_width, GLuint bka_w_height)
{
	bka_window_width = bka_w_width;
	bka_window_height = bka_w_height;
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
	last_x_position = 0.0;
	last_y_position = 0.0;
	x_position_change = 0.0;
	y_position_change = 0.0;
}

int BKA_Window::bka_window_init() {
	if (!glfwInit()) {
		printf("GLFW not initialised");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 6);

	bka_main_window = glfwCreateWindow(bka_window_width, bka_window_height, "BKA_Window", NULL, NULL);

	glfwGetFramebufferSize(bka_main_window, &bka_window_buffer_width, &bka_window_buffer_height);
	create_bka_callbacks();
	//glfwSetInputMode(bka_main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = true;
	glfwMakeContextCurrent(bka_main_window);

	if (glewInit() != GLEW_OK) {
		printf("GLEW not initialised");
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, bka_window_width, bka_window_height);
	glfwSetWindowUserPointer(bka_main_window, this);
	return 0;
}

GLfloat BKA_Window::get_movement_x() {
	GLfloat actual_change = x_position_change;
	x_position_change = 0.0f;
	return actual_change;
}

GLfloat BKA_Window::get_movement_y() {
	GLfloat actual_change = y_position_change;
	y_position_change = 0.0f;
	return actual_change;
}


void BKA_Window::listener_keys_events(GLFWwindow* window, int key, int code, int action, int mode) {
	BKA_Window* actual_window = static_cast<BKA_Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			actual_window->keys[key] = true;
			printf("Pressed Key: %d\n", key);

			int key_value = -1;
			bool valid_key = false;

			switch (key) {
			case GLFW_KEY_1:
				key_value = 0;
				valid_key = true;
				break;
			case GLFW_KEY_2:
				key_value = 1;
				valid_key = true;
				break;
			case GLFW_KEY_3:
				key_value = 2;
				valid_key = true;
				break;
			case GLFW_KEY_4:
				key_value = 3;
				valid_key = true;
				break;
			case GLFW_KEY_5:
				key_value = 4;
				valid_key = true;
				break;
			case GLFW_KEY_6:
				key_value = 5;
				valid_key = true;
				break;
			case GLFW_KEY_7:
				key_value = 6;
				valid_key = true;
				break;
			case GLFW_KEY_8:
				key_value = 7;
				valid_key = true;
				break;
			}
			if (valid_key)
				inventory.delete_item(key_value);
		}
		else if (action == GLFW_RELEASE)
		{
			actual_window->keys[key] = false;
			printf("Released Key: %d\n", key);
		}
	}
}

void BKA_Window::listener_mouse_events(GLFWwindow* window, double new_position_x, double new_position_y) {
	BKA_Window* actual_window = static_cast<BKA_Window*>(glfwGetWindowUserPointer(window));

	if (actual_window->mouse_first_movement) {
		actual_window->last_x_position = new_position_x;
		actual_window->last_y_position = new_position_y;
		actual_window->mouse_first_movement = false;
	}

	actual_window->x_position_change = new_position_x - actual_window->last_x_position;
	actual_window->y_position_change = actual_window->last_y_position - new_position_y;

	actual_window->last_x_position = new_position_x;
	actual_window->last_y_position = new_position_y;

	printf("Change X:%.2f, Change Y:%.2f\n", actual_window->x_position_change, actual_window->y_position_change);
}

void BKA_Window::listener_mouse_clicks(GLFWwindow* window, int button, int action, int mods) {
	BKA_Window* actual_window = static_cast<BKA_Window*>(glfwGetWindowUserPointer(window));
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		Ray_Caster caster = actual_window->get_ray_caster();
		int cube_index = caster.cast_ray(xpos, ypos, actual_window->bka_window_width, actual_window->bka_window_height);
		vector<Spawned_Cube*>* cubes = caster.get_cubes();
		if (cube_index != -1) {
			inventory.add_item(cubes->at(cube_index)->get_item());
			cubes->erase(cubes->begin() + cube_index);
		}
	}
}

void BKA_Window::create_bka_callbacks() {
	glfwSetKeyCallback(bka_main_window, listener_keys_events);
	glfwSetCursorPosCallback(bka_main_window, listener_mouse_events);
	glfwSetMouseButtonCallback(bka_main_window, listener_mouse_clicks);
}

GLFWwindow* BKA_Window::get_glfw_window() {
	return bka_main_window;
}


Ray_Caster BKA_Window::get_ray_caster() {
	return ray_caster;
}

void BKA_Window::set_ray_caster(Ray_Caster _ray_caster) {
	ray_caster = _ray_caster;
}


BKA_Window::~BKA_Window() {
	glfwTerminate();
}
