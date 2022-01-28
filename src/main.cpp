#include <iostream>

#include <game.hpp>

int main(int argc, char** argv) {
  Game* game = nullptr;
  try {
    game = new Game();
    game->run();
  } catch (const std::exception& e) {
    std::cerr << "\033[1;31mERROR: \033[0m" << e.what() << std::endl;
  }
  // only delete game if it was successfully initialized
  if (game != nullptr) {
    delete game;
  }
  return 0;
}
