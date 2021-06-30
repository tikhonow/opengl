#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    gl_Position = projection * view * vec4(aPos, 1.0);
}
#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 TexCoords;
uniform samplerCube skybox1;
uniform samplerCube skybox2;
uniform float blend;

void main() {
    vec4 FragColor1 = texture(skybox1, TexCoords);
    vec4 FragColor2 = texture(skybox2, TexCoords);
    FragColor = mix(FragColor1, FragColor2, blend);
}
