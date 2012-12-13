/*	
Craig Day and Lucas Mynsberge
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
// set up the distance for displacement by taking the difference between the current mouse position adn where it started.




void main()
{
	texLocation = TexPosition;
	// this next part eliminates divide by zero errors without giving the user a noticeable change.
	if(dx == 0){ dx = 0.001;}
	if(dy == 0){ dy = 0.001;}

	// this finds the slopes for movement if the screen is split up into two different halves
	float above_slope = -(1 - mouseStart.y)/dx;
	float below_slope = (mouseStart.y+1)/dx;
	float left_slope = (mouse.x+1)/dy;
	float right_slope = -(1 - mouse.x)/dy;

	// this part splits the x-movement into two parts--that above y=0 and that below. 
	if(va.y >= mouseStart.y)
	{
		if(va.x < 0)
		{
			// here we move the vertices proportional to the movement of the start point for x <0. The edges are held in place.
			va.x -= ((1-va.y)/above_slope)*(va.x+1)/(mouseStart.x+1);
		}
		else
		{
			// here we move the vertices proportional to the movement of the start point for x >0. The edges are held in place.
			va.x -= ((1-va.y)/above_slope)*(1-va.x)/(1-mouseStart.x);
		}
	}
	else
	{
		if(va.x < 0)
		{
			// this is the same as above except now for the y values below 0.
			va.x += ((va.y+1)/below_slope)*(va.x+1)/(mouseStart.x+1);
		}
		else
		{
			va.x += ((va.y+1)/below_slope)*(1-va.x)/(1-mouseStart.x);
		}
	}


	// similarly, splits the y-movement into two parts, except now for x below and above zero.
	
	if (va.x >= mouse.x)
	{
		if(va.y < 0)
		{
			// this section is all the same as the above section except now the movement is for y with it's movement based on the x-axis.
			va.y -= ((1-va.x)/right_slope)*(va.y+1)/(mouseStart.y+1);
		}
		else
		{
			va.y -= ((1-va.x)/right_slope)*(1 - va.y)/(1-mouseStart.y);
		}
	}
	else
	{
		if(va.y < 0)
		{
			va.y += ((va.x+1)/left_slope)*(va.y+1)/(mouseStart.y+1);
		}
		else
		{
			va.y += ((va.x+1)/left_slope)*((1 - va.y)/(1-mouseStart.y));
		}
	}
	


	gl_Position = vec4(va, 0, 1);
}