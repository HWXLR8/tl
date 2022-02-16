#pragma once

#include <glm/glm.hpp>

const float SCALE = 1.0;
const glm::vec2 SCREEN_SIZE {1600, 900};
const glm::vec2 ICON_SIZE {70, 70};
const glm::vec2 TIER_PADDING {20, 20};

// tier size
const glm::vec2 TIER_SIZE {14 * ICON_SIZE.x, ICON_SIZE.y};
const glm::vec2 TIER_LETTER_SIZE {20, 20};

// tier positions
const float TIER_SPACING = 70;
const glm::vec2 T1_POS = {TIER_PADDING.x, 70};
const glm::vec2 T2_POS = T1_POS + glm::vec2{0, ICON_SIZE.y + TIER_SPACING};
const glm::vec2 T3_POS = T2_POS + glm::vec2{0, ICON_SIZE.y + TIER_SPACING};
const glm::vec2 T4_POS = T3_POS + glm::vec2{0, ICON_SIZE.y + TIER_SPACING};
