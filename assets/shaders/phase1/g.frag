#version 330 core

in vec4 currentPos;
out vec4 frag_color;

uniform vec2 cursorPos;
uniform float screenRatio;

void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = currentPos.xy;

    uv.x *= screenRatio;

    uv.x -= cursorPos.x;
    uv.y -= cursorPos.y;

    float val =length(uv);

    if (val < 0.20 ){

        frag_color = vec4(1,1,1,1.0);

        val =length(uv);
        //outer circle
        if (val <0.14 )
            frag_color = vec4(0,0,0,1.0);
        //inner circle
        if (val <0.13 )
            frag_color = vec4(0,0,0,0.0);
        //sector cut off ( by rotation )
        float temp1 = uv.x;
        float temp2 = uv.y;

        temp1 = 0.525 * temp1 + 0.525 * temp2;
        temp2 = -0.525 * temp2 + 0.525 * temp1;

        vec2 rotated_left_uv = vec2(temp1,temp2);

         if (rotated_left_uv.x  >= -0.01 &&  uv.x <=0.2 && rotated_left_uv.y  >=-0.001 && rotated_left_uv.y <=0.075)
          frag_color = vec4(0,0,0,0.0);

        //drawing the vertical rectangle and adjusting coordinates
        uv.y+=0.13;
        uv.x-=0.097;
        val =length(uv);

        if (uv.x >= -0.035 && uv.x <= 0.035 && uv.y >=-0.016 && uv.y <=0.09)
            frag_color = vec4(1,1,1,1.0);
    }
   else 
        frag_color = vec4(0,0,0,1.0);
}