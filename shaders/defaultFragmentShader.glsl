#version 410 core
out vec4 FragColor;

in vec3 Color;
in vec2 TexCoord;

uniform sampler2D texture1;

void main(){
  vec4 base = vec4(Color, 1.0f);
  vec4 overlay = texture(texture1, TexCoord);

  if(overlay.a > 0.01){
    FragColor = overlay;
  }
  else{
    FragColor = base;
  }
  // FragColor = mix(base, overlay, 1.0);
}
