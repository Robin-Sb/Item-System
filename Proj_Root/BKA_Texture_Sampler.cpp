#include "BKA_Texture_Sampler.h"

BKA_Texture_Sampler::BKA_Texture_Sampler() {
	texture_bitdepth = 0;
	texture_file_location = "";
	texture_height = 0;
	texture_width = 0;
	texture_handle = 0;
}

BKA_Texture_Sampler::BKA_Texture_Sampler(const char* tex_file_loc) {
	texture_file_location = tex_file_loc;
}

bool BKA_Texture_Sampler::load_texture() {
	unsigned char* texture_data = stbi_load(texture_file_location, &texture_width, &texture_height, &texture_bitdepth, 0);

	if (!texture_data) {
		printf("Keine Texturdaten vorhanden. %s/n wurde nicht gefunden.", texture_file_location);
		return false;
	}

	glGenTextures(1, &texture_handle);
	glBindTexture(GL_TEXTURE_2D, texture_handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texture_data);

	return true;
}

void BKA_Texture_Sampler::use_texture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_handle);
}