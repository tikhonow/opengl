#shader vertex
#version 330

uniform mat4 ModelViewProjectionMatrix;

layout(location = 0) in vec4 Vertex;
layout(location = 1) in vec4 Color;

out VertexData{
    vec4 mColor;
    vec4 mVertex;
} VertexOut;

void main(void)
{
    VertexOut.mColor = Color;
    VertexOut.mVertex = Vertex;
    gl_Position = ModelViewProjectionMatrix * Vertex;
}

#fragment shader
    #version 330

uniform vec4 CameraEye;
uniform vec4 FogColor;

in VertexData{
    vec4 mColor;
    vec4 mVertex;
} VertexIn;

float getFogFactor(float d)
{
    const float FogMax = 20.0;
    const float FogMin = 10.0;

    if (d>=FogMax) return 1;
    if (d<=FogMin) return 0;

    return 1 - (FogMax - d) / (FogMax - FogMin);
}

void main(void)
{
    vec4 V = VertexIn.mVertex;
    float d = distance(CameraEye, V);
    float alpha = getFogFactor(d);

    gl_FragColor = mix(VertexIn.mColor, FogColor, alpha);
}