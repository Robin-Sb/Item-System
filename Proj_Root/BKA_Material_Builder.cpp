#include "BKA_Material_Builder.h"

BKA_Material_Builder::BKA_Material_Builder() {
	default_bka_material = 0;
	uniform_model = 0;
	uniform_projection = 0;
	uniform_view = 0;
	uniform_ambient_light_color = 0;
	uniform_ambient_light_intensity = 0;
	uniform_cube_colour = 0;
};

std::string BKA_Material_Builder::read_shader_file(const char* shader_file_location) {
	std::string shader_file_content;
	std::ifstream file_stream(shader_file_location, std::ios::in);

	if (!file_stream.is_open()) {

		printf("Fehler beim Lesen der Datei %s. Datei nicht vorhanden!\n", shader_file_location);
		return "";
	}

	std::string content_line = "";
	while (!file_stream.eof()) {
		std::getline(file_stream, content_line);
		shader_file_content.append(content_line + "\n");
	}
	file_stream.close();
	return shader_file_content;
}

void BKA_Material_Builder::create_default_material_from_file(const char* vertex_shader_location, const char* fragment_shader_location) {
	std::string string_vertex_shader = read_shader_file(vertex_shader_location);
	std::string string_fragment_shader = read_shader_file(fragment_shader_location);

	const char* vertex_Code = string_vertex_shader.c_str();
	const char* fragment_Code = string_fragment_shader.c_str();

	compile_default_bka_shader(vertex_Code, fragment_Code);
}

void BKA_Material_Builder::add_default_shader(GLuint default_material_builder, const char* default_shader_code, GLenum default_shader_type) {
	GLuint default_shader = glCreateShader(default_shader_type);

	const GLchar* plain_default_code[1];
	plain_default_code[0] = default_shader_code;

	GLint default_code_length[1];
	default_code_length[0] = strlen(default_shader_code);

	glShaderSource(default_shader, 1, plain_default_code, default_code_length);
	glCompileShader(default_shader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glGetShaderiv(default_shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(default_shader, sizeof(eLog), NULL, eLog);
		printf("Fehler bei der Kompilierung der Shader!");
		return;
	}

	glAttachShader(default_material_builder, default_shader);

	return;
}

void BKA_Material_Builder::compile_default_bka_shader(const char* default_vertex_shader, const char* default_pixel_shader) {
	default_bka_material = glCreateProgram();

	if (!default_bka_material) {
		printf("Erstellung des Shader Programms fehlgeschlagen!\n");
		return;
	}

	add_default_shader(default_bka_material, default_vertex_shader, GL_VERTEX_SHADER);
	add_default_shader(default_bka_material, default_pixel_shader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(default_bka_material);
	glGetProgramiv(default_bka_material, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(default_bka_material, sizeof(eLog), NULL, eLog);
		printf("Fehler beim Linking des Shader Programms!\n");
		return;
	}

	glValidateProgram(default_bka_material);
	glGetProgramiv(default_bka_material, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(default_bka_material, sizeof(eLog), NULL, eLog);
		printf("Fehler bei der Validierung des Shader Programms!");
		return;
	}
	uniform_projection = glGetUniformLocation(default_bka_material, "projection");
	uniform_view = glGetUniformLocation(default_bka_material, "view");
	uniform_model = glGetUniformLocation(default_bka_material, "model");
	uniform_ambient_light_color = glGetUniformLocation(default_bka_material, "sun_light.ambient_light_color");
	uniform_ambient_light_intensity = glGetUniformLocation(default_bka_material, "sun_light.ambient_light_intensity");
	uniform_cube_colour = glGetUniformLocation(default_bka_material, "cube_colour");
}

GLuint BKA_Material_Builder::get_uniform_model() {
	return uniform_model;
}
GLuint BKA_Material_Builder::get_uniform_view() {
	return uniform_view;
}

GLuint BKA_Material_Builder::get_uniform_projection() {
	return uniform_projection;
}

GLuint BKA_Material_Builder::get_uniform_ambient_light_color() {

	return uniform_ambient_light_color;
}

GLuint BKA_Material_Builder::get_uniform_ambient_light_intensity() {

	return uniform_ambient_light_intensity;
}

GLuint BKA_Material_Builder::get_uniform_cube_colour() {
	return uniform_cube_colour;
}

void BKA_Material_Builder::use_default_material() {
	glUseProgram(default_bka_material);
}

void BKA_Material_Builder::unload_default_material() {
	glUseProgram(0);
}

void BKA_Material_Builder::destroy_default_material() {
	if (default_bka_material != 0) {
		glDeleteProgram(default_bka_material);
		default_bka_material = 0;
	}
	uniform_projection = 0;
	uniform_view = 0;
	uniform_ambient_light_color = 0;
	uniform_ambient_light_intensity = 0;
	uniform_cube_colour = 0;
}