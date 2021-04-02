#include "Texture.h"
#include <iostream>
#include <array>

//Можно добавлять текстурки

#define TEX_COUNT 3

std::array<std::shared_ptr<Texture>, TEX_COUNT> textures;

std::shared_ptr<Texture>& getTextureByHp(int hp)
{
	switch (hp)
	{
	case 1: return (textures[1]);
	case 2: return (textures[2]);
	default: return (textures[0]);
	}
}

GLuint Texture::get_tga_file(char const *file)
{
	size_t size;
	int color;
	unsigned char header[18];
	FILE *_file;
	errno_t err;


	err = fopen_s(&_file, file, "rb");
	if (err)
		return 0;
	//Считываем информацию об упаковке
	fread(header, 1, sizeof(header), _file);
	// Не является форматом РГБ
	if (header[2] != 2)
		return 0;

	int width = header[13] * 256 + header[12];
	int height = header[15] * 256 + header[14];

	//Смотрим сколько битов цвета на пиксель имеет файл
	color = header[16] / 8;

	//Смотрим размер массива цвета
	size = width * height * color;

	//Теперь задаем массив с изображением посредством умного указателя, чтобы не следить за памятью
	auto image = std::make_unique<unsigned char[]>(sizeof(unsigned char) * size);
	//Читаем оставшуюся информацию
	fread(image.get(), sizeof(unsigned char), size, _file);
	_fcloseall();

	//ТГА хранит данные в БГР, но рам нужны РГБ
	for (size_t i = 0; i < size; i += color)
	{
		unsigned char tmp = image[i];
		image[i] = image[i + 2];
		image[i + 2] = tmp;
	}

	GLuint tex_id = 0;
	//Загружаем текстуру в "опен жижу" и устанавливаем необходимые настройки 
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glDrawBuffer(GL_BACK);

	//Нужно проверить, zагрузился ли цвет и в каком формате РГБ или РГБА?
	if (color == 3)
		color = GL_RGB;
	else if (color == 4)
		color = GL_RGBA;
	else
		return 0;

	// строим mipmaps по полученной информации
	gluBuild2DMipmaps(GL_TEXTURE_2D, color, width, height, color, GL_UNSIGNED_BYTE, image.get());

	//Если все хорошо, то возвращаем айди загруженной текстуры
	return tex_id;
}