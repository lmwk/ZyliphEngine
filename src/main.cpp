#include "HeaderFiles/ZMesh.h"

const unsigned int width = 800;
const unsigned int height = 800;

double deltatime;
double nowTime;
double prevTime;

//Vertexs for the triangle
Vertex vertices[] =
{   //COORDS      /     RGB VALS        /   TEX COORDS  /      NORMS         /
    Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}

};

GLuint indicies[] =
{
    0, 1, 2,
    0, 2, 3
};

Vertex lightVertices[] =
{
    Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
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

    Texture textures[]
    {
        Texture("./Resources/TestTextures/planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("./Resources/TestTextures/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    //Gary draws things

    Shader shaderProgram("./Resources/shaders/defualt.vert", "./Resources/shaders/defualt.frag");
    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector <GLuint> ind(indicies, indicies + sizeof(indicies) / sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    ZMesh floor(verts, ind, tex);

    Shader lightShader("./Resources/shaders/light.vert", "./Resources/shaders/light.frag");
    std::vector <Vertex> lverts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector <GLuint> lind(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    ZMesh light(lverts, lind, tex);


    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    prevTime = glfwGetTime();

    //Making gary into an off-brand smurf
    //A loop if you couldn't tell, don't worry I got you
    while (!glfwWindowShouldClose(window))
    {
        //Swappy wappy my bwuffews pwease -gawwy
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        nowTime = glfwGetTime();
        deltatime = nowTime - prevTime;
        prevTime = nowTime;
        camera.joystick1Present = glfwJoystickPresent(GLFW_JOYSTICK_1);
        camera.KeyInputs(window, deltatime);
        camera.GamePadInputs(window, deltatime);
        camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

        floor.Draw(shaderProgram, camera);
        light.Draw(lightShader , camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //Deleting drawings
    shaderProgram.Delete();
    lightShader.Delete();
    //Killing garry :(
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}