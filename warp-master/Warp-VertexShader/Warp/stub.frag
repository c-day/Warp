/*	
Craig Day and Lucas Mynsberge
*/

#version 400

layout (location = 0) out vec4 fragment_color;

uniform sampler2D image;
varying vec2 texLocation;

// simply passes the information from the vertex shader to the fragments on the screen.
void main(void)
{
	fragment_color = texture2D(image, texLocation);
}
