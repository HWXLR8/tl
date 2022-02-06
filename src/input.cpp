#include <input.hpp>

#include <algorithm>

Input::Input(GLFWwindow* window) {
  // hack GLFW to accept a c++ member function as a callback
  glfwSetWindowUserPointer(window, this);
  auto keyCallbackAlias = [](GLFWwindow* window, int key, int scancode, int action, int mode) {
    static_cast<Input*>(glfwGetWindowUserPointer(window))->keyCallback(window, key, scancode, action, mode);
  };
  auto cursorPositionCallbackAlias = [](GLFWwindow* window, double xpos, double ypos) {
    static_cast<Input*>(glfwGetWindowUserPointer(window))->cursorPositionCallback(window, xpos, ypos);
  };
  auto scrollCallbackAlias = [](GLFWwindow* window, double xoffset, double yoffset) {
    static_cast<Input*>(glfwGetWindowUserPointer(window))->scrollCallback(window, xoffset, yoffset);
  };
  auto mouseButtonCallbackAlias = [](GLFWwindow* window, int button, int action, int mods) {
    static_cast<Input*>(glfwGetWindowUserPointer(window))->mouseButtonCallback(window, button, action, mods);
  };
  glfwSetKeyCallback(window, keyCallbackAlias);
  glfwSetCursorPosCallback(window, cursorPositionCallbackAlias);
  glfwSetScrollCallback(window, scrollCallbackAlias);
  glfwSetMouseButtonCallback(window, mouseButtonCallbackAlias);
}

void Input::runMouseCommand() {
  switch(mouse_action_) {

  case SCROLL_DOWN:
    break;

  case SCROLL_UP:
    break;
  }
  mouse_action_ = NONE;
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS) {
	keys_[key] = true;
    } else if (action == GLFW_RELEASE) {
      keys_[key] = false;
    }
  }
}

glm::vec2 Input::getMousePosition() {
  return mouse_pos_;
}

void Input::process(CharacterIcon* active_icon, CharacterIcon* held_icon, std::vector<Tier*> tiers, double dt) {
  if (click_ && held_icon != nullptr) {
    // get active tier
    for (auto& tier : tiers) {
      if (tier->isActive(mouse_pos_)) {
	tier->addExistingIcon(held_icon);
	held_icon->toggleDrag();
      }
    }
    click_ = false;
  } else if (click_ && active_icon != nullptr) {
    for (auto& tier : tiers) {
      tier->removeIcon(active_icon);
    }
    active_icon->toggleDrag();
    click_ = false;
  }
}

void Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
  mouse_pos_.x = xpos;
  mouse_pos_.y = ypos;
}

void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  if (yoffset == -1) {
    mouse_action_ = SCROLL_DOWN;
  } else if (yoffset == 1) {
    mouse_action_ = SCROLL_UP;
  }
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    click_ = !click_;
  }
}
