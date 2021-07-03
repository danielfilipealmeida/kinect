#version 120

uniform sampler2DRect tex0;
varying vec2 texCoordVarying;


void main(){
    vec4 color = texture2DRect(tex0, texCoordVarying);
    float val = (color[0] + color[1] + color[2]) / 3.0;
    color = vec4(val, val, val, 1.0);
    gl_FragColor = color;
}
