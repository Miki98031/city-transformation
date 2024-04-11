#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <learnopengl/shader.h>
#include <vector>
#include "learnopengl/model.h"
#include "drawing.h"
#include "../resources/buildings/Door.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod);

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

// camera
glm::vec3 cameraPos   = glm::vec3( 12.0f,  0.11f, -12.0f);
glm::vec3 cameraFront = glm::vec3(-5.0f, 0.0f, 1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//door
Door door;

int main() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // glfw window creation
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    Shader buildingRoofShader("resources/shaders/buildingRoof.vs", "resources/shaders/buildingRoof.fs");
    Shader buildingBaseShader("resources/shaders/buildingBase.vs", "resources/shaders/buildingBase.fs");

    Shader cobblestoneShader("resources/shaders/cobblestone.vs", "resources/shaders/cobblestone.fs");
    Shader grassShader("resources/shaders/grass.vs", "resources/shaders/grass.fs");
    Shader roadShader("resources/shaders/road.vs", "resources/shaders/road.fs");

    stbi_set_flip_vertically_on_load(true);
    //Shader backpackShader("resources/shaders/backpack.vs", "resources/shaders/backpack.fs");
    //Model backpack("resources/objects/backpack/backpack.obj");

    //Shader fountainShader("resources/shaders/fountain.vs", "resources/shaders/fountain.fs");
    //Model fountain("resources/objects/fountain/fountain.obj");

    Shader churchShader("resources/shaders/church.vs", "resources/shaders/church.fs");
    Model church("resources/objects/church/church.obj");

    Shader tavernShader("resources/shaders/tavern.vs", "resources/shaders/tavern.fs");
    Model tavern("resources/objects/tavern/tavern.obj");

    Shader leftDoorShader("resources/shaders/leftDoor.vs", "resources/shaders/leftDoor.fs");
    Model leftDoor("resources/objects/leftDoor/left-door.obj");

    Shader rightDoorShader("resources/shaders/rightDoor.vs", "resources/shaders/rightDoor.fs");
    Model rightDoor("resources/objects/rightDoor/right-door.obj");
    stbi_set_flip_vertically_on_load(false);

    std::vector<Building*> buildings;
    Building::makeInnerBuildings(buildings);
    Building::makeWalls(buildings);
    buildingBaseShader.use();
    buildingBaseShader.setInt("texture4", 3);
    buildingRoofShader.use();
    buildingRoofShader.setInt("texture5", 4);

    Cobblestone cobblestone;
    unsigned cobblestone_texture = Cobblestone::getCobblestoneTexture();
    cobblestoneShader.use();
    cobblestoneShader.setInt("texture1", 0);

    Grass grass;
    unsigned grass_texture = Grass::getGrassTexture();
    grassShader.use();
    grassShader.setInt("texture2", 1);

    Road road;
    unsigned road_texture = Road::getRoadTexture();
    roadShader.use();
    roadShader.setInt("texture3", 2);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawBuildingBase(buildingBaseShader, buildings, fov, cameraPos, cameraFront, cameraUp);
        drawBuildingRoof(buildingRoofShader, buildings, fov, cameraPos, cameraFront, cameraUp);

        drawCobblestone(cobblestoneShader, cobblestone, cobblestone_texture, fov, cameraPos, cameraFront, cameraUp);
        drawGrass(grassShader, grass, grass_texture, fov, cameraPos, cameraFront, cameraUp);
        drawRoad(roadShader, road, road_texture, fov, cameraPos, cameraFront, cameraUp);

        //drawBackpack(backpackShader, backpack, fov, cameraPos, cameraFront, cameraUp);
        //drawFountain(fountainShader, fountain, fov, cameraPos, cameraFront, cameraUp);
        drawChurch(churchShader, church, fov, cameraPos, cameraFront, cameraUp);
        //drawTavern(tavernShader, tavern, fov, cameraPos, cameraFront, cameraUp);

        drawDoor(leftDoorShader, leftDoor, rightDoorShader, rightDoor, fov, cameraPos, cameraFront, cameraUp, door);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    BuildingBase::freeBuffers();
    BuildingRoof::freeBuffers();
    Cobblestone::freeBuffers();
    Grass::freeBuffers();
    Road::freeBuffers();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    glm::vec3 cameraPosPrev = cameraPos;

    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    //prevent movement under terrain
    if (cameraPos.y < 0.11) {
        cameraPos.y = 0.11;
    }

    //prevent movement through buildings
    float buildingHeight = 2.0 + 0.11;
    if(cameraPos.y <= buildingHeight) {
        std::vector<std::pair<float, float>> buildingCenterPosition = Building::getBuildingCenterPosition();
        for (int i = 0; i < buildingCenterPosition.size(); i++) {
            float p = buildingCenterPosition[i].first;
            float q = buildingCenterPosition[i].second;
            float r = 0.7;

            if ((cameraPos.x - p) * (cameraPos.x - p) + (cameraPos.z - q) * (cameraPos.z - q) <= r * r) {
                cameraPos.x = cameraPosPrev.x;
                cameraPos.z = cameraPosPrev.z;
                cameraPos.y = cameraPosPrev.y;
            }
        }
    }

    //prevent movement through doors
    if (cameraPos.y < 2.11) {
        float a = 0.31;
        float b = 0.21;

        glm::vec3 leftDoorPosition = door.getLeftDoorPosition();
        float x1 = leftDoorPosition.x;
        float z1 = leftDoorPosition.z;
        float expression1 = (cameraPos.x - x1) * (cameraPos.x - x1) / (a*a) + (cameraPos.z - z1) * (cameraPos.z - z1) / (b*b);

        glm::vec3 rightDoorPosition = door.getRightDoorPosition();
        float x2 = rightDoorPosition.x;
        float z2 = rightDoorPosition.z;
        float expression2 = (cameraPos.x - x2) * (cameraPos.x - x2) / (a*a) + (cameraPos.z - z2) * (cameraPos.z - z2) / (b*b);

        if (expression1 <= 1.5 || expression2 <= 1.5) {
            cameraPos.x = cameraPosPrev.x;
            cameraPos.z = cameraPosPrev.z;
            cameraPos.y = cameraPosPrev.y;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.9f)
        pitch = 89.9f;
    if (pitch < -89.9f)
        pitch = -89.9f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
    if (key == GLFW_KEY_O && action == GLFW_PRESS) {
        if(door.isDoorClosed()) {
            std::cout << "Door opening" << std::endl;
            door.setDoorOpening(true);
            door.setDoorClosed(false);
        }
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        if(door.isDoorOpened()) {
            std::cout << "Door closing" << std::endl;
            door.setDoorClosing(true);
            door.setDoorOpened(false);
        }
    }
}