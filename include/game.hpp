#ifndef GAME_H
#define GAME_H

#include <GLFW/glfw3.h>

#include <map>
#include <graphic.hpp>

class Game {
 public:
  Game();
  ~Game();
  void run();

private:
  GLFWwindow* window_;
  std::map<std::string, Graphic*> character_list_;
  // Input* input_;

  void initGLFW();
  void initGLAD();
  void initGL();
  void setViewport();
  void update(double dt);
  void render();
  void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

#endif
