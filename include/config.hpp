#pragma once

#include <glm/glm.hpp>

class Config {
public:
  static glm::vec2 SCREEN_SIZE;
  static glm::vec2 ICON_SIZE;
  static glm::vec2 T1_POS;
  static glm::vec2 T2_POS;
  static glm::vec2 T3_POS;
  static glm::vec2 T4_POS;
  static glm::vec2 TIER_SIZE;
  static glm::vec2 TIER_TAIL;
  static glm::vec2 TIER_LETTER_SIZE;
  static glm::vec2 TIER_LABEL_OFFSET;
  static float TIER_SCROLL_SPEED;
  static float TIER_SPACING;
};

const float SCALE = 1.0;
