#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>



int main() {
    // Initialize
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(1366, 768, "Tutorial On Way", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
        return -1;
    
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    
    
    
    // Game Loop
    
    // Vertex Data - Triangle
    static const GLfloat VERTEX_BUFFER_DATA[] = {
        -1.f, -1.f, 0.f,
        1.f, -1.f, 0.f,
        0.f, 1.f, 0.f
    };
    
    // Create vertex buffer
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_BUFFER_DATA), VERTEX_BUFFER_DATA, GL_STATIC_DRAW);
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    while (true) {
        // Draw vertex data on screen
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}
