#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "ext.hpp"
#include <vector>

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID

GLuint quadVAO;

Core::Shader_Loader shaderLoader;

float aa, bb, cc = 0.0f;
glm::vec3 quadPos;
std::vector<glm::vec3> quadsPositions;

void renderScene(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

    float time = glfwGetTime();

    glUseProgram(program);

    //glm::vec3 quadPos = glm::vec3(aa, bb, cc);
    glm::mat4 transformation = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.1f, 0.0f));
    //glm::mat4 transformation = glm::mat4(1.0f);

    //glm::mat4 trans = glm::translate(transformation, quadPos);

    glm::mat4 rotate = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(0.0f, sin(time) / 2, 0.0f));
    rotate = glm::rotate(rotate, time, glm::vec3(0, 0, 1));
    glm::mat4 transRot = transformation * rotate; //* trans;







    glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&transRot); //trans
    Core::drawVAOIndexed(quadVAO, 6);

    glUseProgram(0);

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    printf("%f,%f\n", xpos, ypos);
}


void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    program = shaderLoader.CreateProgram("shaders/shader_1_2.vert", "shaders/shader_1_2.frag");

    float points[] = {
        -0.1,-0.1,0.0,1.0,
         0.1,-0.1,0.0,1.0,
         0.1, 0.1,0.0,1.0,
        -0.1, 0.1,0.0,1.0,
    };
    unsigned int indices[] = {
        0,1,3,
        1,2,3,
    };
    quadVAO = Core::initVAOIndexed(points, indices, 4, 4, 6);

    //Przekopiuj kod do ladowania z poprzedniego zadania
}

void shutdown(GLFWwindow* window)
{
    shaderLoader.DeleteProgram(program);
}

//obsluga wejscia
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        bb = bb + 0.001;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        bb = bb - 0.001;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        aa = aa + 0.001;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        aa = aa - 0.001;
    }

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