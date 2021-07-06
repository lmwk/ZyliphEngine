#include "HeaderFiles/ZModel.h"

const unsigned int width = 800;
const unsigned int height = 800;

double deltatime;
double nowTime;
double prevTime;
unsigned int counter = 0;


float rectangleVertices[] =
{
    // Coords    // texCoords

     1.0f,  1.0f,  1.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f,

     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f,
};

float skyboxVertices[] =
{
    //   Coordinates
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
    1, 2, 6,
    6, 5, 1,
    0, 4, 7,
    7, 3, 0,
    4, 5, 6,
    6, 7, 4,
    0, 3, 2,
    2, 1, 0,
    0, 1, 5,
    5, 4, 0,
    3, 7, 6,
    6, 2, 3
};

//Function that makes everything go brrrrrrrrrrrrrrrrrrrrrrrrr
int main()
{
    //Init GLFW Bruv
    glfwInit();

    //Tell Boss Man what version of GLFW and Opengl it's usin
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a GLFW Window named Garry
    GLFWwindow* window = glfwCreateWindow(width, height, "Garry", NULL, NULL);
    //Checks to see if Garry failed to exist
    if (window == NULL)
    {
        std::cout << "Failed to create Garry :(" << std::endl;
        glfwTerminate();
        return -1;
    }
    //Telling GLFW what window to use 
    glfwMakeContextCurrent(window);

    //Load GLAD to configure Opengl, or whatever
    gladLoadGL();

    //Setting the height and width of garry
    glViewport(0, 0, width, height);

    //Gary draws things

    Shader shaderProgram("./Resources/shaders/defualt.vert", "./Resources/shaders/defualt.frag", "./Resources/shaders/default.geom");
    Shader normalProgram("./Resources/shaders/defualt.vert", "./Resources/shaders/normals.frag", "./Resources/shaders/normals.geom");
    Shader frameProgram("./Resources/shaders/framebuffer.vert", "./Resources/shaders/framebuffer.frag");
    Shader skyShader("./Resources/shaders/skybox.vert", "./Resources/shaders/skybox.frag");


    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    frameProgram.Activate();
    glUniform1i(glGetUniformLocation(frameProgram.ID, "screenTexture"), 0);
    skyShader.Activate();
    glUniform1i(glGetUniformLocation(skyShader.ID, "skybox"), 0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    prevTime = glfwGetTime();



    //glfwSwapInterval(0);


    unsigned int rectVAO, rectVBO;
    glGenVertexArrays(1, &rectVAO);
    glGenBuffers(1, &rectVBO);
    glBindVertexArray(rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    unsigned int FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    unsigned int framebufferTexture;
    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

    unsigned int RBO;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer error: " << fboStatus << std::endl;

    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::string facesCubemap[6] =
    {
        "./Resources/TestTextures/skybox/right.jpg",
        "./Resources/TestTextures/skybox/left.jpg",
        "./Resources/TestTextures/skybox/top.jpg",
        "./Resources/TestTextures/skybox/bottom.jpg",
        "./Resources/TestTextures/skybox/front.jpg",
        "./Resources/TestTextures/skybox/back.jpg",
    };

    unsigned int cubemapTexture;
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D
            (
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
            stbi_image_free(data);
        }
    }

    ZModel model("./Resources/models/statue/scene.gltf");

    //Making gary into an off-brand smurf
    //A loop if you couldn't tell, don't worry I got you
    while (!glfwWindowShouldClose(window))
    {
        nowTime = glfwGetTime();
        deltatime = nowTime - prevTime;
        counter++;
        if (deltatime >= 1.0/30.0)
        {
            std::string FPS = std::to_string((1.0 / deltatime) * counter);
            std::string ms = std::to_string((deltatime / counter) * 1000);
            std::string newTitle = "Garry -" + FPS + "FPS /" + ms + ms;
            glfwSetWindowTitle(window, newTitle.c_str());
            prevTime = nowTime;
            counter = 0;

            camera.joystick1Present = glfwJoystickPresent(GLFW_JOYSTICK_1);
            camera.KeyInputs(window, deltatime);
            camera.GamePadInputs(window, deltatime);
            camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

        }

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        //Swappy wappy my bwuffews pwease -gawwy
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        model.Draw(shaderProgram, camera);
        model.Draw(normalProgram, camera);

        glDepthFunc(GL_LEQUAL);
        skyShader.Activate();
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
        projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(skyShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(skyShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glDepthFunc(GL_LESS);

        glDisable(GL_CULL_FACE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        frameProgram.Activate();
        glBindVertexArray(rectVAO);
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, framebufferTexture);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glEnable(GL_CULL_FACE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //Deleting shaders
    shaderProgram.Delete();
    frameProgram.Delete();
    skyShader.Delete();
    //Killing garry :(
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}