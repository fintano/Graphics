uniform mat4 u_ModelViewProjectionMatrix;

attribute vec4 a_Vertex;

void main(void) {
	gl_Position = u_ModelViewProjectionMatrix * a_Vertex;  
}