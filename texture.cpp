#include "texture.h"

Texture::Texture(const std::string &filepath)
{
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/* ���Ʒ�ʽ */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// S�ᣨ��Ӧ��x�ᣩ�ظ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);	// T�ᣨ��Ӧ��y�ᣩ�ظ�

	/* ������� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, numChannel;
	const char *str = filepath.c_str();
	stbi_set_flip_vertically_on_load(true);
	
	unsigned char *data = stbi_load(str, &width, &height, &numChannel, 0);
	if (data) {
		if(filepath == std::string("importIDL.dxl"))
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		std::string suffix_str = filepath.substr(filepath.length() - 5, filepath.length());
		if (suffix_str.find("jpg", 0) != std::string::npos)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (suffix_str.find("png", 0) != std::string::npos)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "[ERROR] " << __FILE__ << " | " << __LINE__ << ": " \
			<< "open texture file failed" << std::endl;
	}

	stbi_image_free(data);

	textureId = texture;
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}