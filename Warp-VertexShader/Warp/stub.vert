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





void main()
{
	texLocation = TexPosition;

	if(dx == 0){ dx = 0.001;}
	if(dy == 0){ dy = 0.001;}

	float above_slope = -(1 - mouseStart.y)/dx;
	float below_slope = (mouseStart.y+1)/dx;
	float left_slope = (mouse.x+1)/dy;
	float right_slope = -(1 - mouse.x)/dy;

	if(va.y >= mouseStart.y)
	{
		if(va.x < 0)
		{
			va.x -= ((1-va.y)/above_slope)*(va.x + 1);
		}
		else
		{
			va.x -= ((1-va.y)/above_slope)*(1 - va.x);
		}
	}
	else
	{
		if(va.x < 0)
		{
			va.x += ((va.y+1)/below_slope)*(va.x + 1);
		}
		else
		{
			va.x += ((va.y+1)/below_slope)*(1 - va.x);
		}
	}


	//Uncomment the block below to add in y-displacement
	//*
	if (va.x >= mouse.x)
	{
		if(va.y < 0)
		{
			va.y -= ((1-va.x)/right_slope)*(va.y + 1);
		}
		else
		{
			va.y -= ((1-va.x)/right_slope)*(1 - va.y);
		}
	}
	else
	{
		if(va.y < 0)
		{
			va.y += ((va.x+1)/left_slope)*(va.y + 1);
		}
		else
		{
			va.y += ((va.x+1)/left_slope)*(1 - va.y);
		}
	}
	//*/


	gl_Position = vec4(va, 0, 1);
}
