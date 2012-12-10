/*	

*/

#version 400

layout (location = 0) in vec2 VertexPosition;
layout (location = 1) in vec2 TexPosition;

varying vec2 texLocation;
uniform ivec2 framebuffer_size;
uniform vec2 mouse;
uniform vec2 mouseStart;
vec2 va = VertexPosition;
float dx = mouse.x - mouseStart.x;
float dy = mouse.y - mouseStart.y;
vec2 nearest;





float above_slope = -(1 - mouseStart.y)/dx;
float below_slope = (mouseStart.y+1)/dx;

float left_slope = (mouse.x+1)/dy;
float right_slope = -(1 - mouse.x)/dy;

float getSlope() {

	if(mouse.x >= 0)
	{
		nearest.x = 1;
	}
	else
	{
		nearest.x = -1;
	}

	if(mouse.y >= 0) 
	{
		nearest.y = 1;
	}
	else
	{
		nearest.y = -1;
	}

	float slope;

	if(abs(mouse.x-nearest.x) > abs(mouse.y-nearest.y))
	{
		slope = dy/(mouse.y-nearest.y);
	}
	else
	{
		slope = dx/(mouse.x-nearest.x);
	}


	return slope;

}


void main()
{
	texLocation = TexPosition;

	float slope = getSlope();

	if( va.x <= mouse.x )
	{
		va.x = dx*(va.x-nearest.x)/(mouse.x-nearest.x);
	}
	else
	{
		//va.x = dx*(2*mouse.x-va.x-nearest.x)/(mouse.x-nearest.x);
	}

	gl_Position = vec4(va, 0, 1);
}
