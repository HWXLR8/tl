#ifndef CONFIG_H
#define CONFIG_H

#include <glm/glm.hpp>

const float SCALE = 1.0;
const glm::vec2 SCREEN_SIZE {1600, 900};
const glm::vec2 FIELD_CARD_SIZE {86, 123};
const glm::vec2 HAND_CARD_SIZE {105, 153};
const glm::vec2 PLAYMAT_SIZE {858, 647};
const glm::vec2 MAG_CARD_SIZE {500 * 1/1.4576271186, 500};
const glm::vec2 DEFAULT_GROWTH_SPEED {210, 306};
const glm::vec3 DEFAULT_TSUK_SPEED {700, 0, 400};
const int DEFAULT_FLIP_SPEED = 800;
const int DEFAULT_POSITION_CHANGE_SPEED = 500;

struct GameCoord {

} const COORD;

#endif
