#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID

GLuint quadVAO;

Core::Shader_Loader shaderLoader;


void renderScene(GLFWwindow* window)
{
    glClearColor(0.4f, 0.2f, 0.7f, 0.6f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Aktywowanie shadera
    glUseProgram(program);

    //wywolaj funkcje drawVAOIndexed na quadVAO 
    Core::drawVAOIndexed(quadVAO, 6);
    // Wylaczenie shadera
    glUseProgram(0);

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    program = shaderLoader.CreateProgram("shaders/shader_1_1.vert", "shaders/shader_1_1.frag");

    //Stworz czworokat przy uzyciu 4 wierzcholkow i 6 indeksow (typ: const int []) zaladuj go do za pomoca initVAOIndexed do quadVAO
    float wierzcholki[16] = { 0,0,0,1, 0,1,0,1, 1,0,0,1, 1,1,0,1 };
    unsigned int index[12] = { 0,2,1, 2,3,1 };
    quadVAO = Core::initVAOIndexed(wierzcholki, index, 4, 4, 6);

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