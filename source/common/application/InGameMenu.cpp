#include "InGameMenu.hpp"


void famm::InGameMenu::onInitialize() {
    //// Start the ImGui context and set dark style (just my preference :D)
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //io = ImGui::GetIO();
    //ImGui::StyleColorsDark();
    //ImFont* font1 = io.Fonts->AddFontFromFileTTF("assets/Fonts/Roboto-Black.ttf", 22);

    //// Initialize ImGui for GLFW and OpenGL
    //ImGui_ImplGlfw_InitForOpenGL(deviceManager->getWindow(), true);
    //ImGui_ImplOpenGL3_Init("#version 330 core");

    //glClearColor(0.5f, 0.2f, 0.7f, 1.0f);


}

void famm::InGameMenu::onDraw(double deltaTime) {
    //// Start a new ImGui frame
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplGlfw_NewFrame();
    //ImGui::NewFrame();

    //onImmediateGui(io); // Call to run any required Immediate GUI.

    // // If ImGui is using the mouse or keyboard, then we don't want the captured events to affect our keyboard and mouse objects.
    //// For example, if you're focusing on an input and writing "W", the keyboard object shouldn't record this event.
    //deviceManager->getKeyboard().setEnabled(!io.WantCaptureKeyboard, deviceManager->getWindow()); /// TODO: EDIT LATER
    //deviceManager->getMouse().setEnabled(!io.WantCaptureMouse, deviceManager->getWindow());

    //ImGui::Render();

    ///ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //glClear(GL_COLOR_BUFFER_BIT);

    if ((deviceManager->pressedActionChecker(famm::ControlsActions::MENU, famm::PressModes::JUST_PRESSED) && !isPaused)) onPause();


}
void famm::InGameMenu::onDestroy() {
    // Shutdown ImGui & destroy the context
   // ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();
    isTerminated = true;
}
void famm::InGameMenu::onImmediateGui(ImGuiIO& io) {
    ImGuiStyle& style = ImGui::GetStyle();
    style.FramePadding = ImVec2(15, 12);
    style.ItemSpacing = ImVec2(10, 50);



        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::SetNextWindowSize(ImVec2(deviceManager->getWindowSize().x, deviceManager->getWindowSize().y));
        ImGui::Begin("FAMM Engine",NULL, ImGuiWindowFlags_NoCollapse);
    
        if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("home"))
            {
                if (ImGui::Button("Main menu"))
                {
                    onDestroy();

                }
                ImGui::EndTabItem();

            }

            if (ImGui::BeginTabItem("Settings"))
            {
                if (ImGui::BeginTabBar("##tr", ImGuiTabBarFlags_None))
                {
                    if (ImGui::BeginTabItem("Controls"))
                    {
                        // Making a grid
                        ImGui::Columns(4, "mycolumns",false); 
                        ImGui::NextColumn();


                        // Labels
                        ImGui::AlignTextToFramePadding();
                        ImGui::Text("                            Sensitivity");
                        ImGui::AlignTextToFramePadding();
                        ImGui::Text("                            Movements");
                        ImGui::AlignTextToFramePadding();
                        ImGui::Text("                            Camera Up/Down");

                        // Styling bars
                        ImGui::NextColumn();
                        ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(4 / 7.0f, 0.5f, 0.5f));
                        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.5f));
                        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(4 / 7.0f, 0.7f, 0.5f));
                        ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(4 / 7.0f, 0.9f, 0.9f));
                        ImGui::SliderInt("",deviceManager->getSenesitivity(), 0, 10);
                
                
                        // Styling Buttons
                        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.6f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(4 / 7.0f, 0.7f, 0.7f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));

                        // Getting the buttons labels
                        const char UpChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::UP), '\0' };
                        const char DownChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::DOWN), '\0' };
                        const char LeftChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::LEFT), '\0' };
                        const char RightChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::RIGHT), '\0' };
                        const char CameraUpChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::CAMERA_UP), '\0' };
                        const char CameraDownChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::CAMERA_DOWN), '\0' };

                        //Draw movements button
                        int buttonPadding = 100;
                        static int selected = -1;
                

                
                        if (inputButtonFlags[0] || ImGui::Button(UpChar)) {
                            if (!inputButtonFlags[0]) { 
                                for (int i = 0; i < 6; i++) inputButtonFlags[i] = false;
                                inputButtonFlags[0] = true;
                            }
                            else {
                                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
                                ImGui::Button(UpChar);
                                ImGui::PopStyleColor(1);
                            }
                    
                            int key =  deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
                            if (key != -1) { 
                                deviceManager->setCorrespondingKey(famm::ControlsActions::UP, key); 
                                inputButtonFlags[0] = false;
                            }

                        }
                        //if(ImGui::Selectable(UpChar, selected == 0)) selected = 0; 
                        ImGui::SameLine(buttonPadding);
                        buttonPadding += 90;

                        if(inputButtonFlags[1] || ImGui::Button(DownChar)) {
                            if (!inputButtonFlags[1]) { for (int i = 0; i < 6; i++) inputButtonFlags[i] = false; inputButtonFlags[1] = true; }
                            else {
                                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
                                ImGui::Button(DownChar);
                                ImGui::PopStyleColor(1);
                            }
          
                            int key = deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
                            if (key != -1) {
                                deviceManager->setCorrespondingKey(famm::ControlsActions::DOWN, key);
                                inputButtonFlags[1] = false;
                            }
                        }
                        //if(ImGui::Selectable(DownChar, selected == 1)) selected = 1;
                        ImGui::SameLine(buttonPadding);
                        buttonPadding += 90;

                        if (inputButtonFlags[2] || ImGui::Button(LeftChar)) {
                            if (!inputButtonFlags[2]) { for (int i = 0; i < 6; i++) inputButtonFlags[i] = false; inputButtonFlags[2] = true; }
                            else {
                                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
                                ImGui::Button(LeftChar);
                                ImGui::PopStyleColor(1);
                            }

                            int key = deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
                            if (key != -1) {
                                deviceManager->setCorrespondingKey(famm::ControlsActions::LEFT, key);
                                inputButtonFlags[2] = false;
                            }
                        }
                        //if(ImGui::Selectable(LeftChar, selected == 2)) selected = 2;
                        ImGui::SameLine(buttonPadding);

                        if (inputButtonFlags[3] || ImGui::Button(RightChar)) {
                            if (!inputButtonFlags[3]) { for (int i = 0; i < 6; i++) inputButtonFlags[i] = false; inputButtonFlags[3] = true; }
                            else {
                                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
                                ImGui::Button(RightChar);
                                ImGui::PopStyleColor(1);
                            }
    
                            int key = deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
                            if (key != -1) {
                                deviceManager->setCorrespondingKey(famm::ControlsActions::RIGHT, key);
                                inputButtonFlags[3] = false;
                            }
                        }

                        buttonPadding = 100;

                        // Draw Camera up and down buttons
                        if (inputButtonFlags[4] || ImGui::Button(CameraUpChar)) {
                            if (!inputButtonFlags[4]) {
                                for (int i = 0; i < 6; i++) inputButtonFlags[i] = false;
                                inputButtonFlags[4] = true;
                            }
                            else {
                                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
                                ImGui::Button(CameraUpChar);
                                ImGui::PopStyleColor(1);
                            }

                            int key = deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
                            if (key != -1) {
                                deviceManager->setCorrespondingKey(famm::ControlsActions::CAMERA_UP, key);
                                inputButtonFlags[4] = false;
                            }

                        }

                        ImGui::SameLine(buttonPadding);
                        buttonPadding += 90;

                        if (inputButtonFlags[5] || ImGui::Button(CameraDownChar)) {
                            if (!inputButtonFlags[5]) { for (int i = 0; i < 6; i++) inputButtonFlags[i] = false; inputButtonFlags[5] = true; }
                            else {
                                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
                                ImGui::Button(CameraDownChar);
                                ImGui::PopStyleColor(1);
                            }

                            int key = deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
                            if (key != -1) {
                                deviceManager->setCorrespondingKey(famm::ControlsActions::CAMERA_DOWN, key);
                                inputButtonFlags[5] = false;
                            }
                        }



                        ImGui::PopStyleColor(7);
                        ImGui::Columns(1);
                        ImGui::EndTabItem();

                    }

                    if (ImGui::BeginTabItem("Camera"))
                    {
                        ImGui::EndTabItem();

                    }

                    if (ImGui::BeginTabItem("Graphics"))
                    {
                        ImGui::EndTabItem();

                    }
                }
                ImGui::EndTabBar();
                ImGui::EndTabItem();

            }

        }
        ImGui::EndTabBar();
    

        ImGui::End();
}


void famm::InGameMenu::onPause() {
    isPaused = true;
}

void famm::InGameMenu::onResume() {
    isPaused = false;
}

bool famm::InGameMenu::statePaused()
{
    return isPaused;
}

bool famm::InGameMenu::stateTerminated() {
    return isTerminated;
}