#version 330   

uniform sampler2D colorText; //unidad de textura de color

uniform samplerCube textSamplerCube; //nuevo

uniform bool useColorText;
uniform vec4 colorRGBA;
uniform int textureType; //nuevo


in vec2 fTexCoord;
in vec3 fTexCube; //nuevo

out vec4 fragColor;  

void main()  
{  
    vec4 tColor = vec4(0, 0, 0, 0);
    if(useColorText)
        if (textureType == 0) //textura 2D
            {
                tColor = texture(colorText, fTexCoord);
            }
            else if (textureType == 1) //textura cubemap
            {
                tColor=textureCube(textSamplerCube, fTexCube);
            }

    fragColor = colorRGBA*tColor; //asignar color de salida
}  