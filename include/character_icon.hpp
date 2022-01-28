#pragma once

#include <graphic.hpp>

class CharacterIcon {
public:
  CharacterIcon(std::string icon_path, glm::vec2 position);
  void render(Renderer* renderer);
  void drag(glm::vec2 mouse_pos, double dt);
  bool isActive(glm::vec2 mouse_pos);

private:
  Graphic* icon_;
  glm::vec2 position_;
  glm::vec2 size_;
};
