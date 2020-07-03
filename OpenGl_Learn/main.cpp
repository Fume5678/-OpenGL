#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebufferSize(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow * window);

const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 600;


const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 a;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(a.x, a.y, a.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"	color = vec4(1.0f, 0.5f, 0.6f, 1.0f);\n"
"}\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"	color = vec4(0.5f, 1.0f, 0.7f, 1.0f);\n"
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
	int success;
	char infoLog[512];

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "SHADER::VERTEX::COMPILE::FAILED >> " << infoLog;

	}

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "SHADER::FRAGMENT::COMPILE::FAILED >> " << infoLog;

	}

	int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
		std::cout << "SHADER::FRAGMENT::COMPILE::FAILED 2 >> " << infoLog;

	}

	int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	// ������������� ������
	//---------------------------
	float vertices[] = {
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};
	
	float vertices2[] = {
		 0.7f,  0.7f, 0.0f,
		 0.9f,  0.7f, 0.0f,
		 0.5f,  0.6f, 0.0f,
	};
	// ��������� �������
	GLuint VBO[2], VAO[2], EBO;

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������� ��������� ������ ���������� �������, ����� ��������� � ������������� ��������� �����(�), � ����� ������������� ��������� �������(�).
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[0]); // ��������� � ��� ���� ������ ���� V��, ��� ������������� ��������� ��� ������ ���, �� �� ������� ���, ����� ��� ���� ������� ����� �������������
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0); // �� ����� ������ ��� ��� ����������  

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]); // ��������� � ��� ���� ������ ���� V��, ��� ������������� ��������� ��� ������ ���, �� �� ������� ���, ����� ��� ���� ������� ����� �������������
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ������������ �������� (�����������)
	//------------------------
	glDeleteVertexArrays(1, &VAO[0]);
	glDeleteBuffers(1, &VBO[0]);
	glDeleteVertexArrays(1, &VAO[1]);
	glDeleteBuffers(1, &VBO[1]);

	glDeleteProgram(shaderProgram);
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

