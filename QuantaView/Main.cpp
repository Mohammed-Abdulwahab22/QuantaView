#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"


int main()
{
	//Initialize GLFW
	glfwInit();

	//Tell GLFW what version of OpenGL we are using
	//In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW we are using the CORE profile
	//So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,  1.0f,0.0f,0.0f,   0.0f,0.0f,//Lower left corner
		-0.5f, 0.5f, 0.0f,  0.0f,1.0f,0.0f,   0.0f,1.0f,//Upper left corner
		0.5f, 0.5f, 0.0f,   0.0f,0.0f,1.0f,   1.0f,1.0f,//Upper right corner
		0.5f, -0.5f, 0.0f,  1.0f,1.0f,0.0f,   1.0f,0.0f//Lower right corner
	};

	GLuint indices[] = {
		0,2,1, //Upper Triangle
		0,3,2  //Lower Triangle
	};

	//create a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "QuantaView", NULL, NULL);

	//GLFWimage images[1];
	//images[0].pixels = stbi_load("C:/Users/HP/Desktop", &images[0].width, &images[0].height, 0, 4);

	//glfwSetWindowIcon(window, 1, NULL);

	//Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Introduce the window into the current context
	glfwMakeContextCurrent(window); 

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGL in the Window
	glViewport(0, 0, 800, 800);


	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Texture
	Texture sampleTexture("Icon_Bird_512x512.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	sampleTexture.TexUnit(shaderProgram, "tex0", 0);

	//Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	//Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//Take care of all GLFW events
		//This is where we get user input
		//Such as keyboard and mouse
		//And window resizing
		//And many other things
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		sampleTexture.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	sampleTexture.Delete();	
	shaderProgram.Delete();

	//Terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}