#version 330 core

in vec3 out_color;
out vec4 FragColor;
in vec2 text_coord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    FragColor = texture(texture1,text_coord);
}