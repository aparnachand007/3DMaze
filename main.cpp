#include <iostream>
#include<string>
#include<GL/glew.h>
#include "library.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<fstream>

int map[100][100];

void print_map(){
  for(int i=0;i<99;i++){
    for(int j=0;j<99;j++){
      std::cout<<map[i][j]<<std::endl;
    }
  }
}
void bind_shader(unsigned int);
void translate_model(unsigned int,glm::vec3);
void rotate_model(unsigned int,float theta,glm::vec3);
void scale_model(unsigned int,glm::vec3);
void translate_view(unsigned int,glm::vec3);
void add_projection(unsigned int);
void read_file();

int main(){

  read_file();

  Display disp(800,600,"godhelpme");
  Shader shader;
  Cube cube;

  float counter = 0.0f;


  while(!disp.isClosed()){
    disp.clear(0,1,0,0);
    add_projection(shader._shaderProg);
    translate_view(shader._shaderProg,glm::vec3(100.0f+(100*cosf(counter)),-75.0f+(75*sinf(counter)),-100.0f+counter));
    //scale_model(shader._shaderProg,glm::vec3(0.025f,0.025f,0.025f));
    //rotate_model(shader._shaderProg,-45.0f+100*counter,glm::vec3(1.0f,1.0f,1.0f));
    for(int i=0;i<100;i++){
      for(int j=0;j<100;j++){
        translate_model(shader._shaderProg,glm::vec3(-(float)i,(float)j,0.0f));
        bind_shader(shader._shaderProg);
        if(map[i][j]==0){
        cube.draw();
        }
      }
    }
    disp.update();
    if(counter>99.0f){
      counter-=0.01f;
    }
    else{
      counter+=0.01f;
    }
  }

  return 0;
}


void bind_shader(unsigned int shaderID){
  glUseProgram(shaderID);
}

void translate_model(unsigned int shaderID,glm::vec3 translationFactor){
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model,translationFactor);

  int loc = glGetUniformLocation(shaderID, "model");
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
}

void rotate_model(unsigned int shaderID,float theta,glm::vec3 rotationAxis){
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model,glm::radians(theta),rotationAxis);

  int loc = glGetUniformLocation(shaderID, "model");
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
}

void scale_model(unsigned int shaderID,glm::vec3 scaleFactor){
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model,scaleFactor);

  int loc = glGetUniformLocation(shaderID, "model");
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
}


void translate_view(unsigned int shaderID,glm::vec3 translationFactor){
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view,translationFactor);

  int loc = glGetUniformLocation(shaderID, "view");
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
}

void add_projection(unsigned int shaderID){
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  int loc = glGetUniformLocation(shaderID, "projection");
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
}

void read_file(){
  std::fstream file("map_data");
  if(file.is_open()){
    std::string line;
    for(int i=0;i<100;i++){
      for(int j=0;j<100;j++){
        std::getline(file,line);
        map[i][j]=stoi(line);
        //std::cout<<stoi(line)<<std::endl;
      }
    }
    file.close();
  }
}
