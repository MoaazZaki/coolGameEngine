#ifndef APPLICATION_H
#define APPLICATION_H

#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "input/keyboard.hpp"
#include "input/mouse.hpp"
#include "DeviceManager.hpp"

namespace famm {


    // This class act as base class for all the Applications covered in the examples.
    // It offers the functionalities needed by all the examples.
    class Application {
    protected:
        DeviceManager* deviceManager;
        ImGuiIO io;
        // Virtual functions to be overrode and change the default behaviour of the application
        // according to the example needs.
        virtual void configureOpenGL();                             // This function sets OpenGL Window Hints in GLFW.

        virtual void deviceManagerCallbacks(CallbacksModes mode, int param1, int param2, int param3, int param4);
        virtual void setupCallbacks(GLFWwindow* window);             // Sets-up the window callback functions from GLFW to our (Mouse/Keyboard) classes.

    public:
        Application(DeviceManager* deviceManager) {
            this->deviceManager = deviceManager;

        }

        virtual void onInitialize(){}                   // Called once before the game loop.
        virtual void onImmediateGui(ImGuiIO& io){}      // Called every frame to draw the Immediate GUI (if any).
        virtual void onDraw(double deltaTime){}         // Called every frame in the game loop passing the time taken to draw the frame "Delta time".
        virtual void onDestroy(){}                      // Called once after the game loop ends for house cleaning.


        // Override these functions to get mouse and keyboard event.
        virtual void onKeyEvent(int key, int scancode, int action, int mods){}      
        virtual void onCursorMoveEvent(double x, double y){}
        virtual void onCursorEnterEvent(int entered){}
        virtual void onMouseButtonEvent(int button, int action, int mods){}
        virtual void onScrollEvent(double x_offset, double y_offset){}

        int startInit();
        int startLoop(double& last_frame_time);      // This is the main class function that run the whole application (Initialize, Game loop, House cleaning).
        int startCleaning();

    };

}


#endif //APPLICATION_H
