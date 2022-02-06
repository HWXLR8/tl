#include <character_icon.hpp>
#include <config.hpp>

CharacterIcon::CharacterIcon(std::string icon_path, glm::vec2 position) {
  position_ = position;
  size_ = ICON_SIZE;
  icon_ = new Graphic(icon_path, position_, size_, true);
}

void CharacterIcon::render(Renderer* renderer) {
  icon_->render(renderer);
}

void CharacterIcon::toggleDrag() {
  drag_ = !drag_;
}

bool CharacterIcon::isActive(glm::vec2 mouse_pos) {
  return (icon_->isActive(mouse_pos));
}

void CharacterIcon::update(glm::vec2 mouse_pos, double dt) {
  if (drag_) {
    icon_->move(mouse_pos - (0.5f * size_), 0, dt);
  }
}
