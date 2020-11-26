#include "phase1.hpp"


void famm::PhaseOneApplication::onInitialize()  {
    vertex_array = 0;
    cursorPos = glm::vec2(0.0, 0.0);
    currentShader = currentShader = myStore->getShaderPointer("heart");

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);


    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    isPaused = false;

    windowRatio = deviceManager->getWindowSettings().size.x / (glm::float32)deviceManager->getWindowSettings().size.y;

}

void famm::PhaseOneApplication::onDraw(double deltaTime)  {
    
    if (!isPaused) {
        glClear(GL_COLOR_BUFFER_BIT);
        cursorPos = deviceManager->getNormalizedMousePos();


   
        if (deviceManager->pressedActionChecker(famm::ControlsActions::DOWN, famm::PressModes::IS_PRESSED)) currentShader = myStore->getShaderPointer("heart");
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::LEFT, famm::PressModes::IS_PRESSED)) currentShader = myStore->getShaderPointer("g");
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::RIGHT, famm::PressModes::IS_PRESSED)) currentShader = myStore->getShaderPointer("pacman");
        else if (deviceManager->pressedActionChecker(famm::ControlsActions::UP, famm::PressModes::IS_PRESSED)) currentShader = myStore->getShaderPointer("smiley");


         GLuint cursor_uniform_location;
        GLuint window_ratio_uniform_location;
   
        glUseProgram(*currentShader);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        glUseProgram(*myStore->getShaderPointer("pacman"));
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        cursor_uniform_location = glGetUniformLocation(*currentShader, "cursorPos");
        glUniform2f(cursor_uniform_location, cursorPos.x, cursorPos.y);
        window_ratio_uniform_location = glGetUniformLocation(*currentShader, "screenRatio");
        glUniform1f(window_ratio_uniform_location, windowRatio);

        cursor_uniform_location = glGetUniformLocation(*currentShader, "cursorPos");
        glUniform2f(cursor_uniform_location, 0,0);
        window_ratio_uniform_location = glGetUniformLocation(*currentShader, "screenRatio");
        glUniform1f(window_ratio_uniform_location, windowRatio);

        

        glBindVertexArray(0);
    }
 


    

    if ((deviceManager->pressedActionChecker(famm::ControlsActions::MENU, famm::PressModes::JUST_PRESSED) && !isPaused)) onPause();
}

