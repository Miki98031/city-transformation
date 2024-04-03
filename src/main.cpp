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

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

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

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
    };

    // world space positions of our cubes
    std::vector<glm::vec3> buildingBasePositions = {
            //zeleni venac far upper side
            glm::vec3( 3.0f,  0.0f, -2.0f),
            glm::vec3( 4.0f,  0.0f, -2.0f),
            glm::vec3( 5.0f,  0.0f, -2.0f),

            //zeleni venac near upper side
            glm::vec3( 3.0f,  0.0f, -0.0f),
            glm::vec3( 4.0f, 0.0f, -0.0f),
            glm::vec3(5.0f,  0.0f, -0.0f),
            glm::vec3( 6.0f,  0.0f, -0.0f),
            glm::vec3( 7.0f, 0.0f, -0.0f),
            glm::vec3(8.0f,  0.0f, -0.0f),

            //zadarska middle near side
            glm::vec3( 2.0f,  0.0f, -5.0f),
            glm::vec3( 3.0f,  0.0f, -5.0f),
            glm::vec3( 4.0f,  0.0f, -5.0f),

            //zadarska lower near side
            glm::vec3( -1.0f,  0.0f, -6.0f),
            glm::vec3( 0.0f,  0.0f, -6.0f),

            //zadarska middle far side
            glm::vec3( 2.0f,  0.0f, -7.0f),
            glm::vec3( 3.0f,  0.0f, -7.0f),
            glm::vec3( 4.0f,  0.0f, -7.0f),

            //zadarska lower far side
            glm::vec3( -1.0f,  0.0f, -8.0f),
            glm::vec3( 0.0f,  0.0f, -8.0f),
            glm::vec3( 1.0f,  0.0f, -8.0f),

            //kralja petra near side
            glm::vec3( 0.0f,  0.0f, -8.7f),
            glm::vec3( 1.0f,  0.0f, -8.7f),
            glm::vec3( 2.0f,  0.0f, -8.7f),
            //glm::vec3( 3.0f,  0.0f, -8.7f),
            glm::vec3( 4.0f,  0.0f, -8.7f),
            glm::vec3( 5.0f,  0.0f, -8.7f),
            glm::vec3( 6.0f,  0.0f, -8.7f),

            //kralja petra far side
            glm::vec3( 0.1f,  0.0f, -10.4f),
            glm::vec3( 1.1f,  0.0f, -10.4f),
            glm::vec3( 2.1f,  0.0f, -10.4f),
            //glm::vec3( 3.1f,  0.0f, -10.4f),
            glm::vec3( 4.1f,  0.0f, -10.4f),
            glm::vec3( 5.1f,  0.0f, -10.4f),
            glm::vec3( 6.1f,  0.0f, -10.4f),

            //river upper far side
            glm::vec3( -1.0f,  0.0f, -11.4f),
            glm::vec3( -1.0f,  0.0f, -12.4f),
            glm::vec3( -1.0f,  0.0f, -13.4f),
            glm::vec3( -1.0f,  0.0f, -14.4f),
            glm::vec3( -1.0f,  0.0f, -15.4f),
            glm::vec3( -1.0f,  0.0f, -16.4f),
            glm::vec3( -1.0f,  0.0f, -17.4f),

            //river upper near side
            //glm::vec3( -3.0f,  0.0f, -10.4f),
            glm::vec3( -3.0f,  0.0f, -11.4f),
            glm::vec3( -3.0f,  0.0f, -12.4f),
            glm::vec3( -3.0f,  0.0f, -13.4f),
            glm::vec3( -3.0f,  0.0f, -14.4f),
            glm::vec3( -3.0f,  0.0f, -15.4f),
            glm::vec3( -3.0f,  0.0f, -16.4f),
            glm::vec3( -3.0f,  0.0f, -17.4f),
            glm::vec3( -3.0f,  0.0f, -18.4f),
            glm::vec3( -3.0f,  0.0f, -19.4f),
            glm::vec3( -3.0f,  0.0f, -20.4f),
            glm::vec3( -3.0f,  0.0f, -21.4f),

            //river lower near side
            glm::vec3( -3.0f,  0.0f,  0.6f),
            glm::vec3( -3.0f,  0.0f,  -0.4f),
            glm::vec3( -3.0f,  0.0f, -1.4f),
            glm::vec3(-3.0f, 0.0f, -2.4f),
            glm::vec3(-3.0f, 0.0f, -3.4f),
            glm::vec3( -3.0f, 0.0f, -4.4f),
            glm::vec3( -3.0f,  0.0f,  -5.4f),
            glm::vec3( -3.0f,  0.0f, -6.4f),
            glm::vec3(-3.0f, 0.0f, -7.4f),
            glm::vec3(-3.0f, 0.0f, -8.4f),
            glm::vec3( -3.0f, 0.0f, -9.4f),

            //river lower far side
            glm::vec3( -1.0f,  0.0f, -5.0f),
            glm::vec3(0.0f, 0.0f, -5.0f),

            //zeleni venac near lower side
            glm::vec3(-2.07f,  0.0f, 0.11f),
            glm::vec3( -1.07f, 0.0f, 0.11f),
            glm::vec3( -0.07f,  0.0f, 0.11f),
            glm::vec3( 0.93f, 0.0f, 0.11f),
            glm::vec3( 1.93f,  0.0f, 0.11f),

            //kneza sime markovica near side
            glm::vec3( 4.6f,  0.0f, -13.4f),
            glm::vec3( 4.6f,  0.0f, -14.4f),
            glm::vec3( 4.6f,  0.0f, -15.4f),
            glm::vec3( 4.6f,  0.0f, -16.4f),
            glm::vec3( 4.6f,  0.0f, -17.4f),

            //kneza sime markovica far side
            glm::vec3( 6.6f,  0.0f, -11.4f),
            glm::vec3( 6.6f,  0.0f, -12.4f),
            glm::vec3( 6.6f,  0.0f, -13.4f),
            glm::vec3( 6.6f,  0.0f, -14.4f),
            glm::vec3( 6.6f,  0.0f, -15.4f),
            glm::vec3( 6.6f,  0.0f, -16.4f),
            glm::vec3( 6.6f,  0.0f, -17.4f),
            glm::vec3( 6.6f,  0.0f, -18.4f),
            glm::vec3( 6.6f,  0.0f, -19.4f),
            glm::vec3( 6.6f,  0.0f, -20.4f),
            glm::vec3( 6.6f,  0.0f, -21.4f),

            //pop-lukina near side
            glm::vec3( 7.5f,  0.0f, -6.8f),
            glm::vec3( 7.5f,  0.0f, -7.8f),
            glm::vec3( 7.5f,  0.0f, -8.8f),
            glm::vec3( 7.5f,  0.0f, -9.8f),

            //pop-lukina far side
            glm::vec3( 9.5f,  0.0f, -2.8f),
            glm::vec3( 9.5f,  0.0f, -3.8f),
            glm::vec3( 9.5f,  0.0f, -4.8f),
            glm::vec3( 9.5f,  0.0f, -5.8f),
            glm::vec3( 9.5f,  0.0f, -6.8f),
            glm::vec3( 9.5f,  0.0f, -7.8f),
            glm::vec3( 9.5f,  0.0f, -8.8f),
            glm::vec3( 9.5f,  0.0f, -9.8f),
            glm::vec3( 9.5f,  0.0f, -10.8f),

            //srebrenicka upper side
            glm::vec3(2.0f, 0.0f, -2.215f),
            glm::vec3( 2.0f,  0.0f, -3.215f),
            glm::vec3(2.0f,  0.0f, -4.215f),
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //building roof vertices
    float buildingRoofVertices[] = {
            //base
            0.5f, 0.0f, 0.5f,
            0.5f, 0.0f, -0.5f,
            -0.5f, 0.0f, -0.5f,

            -0.5f, 0.0f, -0.5f,
            -0.5f, 0.0f, 0.5f,
            0.5f, 0.0f, 0.5f,


            //front plane
            -0.5f, 0.0f, -0.5f,
            0.5f, 0.0f, -0.5f,
            0.5f, 1.0f, 0.0f,

            0.5f, 1.0f, 0.0f,
            -0.5f, 1.0f, 0.0f,
            -0.5f, 0.0f, -0.5f,


            //back plane
            -0.5f, 0.0f, 0.5f,
            0.5f, 0.0f, 0.5f,
            0.5f, 1.0f, 0.0f,

            0.5f, 1.0f, 0.0f,
            -0.5f, 1.0f, 0.0f,
            -0.5f, 0.0f, 0.5f,


            //left side
            -0.5f, 0.0f, -0.5f,
            -0.5f, 0.0f, 0.5f,
            -0.5f, 1.0f, 0.0f,


            //right side
            0.5f, 0.0f, -0.5f,
            0.5f, 0.0f, 0.5f,
            0.5f, 1.0f, 0.0f
    };

    std::vector<glm::vec3> buildingRoofPositions = {
            glm::vec3(-3.0f, 0.5f, 0.0f),
            glm::vec3( -3.0f,  0.5f, -1.0f),
            glm::vec3(-3.0f, 0.5f, -2.0f),
            glm::vec3(-3.0f, 0.5f, -3.0f),
            glm::vec3( -3.0f, 0.5f, -4.0f),

            glm::vec3(-2.0f,  0.5f, 0.0f),
            glm::vec3( -1.0f, 0.5f, 0.0f),
            glm::vec3( 0.0f,  0.5f, 0.0f),
            glm::vec3( 1.0f, 0.5f, 0.0f),
            glm::vec3( 2.0f,  0.5f, 0.0f),
            glm::vec3(3.0f,  0.5f, 0.0f),
            glm::vec3( 4.0f, 0.5f, 0.0f),
            glm::vec3( 5.0f,  0.5f, 0.0f),
            glm::vec3( 6.0f, 0.5f, 0.0f),
            glm::vec3( 7.0f,  0.5f, 0.0f),


            //glm::vec3( 2.0f,  0.5f, -1.0f),
            glm::vec3(2.0f,  0.5f, -2.0f),
            glm::vec3( 2.0f,  0.5f, -3.0f),
            glm::vec3(2.0f,  0.5f, -4.0f)
    };

    unsigned int buildingRoofVBO, buildingRoofVAO;
    glGenVertexArrays(1, &buildingRoofVAO);
    glGenBuffers(1, &buildingRoofVBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(buildingRoofVAO);

    glBindBuffer(GL_ARRAY_BUFFER, buildingRoofVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buildingRoofVertices), buildingRoofVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    auto buildingBaseLength = buildingBasePositions.size();
    auto buildingRoofLength = buildingRoofPositions.size();

    buildingBaseShader.use();

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

        buildingBaseShader.use();

        // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
        // -----------------------------------------------------------------------------------------------------------
        glm::mat4 buildingRoofProjection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        buildingRoofShader.setMat4("buildingRoofProjection", buildingRoofProjection);

        // camera/view transformation
        glm::mat4 buildingRoofView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
        buildingRoofShader.setMat4("buildingRoofView", buildingRoofView);

        glBindVertexArray(buildingRoofVAO);
        for (unsigned int i = 0; i < buildingRoofLength; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 buildingRoofModel = glm::mat4(1.0f);
            buildingRoofModel = glm::translate(buildingRoofModel, buildingRoofPositions[i] + glm::vec3(0.0, 0.0, 0.0));
            buildingRoofModel = glm::rotate(buildingRoofModel, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            buildingRoofModel = glm::scale(buildingRoofModel, glm::vec3(1.0, 1.0/4.0, 1.0));
            //float angle = 20.0f * i;
            //buildingRoofModel = glm::rotate(buildingRoofModel, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            buildingRoofShader.setMat4("buildingRoofModel", buildingRoofModel);
            //set building color
            buildingRoofShader.setVec3("buildingRoofColor", glm::vec3((i+1.0)/buildingRoofLength, 1.0, 1.0));

            //glDrawArrays(GL_TRIANGLES, 0, 24);
        }


        // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
        // -----------------------------------------------------------------------------------------------------------
        glm::mat4 buildingBaseProjection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        buildingBaseShader.setMat4("buildingBaseProjection", buildingBaseProjection);

        // camera/view transformation
        glm::mat4 buildingBaseView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
        buildingBaseShader.setMat4("buildingBaseView", buildingBaseView);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < buildingBaseLength; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 buildingBaseModel = glm::mat4(1.0f);

            if(i>=0 && i < 9) {
                buildingBaseModel = glm::translate(buildingBaseModel, glm::vec3(-0.215, 0.0, 1.013));
                buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(20.0f), glm::vec3(0.0f, 10.0f, 0.0f));
            }

            if(i>=9 && i<12 || i>=14 && i<17) {
                buildingBaseModel = glm::translate(buildingBaseModel, glm::vec3(-2.05, 0.0, -1.57));
                buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(-30.0f), glm::vec3(0.0f, 10.0f, 0.0f));
            }

            if(i>=12 && i<14 || i>=17 && i<20) {
                buildingBaseModel = glm::translate(buildingBaseModel, glm::vec3(-1.48, 0.0, 0.2));
                buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(-15.0f), glm::vec3(0.0f, 10.0f, 0.0f));
            }

            if(i>=20 && i<26 || i>=26 && i<32) {
                buildingBaseModel = glm::translate(buildingBaseModel, glm::vec3(2.29, 0.0, 0.11));
                buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(20.0f), glm::vec3(0.0f, 10.0f, 0.0f));
            }

            if(i>=32 && i<39 || i>=39 && i<50) {
                buildingBaseModel = glm::translate(buildingBaseModel, glm::vec3(-4.13, 0.0, 0.75));
                buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(-20.0f), glm::vec3(0.0f, 10.0f, 0.0f));
            }

            if(i>=50 && i<61) {
                buildingBaseModel = glm::translate(buildingBaseModel, glm::vec3(-0.08, 0.0, -0.49));
                buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(1.0f), glm::vec3(0.0f, 10.0f, 0.0f));
            }

            if(i>=63 && i<68) {
                buildingBaseModel = glm::translate(buildingBaseModel, glm::vec3(-0.0, 0.0, -0.0));
                buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(1.0f), glm::vec3(0.0f, 10.0f, 0.0f));
            }

            if(i>=68 && i<73 || i>=73 && i<84) {
                buildingBaseModel = glm::translate(buildingBaseModel, glm::vec3(9.899, 0.0, 0.118));
                buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(40.051f), glm::vec3(0.0f, 10.0f, 0.0f));
            }

            if(i>=84 && i<88 || i>=88 && i<97) {
                buildingBaseModel = glm::translate(buildingBaseModel, glm::vec3(-1.41, 0.0, 0.482));
                buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(0.0f), glm::vec3(0.0f, 10.0f, 0.0f));
            }

            if(i>=97 && i<100) {
                buildingBaseModel = glm::translate(buildingBaseModel, glm::vec3(-0.406, 0.0, -0.15));
                buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(-5.0f), glm::vec3(0.0f, 10.0f, 0.0f));
            }

            buildingBaseModel = glm::translate(buildingBaseModel, buildingBasePositions[i] + glm::vec3(0.0, 0.0, 0.0));

            buildingBaseModel = glm::scale(buildingBaseModel, glm::vec3(1.0, 1.0, 1.0));
            //float angle = 20.0f * i;
            //buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            buildingBaseShader.setMat4("buildingBaseModel", buildingBaseModel);
            //set building color
            buildingBaseShader.setVec3("buildingBaseColor", glm::vec3((i+1.0)/buildingBaseLength, (i+1.0)/buildingBaseLength, (i+1.0)/buildingBaseLength));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
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