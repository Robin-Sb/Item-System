#pragma once
#include <GL/glew.h>


class BKA_Object_Builder {
public:
	BKA_Object_Builder();

	void create_bka_objects(GLfloat* vertices, unsigned int* indicies, unsigned int count_vertices, unsigned int count_indicies);

	void render_bka_objects();

	void delete_bka_objects();

	~BKA_Object_Builder();

private:
	GLuint obj_vao;
	GLuint obj_vbo;
	GLuint obj_ibo;

	GLsizei indicies_count;
};
