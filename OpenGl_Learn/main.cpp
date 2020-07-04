#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

void framebufferSize(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow * window);

const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 600;


const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"	ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"	color = vec4(ourColor, 1.0f);\n"
"}\0";


int main() 
{
	

	// ������������� � ����������������
	//-------------------------------
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// �������� ����
	// ------------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "main", NULL, NULL);
	if (!window) {
		std::cout << "WINDOW::CREATE::FAILED\n";
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSize);

	// �������� ���������� 
	//-------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD::LOADGL::FAILED\n";
		glfwTerminate();
		return -1;
	}

	// �������� � ���������� ��������
	//--------------------------------
	Shader ourShader("../ShaderPrograms/vertexShader.vert", "../ShaderPrograms/fragmentShader.frag");

	// ������������� ������
	//---------------------------
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
	};
	
	// ��������� �������
	GLuint VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// ������� ��������� ������ ���������� �������, ����� ��������� � ������������� ��������� �����(�), � ����� ������������� ��������� �������(�).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ������������ �������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// �������� �������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ������ �������� ���������, ����� glVertexAttribPointer ��������������� VBO ��� ����������� ��������� �������� ������ ��� ���������� ��������, ��� ��� ����� �� ����� �������� ��������
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// �� ����������� EBO, ���� V�� �������, ��������� ���������� ������ ������ �������� �������� � V��; ���������� �������� EBO.
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ����� ����� �� ������ �������� �������� V��, ����� ������ ������ V�� �������� �� �������� ���� VAO, �� ��� ����� ����������.
	// ��������� ������ �������� VAO ������� ������ glBindVertexArray � ����� ������, ������� �� ������ �� ������� �������� VAO (��� VBO), ����� ��� ��������������� �� ���������.
	glBindVertexArray(0);

	// ���� �������
	//---------------------------
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.3f, 0.5f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			ourShader.setFloat("Offset", 0.5);
		}
		glBindVertexArray(VAO); // ��������� � ��� ���� ������ ���� V��, ��� ������������� ��������� ��� ������ ���, �� �� ������� ���, ����� ��� ���� ������� ����� �������������
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0); // �� ����� ������ ��� ��� ����������  

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ������������ �������� (�����������)
	//------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

// ���������� ������ ������� ��� ��������� ������� ����
//-----------------------------
void framebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// ��������� ������� �����
//-----------------------------
void processInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

