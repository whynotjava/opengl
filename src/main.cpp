// #define STB_IMAGE_IMPLEMENTATION
// #include<stb/stb_image.h>


#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"headerFiles/shaderClass.h"
#include"headerFiles/VAO.h"
#include"headerFiles/VBO.h"
#include"headerFiles/EBO.h"
#include"headerFiles/Texture.h"
#include <math.h>
#include<stb/stb_image.h>

// Vertices coordinates
GLfloat vertices[] =
{  //              COORDINATES   /      COLORS     //  vericies
	-0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f,  		0.0f, 1.0f,
	0.5f, 0.5f, 0.0f,      0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 	   1.0f, 0.0f, 0.0f,		1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1,
	0, 3, 2

};



int main()
{
	// Initialize GLFW
	glfwInit();
    std::cout<<"start"<<std::endl;

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "openGl tests and other shit I do", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);
    // std::cout<<"debug"<<std::endl;
	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("../res/shaders/default-vert.txt", "../res/shaders/default-frag.txt");
    
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// textures!!!!!!
	std::string texPath = "../res/tex/";
	Texture popCat((texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	
	
    glEnable(GL_TEXTURE_2D);
	std::cout<<"entered loop"<<std::endl;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		
		shaderProgram.Activate();
        glUniform1f(uniID, 0.0f);

		popCat.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	std::cout<<"exited loop "<<std::endl;



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
    std::cout<<"stop";
	return 0;
}