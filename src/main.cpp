#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>


//Fragment Shader source code


int main(){
    std::cout << "start" << std::endl;
    //INistilizes glfw
    glfwInit();
    //helps/gives hints to glfw what we want to happen
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    

    //tells glfw that window is a glfw window type
    GLFWwindow* window = glfwCreateWindow(800,800,"Hello",NULL,NULL);
    //error checking
    if(window == NULL){
        std::cout <<"failed to create a window broh" << std::endl;
        glfwTerminate();
        return -1;
    }
    //tells window to exists 
    glfwMakeContextCurrent(window);
    //loads glad
    gladLoadGL();
    //viewport???
    glViewport(0,0,800,800);
    //creates a vertex shader using opengl
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    //compiles the vertex shader
    glCompileShader(vertexShader);
    //same thing for framnet shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    //creates a shader progam
    GLuint shaderProgram = glCreateProgram();
    //attachs the shades to the shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //cleans up unneccary vertex and fragment shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLfloat vertices[] = {
         -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
         0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
         0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // upper corner
         -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
         0.5 / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
         0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
    };
    GLuint indices[] = {
        0,3,5, // Lower left triangle
        3,2,4, //Lower right triangle
        5,4,1
    };

    //creatses a VBO(vertex buffer object) and VAO(vertex array object)
    GLuint VAO, VBO, EBO;
    //generats VAO
    glGenVertexArrays(1,&VAO);
    //initilizes VBO
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // Binds / sets VBO as current object
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //stores data in the VBO buffer
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //enables the just iniilaized vertex attibits
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //give us the color we want
    glClearColor(0.08f,0.12f,0.12f,0.7f);
    //clears the jus used buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //swaps the front and back buffer
    glfwSwapBuffers(window);
    //keeps window open until we want to close it
    while(!glfwWindowShouldClose(window)){

        glClearColor(0.08f,0.12f,0.12f,0.7f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        //runs any glfw event needed
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers( 1 ,&EBO);
    glDeleteProgram(shaderProgram);

    //kills window and glfw init
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}