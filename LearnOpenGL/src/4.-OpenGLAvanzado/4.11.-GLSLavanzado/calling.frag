#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D frontTexture;

void main(){
//	vec4 texColor = texture(texture1, TexCoords);
//	FragColor = texColor;
//	if(gl_FragCoord.x < 400){
//		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
//	}
//	else{
//		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
//	}
	if(gl_FrontFacing){
		gl_FragDepth = 0.0;
		FragColor = texture(frontTexture, TexCoords);
	}
	else{
		FragColor = vec4(0.0, 1.0, 0.0, 0.1);	
	}
}