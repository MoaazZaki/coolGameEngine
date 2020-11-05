#version 330 core


void main() {
    // This time we have 6 points since we are drawing a Quad (in NDC, it is a square).
    const vec3 positions[6] = vec3[6](
        vec3(-1.0, -1.0, 0.0),
        vec3( 1.0, -1.0, 0.0),
        vec3( 1.0,  1.0, 0.0),
        vec3( 1.0,  1.0, 0.0),
        vec3(-1.0,  1.0, 0.0),
        vec3(-1.0, -1.0, 0.0)
    );

    // get the position based on the vertex id
    vec3 position = positions[gl_VertexID];

    // Finally send the value to "gl_Position".
    gl_Position = vec4(position, 1.0);
}