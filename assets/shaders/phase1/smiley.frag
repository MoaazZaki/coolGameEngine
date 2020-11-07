#version 330 core

in vec4 currentPos;
out vec4 frag_color;

uniform vec2 cursorPos;
uniform float screenRatio;

void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = currentPos.xy;
    //uv.x-=0.5;
    //uv.y-=0.5; 
    uv.x *= screenRatio;
    
    uv.x -= cursorPos.x;
    uv.y -= cursorPos.y;

    float val =length(uv);
    
    if (val < 0.25 ){
        
        frag_color = vec4(1,1,1,1.0);
        
        //draw mouth
        uv.y+=0.02;
        
        val =length(uv);
        //outer circle
        if (val <0.15 && uv.y < 0.0 ) {
            frag_color = vec4(0,0,0,1.0);
        }
        //inner circle
        if (val <0.11 && uv.y < 0.0 ) {
            frag_color = vec4(1,1,1,1.0);
        }

        //draw right eye
        uv.x-=0.1;
        uv.y-=0.08; 
        val =length(uv);
        if (val <0.04) {
            frag_color = vec4(0,0,0,1.0);
        }
        
        //draw left eye
        uv.x+=0.2; 
        val =length(uv);
        if (val <0.04) {
            frag_color = vec4(0,0,0,1.0);
        }  
    }
    
    else {
    frag_color = vec4(0,0,0,1.0);
    }
    
}