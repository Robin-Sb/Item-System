#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>

class BKA_Material_Builder {
public: 
	BKA_Material_Builder();

	void use_default_material();

	void unload_default_material();

	void destroy_default_material();

	void create_default_material_from_file(const char* vertex_shader_location, const char* fragment_shader_location);

	std::string read_shader_file(const char* shader_file_location);

	GLuint get_uniform_ambient_light_color();
	GLuint get_uniform_ambient_light_intensity();
	GLuint get_uniform_model();
	GLuint get_uniform_view();
	GLuint get_uniform_projection();
	GLuint get_uniform_cube_colour();

private:
	GLuint default_bka_material;
	GLuint uniform_model;
	GLuint uniform_projection;
	GLuint uniform_view;
	GLuint uniform_ambient_light_color;
	GLuint uniform_ambient_light_intensity;
	GLuint uniform_cube_colour;

	void compile_default_bka_shader(const char* default_vertex_shader, const char* default_pixel_shader);

	void add_default_shader(GLuint default_material_builder, const char* default_shader_code, GLenum default_shader_type);
};
