#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID

GLuint quadVAO;
GLuint quadVAO1;

Core::Shader_Loader shaderLoader;


void renderScene(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Zmienna "time" przechowuje czas ktory uplynal od uruchomienia aplikacji
	float time = glfwGetTime();

	glUseProgram(program);

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ! Macierz translation jest definiowana wierszowo dla poprawy czytelnosci. OpenGL i GLM domyslnie stosuje macierze kolumnowe, dlatego musimy ja transponowac !
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	glm::mat4 rotation =
	{ cos(time)/2, -sin(time)/2, 0,0,
	  sin(time)/2,cos(time)/2,0,0,
	  0,0,1,0,
	  0,0,0,1 };

	glm::mat4 translation =
	{ 1,0,0,0,
	  0,1,0,sin(time)/2,
	  0,0,1,0,
	  0,0,0,1 };
	translation = glm::transpose(translation);
	rotation = glm::transpose(rotation);


	// ZADANIE: Narysuj dwa czworokaty, jeden ruszajacy sie, drugi obracajacy sie 
	// Do rysowania ruszajacego sie czworokatu mozesz uzyc kodu z poprzedniego zadania, zmodyfikuj tylko macierz translacji, zeby byly obok siebie, nie jeden na drugim
	// Uzyj zmiennej "time" do zdefiniowania takiej macierzy rotacji, aby czworokat obracal sie wokol srodka (znajdz odpowiednia macierz 4x4 w internecie)
	// Kat obrotu podajemy w radianach
	
	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&rotation);
	Core::drawVAOIndexed(quadVAO, 6);
	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&translation);
	Core::drawVAOIndexed(quadVAO1, 6);
	

	glUseProgram(0);

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	program = shaderLoader.CreateProgram("shaders/shader_1_2.vert", "shaders/shader_1_2.frag");

    //Przekopiuj kod do ladowania z poprzedniego zadania
	float wierzcholki[16] = { -0.5,-0.5,0,1, -0.5,0.5,0,1, 0.5,-0.5,0,1, 0.5,0.5,0,1 };
	unsigned int index[6] = { 0,2,1, 2,3,1 };
	quadVAO = Core::initVAOIndexed(wierzcholki, index, 4, 4, 6);
	float wierzcholki1[16] = { 0.5,0.5,0,1, 1,0.5,0,1, 1,0,0,1, 0.5,0,0,1 };
	unsigned int index1[6] = { 0,1,2, 2,3,0 };
	quadVAO1 = Core::initVAOIndexed(wierzcholki1, index1, 4, 4, 6);
}

void shutdown(GLFWwindow* window)
{
    shaderLoader.DeleteProgram(program);
}


//obsluga wejscia
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// funkcja jest glowna petla
void renderLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        renderScene(window);
        glfwPollEvents();
    }
}
//}