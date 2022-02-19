#include <config.hpp>

glm::vec2 Config::SCREEN_SIZE = {1600, 900};
glm::vec2 Config::ICON_SIZE = {70, 70};
glm::vec2 Config::T1_POS = {20, ICON_SIZE.y};
glm::vec2 Config::T2_POS = T1_POS + glm::vec2{0, ICON_SIZE.y + TIER_SPACING};
glm::vec2 Config::T3_POS = T2_POS + glm::vec2{0, ICON_SIZE.y + TIER_SPACING};
glm::vec2 Config::T4_POS = T3_POS + glm::vec2{0, ICON_SIZE.y + TIER_SPACING};
glm::vec2 Config::TIER_SIZE = {14 * ICON_SIZE.x, ICON_SIZE.y};
glm::vec2 Config::TIER_TAIL = {60, 0};
glm::vec2 Config::TIER_LETTER_SIZE {20, 20};
glm::vec2 Config::TIER_LABEL_OFFSET {0, TIER_LETTER_SIZE.y + 8};
float Config::TIER_SCROLL_SPEED = 30;
float Config::TIER_SPACING = 70;
