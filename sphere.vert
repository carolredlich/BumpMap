#version 440

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 m;
uniform mat4 v;
uniform mat3 mv3;
uniform mat3 normalMatrix;
uniform vec3 lightPosition;
uniform vec3 eye;

in vec3 vtx;
in vec3 normal;
in vec2 texCoord;
in vec3 tangent;
in vec3 bitangent;

out vec3 lightDir_CS;
out vec3 eyeDir_CS;

smooth out vec3 light;
smooth out vec2 texCoordFrag;
smooth out vec3 eyePos;


vec3 computeVaryingLightDir(vec3 position, vec3 vLight)
{
    //Converte o vertice para as coordenadas da camera.
    vec4 vertex = vec4(position, 1.0f);
    vec4 vPosition4 = mv * vertex;
   
    //Faz a correcao pelo valor de w.
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;
   
    //Calcula o vetor da luy para a posicao do vertice.
    return normalize(vLight - vPosition3);
}

void main(void)
{   
    
    vec3 normalCameraspace = normalMatrix * normalize(normal);
    vec3 tangentCameraspace = normalMatrix * normalize(tangent);
    vec3 bitangentCameraspace = normalMatrix * normalize(bitangent);

    mat3 TBN = transpose(mat3(
    tangentCameraspace,
    bitangentCameraspace,
    normalCameraspace
    ));
  
    

    //light = computeVaryingLightDir( vtx, lightPosition );
    vec3 L_CS = ( v * vec4( lightPosition, 1)).xyz;
    vec3 vtx_CS = ( mv * vec4( vtx, 1)).xyz;

    lightDir_CS = L_CS - vtx_CS;
    eyeDir_CS = -vtx_CS;

    light = TBN * ( L_CS - vtx_CS );
    //light = TBN * ( lightPosition - vtx);
    
    eyePos = TBN * (  -vtx_CS );

    //Passa as coordenadas de textura
    texCoordFrag = texCoord;
 
    //Projeta as coordendas do vertice.
    gl_Position = mvp * vec4(vtx, 1.0f);
}   
