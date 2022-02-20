#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

class Config {
public:
  static glm::vec2 SCALE;
  static glm::vec2 SCREEN_SIZE;
  static glm::vec2 ICON_SIZE;
  static glm::vec2 T0_POS;
  static glm::vec2 T1_POS;
  static glm::vec2 T2_POS;
  static glm::vec2 T3_POS;
  static glm::vec2 T4_POS;
  static glm::vec2 TIER_POS_OFFSET;
  static glm::vec2 T0_SIZE;
  static glm::vec2 TIER_SIZE;
  static glm::vec2 TIER_TAIL;
  static glm::vec2 TIER_LETTER_SIZE;
  static glm::vec2 TIER_LABEL_OFFSET;
  static glm::vec2 TIER_SCROLL_SPEED;
  static glm::vec2 TIER_SPACING;
  static glm::vec2 TIER_BG_PADDING;
  static std::vector<std::string> character_list;

  static void calculateNewScale(glm::vec2 new_screen_size);
  static glm::vec2 getScale();
};
