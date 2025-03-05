#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>



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
		glfwPollEvents();
	}

	//Terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}