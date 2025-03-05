#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//vertex shader source code 
//This code is compiled on the GPU
//GLSL (OpenGL Shading Language)
//Shaders are small programs that run on the GPU (Graphics Processing Unit) and are responsible for rendering visuals.
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//fragment shader source code
//This code is compiled on the GPU
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

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
		-0.5f, -0.5f * float(sqrt(3)), 0.0f, //Bottom-left vertex
		0.5f, -0.5f * float(sqrt(3)), 0.0f, //Bottom-right vertex
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f //Top vertex
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


	//Create a vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Create a fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	//Delete the vertex and fragment shaders once linked
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Create a Vertex Buffer Object and copy the vertex data to it
	//VAO - Vertex Array Object
	//VBO - Vertex Buffer Object
	GLuint VAO,VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	//Terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}