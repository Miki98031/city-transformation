#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader.h>
#include <GL/gl.h>
#include <vector>
#include "../resources/buildings/Building.h"
#include "../resources/terrains/Cobblestone.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

void drawBuildingBase(Shader buildingBaseShader, std::vector<Building*> &buildings);

void drawBuildingRoof(Shader buildingRoofShader, std::vector<Building*> &buildings);

void drawCobblestone(Shader shader, Cobblestone cobblestone, unsigned cobblestone_texture);

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

// camera
glm::vec3 cameraPos   = glm::vec3( 12.0f,  0.0f, -12.0f);
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

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // glfw window creation
    // --------------------
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

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader buildingRoofShader("resources/shaders/buildingRoof.vs", "resources/shaders/buildingRoof.fs");
    Shader buildingBaseShader("resources/shaders/buildingBase.vs", "resources/shaders/buildingBase.fs");

    Shader cobblestoneShader("resources/shaders/cobblestone.vs", "resources/shaders/cobblestone.fs");

    std::vector<Building*> buildings;
    Building::makeInnerBuildings(buildings);
    Building::makeWalls(buildings);

    Cobblestone cobblestone;
    unsigned cobblestone_texture = Cobblestone::getCobblestoneTexture();

    cobblestoneShader.use();
    cobblestoneShader.setInt("texture1", 0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawBuildingBase(buildingBaseShader, buildings);
        drawBuildingRoof(buildingRoofShader, buildings);

        drawCobblestone(cobblestoneShader, cobblestone, cobblestone_texture);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawBuildingBase(Shader buildingBaseShader, std::vector<Building*> &buildings) {
    buildingBaseShader.use();
    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    glm::mat4 buildingBaseProjection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    buildingBaseShader.setMat4("buildingBaseProjection", buildingBaseProjection);

    // camera/view transformation
    glm::mat4 buildingBaseView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    buildingBaseShader.setMat4("buildingBaseView", buildingBaseView);

    // render boxes
    glBindVertexArray(BuildingBase::getBuildingBaseVAO());
    int buildingBaseLength = buildings.size();
    //std::cout << BuildingBase::getBuildingBaseVAO() << "--" << std::endl;

    for (int i = 0; i < buildingBaseLength; i++)
    {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 buildingBaseModel = glm::mat4(1.0f);

        buildingBaseModel = glm::translate(buildingBaseModel, buildings[i]->getAdditionalTranslate());

        buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(buildings[i]->getRotateAngle()), glm::vec3(0.0f, 10.0f, 0.0f));

        buildingBaseModel = glm::translate(buildingBaseModel, buildings[i]->getPosition() + glm::vec3(0.0, 0.5, 0.0));

        buildingBaseModel = glm::scale(buildingBaseModel, glm::vec3(1.0, 1.0, 1.0));

        buildingBaseShader.setMat4("buildingBaseModel", buildingBaseModel);

        //set building color
        buildingBaseShader.setVec3("buildingBaseColor", glm::vec3((i+1.0)/buildingBaseLength, (i+1.0)/buildingBaseLength, (i+1.0)/buildingBaseLength));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void drawBuildingRoof(Shader buildingRoofShader, std::vector<Building*> &buildings) {
    buildingRoofShader.use();
    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    glm::mat4 buildingRoofProjection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    buildingRoofShader.setMat4("buildingRoofProjection", buildingRoofProjection);

    // camera/view transformation
    glm::mat4 buildingRoofView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    buildingRoofShader.setMat4("buildingRoofView", buildingRoofView);

    // render boxes
    glBindVertexArray(BuildingRoof::getBuildingRoofVAO());
    int buildingRoofLength = buildings.size();

    for (int i = 0; i < buildingRoofLength; i++) {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 buildingRoofModel = glm::mat4(1.0f);

        buildingRoofModel = glm::translate(buildingRoofModel, buildings[i]->getAdditionalTranslate());

        buildingRoofModel = glm::rotate(buildingRoofModel, glm::radians(buildings[i]->getRotateAngle()),
                                        glm::vec3(0.0f, 10.0f, 0.0f));

        buildingRoofModel = glm::translate(buildingRoofModel, buildings[i]->getPosition() + glm::vec3(0.0, 1.0, 0.0));

        buildingRoofModel = glm::scale(buildingRoofModel, glm::vec3(1.0, 1.0/4.0, 1.0));

        buildingRoofShader.setMat4("buildingRoofModel", buildingRoofModel);

        //set building color
        buildingRoofShader.setVec3("buildingRoofColor",
                                   glm::vec3((i + 1.0) / buildingRoofLength, (i + 1.0) / buildingRoofLength,
                                             (i + 1.0) / buildingRoofLength));

        glDrawArrays(GL_TRIANGLES, 0, 24);
    }
}

void drawCobblestone(Shader cobblestoneShader, Cobblestone cobblestone, unsigned cobblestone_texture) {
    //bind Texture
    cobblestoneShader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cobblestone_texture);

    float ang_rad = glm::radians(30.0); // angle in radians

    glm::mat2 rotMat;
/*            {
                    static_cast<float>(cos(ang_rad)), static_cast<float>(sin(ang_rad)),
                    static_cast<float>(-sin(ang_rad)), static_cast<float>(cos(ang_rad ))
            };*/

    //cobblestoneShader.setMat2("rotMat", rotMat);

    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    glm::mat4 cobblestoneProjection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    cobblestoneShader.setMat4("cobblestoneProjection", cobblestoneProjection);

    // camera/view transformation
    glm::mat4 cobblestoneView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    cobblestoneShader.setMat4("cobblestoneView", cobblestoneView);

    // render boxes
    glBindVertexArray(Cobblestone::getCobblestoneVAO());

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 cobblestoneModel = glm::mat4(1.0f);

    //cobblestoneModel = glm::translate(cobblestoneModel, buildings[i]->getAdditionalTranslate());

    //cobblestoneModel = glm::rotate(cobblestoneModel, glm::radians(buildings[i]->getRotateAngle()), glm::vec3(0.0f, 10.0f, 0.0f));

    cobblestoneModel = glm::translate(cobblestoneModel, glm::vec3(0.0, 0.0, 0.0));

    cobblestoneModel = glm::scale(cobblestoneModel, glm::vec3(1.0, 1.0, 1.0));

    cobblestoneShader.setMat4("cobblestoneModel", cobblestoneModel);

    //set building color
    //cobblestoneShader.setVec3("cobblestoneColor", 0.0, 1.0, 0.0);

    glDrawArrays(GL_TRIANGLES, 0, 12);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
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
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}