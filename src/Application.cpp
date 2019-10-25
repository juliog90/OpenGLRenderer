#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
      if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    /* Initalize GLEW */
    if(glewInit() != GLEW_OK) {
        std::cout << "Error" << std::endl;
    }

    unsigned int indices[] =
    {
        0, 1, 2 ,
        3, 2, 1
    };

    float positions[] {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
        -0.5f,  0.5f, 1.0f, 0.0f, // 1
         0.5f, -0.5f, 1.0f, 1.0f, // 2
         0.5f,  0.5f, 0.0f, 1.0f  // 3
    };

    // Vertex Array
    VertexArray va;

    // Vertex Buffer
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    // Vertex Buffer Layout
    VertexBufferLayout layout;
    layout.PushFloat(2);
    layout.PushFloat(2);
    va.AddBuffer(vb, layout);

    // Index Buffer
    IndexBuffer ib(indices, 6);

    // Shader Setup
    Shader shader("res/shaders/basic.shader");
    shader.Bind();
    shader.SetUniforms4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    Texture texture("res/textures/melchor.png");
    texture.Bind();
    shader.SetUniforms1i("u_Texture", 0);

    float r = 0.0f;
    float increment = 0.05f;

    Renderer renderer;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
         renderer.Clear();

         glfwSwapInterval(1);
         shader.SetUniforms4f("u_Color", r, 0.3f, 0.8f, 1.0f);
         positions[1] += 0.1;
         vb.Bind();


         renderer.Draw(va, ib, shader);

         if(r > 1.0f)
         {
             increment = -0.05f;
         }
         else if (r < 0.0f)
         {
             increment = 0.05f;
         }

         r += increment;

        /* Swap front and back buffers */
         glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
