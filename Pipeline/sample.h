#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Function to handle window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

int main()
{
  // Initialize GLFW
  glfwInit();

  // Configure GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a window
  GLFWwindow* window = glfwCreateWindow(800, 600, "Rendering Pipeline", NULL, NULL);
  if (window == NULL)
  {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Set the callback function for window resize
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize GLEW
  if (glewInit() != GLEW_OK)
  {
    glfwTerminate();
    return -1;
  }

  // Main rendering loop
  while (!glfwWindowShouldClose(window))
  {
    // Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the front and back buffers
    glfwSwapBuffers(window);

    // Poll for events
    glfwPollEvents();
  }

  // Terminate GLFW
  glfwTerminate();

  return 0;
}
// Define vertex shader source code
const char* vertexShaderSource = R"(
  #version 330 core
  layout (location = 0) in vec3 aPos;
  void main()
  {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  }
)";

// Define fragment shader source code
const char* fragmentShaderSource = R"(
  #version 330 core
  out vec4 FragColor;
  void main()
  {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
  }
)";

// Create and compile the vertex shader
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);

// Check for vertex shader compilation errors
int success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if (!success)
{
  glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
  std::cout << "Vertex shader compilation failed: " << infoLog << std::endl;
}

// Create and compile the fragment shader
unsigned int fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);

// Check for fragment shader compilation errors
glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
if (!success)
{
  glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
  std::cout << "Fragment shader compilation failed: " << infoLog << std::endl;
}

// Create the shader program and link the shaders
unsigned int shaderProgram;
shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);

// Check for shader program linking errors
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if (!success)
{
  glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
  std::cout << "Shader program linking failed: " << infoLog << std::endl;
}

// Delete the shaders as they are no longer needed
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);

// Define the vertices of the plane
float vertices[] = {
  -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  0.0f, 0.5f, 0.0f
};

// Create and bind the vertex buffer object (VBO)
unsigned int VBO;
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// Create and bind the vertex array object (VAO)
unsigned int VAO;
glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// Unbind the VAO and VBO
glBindVertexArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);

// Render loop
while (!glfwWindowShouldClose(window))
{
  // Clear the screen
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Use the shader program
  glUseProgram(shaderProgram);

  // Bind the VAO
  glBindVertexArray(VAO);

  // Draw the plane
  glDrawArrays(GL_TRIANGLES, 0, 3);

  // Unbind the VAO
  glBindVertexArray(0);

  // Swap the front and back buffers
  glfwSwapBuffers(window);

  // Poll for events
  glfwPollEvents();
}

// Delete the VAO and VBO
glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);