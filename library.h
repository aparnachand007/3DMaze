#ifndef LIBRARY_H
#define LIBRARY_H
#include<string>
#include<SDL2/SDL.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<GL/glew.h>
#include<glm/gtx/transform.hpp>

//display class
class Display{
public:
  Display(int w, int h, const char *title);
  void update();
  bool isClosed();
  void clear(float r, float g, float b, float a);
  virtual ~Display();
private:
  SDL_Window *_window;
  SDL_GLContext _glContext;
  bool _closed;
protected:
};

//cube class
class Cube{
public:
  Cube();
  void draw();
  virtual ~Cube();
private:
  float _vertexData[108] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};
unsigned int _vertexBufferObject,_vertexArrayObject;
protected:
};


//shader class
class Shader{
public:
  glm::mat4 _trans;
  Shader();
  void bind();
  virtual ~Shader();
  unsigned int _shaderProg;
private:
  const char *_vertexShaderSource = "#version 120\nattribute vec3 pos;\nuniform mat4 model;\nuniform mat4 view;\nuniform mat4 projection;\nvoid main(){\ngl_Position = projection * view * model * vec4(pos,1.0);\n}\0";

  const char *_fragShaderSource = "#version 120\nvoid main(){\ngl_FragColor=vec4(1.0f,0.0f,1.0f,1.0f);\n}\0";

  unsigned int _vertexShader;
  unsigned int _fragmentShader;
protected:
};


#endif
