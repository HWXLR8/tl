#include <tier.hpp>

#include <algorithm>

#include <config.hpp>

Tier::Tier(unsigned int num, std::string name, glm::vec2 position, glm::vec2 size, std::optional<std::vector<std::string>> characters) {
  position_ = position;
  size_ = size;

  // set background texture
  bg_ = new Graphic("assets/tier_bg.gif", position, size, false);

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
  if (!active_index_.has_value()) {
    icons_.push_back(icon);
    incrementIconIndex();
    return;
  }

  glm::vec2 index = active_index_.value();
  // if the active index is at the end of the tier or beyond, add to the end
  if ((index.y > last_icon_index_.y) ||
      (index.y == last_icon_index_.y && index.x > last_icon_index_.x)) {
    icons_.push_back(icon);
  } else {
    // convert 2D index to 1D
    int position = (index.y * icon_capacity_.x) + index.x;
    icons_.insert(icons_.begin() + position, icon);
  }
  incrementIconIndex();
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
  bg_->render(renderer);
  for (auto& icon : icons_) {
    icon->render(renderer);
  }
}

void Tier::update(glm::vec2 mouse_pos, bool part_icons, double dt) {
  for (auto& icon : icons_) {
    icon->update(mouse_pos, dt);
  }
  getActiveIndex(mouse_pos);
  if (active_index_.has_value()) {
  }
  clean(part_icons, dt);

  // grow and shrink background
  glm::vec2 bg_size = {size_.x, (last_icon_index_.y + 1) * ICON_SIZE.y};
  size_ = bg_size;
  bg_->setSize(bg_size);
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

void Tier::clean(bool part_icons, double dt) {
  last_icon_index_ = glm::vec2{0, 0};
  for (auto& icon : icons_) {
    if (part_icons && active_index_.has_value() && last_icon_index_ == active_index_.value()) {
      incrementIconIndex();
    }
    glm::vec2 icon_position = (last_icon_index_ * ICON_SIZE) + position_;
    icon->move(icon_position, dt);
    incrementIconIndex();
  }
}

void Tier::getActiveIndex(glm::vec2 mouse_pos) {
  glm::vec2 index = {0, 0};

  while (true) {
    // the mouse is not within any of the icon indices
    if ((index.y > last_icon_index_.y) ||
	(index.y == last_icon_index_.y && index.x > last_icon_index_.x)) {
      active_index_ = std::nullopt;
      return;
    }

    // calculate icon position based on index, icon size and tier position
    glm::vec2 icon_position = (index * ICON_SIZE) + position_;

    // if mouse is within the icon
    if ((icon_position.x <= mouse_pos.x) &&
	(mouse_pos.x <= icon_position.x + ICON_SIZE.x) &&
	(icon_position.y <= mouse_pos.y) &&
	(mouse_pos.y <= icon_position.y + ICON_SIZE.y)) {
      active_index_ = index;
      return;
    }

    // move to next index
    if (index.x == icon_capacity_.x - 1) {
      index.x = 0;
      index.y += 1;
    } else {
      index.x += 1;
    }
  }
}
