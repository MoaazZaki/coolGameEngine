#include <application.hpp>
#include <shader.hpp>

#include <iostream>
class UniformsApplication : public famm::Application {

    famm::ShaderProgram program_heart, program_smiley, program_pacman, program_g;
    GLuint vertex_array = 0;

    glm::vec2 cursorPos = glm::vec2(0.0, 0.0);
    glm::float32 windowRatio;
    
    GLuint currentShape = 1;

    famm::WindowConfiguration getWindowConfiguration() override {
        return { "Phase 1 Task", {1920, 1080}, false };
    }

    void onInitialize() override {
        program_heart.create();
        program_smiley.create();
        program_pacman.create();
        program_g.create();

        program_heart.attach("assets/shaders/phase1/quad.vert", GL_VERTEX_SHADER);
        program_heart.attach("assets/shaders/phase1/heart.frag", GL_FRAGMENT_SHADER);
        program_heart.link();

        program_smiley.attach("assets/shaders/phase1/quad.vert", GL_VERTEX_SHADER);
        program_smiley.attach("assets/shaders/phase1/smiley.frag", GL_FRAGMENT_SHADER);
        program_smiley.link();

        program_pacman.attach("assets/shaders/phase1/quad.vert", GL_VERTEX_SHADER);
        program_pacman.attach("assets/shaders/phase1/pacman.frag", GL_FRAGMENT_SHADER);
        program_pacman.link();

        program_g.attach("assets/shaders/phase1/quad.vert", GL_VERTEX_SHADER);
        program_g.attach("assets/shaders/phase1/g.frag", GL_FRAGMENT_SHADER);
        program_g.link();

        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);

        windowRatio = getWindowConfiguration().size.x / (glm::float32)getWindowConfiguration().size.y;

        glEnableVertexAttribArray(0);

        glBindVertexArray(0);


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void onDraw(double deltaTime) override {
        glClear(GL_COLOR_BUFFER_BIT);

        cursorPos = famm::Application::mouse.getMousePosition();
        cursorPos.y = 1080.0 - cursorPos.y;
        cursorPos = (cursorPos / glm::vec2(1600.0 / 3.0, 540.0)) - glm::vec2(1.8, 1);
        
   
        if (keyboard.justPressed(GLFW_KEY_2)  || keyboard.justPressed(GLFW_KEY_KP_2) ) currentShape = 2;
        else if (keyboard.justPressed(GLFW_KEY_3) || keyboard.justPressed(GLFW_KEY_KP_3) ) currentShape = 3;
        else if (keyboard.justPressed(GLFW_KEY_4) || keyboard.justPressed(GLFW_KEY_KP_4) ) currentShape = 4;
        else if (keyboard.justPressed(GLFW_KEY_1) || keyboard.justPressed(GLFW_KEY_KP_1) ) currentShape = 1;

        GLuint cursor_uniform_location;
        GLuint window_ratio_uniform_location;

        switch (currentShape) {
            case 1:
                glUseProgram(program_smiley);
                cursor_uniform_location = glGetUniformLocation(program_smiley, "cursorPos");
                glUniform2f(cursor_uniform_location, cursorPos.x, cursorPos.y);
                window_ratio_uniform_location = glGetUniformLocation(program_smiley, "screenRatio");
                glUniform1f(window_ratio_uniform_location, windowRatio);
                break;

            case 2:
                glUseProgram(program_heart);
                cursor_uniform_location = glGetUniformLocation(program_heart, "cursorPos");
                glUniform2f(cursor_uniform_location, cursorPos.x, cursorPos.y);
                window_ratio_uniform_location = glGetUniformLocation(program_heart, "screenRatio");
                glUniform1f(window_ratio_uniform_location, windowRatio);
                break;
            case 3:
                glUseProgram(program_pacman);
                cursor_uniform_location = glGetUniformLocation(program_pacman, "cursorPos");
                glUniform2f(cursor_uniform_location, cursorPos.x, cursorPos.y);
                window_ratio_uniform_location = glGetUniformLocation(program_pacman, "screenRatio");
                glUniform1f(window_ratio_uniform_location, windowRatio);
                break;
            case 4:
                glUseProgram(program_g);
                cursor_uniform_location = glGetUniformLocation(program_g, "cursorPos");
                glUniform2f(cursor_uniform_location, cursorPos.x, cursorPos.y);
                window_ratio_uniform_location = glGetUniformLocation(program_g, "screenRatio");
                glUniform1f(window_ratio_uniform_location, windowRatio);
                break;
        }


        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);
    }

    void onDestroy() override {
        program_smiley.destroy();
        program_heart.destroy();
        program_pacman.destroy();
        program_g.destroy();
        glDeleteVertexArrays(1, &vertex_array);
    }

};

int main(int argc, char** argv) {
    return UniformsApplication().run();
}
