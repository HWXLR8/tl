#include <tier.hpp>

#include <algorithm>

#include <config.hpp>

Tier::Tier(glm::vec2 position, glm::vec2 size, std::optional<std::vector<std::string>> characters) {
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

void Tier::createNewIcon(std::string character_name) {
  incrementIconIndex();
  glm::vec2 position = (last_icon_index_ * ICON_SIZE) + position_;
  CharacterIcon* icon = new CharacterIcon(character_name, position);
  icons_.push_back(icon);
}

void Tier::addExistingIcon(CharacterIcon* icon) {
  incrementIconIndex();
  icons_.push_back(icon);
}

void Tier::removeIcon(CharacterIcon* icon) {
  icons_.erase(std::remove(icons_.begin(), icons_.end(), icon), icons_.end());
  decrementIconIndex();
}

void Tier::incrementIconIndex() {
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

void Tier::decrementIconIndex() {
  // special case for first icon
  if (last_icon_index_ == glm::vec2{0, 0}) {
    last_icon_index_ = {-1, -1};
    return;
  }
  // we have reached the beginning of a row
  if (last_icon_index_.x == 0) {
    last_icon_index_.x = icon_capacity_.x - 1;
    last_icon_index_.y -= 1;
  } else {
    last_icon_index_.x -= 1;
  }
}

void Tier::render(Renderer* renderer) {
  for (auto& icon : icons_) {
    icon->render(renderer);
  }
}

void Tier::update(glm::vec2 mouse_pos, double dt) {
  for (auto& icon : icons_) {
    icon->update(mouse_pos, dt);
  }
}

CharacterIcon* Tier::getActiveIcon(glm::vec2 mouse_pos) {
  for (auto& icon : icons_) {
    if (icon->isActive(mouse_pos)) {
      return icon;
    }
  }
  return nullptr;
}

bool Tier::isActive(glm::vec2 mouse_pos) {
  return ((position_.x <= mouse_pos.x) &&
	  (mouse_pos.x <= position_.x + size_.x) &&
	  (position_.y <= mouse_pos.y) &&
	  (mouse_pos.y <= position_.y + size_.y));
}

void Tier::clean(double dt) {
  last_icon_index_ = glm::vec2{0, 0};
  for (auto& icon : icons_) {
    glm::vec2 icon_position = (last_icon_index_ * ICON_SIZE) + position_;
    icon->move(icon_position, dt);
    incrementIconIndex();
  }
}