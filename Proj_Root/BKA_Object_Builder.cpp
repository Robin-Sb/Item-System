#include <stdio.h>
#include "BKA_Object_Builder.h"

BKA_Object_Builder::BKA_Object_Builder () {
	obj_vao = 0;
	obj_vbo = 0;
	obj_ibo = 0;
	indicies_count = 0;
}

void BKA_Object_Builder::create_bka_objects(GLfloat* vertices, unsigned int* indicies, unsigned int count_vertices, unsigned int count_indicies) {
	indicies_count = count_indicies;
	glGenVertexArrays(1, &obj_vao);
	glBindVertexArray(obj_vao);

	glGenBuffers(1, &obj_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies[0]) * count_indicies, indicies, GL_STATIC_DRAW);

	glGenBuffers(1, &obj_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, obj_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indicies[0]) * count_indicies, vertices, GL_STATIC_DRAW);
		
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BKA_Object_Builder::render_bka_objects() {
	glBindVertexArray(obj_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj_ibo);
	glDrawElements(GL_TRIANGLES_ADJACENCY, indicies_count, GL_UNSIGNED_SHORT, 0);

	// unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BKA_Object_Builder::delete_bka_objects() {
	if (obj_ibo != 0) {
		glDeleteBuffers(1, &obj_ibo);
		obj_ibo = 0;
	}

	if (obj_vbo != 0) {
		glDeleteBuffers(1, &obj_vbo);
		obj_vbo = 0;
	}

	if (obj_vao != 0) {
		glDeleteBuffers(1, &obj_vao);
		obj_vao = 0;
	}

	indicies_count = 0;
}

BKA_Object_Builder::~BKA_Object_Builder() {
	delete_bka_objects();
}