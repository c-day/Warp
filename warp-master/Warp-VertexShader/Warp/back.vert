/*	

*/

#version 400

layout (location = 0) in vec2 VertexPosition;

varying vec2 texLocation;

void main()
{
	texLocation = VertexPosition/2.0 - 0.5;

	gl_Position = vec4(VertexPosition, 0, 1);
}
