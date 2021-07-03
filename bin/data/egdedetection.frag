#version 120

uniform sampler2DRect tex0;
varying vec2 texCoordVarying;


void getNeighbouringPixels(sampler2DRect tex0, vec2 texCoordVarying, out vec4[9] result) {
    result[0] = texture2DRect(tex0, texCoordVarying + vec2(-1.0, -1.0));
    result[1] = texture2DRect(tex0, texCoordVarying + vec2(-1.0));
    result[2] = texture2DRect(tex0, texCoordVarying + vec2(1.0, -1.0));
    
    result[3] = texture2DRect(tex0, texCoordVarying + vec2(-1.0, 0));
    result[4] = texture2DRect(tex0, texCoordVarying);
    result[5] = texture2DRect(tex0, texCoordVarying + vec2(+1.0, 0));
    
    result[6] = texture2DRect(tex0, texCoordVarying + vec2(-1.0, +1.0));
    result[7] = texture2DRect(tex0, texCoordVarying + vec2(0.0, +1.0));
    result[8] = texture2DRect(tex0, texCoordVarying + vec2(+1.0, +1.0));
}

vec4 applyKernel(vec4[9] pixels, float[9] kernel)
{
    vec4 result = vec4(0,0,0,0);
    
    for (int i=0; i<9; i++) {
        result += kernel[i] * pixels[i];
    }
    result[3] = 1.0;
    return result;
}

void main(){
    
    float kernel[9] = float[9](-1, -1, -1,
                               -1,  8, -1,
                               -1, -1, -1);
     
    vec4 pixels[9];
    getNeighbouringPixels(tex0, texCoordVarying, pixels);
    gl_FragColor = applyKernel(pixels, kernel);
}
