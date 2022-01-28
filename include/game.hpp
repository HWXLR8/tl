#ifndef GAME_H
#define GAME_H

#include <GLFW/glfw3.h>

#include <map>
#include <optional>

#include <character_icon.hpp>
#include <graphic.hpp>
#include <input.hpp>

class Game {
 public:
  Game();
  ~Game();
  void run();

private:
  GLFWwindow* window_;
  std::map<std::string, CharacterIcon*> character_list_;
  std::optional<CharacterIcon*> active_icon_;
  Input* input_;
  glm::vec2 mouse_pos_;

  void initGLFW();
  void initGLAD();
  void initGL();
  void update(double dt);
  void render();
  void framebufferSizeCallback(GLFWwindow* window, int width, int height);
  void windowSizeCallback(GLFWwindow* window, int width, int height);
  void recalculateProjectionMatrix(glm::vec2 new_screen_size);
  void updateActiveIcon();
};

#endif
