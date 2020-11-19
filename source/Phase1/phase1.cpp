#include "phase1.hpp"



void famm::PhaseOneApplication::onInitialize()  {
    vertex_array = 0;
    cursorPos = glm::vec2(0.0, 0.0);
    currentShape = 1;

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

    windowRatio = deviceManager->getWindowSettings().size.x / (glm::float32)deviceManager->getWindowSettings().size.y;

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void famm::PhaseOneApplication::onDraw(double deltaTime)  {
    glClear(GL_COLOR_BUFFER_BIT);

    cursorPos = deviceManager->getNormalizedMousePos();

    
    if (deviceManager->pressChecker(famm::ControlsActions::DOWN, famm::PressModes::IS_PRESSED)) currentShape = 2;
    else if (deviceManager->pressChecker(famm::ControlsActions::LEFT, famm::PressModes::IS_PRESSED)) currentShape = 3;
    else if (deviceManager->pressChecker(famm::ControlsActions::RIGHT, famm::PressModes::IS_PRESSED)) currentShape = 4;
    else if (deviceManager->pressChecker(famm::ControlsActions::UP, famm::PressModes::IS_PRESSED)) currentShape = 1;

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

void famm::PhaseOneApplication::onDestroy()  {
    program_smiley.destroy();
    program_heart.destroy();
    program_pacman.destroy();
    program_g.destroy();
    glDeleteVertexArrays(1, &vertex_array);
}


//
//int main(int argc, char** argv) {
//    return famm::PhaseOneApplication().run();
//}
