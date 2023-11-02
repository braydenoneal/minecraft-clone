#include <glm/vec3.hpp>
#include <list>

class GameContext {
public:
    glm::vec3 camera_position{glm::vec3(0.0f, 0.0f, -5.0f)};
    glm::vec3 camera_angle{glm::vec3(0.0f)};
    glm::vec3 model_position{glm::vec3(0.0f)};
    glm::vec3 model_angle{glm::vec3(0.0f)};
    int cube_count{1};
};
