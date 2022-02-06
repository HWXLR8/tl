#include <icon_container.hpp>
#include <config.hpp>

IconContainer::IconContainer(glm::vec2 position, glm::vec2 size, std::optional<std::vector<std::string>> characters) {
  position_ = position;
  size_ = size;

  // calculate icon capacity based on container size
  icon_capacity_ = {
    std::floor(size.x / ICON_SIZE.x),
    std::floor(size.y / ICON_SIZE.y),
  };

  if (characters.has_value()) {
    for (std::string character : characters.value()) {
      createNewIcon(character);
    }
  }
}

void IconContainer::createNewIcon(std::string character_name) {
  std::string filename = "assets/" + character_name + ".png";
  incrementIconIndex();
  glm::vec2 position = (last_icon_index_ * ICON_SIZE);
  CharacterIcon* icon = new CharacterIcon(filename, position);
  icons_.insert({character_name, icon});
}

void IconContainer::incrementIconIndex() {
  // special case for first icon
  if (last_icon_index_ == glm::vec2{-1, -1}) {
    last_icon_index_ = {0, 0};
    return;
  }
  // we have reached max horizontal capacity
  if (last_icon_index_.x == icon_capacity_.x - 1) {
    last_icon_index_.x = 0;
    last_icon_index_.y += 1;
  } else {
    last_icon_index_.x += 1;
  }
}

void IconContainer::render(Renderer* renderer) {
  for (auto& [key, val] : icons_) {
    val->render(renderer);
  }
}

void IconContainer::update(glm::vec2 mouse_pos, double dt) {
  for (auto& [key, val] : icons_) {
    val->update(mouse_pos, dt);
  }
}

std::optional<CharacterIcon*> IconContainer::getActiveIcon(glm::vec2 mouse_pos) {
  for (auto& [key, val] : icons_) {
    if (val->isActive(mouse_pos)) {
      return val;
    }
  }
  return std::nullopt;
}
