#version 330 core
#extension GL_ARB_explicit_uniform_location : require

in vec4 vertex_color;

layout (location = 1) uniform vec4 tint; // A tint is something we can use to modify colors

out vec4 frag_color;

void main() {
    // We use a uniform and a varying together to be able to have a unique color for each object while sharing the same vertex data.
    frag_color = tint * vec4(0.4, 0.352, 0.301,0);
}
