#include "Test.h"

namespace Zyliph
{

    double deltatime;
    double nowTime;
    double prevTime;
    unsigned int counter = 0;

    TestApp* TestApp::z_Instance = nullptr;

   TestApp::TestApp()
   {
       Z_CORE_ASSERT(!z_Instance, "Application already exists")
       z_Instance = this;

       ZLogger::Init();
       z_Window = Window::Create();
       z_Window->SetEventCallback(Z_BIND_EVENT_FN(OnEvent));

       z_GuiLayer = new GUILayer();
       PushOverlay(z_GuiLayer);

       camera = Camera(z_Window->GetWidth(), z_Window->GetHeight(), glm::vec3(0.0f, 0.0f, 2.0f));
   }

    TestApp::~TestApp()
    {
        
    }

    void TestApp::PushLayer(Layer* layer)
    {
        z_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void TestApp::PushOverlay(Layer* layer)
    {
        z_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void TestApp::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(Z_BIND_EVENT_FN(OnWindowClosed));

        Z_CORE_INFO("{0}", e);

       for (auto it = z_LayerStack.end(); it != z_LayerStack.begin();)
       {
           (*--it)->OnEvent(e);
           if (e.handled)
               break;
       }
    }

    bool TestApp::OnWindowClosed(WindowCloseEvent& e)
    {
        z_Running = false;
        return true;
    }


    void TestApp::Run()
    {
        Shader shaderProgram("../ZyliphEngine/src/Resources/shaders/defualt.vert", "../ZyliphEngine/src/Resources/shaders/defualt.frag");

        glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

        shaderProgram.Activate();
        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

        ZModel model("../ZyliphEngine/src/Resources/models/sword/scene.gltf", 1);

        while (z_Running)
        {

            nowTime = glfwGetTime();
            deltatime = nowTime - prevTime;
            counter++;
            if (deltatime >= 1.0 / 30.0)
            {
                std::string FPS = std::to_string((1.0 / deltatime) * counter);
                std::string ms = std::to_string((deltatime / counter) * 1000);
                std::string newTitle;
                newTitle.append("ZyliphEngine - FPS:" + FPS + " /" + ms);
                glfwSetWindowTitle(static_cast<GLFWwindow*>(z_Window->GetNativeWindow()), newTitle.c_str());
                prevTime = nowTime;
                counter = 0;

                camera.joystick1Present = glfwJoystickPresent(GLFW_JOYSTICK_1);
                camera.KeyInputs(deltatime);
                camera.GamePadInputs(deltatime);
                camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

            }
            //Swappy wappy my bwuffews pwease -gawwy
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            model.Draw(shaderProgram, camera);

            glDepthFunc(GL_LEQUAL);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);
            view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
            projection = glm::perspective(glm::radians(45.0f), (float)z_Window->GetWidth() / z_Window->GetHeight(), 0.1f, 100.0f);

            glEnable(GL_CULL_FACE);

            for (Layer* layer : z_LayerStack)
                layer->OnUpdate();

            z_GuiLayer->Begin();
            for (Layer* layer : z_LayerStack)
                layer->OnImGuiRender();
            z_GuiLayer->End();

            z_Window->OnUpdate();
        }
    }
}
