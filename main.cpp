#define GLAD_GL_IMPLEMENTATION
#include "external/glfw/deps/glad/gl.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

const char * glsl_version = "#version 130";

// my work
bool fullscreen = false;
int windowed_x, windowed_y, windowed_width, windowed_height; // Объявляем переменные для сохранения размеров окна

void ToggleFullscreen(GLFWwindow* window) {
    fullscreen = !fullscreen;

    if (fullscreen) {
        // Сохраняем текущие размеры окна
        glfwGetWindowPos(window, &windowed_x, &windowed_y);
        glfwGetWindowSize(window, &windowed_width, &windowed_height);

        // Получаем информацию о мониторе
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        // Переключаем окно в полноэкранный режим
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        // Восстанавливаем окно в режим оконного приложения
        glfwSetWindowMonitor(window, NULL, windowed_x, windowed_y, windowed_width, windowed_height, 0);
    }
}
//close my work

int main(int, char**){

    //GLFWwindow* window;
    int width, height;

    if( !glfwInit() )
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit( EXIT_FAILURE );
    }

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "My Fullscreen App", glfwGetPrimaryMonitor(), NULL); // exe на весь экран
    if (!window) {
        glfwTerminate();
        return -1;
    }
    //window = glfwCreateWindow( 600, 600, "Scanner", nullptr, nullptr );
    if (!window)
    {
        std::cerr << "Failed to open GLFW window\n";
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval( 1 );

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    int counter = 0;
    bool should_show_demo = true;
    
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

     while( !glfwWindowShouldClose(window) )
    {
        // glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::ShowDemoWindow();
        // GUI
        // ImGui::ShowDemoWindow(&should_show_demo);
        //ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize); большое окно
         ImGui::Begin("Hello, world!");
         ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)



        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::End();

        // END GUI


        //Мои добавления
       // Инициализация GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Создание окна
    GLFWwindow* window = glfwCreateWindow(1280, 720, "My App", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Инициализация IMGUI
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Инициализация ImGui для GLFW и OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Начало рисования GUI с использованием IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Создание интерфейса с кнопкой для переключения полноэкранныго режима
        if (ImGui::Button("Toggle Fullscreen")) {
            ToggleFullscreen(window);
        }

        // Завершение рисования GUI
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Освобождение ресурсов ImGui и GLFW
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();

    glfwDestroyWindow(window);
// close my add



        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        ImGui::Render();

        
        // int display_w, display_h;
        // glfwGetFramebufferSize(window, &display_w, &display_h);
        // glViewport(0, 0, display_w, display_h);
        // glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}