#ifndef GAME_H
#define GAME_H

#include <GLFW/glfw3.h>

#include <optional>

#include <character_icon.hpp>
#include <graphic.hpp>
#include <input.hpp>
#include <icon_container.hpp>

class Game {
 public:
  Game();
  ~Game();
  void run();

private:
  GLFWwindow* window_;
  // TODO do not make optional, use nullptr instead?
  CharacterIcon* active_icon_ = nullptr; // icon the cursor is hovering over
  CharacterIcon* held_icon_ = nullptr; // icon being held in hand while being dragged
  Input* input_;
  glm::vec2 mouse_pos_;
  std::vector<IconContainer*> tiers_;

  void initGLFW();
  void initGLAD();
  void initGL();
  void update(double dt);
  void render();
  void framebufferSizeCallback(GLFWwindow* window, int width, int height);
  void windowSizeCallback(GLFWwindow* window, int width, int height);
  void recalculateProjectionMatrix(glm::vec2 new_screen_size);
  void getActiveIcon();
};

#endif
