#version 330 core

// The output that goes to the frame buffer
out vec4 frag_color;


void main() {
    // Convert RGB to RGBA (in other words, add an alpha value).
    frag_color = vec4(0,1,1, 1.0);
}
