#pragma once

#include <GL/glew.h>
#include "stb_image.h"


class BKA_Texture_Sampler {
public: 
	bool load_texture();
	void use_texture();
	void delete_texture();
	BKA_Texture_Sampler(const char* tex_file_loc);
	BKA_Texture_Sampler();
private:
	GLuint texture_handle;
	int texture_width, texture_height, texture_bitdepth;
	const char* texture_file_location;
};