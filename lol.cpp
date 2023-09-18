#define GLAD_GL_IMPLEMENTATION
#include "external/glfw/deps/glad/gl.h"
#include "implot.h"
#include "implot_internal.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>


void DrawVectorDiagram()
{
    float x_values1[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    float y_values1[] ={1.1, 2.2, 3.3, 4.4, 5.5};
    int num_points1= 4;
    float x_values2[]= {-1.1, -2.2, -3.3, -4.4, -5.5};
    float y_values2[] = {-1.1, -2.2, -3.3, -4.4, -5.5};
    int num_points2= 4;
    // Начало окна рисования с помощью библиотеки implot
    ImPlot::BeginPlot("Vector Diagram", nullptr, nullptr, ImVec2(400, 400));

    // Отрисовка первой линии
    ImPlot::PlotLine("Line 1", x_values1, y_values1, num_points1);

    // Отрисовка второй линии
    ImPlot::PlotLine("Line 2", x_values2, y_values2, num_points2);

    // Завершение окна рисования
    ImPlot::EndPlot();
}

void WindowBriefInformation(float data[8], ImVec2 windowSize, GLFWwindow* window) {
    ImGui::SetWindowSize(windowSize);
    ImGui::Begin("Protocol data", nullptr, ImGuiWindowFlags_MenuBar);
    ImGui::Text("Stream:");
    ImGui::Text("MAC dst:");
    ImGui::Text("MAC src:");
    ImGui::Text("svID:");
    ImGui::Text("Ia= ");
    ImGui::Text("Ib= ");
    ImGui::Text("Ic= ");
    ImGui::Text("In= ");
    ImGui::Text("Ua= ");
    ImGui::Text("Ub= ");
    ImGui::Text("Uc= ");
    ImGui::Text("Un= ");
    if (ImPlot::BeginPlot("my chart")) {
            // Создание данных для графика (здесь просто создаем несколько точек)
            double x[] = {1.0, 2.0, 3.0, 4.0, 5.0};
            double y[] = {1.0, 4.0, 9.0, 16.0, 25.0};

            // Отображение линейного графика
            ImPlot::PlotLine("График", x, y, 5);

            // Завершение графика
            ImPlot::EndPlot();
    }
    
    ImGui::End();
}

int main(int, char**) {
    //Инициализация библиотеки GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return EXIT_FAILURE;
    }
    //Создаю окно 
    GLFWwindow* window = glfwCreateWindow(640, 480, "My window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Создание контекста OpenGL
    glfwMakeContextCurrent(window);
    //Что это не знаю, но без него не работает(
    gladLoadGL(glfwGetProcAddress);
    //Частота обновления кадров в приложении такая же, как у монитора
    glfwSwapInterval(1);

    //Инициализация ImGui и Implot
    ImGui::CreateContext();
    ImPlot::CreateContext();
    //Инициализация ImGui для работы с библиотекой GLFW и OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    //Инициализация ImGui для работы с OpenGL версии 3.3
    ImGui_ImplOpenGL3_Init("#version 130");

    float data[8] = {0.0f}; // Инициализация массива данными по умолчанию


    while (!glfwWindowShouldClose(window)) { //Цикл будет выполняться пока окно не закроется
        glfwPollEvents();//Обрабатывает все события, которые происходят в окне и позволяет реагировать на них

        //Готовят imGui к отрисовке нового кадра в пользовательском интерфейсе
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Задаёт размер окна 
        ImVec2 customWindowSize(200, 200);
        // Вызывает функцию со столбцами
        WindowBriefInformation(data, customWindowSize, window);
        //DrawVectorDiagram();

        //Завершает отрисовку интерфейса и выводит на экран результат
        ImGui::Render();


        //Очищает буфер кадра, обычно для подготовки его к отрисовке нового кадра.
        glClear(GL_COLOR_BUFFER_BIT);

        //Рисует данные пользовательского интерфейса ImGui на текущем буфере кадра OpenGL
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Меняет местами буферы кадра GLFW, чтобы отобразить новый кадр на экране.
        glfwSwapBuffers(window);
    }
    //Освобождает все выделенные ресурсы, связанные с GLFW и завершает работу этой библиотеки 
    ImPlot::DestroyContext();
    glfwTerminate();
    
    return 0;
}