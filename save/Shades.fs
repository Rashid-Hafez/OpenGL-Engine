#version 410 core

out vec4 frag;
uniform sampler2D myTexture;
in vec2 texCoord0;

void main(){
    frag = texture(myTexture, texCoord0);
}
