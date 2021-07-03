#version 120

uniform sampler2DRect tex0;
varying vec2 texCoordVarying;
uniform float seed;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main(){
    vec2 st = gl_FragCoord.xy;

    float rnd = rand( st * seed );

    gl_FragColor = vec4(vec3(rnd),1.0);
}
