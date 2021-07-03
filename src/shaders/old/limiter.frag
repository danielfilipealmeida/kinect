#version 120

uniform sampler2DRect tex0;
varying vec2 texCoordVarying;

uniform float lowerLimit, upperLimit;

void main(){
    vec4 col = texture2DRect(tex0, texCoordVarying);
    
    col = vec4(
               clamp(col[0], lowerLimit, upperLimit),
               clamp(col[1], lowerLimit, upperLimit),
               clamp(col[2], lowerLimit, upperLimit),
               col[3]
            );
    
    gl_FragColor = col;
}
