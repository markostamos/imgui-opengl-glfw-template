#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <cstdlib>

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}
class AppWrapper
{
public:
    AppWrapper(const char *window_name)
    {
        // Setup window
        glfwSetErrorCallback(error_callback);
        if (!glfwInit())
            std::exit(1);
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(1280, 720, window_name, NULL, NULL);
        glfwMakeContextCurrent(window);

        glewInit();

        // Setup ImGui binding
        ImGui_ImplGlfwGL3_Init(window, true);
    }
    ~AppWrapper()
    {
        // Cleanup
        ImGui_ImplGlfwGL3_Shutdown();
        glfwTerminate();
    }
    void run()
    {
        startup();

        while (!glfwWindowShouldClose(window))
        {
            ImGui_ImplGlfwGL3_NewFrame();

            update();

            // Rendering
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui::Render();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    virtual void update() = 0;
    virtual void startup() = 0;

protected:
    GLFWwindow *window;
    ImVec4 clear_color = ImColor(114, 144, 154);
};