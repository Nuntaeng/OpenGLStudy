#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>





std::string readCode(std::string filePath_) {
    std::string retcode = "";
    std::ifstream stream(filePath_, std::ios::in);
    if (stream.is_open()) {
        std::string line = "";
        while (getline(stream, line))
            retcode += "\n" + line;
        stream.close();
    }
    return retcode;
}

GLuint LoadShaders(std::string vFilePath_, std::string fFilePath_) {
    std::string vShaderCode = readCode(vFilePath_);
    std::string fShaderCode = readCode(fFilePath_);
    
    GLuint vShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Compile Vertex Shader
    printf("Compiling Vertex Shader... %s\n", vFilePath_.c_str());
    const char* vCodePtr = vShaderCode.c_str();
    glShaderSource(vShaderID, 1, &vCodePtr, NULL);
    glCompileShader(vShaderID);
    
    // Compile Fragment Shader
    printf("Compiling Fragment Shader... %s\n", fFilePath_.c_str());
    const char* fCodePtr = fShaderCode.c_str();
    glShaderSource(fShaderID, 1, &fCodePtr, NULL);
    glCompileShader(fShaderID);
    
    printf("Linking to Program...\n");
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vShaderID);
    glAttachShader(programID, fShaderID);
    glLinkProgram(programID);
    
    glDeleteShader(vShaderID);
    glDeleteShader(fShaderID);
    
    return programID;
}


int main() {
    
    // Initialize
    if (!glfwInit())
        return -1;
    
    // Create GLFW window context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1366, 768, "Tutorial On Way", NULL, NULL);
    if (!window) {
        printf("Error : GLFW Initialization Failed!\n");
        glfwTerminate();
        return -1;
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    // Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Error : GLEW Initialization Failed!\n");
        return -1;
    }
    
    // Initialize Shader
    GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");
    
    // Print Initialized Information
    puts("===== LOAD SUCCESS =====");
    printf("OpenGL Version = %s\n", glGetString(GL_VERSION));
    printf("GLSL Version = %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    
    
    // Game Init
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Game Loop
    while (!glfwWindowShouldClose(window)) {
        const static GLfloat bgColor[] = { 0.f, 0.f, 0.f, 1.f };
        glClearBufferfv(GL_COLOR, 0, bgColor);
        
        glUseProgram(programID);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Destroy
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &vao);
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
