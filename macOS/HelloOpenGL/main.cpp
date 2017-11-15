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
    glShaderSource(vShaderID, 1, &vCodePtr, nullptr);
    glCompileShader(vShaderID);
    
    // Compile Fragment Shader
    printf("Compiling Fragment Shader... %s\n", fFilePath_.c_str());
    const char* fCodePtr = fShaderCode.c_str();
    glShaderSource(fShaderID, 1, &fCodePtr, nullptr);
    glCompileShader(fShaderID);
    
    printf("Linking to Program...\n");
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vShaderID);
    glAttachShader(programID, fShaderID);
    glLinkProgram(programID);
    
    glDetachShader(programID, vShaderID);
    glDetachShader(programID, fShaderID);
    glDeleteShader(vShaderID);
    glDeleteShader(fShaderID);
    
    return programID;
}


int main() {
    
    // Initialize
    if (!glfwInit())
        return -1;
    
    
    // Create GLFW window context
    glfwWindowHint(GLFW_SAMPLES, 4);
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
    glfwMakeContextCurrent(window);
    
    // Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Error : GLEW Initialization Failed!\n");
        return -1;
    }
    
    // Init vertex array
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    
    
    // Initialize datas for drawing triangle
    static const GLfloat VERTEX_TRIANGLE[] {
        -1.f, -1.f, 0.f,
        1.f, 1.f, 0.f,
        0.f, 1.f, 0.f
    };
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_TRIANGLE), VERTEX_TRIANGLE, GL_STATIC_DRAW);
    
    // Initialize Shader
    GLuint programID = LoadShaders("Vertex.glsl", "fragment.glsl");
    
    // Print Initialized Information
    puts("===== LOAD SUCCESS =====");
    printf("OpenGL Version = %s\n", glGetString(GL_VERSION));
    printf("GLSL Version = %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    
    // Game Loop
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
