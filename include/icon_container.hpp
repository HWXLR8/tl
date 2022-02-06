#pragma once

#include <map>
#include <optional>
#include <string>
#include <vector>

#include <character_icon.hpp>

class IconContainer {
public:
  IconContainer(glm::vec2 position, glm::vec2 size, std::optional<std::vector<std::string>> characters);
  void createNewIcon(std::string character_name);
  void addExistingIcon(CharacterIcon* icon);
  void render(Renderer* renderer);
  void update(glm::vec2 mouse_pos, double dt);
  std::optional<CharacterIcon*> getActiveIcon(glm::vec2 mouse_pos);

private:
  glm::vec2 getLastIconPosition();
  void incrementIconIndex();
  void decrementIconIndex();

  glm::vec2 position_;
  glm::vec2 size_;
  std::map<std::string, CharacterIcon*> icons_;
  glm::vec2 icon_capacity_;
  glm::vec2 last_icon_index_ = {-1, -1};
};
