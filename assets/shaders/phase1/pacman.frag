#version 330 core

in vec4 currentPos;
out vec4 frag_color;

uniform vec2 cursorPos;
uniform float screenRatio;

void main()
{
    //Normalized pixel coordinates (from 0 to 1)
    vec2 uv = currentPos.xy;

    uv.x *= screenRatio;
     
    uv.x -= cursorPos.x;
    uv.y -= cursorPos.y;

    float radius = length(uv);

    //Draw circle at the center (whole face of pacman)
    if (radius < 0.25)
    {  
        frag_color = vec4(1,1,1,1.0); //white
        
        //Draw circle at the top middle (eye of pacman)
        uv.y -= 0.15; 
        
        radius = length(uv);
        
        if (radius < 0.04)
            frag_color = vec4(0,0,0,1.0); //black
        
        //Draw square (mouth of pacman)
        
        uv.y += 0.15; // going back to center
        
        float width = 0.125; //square dimensions
        float height = 0.125;
        
        //By calculating distance between center and chord of circle 
        // distance = sqrt((0.25)^2 + (0.25)^2) / 2 ~= 0.176
        vec2 location = vec2(0.176,0.0); 
        
        float x = length(location.x - uv.x); 
        float y = length(location.y - uv.y); 

           x = x * 0.707 + y * 0.707; // Rotate 45 degrees: cos(45) = root(2)/2
        y = y * 0.707 - x * 0.707; // and sin(45) = root(2)/2

        if (x <= width &&  y <= height) //If still in range, fill with black
            frag_color = vec4(0,0,0,1.0);
     
    }
    else
        frag_color = vec4(0,0,0,1.0); 
}