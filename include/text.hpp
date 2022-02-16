#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <ascii_graphic.hpp>
#include <graphic.hpp>

class Text {
public:
  Text(std::string text, glm::vec2 position, glm::vec2 letter_size, glm::vec2 spacing);
  void render(Renderer* renderer);

private:
  std::vector<ASCIIGraphic*> letters_;
  ASCIIGraphic* letter;
};
