#include "DeviceManager.hpp"



famm::DeviceManager::DeviceManager() {
    windowSettings = { "PHASE1",{1920,1080},false ,true };
    controlSettings = { GLFW_MOUSE_BUTTON_1,GLFW_KEY_W , GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_A,GLFW_KEY_LEFT_SHIFT,GLFW_KEY_Q,GLFW_KEY_E, GLFW_KEY_F12,GLFW_KEY_ESCAPE,5};
}

void famm::DeviceManager::setupCallbacks(CallbacksModes mode, int param1, int param2, int param3=0, int param4=0) {
    switch (mode)
    {
    case famm::CallbacksModes::KEY_EVENT:
        keyboard.keyEvent(param1, param2, param3, param4);
        break;
    case famm::CallbacksModes::CURSOR_MOVE_EVENT:
        mouse.CursorMoveEvent(param1, param2);
        break;
    case famm::CallbacksModes::MOUSE_BUTTON_EVENT:
        mouse.MouseButtonEvent(param1, param2, param3);
        break;
    case famm::CallbacksModes::SCROLL_EVENT:
        mouse.ScrollEvent(param1, param2);
        break;
    }
}

void famm::DeviceManager::destroyWindow()
{
    glfwDestroyWindow(window);
}

void famm::DeviceManager::attachWindow()
{
    keyboard.enable(window);
    mouse.enable(window);
}

int famm::DeviceManager::createNewWindow() {
    auto win_config = getWindowSettings();             // Returns the WindowConfiguration current struct instance.


// Create a window with the given "WindowConfiguration" attributes.
// If it should be fullscreen, monitor should point to one of the monitors (e.g. primary monitor), otherwise it should be null
    GLFWmonitor* monitor = win_config.isFullscreen ? glfwGetPrimaryMonitor() : nullptr;
    // The last parameter "share" can be used to share the resources (OpenGL objects) between multiple windows.
    window = glfwCreateWindow(win_config.size.x, win_config.size.y, win_config.title, monitor, nullptr);
    if (!window) {
        std::cerr << "Failed to Create Window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);         // Tell GLFW to make the context of our window the main context on the current thread.

    return 0;
}

void famm::DeviceManager::updateWindowSettings(bool isFullScreen, std::uint16_t width = 0, std::uint16_t height = 0)
{
    if (width && height)
        windowSettings.size = glm::i16vec2(width, height);
    windowSettings.isFullscreen = isFullScreen;
    windowSettings.isRefreshed = false;

}

void famm::DeviceManager::refreshWidow() {
    destroyWindow();
    createNewWindow();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    windowSettings.isRefreshed = true;
}

void famm::DeviceManager::swapWindowBuffers()
{
    glfwSwapBuffers(window);
}

void famm::DeviceManager::updateInput()
{
    keyboard.update();
    mouse.update();
}

bool famm::DeviceManager::pressedActionChecker(ControlsActions action, PressModes mode)
{
    std::uint16_t key = getCorrespondingKey(action);
    switch (mode)
    {
    case famm::PressModes::IS_PRESSED:
        return keyboard.isPressed(key);
        break;
    case famm::PressModes::JUST_PRESSED:
        return keyboard.justPressed(key);
        break;
    case famm::PressModes::JUST_RELEASED:
        return keyboard.justReleased(key);
        break;
    default:
        std::cout << "WARNING: Wrong press mode is passed!"<< std::endl;
        return false;
        break;
    }
}

bool famm::DeviceManager::mouseActionChecker(ControlsActions action, PressModes mode)
{
    std::uint16_t key = getCorrespondingKey(action);
    switch (mode)
    {
    case famm::PressModes::IS_PRESSED:
        return mouse.isPressed(key);
        break;
    case famm::PressModes::JUST_PRESSED:
        return mouse.justPressed(key);
        break;
    case famm::PressModes::JUST_RELEASED:
        return mouse.justReleased(key);
        break;
    default:
        std::cout << "WARNING: Wrong press mode is passed!" << std::endl;
        return false;
        break;
    }
}

bool famm::DeviceManager::pressedKeyChecker(std::uint16_t key, PressModes mode)
{

    switch (mode)
    {
    case famm::PressModes::IS_PRESSED:
        return keyboard.isPressed(key);
        break;
    case famm::PressModes::JUST_PRESSED:
        return keyboard.justPressed(key);
        break;
    case famm::PressModes::JUST_RELEASED:
        return keyboard.justReleased(key);
        break;
    default:
        std::cout << "WARNING: Wrong press mode is passed!" << std::endl;
        return false;
        break;
    }
}

std::int16_t famm::DeviceManager::getUsedKey(PressModes mode)
{
    for (int i = 65; i < 91; i++)
    {
        if (pressedKeyChecker(i,mode)) return i;
    }

    return -1;
}

std::uint16_t famm::DeviceManager::getCorrespondingKey(ControlsActions action) {
    switch (action)
    {
    case famm::ControlsActions::MOUSE_LEFT:
        return controlSettings.mouseLeft;
        break;
    case famm::ControlsActions::UP:
        return controlSettings.up;
        break;
    case famm::ControlsActions::DOWN:
        return controlSettings.down;
        break;
    case famm::ControlsActions::RIGHT:
        return controlSettings.right;
        break;
    case famm::ControlsActions::LEFT:
        return controlSettings.left;
        break;
    case famm::ControlsActions::SPRINT:
        return controlSettings.sprint;
    case famm::ControlsActions::CAMERA_UP:
        return controlSettings.cameraUp;
        break;
    case famm::ControlsActions::CAMERA_DOWN:
        return controlSettings.cameraDown;
        break;
    case famm::ControlsActions::SCREEN_SHOT:
        return controlSettings.screenShot;
        break;
    case famm::ControlsActions::MENU:
        return controlSettings.menu;
        break;
    }
}

glm::vec2 famm::DeviceManager::getNormalizedMousePos() {
    glm::vec2 cursorPos = mouse.getMousePosition();
    cursorPos.y = windowSettings.size.y - cursorPos.y;
    float sensitivityRatio = controlSettings.sensitivity / 10.0;
    cursorPos = cursorPos * glm::vec2(2 * (1.3 + sensitivityRatio) / windowSettings.size.x, 2 * (0.71875 + (windowSettings.size.y / (float)windowSettings.size.x) * sensitivityRatio) / windowSettings.size.y) - glm::vec2(1.3 + sensitivityRatio, 0.71875 + (windowSettings.size.y / (float)windowSettings.size.x) * sensitivityRatio);
    return cursorPos;
}

int* famm::DeviceManager::getSenesitivity() {
    return &(controlSettings.sensitivity);
}

void famm::DeviceManager::setCorrespondingKey(ControlsActions action, std::uint16_t key)
{
    switch (action)
    {
    case famm::ControlsActions::UP:
        controlSettings.up = key;
        break;
    case famm::ControlsActions::DOWN:
        controlSettings.down = key;
        break;
    case famm::ControlsActions::RIGHT:
        controlSettings.right = key;
        break;
    case famm::ControlsActions::LEFT:
        controlSettings.left = key;
        break;
    case famm::ControlsActions::CAMERA_UP:
        controlSettings.cameraUp = key;
        break;
    case famm::ControlsActions::CAMERA_DOWN:
        controlSettings.cameraDown = key;
        break;
    case famm::ControlsActions::SCREEN_SHOT:
        controlSettings.screenShot = key;
        break;
    case famm::ControlsActions::MENU:
        controlSettings.menu = key;
        break;
    }
}
