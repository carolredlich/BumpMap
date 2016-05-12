#version 440

uniform vec4 lightAmbient;
uniform vec4 lightDifuse;
uniform vec4 lightSpecular;

uniform sampler2D textImg;
uniform sampler2D textNormal;

in vec2 texCoordFrag;
in vec3 light;
in vec3 eyePos;

in vec3 lightDir_CS;
in vec3 eyeDir_CS;

out vec4 fragmentColor;

void main(void)
{
    
   //Transforma rgb para normal
    vec3 normal = normalize(2 * ( texture( textNormal, texCoordFrag ).rgb - vec3(0.5, 0.5, 0.5) ) );

    vec4 texColor = texture( textImg, texCoordFrag );
        
    //Normaliza as direcoes das luzes
    vec3 L =  normalize( light );

    //Inicializa a cor do fragmento com a cor ambiente.
    fragmentColor = lightAmbient ;
   
    //Faz o calculo da cor difusa
    float diff1 = max( 0.0f, dot( normal, L ) );
    fragmentColor.rgb += diff1 * lightDifuse.rgb ;

    //Interpola cor com a textura
    fragmentColor.rgb = mix(fragmentColor, texColor, 0.5 ).rgb;
  
    //Calcula a especular da luz.
    if (diff1 != 0)
    {
        vec3 vReflection = normalize(reflect(-L, normal ));
        float spec = max(0.0, dot(normalize(eyePos), vReflection)) ;
        //float spec = max(0.0, dot(normalize(normal), vReflection)) ;
        //float fSpec = pow(spec*0.8, 8); //Basquete
        float fSpec = pow(spec*0.6, 3);
        //float fSpec = pow(spec, 9);

        fragmentColor.rgb += lightSpecular.rgb * fSpec ;

        
    }

    vec3 n_lightDir_CS = normalize( lightDir_CS );
    vec3 n_eyeDir_CS = normalize( eyeDir_CS );

    //fragmentColor.rgb = n_lightDir_CS;
}