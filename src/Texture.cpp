#include"headerFiles/Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixlelType){
    type = texType;

	int widthImg, heightImg, numColCh;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	if(bytes){
	std::cout<<"image loaded"<<std::endl;
	}
	else{
		std::cout<<"failed to load image"<<std::endl;
		std::cout<<"stbi error: "<<stbi_failure_reason()<<std::endl;
	}  

	GLuint texture;

	glGenTextures(1, &ID);
	glBindTexture(texType, ID);
	glActiveTexture(slot);
	
	std::cout<<"gen and activated texture"<<std::endl;

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	std::cout<<"made changes to tex settings"<<std::endl;

	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixlelType, bytes);

	std::cout<<"set up 2d tex"<<std::endl;

	glGenerateMipmap(texType);

	std::cout<<"gen minpap"<<std::endl;

	stbi_image_free(bytes);

	glBindTexture(texType, 0);

	std::cout<<"unboud and freed tex"<<std::endl;

    // glEnable(texType);

    std::cout<<"texture loaded succseully!"<<std::endl;
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit){

    GLuint tex0Uni = glGetUniformLocation(shader.ID, "tex0");

    shader.Activate();

    glUniform1i(tex0Uni, unit);
}

void Texture::Bind(){
    glBindTexture(type, ID);
}

void Texture::Unbind(){
    glBindTexture(type, 0);
}

void Texture::Delete(){
    glDeleteTextures(1, &ID);
}