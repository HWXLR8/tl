#include <config.hpp>

glm::vec2 Config::SCALE = {1.0, 1.0};
glm::vec2 Config::SCREEN_SIZE = {1600, 900};
glm::vec2 Config::ICON_SIZE = {70, 70};
glm::vec2 Config::T0_POS = {SCREEN_SIZE.x - 6 * ICON_SIZE.x, 0};
glm::vec2 Config::T1_POS = {20, ICON_SIZE.y};
glm::vec2 Config::T2_POS = T1_POS + glm::vec2{0, ICON_SIZE.y} + TIER_SPACING;
glm::vec2 Config::T3_POS = T2_POS + glm::vec2{0, ICON_SIZE.y} + TIER_SPACING;
glm::vec2 Config::T4_POS = T3_POS + glm::vec2{0, ICON_SIZE.y} + TIER_SPACING;
glm::vec2 Config::T0_SIZE = {6 * ICON_SIZE.x, SCREEN_SIZE.y};
glm::vec2 Config::TIER_SIZE = {14 * ICON_SIZE.x, ICON_SIZE.y};
glm::vec2 Config::TIER_TAIL = {60, 0};
glm::vec2 Config::TIER_LETTER_SIZE {20, 20};
glm::vec2 Config::TIER_LABEL_OFFSET {0, TIER_LETTER_SIZE.y + 8};
glm::vec2 Config::TIER_SCROLL_SPEED = {0, 30};
glm::vec2 Config::TIER_SPACING = {0, 70};

void Config::calculateNewScale(glm::vec2 new_screen_size) {
  SCALE = new_screen_size / SCREEN_SIZE;
  ICON_SIZE *= SCALE;
  TIER_SIZE *= SCALE;
  T0_SIZE *= SCALE;
  T0_POS *= SCALE;
  T1_POS *= SCALE;
  T2_POS *= SCALE;
  T3_POS *= SCALE;
  T4_POS *= SCALE;
  TIER_TAIL *= SCALE;
  TIER_LETTER_SIZE *= SCALE;
  TIER_LABEL_OFFSET *= SCALE;
  TIER_SCROLL_SPEED *= SCALE;
  TIER_SPACING *= SCALE;

  SCREEN_SIZE = new_screen_size;
}

glm::vec2 Config::getScale() {
  return SCALE;
}
