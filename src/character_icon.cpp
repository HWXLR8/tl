#include <character_icon.hpp>

CharacterIcon::CharacterIcon(std::string icon_path, glm::vec2 position) {
  position_ = position;
  size_ = glm::vec2(70, 70);
  icon_ = new Graphic(icon_path, position_, size_, true);
}

void CharacterIcon::render(Renderer* renderer) {
  icon_->render(renderer);
}

void CharacterIcon::drag(glm::vec2 mouse_pos, double dt) {
  icon_->move(mouse_pos - (0.5f * size_), 0, dt);
}

bool CharacterIcon::isActive(glm::vec2 mouse_pos) {
  return (icon_->isActive(mouse_pos));
}
