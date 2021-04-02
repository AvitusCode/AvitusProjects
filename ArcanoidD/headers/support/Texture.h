#pragma once
#include "glut.h"
#include <memory>

enum tex_name
{
	DEFAULT_TEX,
	TEX_1,
	TEX_2
};

class Texture
{
public:
	Texture(const char *file) : file_name(file) {
		id = get_tga_file(file_name);
	};
	
	GLuint getId() const {
		return id;
	}
	const char *getTexFile() const {
		return file_name;
	}

	~Texture(){
		if (id != 0)
			glDeleteTextures(1, &id);
	}
private:
	GLuint id = 0;
	const char *file_name;
	GLuint get_tga_file(char const *file);
};

std::shared_ptr<Texture>& getTextureByHp(int hp);