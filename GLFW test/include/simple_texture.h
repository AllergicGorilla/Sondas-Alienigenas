#ifndef SIMPLE_TEXTURE_H
#define SIMPLE_TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture
{
public:
	Texture(const char* imagePath, int req_comp = STBI_rgb)
	{
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//Load image
		int image_width, image_height, image_channels_per_pixel;
		typedef unsigned char BYTE;
		BYTE* image = stbi_load(imagePath, &image_width, &image_height, &image_channels_per_pixel, req_comp);
		if(image == NULL)
			{
				std::cout << "Unable to load image." << std::endl;
			}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	GLuint ID;
};

#endif
