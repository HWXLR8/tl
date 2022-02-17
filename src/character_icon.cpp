#include <character_icon.hpp>
#include <config.hpp>

CharacterIcon::CharacterIcon(std::string character_name, glm::vec2 position) {
  position_ = position;
  size_ = ICON_SIZE;
  character_name_ = character_name;
  std::string filename = "assets/" + character_name + ".png";
  icon_ = new Graphic(filename, position_, size_, true);
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

std::string CharacterIcon::getCharacterName() {
  return character_name_;
}

bool CharacterIcon::isBeingDragged() {
  return drag_;
}

void CharacterIcon::setPosition(glm::vec2 position) {
  position_ = position;
  icon_->setPosition(position);
}

glm::vec2 CharacterIcon::getPosition() {
  return position_;
}
