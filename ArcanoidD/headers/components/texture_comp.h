#pragma once
#include "component.h"
#include "Texture.h"

#include <memory>
#include "glut.h"



class TextureComp : public ComponentInterface
{
public:
	TextureComp(std::shared_ptr<Texture> &tex) {
		texture = tex;
	};

	Texture *getT() const {
		return texture.get();
	};

private:
	std::shared_ptr<Texture> texture;
};