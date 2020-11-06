#include <application.hpp>
#include <shader.hpp>


class UniformsApplication : public our::Application {

    our::ShaderProgram program;
    GLuint vertex_array = 0;

    our::WindowConfiguration getWindowConfiguration() override {
        return { "Phase 1 Task", {1920, 1080}, false };
    }

    void onInitialize() override {
        program.create();
        program.attach("assets/shaders/phase1/quad.vert", GL_VERTEX_SHADER);
        program.attach("assets/shaders/phase1/heart.frag", GL_FRAGMENT_SHADER);
        program.link();

        glm::vec2 windowResolution = getWindowConfiguration().size; //TODO: please clean this ..
        int16_t resolution[] = {
                windowResolution.y , windowResolution.x
        };

        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);


        glBindVertexArray(0);


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void onDraw(double deltaTime) override {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);

        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);
    }

    void onDestroy() override {
        program.destroy();
        glDeleteVertexArrays(1, &vertex_array);
    }

};

int main(int argc, char** argv) {
    return UniformsApplication().run();
}
