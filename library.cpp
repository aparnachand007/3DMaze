#include<string>
#include<SDL2/SDL.h>
#include<glm/glm.hpp>
#include<GL/glew.h>
#include<glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "library.h"
#include<iostream>
#include<fstream>

//display class
Display::Display(int w, int h, const char *title){
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  _window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_OPENGL);
  _glContext = SDL_GL_CreateContext(_window);

  GLenum status = glewInit();

  if(status != GLEW_OK){
    std::cerr<<"failed to init glew!"<<std::endl;
  }
  _closed = false;
}

Display::~Display(){
  SDL_GL_DeleteContext(_glContext);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

void Display::clear(float r, float g, float b, float a){
  glClearColor(r,g,b,a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::isClosed(){
  return _closed;
}

void Display::update(){
  SDL_GL_SwapWindow(_window);
  SDL_Event event;

  while(SDL_PollEvent(&event)){
    if(event.type==SDL_QUIT){
      _closed = true;
    }
  }
}

//cube class
Cube::Cube(){

  glGenVertexArrays(1,&_vertexArrayObject);
  glBindVertexArray(_vertexArrayObject);

  glGenBuffers(1,&_vertexBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER,_vertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER,sizeof(_vertexData),_vertexData,GL_STATIC_DRAW);
  std::cout<<sizeof(_vertexData);

}

void Cube::draw(){
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,_vertexBufferObject);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
  glDrawArrays(GL_TRIANGLES,0,sizeof(_vertexData)/3*sizeof(_vertexData[0]));
}

Cube::~Cube(){
  glDisableVertexAttribArray(0);
}


//shader class
Shader::Shader(){

  //_trans = glm::mat4(1.0f);

  //vertex shader
  _vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(_vertexShader,1,&_vertexShaderSource,NULL);
  glCompileShader(_vertexShader);

  int success_v;
  char log_v[1024];
  glGetShaderiv(_vertexShader,GL_COMPILE_STATUS,&success_v);

  if(!success_v){
    glGetShaderInfoLog(_vertexShader,1024,NULL,log_v);
    std::cerr<<"vertex shader error:\t"<<log_v<<std::endl;
  }

  //fragment shader
  _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(_fragmentShader,1,&_fragShaderSource,NULL);
  glCompileShader(_fragmentShader);

  int success_f;
  char log_f[1024];
  glGetShaderiv(_fragmentShader,GL_COMPILE_STATUS,&success_f);

  if(!success_f){
    glGetShaderInfoLog(_fragmentShader,1024,NULL,log_f);
    std::cerr<<"fragment shader error:\t"<<log_f<<std::endl;
  }

  _shaderProg = glCreateProgram();
  glAttachShader(_shaderProg,_vertexShader);
  glAttachShader(_shaderProg,_fragmentShader);
  glLinkProgram(_shaderProg);

  int success_l;
  char log_l[1024];
  glGetProgramiv(_shaderProg,GL_LINK_STATUS,&success_l);

  if(!success_l){
    glGetProgramInfoLog(_shaderProg,1024,NULL,log_l);
    std::cerr<<"shader program error:\t"<<log_l<<std::endl;
  }

}

void Shader::bind(){
  glUseProgram(_shaderProg);
}


Shader::~Shader(){
  glDeleteShader(_vertexShader);
  glDeleteShader(_fragmentShader);
}