void famm::PhaseOneApplication::onImmediateGui(ImGuiIO* io)
{
    //if ((deviceManager->pressedActionChecker(famm::ControlsActions::MENU, famm::PressModes::JUST_PRESSED) && !isPaused)) onPause();
    //else if ((deviceManager->pressedActionChecker(famm::ControlsActions::MENU, famm::PressModes::JUST_PRESSED) && isPaused)) onResume();
    //
    //ImGuiStyle& style = ImGui::GetStyle();
    //style.FramePadding = ImVec2(15, 12);
    //style.ItemSpacing = ImVec2(10, 50);
    //
    //
 
    //    ImGui::SetNextWindowPos(ImVec2(0,0));
    //    ImGui::SetNextWindowSize(ImVec2(deviceManager->getWindowSize().x, deviceManager->getWindowSize().y));
    //    ImGui::Begin("Settings",NULL, ImGuiWindowFlags_NoCollapse);
    //    
    //    if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
    //    {
    //        if (ImGui::BeginTabItem("Controls"))
    //        {
    //            // Making a grid
    //            ImGui::Columns(4, "mycolumns",false); 
    //            ImGui::NextColumn();


    //            // Labels
    //            ImGui::AlignTextToFramePadding();
    //            ImGui::Text("                            Sensitivity");
    //            ImGui::AlignTextToFramePadding();
    //            ImGui::Text("                            Movements");
    //            ImGui::AlignTextToFramePadding();
    //            ImGui::Text("                            Camera Up/Down");

    //            // Styling bars
    //            ImGui::NextColumn();
    //            ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(4 / 7.0f, 0.5f, 0.5f));
    //            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.5f));
    //            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(4 / 7.0f, 0.7f, 0.5f));
    //            ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(4 / 7.0f, 0.9f, 0.9f));
    //            ImGui::SliderInt("",deviceManager->getSenesitivity(), 0, 10);
    //            
    //            
    //            // Styling Buttons
    //            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.6f, 0.6f));
    //            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(4 / 7.0f, 0.7f, 0.7f));
    //            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));

    //            // Getting the buttons labels
    //            const char UpChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::UP), '\0' };
    //            const char DownChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::DOWN), '\0' };
    //            const char LeftChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::LEFT), '\0' };
    //            const char RightChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::RIGHT), '\0' };
    //            const char CameraUpChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::CAMERA_UP), '\0' };
    //            const char CameraDownChar[2] = { deviceManager->getCorrespondingKey(famm::ControlsActions::CAMERA_DOWN), '\0' };

    //            //Draw movements button
    //            int buttonPadding = 100;
    //            static int selected = -1;
    //            

    //            
    //            if (inputButtonFlags[0] || ImGui::Button(UpChar)) {
    //                if (!inputButtonFlags[0]) { 
    //                    for (int i = 0; i < 6; i++) inputButtonFlags[i] = false;
    //                    inputButtonFlags[0] = true;
    //                }
    //                else {
    //                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
    //                    ImGui::Button(UpChar);
    //                    ImGui::PopStyleColor(1);
    //                }
    //                
    //                int key =  deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
    //                if (key != -1) { 
    //                    deviceManager->setCorrespondingKey(famm::ControlsActions::UP, key); 
    //                    inputButtonFlags[0] = false;
    //                }

    //            }
    //            //if(ImGui::Selectable(UpChar, selected == 0)) selected = 0; 
    //            ImGui::SameLine(buttonPadding);
    //            buttonPadding += 90;

    //            if(inputButtonFlags[1] || ImGui::Button(DownChar)) {
    //                if (!inputButtonFlags[1]) { for (int i = 0; i < 6; i++) inputButtonFlags[i] = false; inputButtonFlags[1] = true; }
    //                else {
    //                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
    //                    ImGui::Button(DownChar);
    //                    ImGui::PopStyleColor(1);
    //                }
    //      
    //                int key = deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
    //                if (key != -1) {
    //                    deviceManager->setCorrespondingKey(famm::ControlsActions::DOWN, key);
    //                    inputButtonFlags[1] = false;
    //                }
    //            }
    //            //if(ImGui::Selectable(DownChar, selected == 1)) selected = 1;
    //            ImGui::SameLine(buttonPadding);
    //            buttonPadding += 90;

    //            if (inputButtonFlags[2] || ImGui::Button(LeftChar)) {
    //                if (!inputButtonFlags[2]) { for (int i = 0; i < 6; i++) inputButtonFlags[i] = false; inputButtonFlags[2] = true; }
    //                else {
    //                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
    //                    ImGui::Button(LeftChar);
    //                    ImGui::PopStyleColor(1);
    //                }

    //                int key = deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
    //                if (key != -1) {
    //                    deviceManager->setCorrespondingKey(famm::ControlsActions::LEFT, key);
    //                    inputButtonFlags[2] = false;
    //                }
    //            }
    //            //if(ImGui::Selectable(LeftChar, selected == 2)) selected = 2;
    //            ImGui::SameLine(buttonPadding);

    //            if (inputButtonFlags[3] || ImGui::Button(RightChar)) {
    //                if (!inputButtonFlags[3]) { for (int i = 0; i < 6; i++) inputButtonFlags[i] = false; inputButtonFlags[3] = true; }
    //                else {
    //                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
    //                    ImGui::Button(RightChar);
    //                    ImGui::PopStyleColor(1);
    //                }
    //
    //                int key = deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
    //                if (key != -1) {
    //                    deviceManager->setCorrespondingKey(famm::ControlsActions::RIGHT, key);
    //                    inputButtonFlags[3] = false;
    //                }
    //            }

    //            buttonPadding = 100;

    //            // Draw Camera up and down buttons
    //            if (inputButtonFlags[4] || ImGui::Button(CameraUpChar)) {
    //                if (!inputButtonFlags[4]) {
    //                    for (int i = 0; i < 6; i++) inputButtonFlags[i] = false;
    //                    inputButtonFlags[4] = true;
    //                }
    //                else {
    //                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
    //                    ImGui::Button(CameraUpChar);
    //                    ImGui::PopStyleColor(1);
    //                }

    //                int key = deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
    //                if (key != -1) {
    //                    deviceManager->setCorrespondingKey(famm::ControlsActions::CAMERA_UP, key);
    //                    inputButtonFlags[4] = false;
    //                }

    //            }

    //            ImGui::SameLine(buttonPadding);
    //            buttonPadding += 90;

    //            if (inputButtonFlags[5] || ImGui::Button(CameraDownChar)) {
    //                if (!inputButtonFlags[5]) { for (int i = 0; i < 6; i++) inputButtonFlags[i] = false; inputButtonFlags[5] = true; }
    //                else {
    //                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4 / 7.0f, 0.8f, 0.8f));
    //                    ImGui::Button(CameraDownChar);
    //                    ImGui::PopStyleColor(1);
    //                }

    //                int key = deviceManager->getUsedKey(famm::PressModes::IS_PRESSED);
    //                if (key != -1) {
    //                    deviceManager->setCorrespondingKey(famm::ControlsActions::CAMERA_DOWN, key);
    //                    inputButtonFlags[5] = false;
    //                }
    //            }



    //            ImGui::PopStyleColor(7);
    //            ImGui::Columns(1);
    //            ImGui::EndTabItem();
    //        }

    //        if (ImGui::BeginTabItem("Camera"))
    //        {
    //            ImGui::SliderInt("Sensitivity", deviceManager->getSenesitivity(), 0, 10);
    //            ImGui::EndTabItem();
    //        }

    //        if (ImGui::BeginTabItem("Graphics"))
    //        {
    //            // Making a grid
    //            ImGui::Columns(4, "mycolumns", false);
    //            ImGui::NextColumn();

    //            // Labels
    //            ImGui::AlignTextToFramePadding();
    //            ImGui::Text("                            Sensitivity");

    //            ImGui::NextColumn();

    //            static int item_current_3 = 0; // If the selection isn't within 0..count, Combo won't display a preview
    //            const char* items[] = { "1920x1080", "800x600"};
    //            ImGui::Combo(" ", &item_current_3, items, IM_ARRAYSIZE(items));
    //            if (item_current_3)
    //            {
    //            //    deviceManager->updateWindowSettings(false, 800, 600);
    //            }
    //            ImGui::EndTabItem();
    //        }
    //        ImGui::EndTabBar();
    //    

    //    ImGui::End();
    //}
}

void famm::PhaseOneApplication::onDestroy()  {
    /*program_smiley.destroy();
    program_heart.destroy();
    program_pacman.destroy();
    program_g.destroy();*/
    glDeleteVertexArrays(1, &vertex_array);
}

void famm::PhaseOneApplication::onPause() {
    isPaused = true;
}

void famm::PhaseOneApplication::onResume() {
    isPaused = false;
}


void famm::PhaseOneApplication::changeCurrentShape(famm::ControlsActions action) {
    /*switch (action)
    {
    case famm::ControlsActions::UP:
        currentShape = 1;
        break;
    case famm::ControlsActions::DOWN:
        currentShape = 2;
        break;
    case famm::ControlsActions::RIGHT:
        currentShape = 3;
        break;
    case famm::ControlsActions::LEFT:
        currentShape = 4;
        break;*/

    }

bool famm::PhaseOneApplication::statePaused()
{
    return isPaused;
}

//
//int main(int argc, char** argv) {
//    return famm::PhaseOneApplication().run();
//}
