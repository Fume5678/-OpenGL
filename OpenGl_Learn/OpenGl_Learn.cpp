// OpenGl_Learn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800; // ������ ���� �� ���������
const unsigned int SCR_HEIGHT = 600; // ������ ���� �� ���������

GLuint VBO; // ��������� �����
GLuint VAO; // ��������� ������
GLuint EBO; // ������ ����������� ������
GLuint vertexShader; // ��������� ������
GLuint fragmentShader; // ����������� ������
GLuint shaderProgram; // ��������� ���������
int success;
char infoLog[512];

float verticles[] = {  // ����� ��������� ������
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
};

GLuint indices[] = { // ��������������� ������
    0, 1, 3,    // ������ �����������
    1, 2, 3     // ������ �����������
};

const char* vertexShaderSource = "#version 330\n" // �������� ��� ���������� �������
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* FragColor = "#version 330\n" // �������� ��� ������������ �������
"out vec4 FragColor;"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";


int main()
{
    // ������������� GLFW � ������ ���������� 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // �������� ���� ����������
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ������������� ��������� ���� �������� ����������
    glfwMakeContextCurrent(window);

    // �������� ���� ���������� �� OpenGl �������
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
    }

    // ������������� ���������� ������� � ������ ��������� ������� ����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // �������� �������  � ���������������
    glGenVertexArrays(1, &VAO);
    // ��������� ���������� ������
    glBindVertexArray(VAO);

    // �������� ������ � ����������������
    glGenBuffers(1, &VBO);
    // �������� ������ � �������� ���� GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // ����������� ���������������� ������ � ������� �����
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW); 
    
    // �������� ������� ������� � ��������� ������������ �� ���� ��������������
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // ����������� �������� ������ � ����������� ���
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // ��������� ������ ��� ���������� (���� ������ ���, ���������� 0)
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED >> " << infoLog << std::endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragColor, NULL);
    glCompileShader(fragmentShader);

    // ��������� ������ ��� ���������� (���� ������ ���, ���������� 0)
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED >> " << infoLog << std::endl;
    }

    // �������� ��������� ���������
    shaderProgram = glCreateProgram();
    // ������������ �������� � ��������� ���������
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // �� ����������
    glLinkProgram(shaderProgram);

    // ��������� ������ ��� ������
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAMM::LINK_FAILED >> " << infoLog << std::endl;
    }

    // �������� �� ������ ��������� ��������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ��������� ���������� ��������� ���������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // ���� �������
    while (!glfwWindowShouldClose(window)) {
        // ��������� �����
        processInput(window);

        // ���������� ����������
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ��������� ��������� ���������
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: ����������, ������������ ���� ��������������� GLFW-��������
    glfwTerminate();
    return 0;
}


// ���������� ������ ��� ��� ��������� ������� ���� (� ��� ����� � ��� �������������)
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // ��������� ������� ���� ���������
    glViewport(0, 0, width, height);
    std::cout << "Window size changer func was called\n";
}


// �������� ���� ������� �����
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        std::cout << "Escape press\n";
    }
}

*/