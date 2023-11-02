#include <map>
#include <list>
#include <iostream>

class Input {
public:
    WindowContext *window_context;
    GameContext *game_context;

    std::map<int, int> keys;

    Input(WindowContext *input_window_context, GameContext *input_game_context) {
        window_context = input_window_context;
        game_context = input_game_context;

        glfwSetWindowUserPointer(window_context->window, this);
        glfwSetKeyCallback(window_context->window, key_callback);
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto *input = (Input *) glfwGetWindowUserPointer(window);
        input->keys[key] = action;
    }

    void do_actions() {
        for (std::pair<const int, int> key : keys) {
            if (keys[key.first]) {
                Action::do_action(key.first, window_context, game_context);
            }
        }
    }
};
