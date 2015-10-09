uniform mat4 u_ModelViewMatrix;
uniform mat4 u_ModelViewInvTransMatrix;
uniform mat4 u_ModelViewProjectionMatrix;

attribute vec4 a_Vertex;
attribute vec3 a_Normal;
attribute vec2 a_TexCoord;

varying vec4 v_P;
varying vec3 v_N;
varying vec2 v_TexCoord;

void main(void) {
	v_P = u_ModelViewMatrix * a_Vertex;
	v_N = normalize(mat3(u_ModelViewInvTransMatrix) * a_Normal);
	v_TexCoord = a_TexCoord;
	gl_Position = u_ModelViewProjectionMatrix * a_Vertex;  
}
