#include <config.hpp>

glm::vec2 Config::SCALE = {1.0, 1.0};
glm::vec2 Config::SCREEN_SIZE = {1600, 900};
glm::vec2 Config::ICON_SIZE = {70, 70};
glm::vec2 Config::T0_POS = {SCREEN_SIZE.x - 6 * ICON_SIZE.x, 0};
glm::vec2 Config::T1_POS = {20, ICON_SIZE.y};
glm::vec2 Config::T2_POS = T1_POS + glm::vec2{0, ICON_SIZE.y} + TIER_SPACING;
glm::vec2 Config::T3_POS = T2_POS + glm::vec2{0, ICON_SIZE.y} + TIER_SPACING;
glm::vec2 Config::T4_POS = T3_POS + glm::vec2{0, ICON_SIZE.y} + TIER_SPACING;
glm::vec2 Config::TIER_POS_OFFSET = {7.5, 7.5};
glm::vec2 Config::T0_SIZE = {6 * ICON_SIZE.x, SCREEN_SIZE.y};
glm::vec2 Config::TIER_SIZE = {14 * ICON_SIZE.x, ICON_SIZE.y};
glm::vec2 Config::TIER_TAIL = {60, 0};
glm::vec2 Config::TIER_LETTER_SIZE {20, 20};
glm::vec2 Config::TIER_LABEL_OFFSET {0, TIER_LETTER_SIZE.y + 8};
glm::vec2 Config::TIER_SCROLL_SPEED = {0, 30};
glm::vec2 Config::TIER_SPACING = {0, 70};
glm::vec2 Config::TIER_BG_PADDING = {15, 15};
std::vector<std::string> Config::character_list = {
  "mario",
  "donkeykong",
  "link",
  "samus",
  "darksamus",
  "yoshi",
  "kirby",
  "fox",
  "pikachu",
  "luigi",
  "ness",
  "captainfalcon",
  "jigglypuff",
  "peach",
  "daisy",
  "bowser",
  "icies",
  "sheik",
  "zelda",
  "drmario",
  "pichu",
  "falco",
  "marth",
  "lucina",
  "younglink",
  "ganondorf",
  "mewtwo",
  "roy",
  "chrom",
  "mrgameandwatch",
  "metaknight",
  "pit",
  "darkpit",
  "zerosuitsamus",
  "wario",
  "snake",
  "ike",
  // "pokemontrainer",
  "pokemontrainerfemale",
  "diddykong",
  "lucas",
  "sonicthehedgehog",
  "kingdedede",
  "pikminandolimar",
  "lucario",
  "rob",
  "toonlink",
  "wolf",
  "villager",
  "megaman",
  // "wiifitmale",
  "wiifittrainer",
  "rosalinaandluma",
  "littlemac",
  "greninja",
  "palutena",
  "pacman",
  "robin",
  // "robinfemale",
  "shulk",
  "bowserjr",
  "duckhunt",
  "ryu",
  "ken",
  "cloud",
  "corrin",
  // "corrinfemale",
  "bayonetta",
  "inkling",
  // "inklingmale",
  "ridley",
  "simon",
  "richter",
  "kingkrool",
  "isabelle",
  "incineroar",
  "piranhaplant",
  "joker",
  "hero-dqiii",
  // "hero-dqiv",
  // "hero-dqviii",
  // "hero-dqxi",
  "banjokazooie",
  "terry",
  // "byleth",
  "bylethf",
  "minmin",
  "steve",
  "sephiroth",
  "pyra_mythra",
  "kazuya",
  "sora",
  "miifighter-brawler",
  "miifighter-sword",
  "miifighter-shooter",

  // "ivysaur",
  // "alex",
  // "alph",
  // "charizard",
  // "enderman",
  // "mythra",
  // "pyra",
  // "sans",
  // "squirtle",
  // "zombie",
};


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
  TIER_POS_OFFSET *= SCALE;
  TIER_TAIL *= SCALE;
  TIER_LETTER_SIZE *= SCALE;
  TIER_LABEL_OFFSET *= SCALE;
  TIER_SCROLL_SPEED *= SCALE;
  TIER_SPACING *= SCALE;
  TIER_BG_PADDING *= SCALE;

  SCREEN_SIZE = new_screen_size;
}

glm::vec2 Config::getScale() {
  return SCALE;
}
