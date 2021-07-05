#shader vertex
#version 330

varying vec3 V_Normal;
varying vec3 V_WorldPos;
varying vec4 V_EyeSpacePos;
void main()
{
    V_Normal=mat3(NM)*normal;
    vec4 worldPos=M*vec4(pos,1.0);
    V_WorldPos=worldPos.xyz;
    V_EyeSpacePos=V*worldPos;
    gl_Position=P*V*worldPos;
}

#shader fragment
#version 330
uniform float U_FogStart;
uniform float U_FogEnd;
uniform vec4 U_FogColor;
varying vec3 V_Normal;
varying vec3 V_WorldPos;
varying vec4 V_EyeSpacePos;
float LinearFog(float distance)
{
    float fogAlpha=(distance-U_FogStart)/(U_FogEnd-U_FogStart);
    fogAlpha=clamp(fogAlpha,0.0,1.0);
    return fogAlpha;
}
void main()
{
    float fogAlpha = LinearFog(abs(V_EyeSpacePos.z/V_EyeSpacePos.w));
    gl_FragColor=mix(color, U_FogColor, fogAlpha);
}