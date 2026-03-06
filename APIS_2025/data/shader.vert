#version 330   
uniform mat4 mMat; 
uniform mat4 M;

in vec4 vPos;  
in vec2 vTexCoord;

out vec2 fTexCoord;
out vec3 fTexCube;
out vec4 fPos;

void main()  
{  
	gl_Position=mMat*vPos;  
	fTexCoord = vTexCoord;
	fPos = M*vPos; //mandamos el fragmento movido según indique Model
    fTexCube = (fPos.xyz);
}  