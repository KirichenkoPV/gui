#define GLAD_GL_IMPLEMENTATION
#include "external/glfw/deps/glad/gl.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>




int main(){

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return EXIT_FAILURE;
    }

    //Создание окна GLFW
    GLFWwindow* window = glfwCreateWindow(640, 480, "Мое окно", NULL, NULL);
    if (!window) {
        std::cerr << "Ошибка создания окна GLFW" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Создание контекста OpenGL
    glfwMakeContextCurrent(window);

    //Инициализация ImGui
    ImGui::CreateContext();
    //Инициализация ImGui для работы с библиотекой GLFW и OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    //Инициализация ImGui для работы с OpenGL версии 3.3
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Основной цикл приложения
while (!glfwWindowShouldClose(window)) {
        // Очистка буфера
        glClear(GL_COLOR_BUFFER_BIT);

        // Начало рендеринга ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Создание интерфейса ImGui здесь
        ImGui::Begin("Мое окно");
        ImGui::Text("Привет, мир!");
        ImGui::End();

        // Завершение рендеринга ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Обмен буферов
        glfwSwapBuffers(window);

        // Обработка событий
        glfwPollEvents();
    }
    // ImGui::Begin("my window", NULL);

    // ImGui::End();

    return 0;
}
