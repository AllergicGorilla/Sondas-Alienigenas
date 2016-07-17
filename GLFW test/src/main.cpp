#include <iostream>
#include "shader.h"
#include <math.h>
#include "simple_texture.h"

// THIS IS OPTIONAL AND NOT REQUIRED, ONLY USE THIS IF YOU DON'T WANT GLAD TO INCLUDE windows.h
// GLAD will include windows.h for APIENTRY if it was not previously defined.
// Make sure you have the correct definition for APIENTRY for platforms which define _WIN32 but don't use __stdcall
#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#include <glad/glad.h>

#ifdef _WINDOWS_
#error windows.h was included!
#endif

#include <GLFW/glfw3.h>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
  std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
  glfwMakeContextCurrent(window);
  if (window == NULL)
    {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
    }

  glfwSetKeyCallback(window, key_callback);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
      std::cout << "Failed to initialize OpenGL context" << std::endl;
      return -1;
    }

  glViewport(0, 0, WIDTH, HEIGHT);

  Texture runememe("images/rune_meme.jpg");
  Texture awesomeface("images/awesomeface.png");

  GLfloat triangle_1[] =
    {
      0.4f, 0.8f, 0.0f,
      0.75f, 0.25f, 0.0f,
      0.2f, 0.4f, 0.0f
    };
  GLfloat triangle_2[] =
    {
      0.18f, -0.09f, 0.0f,
      -0.32f, 0.34f, 0.0f,
      -0.4f, -0.2f, 0.0f
    };
  GLfloat color_triangle[] =
    {
      // Positions        // Colors
      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom Right
      -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom Left
      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Top
    };
  GLfloat square[] =
    {
      // Positions         // Colors           // Texture Coords
      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // Top Left
    };
  GLint indices[] =
    {
      0, 1, 3,
      1, 2, 3
    };
  GLuint VBO_1;
  glGenBuffers(1, &VBO_1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_1), triangle_1, GL_STATIC_DRAW);

  GLuint VBO_2;
  glGenBuffers(1, &VBO_2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_2), triangle_2, GL_STATIC_DRAW);

  GLuint VBO_3;
  glGenBuffers(1, &VBO_3);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_3);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color_triangle), color_triangle, GL_STATIC_DRAW);

  Shader orange_shader("shaders/random_vertexShader.glsl", "shaders/orange_fragmentShader.glsl");
  Shader yellow_shader("shaders/random_vertexShader.glsl", "shaders/yellow_fragmentShader.glsl");
  Shader color_shader("shaders/color_vertexShader.glsl", "shaders/color_fragmentShader.glsl");
  Shader texture_shader("shaders/texture_vertexShader.glsl", "shaders/texture_fragmentShader.glsl");


  //Vertex array object
  GLuint VAO_1;
  glGenVertexArrays(1, &VAO_1);

  // ..:: Initialization code (done once (unless your object frequently changes)) ::..
  // 1. Bind Vertex Array Object
  glBindVertexArray(VAO_1);
  // 2. Copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_1), triangle_1, GL_STATIC_DRAW);
  // 3. Then set our vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  //4. Unbind the VAO
  glBindVertexArray(0);

  //Vertex array object
  GLuint VAO_2;
  glGenVertexArrays(1, &VAO_2);

  // ..:: Initialization code (done once (unless your object frequently changes)) ::..
  // 1. Bind Vertex Array Object
  glBindVertexArray(VAO_2);
  // 2. Copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_2), triangle_2, GL_STATIC_DRAW);
  // 3. Then set our vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  //4. Unbind the VAO
  glBindVertexArray(0);

  //Vertex array object
  GLuint VAO_3;
  glGenVertexArrays(1, &VAO_3);

  // ..:: Initialization code (done once (unless your object frequently changes)) ::..
  // 1. Bind Vertex Array Object
  glBindVertexArray(VAO_3);
  // 2. Copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO_3);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color_triangle), color_triangle, GL_STATIC_DRAW);
  // 3. Then set our vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); // Position
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Color
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  //4. Unbind the VAO
  glBindVertexArray(0);

  GLuint VBO_square, VAO_square, EBO;
  glGenVertexArrays(1, &VAO_square);
  glGenBuffers(1, &VBO_square);
  glGenBuffers(1, &EBO);
  // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
  glBindVertexArray(VAO_square);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_square);
  glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  //Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  //Color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  //Texture
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindVertexArray(0); // Unbind VAO_square (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO_square

  GLint vertexColorLocation = glGetUniformLocation(yellow_shader.Program, "ourColor");

  while (!glfwWindowShouldClose(window))
    {
      // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
      glfwPollEvents();

      // Render
      // Clear the colorbuffer
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);


      orange_shader.Use();
      glBindVertexArray(VAO_1);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);

      yellow_shader.Use();
      GLfloat timeValue = glfwGetTime();
      GLfloat greenValue = (sin(timeValue) / 2) + 0.5;

      glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.2f, 1.0f);
      glBindVertexArray(VAO_2);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);

      color_shader.Use();
      glBindVertexArray(VAO_3);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);

      texture_shader.Use();
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, runememe.ID);
      glUniform1i(glGetUniformLocation(texture_shader.Program, "ourTexture1"), 0);

      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, awesomeface.ID);
      glUniform1i(glGetUniformLocation(texture_shader.Program, "ourTexture2"), 1);

      glBindVertexArray(VAO_square);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);

      glfwSwapBuffers(window);
    }

  // Terminates GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();
  return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
