#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <thread>

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
  glm::mat4 projection = glm::ortho(0.0f, SCREEN_SIZE.x, SCREEN_SIZE.y, 0.0f, -100.0f, 100.0f);
  ResourceManager::getShader("static_image").use().setInteger("image", 0);
  ResourceManager::getShader("static_image").setMatrix4("projection", projection);
  Shader shader = ResourceManager::getShader("static_image");
  renderer = new Renderer(shader);

  // load charater icons
  CharacterIcon* t = new CharacterIcon("assets/terry.png", glm::vec2(0, 0));
  character_list_.insert({"terry", t});

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
  window_ = glfwCreateWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "SSBU TIER LIST", nullptr, nullptr);
  glfwMakeContextCurrent(window_);
}

void Game::initGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
    return;
  }
}

void Game::initGL() {
  glViewport(0, 0, SCREEN_SIZE.x, SCREEN_SIZE.y);
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
  updateActiveIcon();
  input_->process(active_icon_, dt);
}

void Game::render() {
  Shader static_image = ResourceManager::getShader("static_image");
  renderer->setShader(static_image);
  for (auto& [key, val] : character_list_) {
    val->render(renderer);
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

void Game::updateActiveIcon() {
  active_icon_ == std::nullopt;
  for (auto& [key, val] : character_list_) {
    if (val->isActive(mouse_pos_)) {
      active_icon_ = val;
    }
  }
}
