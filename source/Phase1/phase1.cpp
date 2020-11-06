#include <application.hpp>
#include <shader.hpp>

#include <iostream>
class UniformsApplication : public famm::Application {

    famm::ShaderProgram program;
    GLuint vertex_array = 0, resolution_buffer = 0;

    glm::vec2 cursorPos = glm::vec2(0.0, 0.0);
    glm::float32 windowRatio;

    famm::WindowConfiguration getWindowConfiguration() override {
        return { "Phase 1 Task", {1920, 1080}, false };
    }

    void onInitialize() override {
        program.create();
        program.attach("assets/shaders/phase1/quad.vert", GL_VERTEX_SHADER);
        program.attach("assets/shaders/phase1/smile_face.frag", GL_FRAGMENT_SHADER);
        program.link();

        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);

        //glGenBuffers(1, &resolution_buffer);
        //glBindBuffer(GL_ARRAY_BUFFER, resolution_buffer);

        //float ratio[] = { 1920.0 / 1080.0 };
        //glBufferData(GL_ARRAY_BUFFER, sizeof(float), ratio, GL_STATIC_DRAW);
        //glVertexAttribPointer(0, 1, GL_FLOAT, false, sizeof(float), (void*)0);
        windowRatio = getWindowConfiguration().size.x / (glm::float32)getWindowConfiguration().size.y;

        glEnableVertexAttribArray(0);

        glBindVertexArray(0);


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void onDraw(double deltaTime) override {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);

        //myMouse.update();
        cursorPos = famm::Application::mouse.getMousePosition();
        cursorPos.y = 1080.0 - cursorPos.y;

        cursorPos = (cursorPos / glm::vec2(1600.0/3.0,540.0)) - glm::vec2(1.8,1);
        //std::cout << cursorPos.x << "," << cursorPos.y << " - ";

        GLuint cursor_uniform_location = glGetUniformLocation(program, "cursorPos");
        glUniform2f(cursor_uniform_location, cursorPos.x, cursorPos.y);

        GLuint window_ratio_uniform_location = glGetUniformLocation(program, "screenRatio");
        glUniform1f(window_ratio_uniform_location, windowRatio);

        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);
    }


    /*void onImmediateGui(ImGuiIO& io) override {
        ImGui::Begin("Controls");
        ImGui::SliderFloat2("Scale", glm::value_ptr(cursorPos), -2, 2);
        ImGui::End();

    }*/

    void onDestroy() override {
        program.destroy();
        glDeleteVertexArrays(1, &vertex_array);
    }

};

int main(int argc, char** argv) {
    return UniformsApplication().run();
}
