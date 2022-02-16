#include <text.hpp>

Text::Text(std::string text, glm::vec2 position, glm::vec2 letter_size, glm::vec2 spacing) {
  letter_size_ = letter_size;
  int c = 0;
  for (auto ch : text) {
    glm::vec2 pos = {position.x + letter_size.x * c, position.y};
    letter = new ASCIIGraphic(ch, "assets/ascii.gif", pos, letter_size, true);
    letters_.push_back(letter);
    c++;
  }
}

void Text::render(Renderer* renderer) {
  for (auto& letter : letters_) {
    letter->render(renderer);
  }
}

void Text::setPosition(glm::vec2 position) {
  int c = 0;
  for (auto& letter : letters_) {
    glm::vec2 pos = {position.x + letter_size_.x * c, position.y};
    letter->setPosition(pos);
    c++;
  }
}
