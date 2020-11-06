#version 330 core

//in float ratio;

out vec4 currentPos;
out float screenRatio;



void main() {
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

    currentPos = gl_Position ;
    //screenRatio = ratio;
}