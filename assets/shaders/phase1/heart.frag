#version 330 core

in vec4 currentPos;
//in float screenRatio;
out vec4 frag_color;

uniform vec2 cursorPos;
uniform float screenRatio;

void main()
{
      // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = currentPos.xy;
   
   //uv.x+=0.3;
    //uv.y+=0.5; 

    
    uv.x *= 1920.0/1080.0;
    uv.y *= 0.86;
    uv.x *= 0.98;
    
    uv.x -= cursorPos.x;
    uv.y -= cursorPos.y;


    float temp1 = uv.x;
    float temp2 = uv.y;   
    
    temp1 = 0.707 * temp1 - 0.707 * temp2;
    temp2 = 0.707 * temp2 + 0.707 * temp1;
    vec2 rotated_right_uv = vec2(temp1,temp2);
    
    vec2 ellipse_center1 = vec2(0.12,0.0);
    float distance_center1 = distance(rotated_right_uv,ellipse_center1);

    
    if (distance_center1 < 0.15 && temp2 > -0.075){
        frag_color = vec4(1,1,1,1.0);  
    }
  
    
    temp1 = uv.x;
    temp2 = uv.y;  
    
    temp1 = 0.707 * temp1 + 0.707 * temp2;
    temp2 = -0.707 * temp2 + 0.707 * temp1;
       vec2 rotated_left_uv = vec2(temp1,temp2);
    
    vec2 ellipse_center2 = vec2(-0.12,0.0);
    float distance_center2 = distance(rotated_left_uv,ellipse_center2);
    
    if (distance_center2 < 0.15 && temp2 < 0.075)
    {
        frag_color = vec4(1,1,1,1.0); 
    }
    
}