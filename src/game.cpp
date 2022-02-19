#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <thread>
#include <vector>

#include <game.hpp>
#include <resource_manager.hpp>
#include <renderer.hpp>
#include <config.hpp>

Renderer *renderer;

Game::Game() {
  // window/GL
  initGLFW();
  initGLAD();
  initGL();

  // hack GLFW to accept a c++ member function as a callback
  auto framebufferSizeCallbackAlias = [](GLFWwindow* window, int width, int height) {
    static_cast<Game*>(glfwGetWindowUserPointer(window))->framebufferSizeCallback(window, width, height);
  };
  auto windowSizeCallbackAlias = [](GLFWwindow* window, int width, int height) {
    static_cast<Game*>(glfwGetWindowUserPointer(window))->windowSizeCallback(window, width, height);
  };
  glfwSetFramebufferSizeCallback(window_, framebufferSizeCallbackAlias);
  glfwSetWindowSizeCallback(window_, windowSizeCallbackAlias);

  // main shader
  ResourceManager::loadShader("shader/vert.glsl", "shader/frag.glsl", nullptr, "static_image");
  glm::mat4 projection = glm::ortho(0.0f, Config::SCREEN_SIZE.x, Config::SCREEN_SIZE.y, 0.0f, -100.0f, 100.0f);
  ResourceManager::getShader("static_image").use().setInteger("image", 0);
  ResourceManager::getShader("static_image").setMatrix4("projection", projection);
  Shader shader = ResourceManager::getShader("static_image");
  renderer = new Renderer(shader);

  // load charater icons
  std::vector<std::string> characters = {
    // "alex",
    // "alph",
    "banjokazooie",
    "bayonetta",
    "bowser",
    "bowserjr",
    // "byleth",
    "bylethf",
    "captainfalcon",
    // "charizard",
    "chrom",
    "cloud",
    "corrin",
    "corrinfemale",
    "daisy",
    "darkpit",
    "darksamus",
    "diddykong",
    "donkeykong",
    "drmario",
    "duckhunt",
    "enderman",
    "falco",
    "fox",
    "ganondorf",
    "greninja",
    "hero-dqiii",
    // "hero-dqiv",
    // "hero-dqviii",
    // "hero-dqxi",
    "icies",
    "ike",
    "incineroar",
    "inkling",
    // "inklingmale",
    "isabelle",
    // "ivysaur",
    "jigglypuff",
    "joker",
    "kazuya",
    "ken",
    "kingdedede",
    "kingkrool",
    "kirby",
    "link",
    "littlemac",
    "lucario",
    "lucas",
    "lucina",
    "luigi",
    "mario",
    "marth",
    "megaman",
    "metaknight",
    "mewtwo",
    "miifighter-brawler",
    "miifighter-shooter",
    "miifighter-sword",
    "minmin",
    "mrgameandwatch",
    // "mythra",
    "ness",
    "pacman",
    "palutena",
    "peach",
    "pichu",
    "pikachu",
    "pikminandolimar",
    "piranhaplant",
    "pit",
    // "pokemontrainer",
    "pokemontrainerfemale",
    // "pyra",
    "pyra_mythra",
    "richter",
    "ridley",
    "rob",
    "robin",
    // "robinfemale",
    "rosalinaandluma",
    "roy",
    "ryu",
    "samus",
    // "sans",
    "sephiroth",
    "sheik",
    "shulk",
    "simon",
    "snake",
    "sonicthehedgehog",
    "sora",
    // "squirtle",
    "steve",
    "terry",
    "toonlink",
    "villager",
    "wario",
    // "wiifitmale",
    "wiifittrainer",
    "wolf",
    "yoshi",
    "younglink",
    "zelda",
    "zerosuitsamus",
    // "zombie",
  };
  Tier* character_pool = new Tier(0, "", glm::vec2{Config::SCREEN_SIZE.x - 6 * Config::ICON_SIZE.x, 0}, glm::vec2{6 * Config::ICON_SIZE.x, Config::SCREEN_SIZE.y}, characters);
  Tier* t1 = new Tier(1, "TOP TIER", Config::T1_POS, Config::TIER_SIZE, std::nullopt);
  Tier* t2 = new Tier(2, "HIGH TIER", Config::T2_POS, Config::TIER_SIZE, std::nullopt);
  Tier* t3 = new Tier(3, "MID TIER", Config::T3_POS, Config::TIER_SIZE, std::nullopt);
  Tier* t4 = new Tier(4, "LOW TIER", Config::T4_POS, Config::TIER_SIZE, std::nullopt);
  tiers_.push_back(character_pool);
  tiers_.push_back(t1);
  tiers_.push_back(t2);
  tiers_.push_back(t3);
  tiers_.push_back(t4);

  // input
  input_ = new Input(window_);
}

