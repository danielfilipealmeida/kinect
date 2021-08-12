#version 120

uniform sampler2DRect tex0;
varying vec2 texCoordVarying;
uniform vec3 color;

float channelOperation(float val1, float val2) {
    return clamp(1 - (val1 * val2), 0.0, 1.0);
}

void main(){
    
    vec4 col = texture2DRect(tex0, texCoordVarying);
    
    col[0] = channelOperation(col[0], color[0]);
    col[1] = channelOperation(col[1], color[1]);
    col[2] = channelOperation(col[2], color[2]);

    gl_FragColor = col;
}
