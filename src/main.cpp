#include <iostream>

#include <glprg.hpp>

int main(int argc, char** argv) {
  GLPRG* game = nullptr;
  try {
    game = new GLPRG();
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