Game::~Game() {
  ResourceManager::clear();
  glfwTerminate();
}

void Game::initGLFW() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif
  glfwWindowHint(GLFW_RESIZABLE, false);
  window_ = glfwCreateWindow(Config::SCREEN_SIZE.x, Config::SCREEN_SIZE.y, "SSBU TIER LIST", nullptr, nullptr);
  glfwMakeContextCurrent(window_);
}

void Game::initGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
    return;
  }
}

void Game::initGL() {
  glViewport(0, 0, Config::SCREEN_SIZE.x, Config::SCREEN_SIZE.y);
  // glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  glm::vec2 new_screen_size {width, height};
  recalculateProjectionMatrix(new_screen_size);
}

// TODO is this necessary?
void Game::windowSizeCallback(GLFWwindow* window, int width, int height) {
  // glm::vec2 new_screen_size {width, height};
  // recalculateProjectionMatrix(new_screen_size);
}

void Game::recalculateProjectionMatrix(glm::vec2 new_screen_size) {
  glm::mat4 projection = glm::ortho(0.0f, new_screen_size.x, new_screen_size.y, 0.0f, -100.0f, 100.0f);
  ResourceManager::getShader("static_image").setMatrix4("projection", projection);
}

void Game::update(double dt) {
  mouse_pos_ = input_->getMousePosition();
  getActiveIcon();
  input_->process(active_icon_, held_icon_, tiers_, dt);
  // store the held icon so we don't lose it after removing it from the container
  if (active_icon_ != nullptr && active_icon_->isBeingDragged()) {
    held_icon_ = active_icon_;
  } else {
    held_icon_ = nullptr;
  }
  if (held_icon_ != nullptr) {
    held_icon_->update(mouse_pos_, dt);
  }

  // update tiers
  for (auto& tier : tiers_) {
    bool part_icons = false;
    if (held_icon_ != nullptr) {
      part_icons = true;
    }

    // update position relative to all previous tier sizes, this is disgusting
    int tier_num = tier->getTierNumber();
    // tier 0 and 1 never move
    if (tier_num != 0 && tier_num != 1) {
      // new tier position, the cumulative size of all previous tiers plus 20 pixel space
      glm::vec2 new_pos = Config::T1_POS;
      for (int c = 1; c != tier_num; c++) {
	new_pos.y += tiers_[c]->getSize().y;
	new_pos.y += Config::TIER_SPACING;
      }
      tier->setPosition(new_pos);
    }

    tier->update(mouse_pos_, part_icons, dt);
  }
}

void Game::render() {
  Shader static_image = ResourceManager::getShader("static_image");
  renderer->setShader(static_image);
  for (auto& tier : tiers_) {
    tier->render(renderer);
  }
  if (active_icon_ != nullptr) {
    active_icon_->render(renderer);
  }
  if (held_icon_ != nullptr) {
    held_icon_->render(renderer);
  }
}

void Game::run() {
  double dt = 0.0;
  double lastFrame = glfwGetTime();
  while (!glfwWindowShouldClose(window_)) {
    double currentFrame = glfwGetTime();
    dt = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents();

    update(dt);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    render();
    glfwSwapBuffers(window_);
  }
}

void Game::getActiveIcon() {
  if (held_icon_ != nullptr) {
    active_icon_ = held_icon_;
    return;
  }

  CharacterIcon* active_icon = nullptr;
  for (auto& tier : tiers_) {
    active_icon = tier->getActiveIcon(mouse_pos_);
    if (active_icon != nullptr) {
      active_icon_ = active_icon;
      return;
    }
  }
  active_icon_ = nullptr;
}
