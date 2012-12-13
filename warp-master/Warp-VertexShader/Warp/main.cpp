#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <assert.h>

#undef _UNICODE

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include "globals.h"
#include "fbo.h"
#include "shader.h"
#include "bowl.h"

/*
*************************************************
***             Project 2: Warp               ***
***                                           ***
***                   By:                     ***
***                Craig Day                  ***
***              Lucas Mynsberge              ***
*************************************************
*/


bool wire_frame = false;
// sets up wire frame option (toggle)
bool screen_visible = true;
// sets up curtain's visibility to part
int window_width = 1001;
int window_height = 610;
// sets nominal window conditions (and used to scale for resizing)
int image_1_w;
int image_1_h;
int tex_h;
int tex_w;
int pop_w;
int pop_h;
// provide the widths and heights (w,h) for the various textures used

//Shader Objects
Shader shader;
Shader background;
//Framebuffer Objects
FrameBufferObject frame;
FrameBufferObject overlay;
Bowl aBowl;
//Used by warp shader
vector<glm::vec2> sh_vertices;
vector<glm::vec2> tex_vertices;
GLuint vertex_coordinate_handle;
GLuint vertex_array_handle;
GLuint tex_coord_handle;
//Used by background shader
vector<glm::vec2> back_vertices;
GLuint back_coord_handle;
GLuint back_array_handle;
//General Use
GLuint image_1_handle;
GLuint tex_handle;
GLuint left_overlay_handle;
GLuint right_overlay_handle;
GLuint right_curtain_handle;
GLuint left_curtain_handle;
GLuint pop_handle;
glm::vec2 mouse(0,0);
glm::vec2 mouse_start(0, 0);

void rollCurtainOut()
{

}

void rollCurtainBack()
{

}

// function to render a frame buffer object
void RenderIntoBuffer(FrameBufferObject fbo, GLuint handle) 
{
	fbo.Bind();
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fbo.size.x/2, fbo.size.x/2, -fbo.size.y/2, fbo.size.y/2, 1, 10);
	// setting the ortho view and matrix views

	if (sh_vertices.size() == 0)
	{
		for (float i = -1.0; i <= 1.0; i += 0.01f)
		{
			for (float j = -1.0; j <= 1.0; j += 0.01f )
			{
				sh_vertices.push_back(glm::vec2( j, i ));
				sh_vertices.push_back(glm::vec2( j + 0.01, i ));
				sh_vertices.push_back(glm::vec2( j + 0.01, i + 0.01));
				sh_vertices.push_back(glm::vec2( j, i + 0.01));

				tex_vertices.push_back(glm::vec2( (j+1)/2.0f, (i+1)/2.0f ));
				tex_vertices.push_back(glm::vec2( ((j + 0.01)+1)/2.0f, (i+1)/2.0f ));
				tex_vertices.push_back(glm::vec2( ((j + 0.01)+1)/2.0f, ((i + 0.01)+1)/2.0f));
				tex_vertices.push_back(glm::vec2( (j+1)/2.0f, ((i + 0.01)+1)/2.0f));

			}
		}

		// get all the handles and bind them
		glGenBuffers(1, &vertex_coordinate_handle);
		assert(vertex_coordinate_handle != (GLuint) -1);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_coordinate_handle);
		glBufferData(GL_ARRAY_BUFFER, sh_vertices.size() * sizeof(glm::vec2), &sh_vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &tex_coord_handle);
		assert(tex_coord_handle != (GLuint) -1);
		glBindBuffer(GL_ARRAY_BUFFER, tex_coord_handle);
		glBufferData(GL_ARRAY_BUFFER, tex_vertices.size() * sizeof(glm::vec2), &tex_vertices[0], GL_STATIC_DRAW);

		glGenVertexArrays(1, &vertex_array_handle);
		glBindVertexArray(vertex_array_handle);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_coordinate_handle);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte *) NULL);
		glBindBuffer(GL_ARRAY_BUFFER, tex_coord_handle);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte *) NULL);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	// use the shader
	shader.Use();
	glUniform2i(shader.size_handle, fbo.size.x, fbo.size.y);
	glUniform2f(shader.mouse_handle, mouse.x, mouse.y);
	glUniform2f(shader.mouse_start_handle, mouse_start.x, mouse_start.y);

	glBindTexture(GL_TEXTURE_2D, handle);
	glUniform1i(shader.image_handle, GL_TEXTURE0 + handle);

	glViewport(0, 0, fbo.size.x, fbo.size.y);

	glClearColor(0, 0, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	assert(vertex_array_handle != (GLuint) -1);
	glBindVertexArray(vertex_array_handle);
	glDrawArrays(GL_QUADS, 0, (GLsizei) sh_vertices.size());

	// complete binding and then unbind the frame buffer object
	glBindVertexArray(0);
	glUseProgram(0);
	glEnable(GL_DEPTH_TEST);
	fbo.Unbind();
}

void DisplayFunc()
{
	glPolygonMode(GL_FRONT_AND_BACK, wire_frame ? GL_LINE : GL_FILL);
	
	RenderIntoBuffer(frame, image_1_handle);
	
	static GLfloat light_position[] = {0 , 0 , 15 , 1.0 };

	//clear the color and set up the model view and lighting
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0 , GL_POSITION , light_position);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0 );
	glEnable(GL_COLOR_MATERIAL);

	//////////////////////Main Scene image using background shader////////////////////
	//*

	// sets up the background
	glDisable(GL_LIGHTING | GL_DEPTH_TEST);
	if (back_vertices.size() == 0)
	{
		back_vertices.push_back(glm::vec2( -1.0, -1.0));
		back_vertices.push_back(glm::vec2( 1.0, -1.0));
		back_vertices.push_back(glm::vec2( 1.0, 1.0));
		back_vertices.push_back(glm::vec2( -1.0, 1.0));
		
		glGenBuffers(1, &back_coord_handle);
		assert(back_coord_handle != (GLuint) -1);
		glBindBuffer(GL_ARRAY_BUFFER, back_coord_handle);
		glBufferData(GL_ARRAY_BUFFER, back_vertices.size() * sizeof(glm::vec2), &back_vertices[0], GL_STATIC_DRAW);

		glGenVertexArrays(1, &back_array_handle);
		glBindVertexArray(back_array_handle);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, back_coord_handle);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte *) NULL);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	background.Use();
	
	glBindTexture(GL_TEXTURE_2D, tex_handle);
	glUniform1i(shader.image_handle, GL_TEXTURE0 + tex_handle);

	glClearColor(0, 0, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	assert(vertex_array_handle != (GLuint) -1);
	glBindVertexArray(back_array_handle);
	glDrawArrays(GL_QUADS, 0, (GLsizei) back_vertices.size());

	glBindVertexArray(0);
	glUseProgram(0);
	glEnable(GL_LIGHTING | GL_DEPTH_TEST);
	//////////////////////*/

	// the popcorn bucket is placed "on" the table
	glPushMatrix();
	glTranslated(0.6,-0.65,3.1);

	glPushMatrix();
	glRotated(23.0,1.0,0.0,0.0);
	glRotated(0.0,0.0,1.0,0.0);
	glRotated(0.0,0.0,0.0,1.0);

	glScalef(0.7,0.7,0.7);
	aBowl.bowlmake();

	glPopMatrix();

	glPopMatrix();

	//*

	// two curtains are placed over the screen
	glBindTexture(GL_TEXTURE_2D, left_overlay_handle);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.51f, -1.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.51f, 1.0f, 3.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 3.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	//*/


	//*
	glBindTexture(GL_TEXTURE_2D, right_overlay_handle);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 3.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.525f, -1.0f, 3.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.525f, 1.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 3.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	//*/

	//*
	glBegin(GL_QUADS);
	glColor3f(0.635f, 0.039f, 0.039f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -0.04f, 2.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, -0.04f, 2.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0f, 0.82f, 2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 0.82f, 2.0f);
	glEnd();
	//*/

	//*

	// the actual screen is placed.
	glBindTexture(GL_TEXTURE_2D, frame.texture_handles[0]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.52f, 0.8f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.52f, 0.8f, 1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	//*/
	


	glutSwapBuffers();
	glutPostRedisplay();
}

void TimerFunc(int period)
{
	glutTimerFunc(1000 / 60, TimerFunc, 1000 / 60);
	glutPostRedisplay();
}

void ReshapeFunc(int w, int h)
{
	if(w != 0 && h !=0 ) {
	window_width = w;
	window_height = h;
	}
}

void SpecialFunc(int c, int x, int y)
{

}

void KeyboardFunc(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'o':
		// provides the option to roll the curtains in or out
		screen_visible ? rollCurtainOut() : rollCurtainBack();
		break;
	case 'w':
		// allows wire fram mode to be toggled on or off (not interesting)
		wire_frame = !wire_frame;
		break;
	case 27:
	case 'x':
		glutLeaveMainLoop();
		return;

	}
}

void MouseFunc(int button, int state, int x, int y) 
{
	/*
	This part provides our starting mouse position for the warpable screen.  If outside the screen, it sets the value of the mouse to its proper location (either -1 or 1).
	In the case that it is in the screen, the mouse is set to the proper location via scaling the program's window's height and width.
	*/

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if(x < 0.25*window_width)
		{
			mouse_start.x = -1.0;
		}
		else if(x > 0.75*window_width)
		{
			mouse_start.x = 1.0;
		}
		else
		{
			mouse_start.x = float((x - (window_width/2.0))/(window_width/4.0));
		}
		if(y < 0.1*window_height)
		{
			mouse_start.y = 1.0;
		}
		else if(y > 0.5*window_height)
		{
			mouse_start.y = -1.0;
		}
		else 
		{
			mouse_start.y = float((window_height - y)/(0.20*window_height) - 3.50);
		}

		cout << "Mouse Start: " << mouse_start.x << ", " << mouse_start.y << endl;
	}
	
	// This just sets up the mouse location if the button isn't pressed down.
	if(x < 0.25*window_width)
	{
		mouse.x = -1.0;
	}
	else if(x > 0.75*window_width)
	{
		mouse.x = 1.0;
	}
	else
	{
		mouse.x = float((x - (window_width/2.0))/(window_width/4.0));
	}
	if(y < 0.1*window_height)
	{
		mouse.y = 1.0;
	}
	else if(y > 0.5*window_height)
	{
		mouse.y = -1.0;
	}
	else 
	{
		mouse.y = float((window_height - y)/(0.20*window_height) - 3.50);
	}
	
}

void MotionFunc(int x, int y)
{
	/*
	This part provides our current mouse position for the warpable screen.  If outside the screen, it sets the value of the mouse to its proper location (either -1 or 1).
	In the case that it is in the screen, the mouse is set to the proper location via scaling the program's window's height and width.
	*/
	
	if(x < 0.25*window_width)
	{
		mouse.x = -1.0;
	}
	else if(x > 0.75*window_width)
	{
		mouse.x = 1.0;
	}
	else
	{
		mouse.x = float((x - (window_width/2.0))/(window_width/4.0));
	}
	if(y < 0.1*window_height)
	{
		mouse.y = 1.0;
	}
	else if(y > 0.5*window_height)
	{
		mouse.y = -1.0;
	}
	else 
	{
		mouse.y = float((window_height - y)/(0.20*window_height) - 3.50 );
	}

	cout << "Mouse: " << mouse.x << ", " << mouse.y << endl;
	
}

void CloseFunc()
{
	shader.TakeDown();
	frame.TakeDown();
}

int main(int argc, char * argv[])
{
	glutInit(&argc , argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(0 , 0);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Warp");
	glutDisplayFunc(DisplayFunc);
	glutTimerFunc(1000 / 60, TimerFunc, 1000 / 60);
	glutReshapeFunc(ReshapeFunc);
	glutSpecialFunc(SpecialFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MotionFunc);
	glutCloseFunc(CloseFunc);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glEnable(GL_DEPTH_TEST);

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW failed to initialize." << endl;
		return 0;
	}
			
	if (!shader.Initialize("stub.vert", "stub.frag"))
	{
		return 0;
	}

	if (!background.Initialize("back.vert", "back.frag"))
	{
		return 0;
	}

	// uses DevIL to grab the images used in textures and then prepares them for us.
	image_1_handle = ilutGLLoadImage("lotr-scene.jpg");
	image_1_w = ilGetInteger(IL_IMAGE_WIDTH);
	image_1_h = ilGetInteger(IL_IMAGE_HEIGHT);
	
	tex_handle = ilutGLLoadImage("Home-Theater.jpg");
	tex_w = ilGetInteger(IL_IMAGE_WIDTH);
	tex_h = ilGetInteger(IL_IMAGE_HEIGHT);

	left_overlay_handle = ilutGLLoadImage("left-over.jpg");
	right_overlay_handle = ilutGLLoadImage("right-over.jpg");
	left_curtain_handle = ilutGLLoadImage("left-curtain.jpg");

	pop_handle = ilutGLLoadImage("popcorn.jpg");
	pop_w = ilGetInteger(IL_IMAGE_WIDTH);
	pop_h = ilGetInteger(IL_IMAGE_HEIGHT);

	aBowl.setTex(pop_handle);

	cout << "Image 1: " << image_1_w << " x " << image_1_h << endl;
	cout << "Background: " << tex_w << " x " << tex_h << endl;
	cout << "Popcorn: " << pop_w << " x " << pop_h << endl;

	if (!frame.Initialize(glm::ivec2(image_1_w, image_1_h), 1, true))
	{
		cerr << "Frame buffer 1 failed to initialize." << endl;
		return 0;
	}

	cout << "Window Size: " << window_width << " x " << window_height << endl;
	cout << "Frame buffer 1 size: " << frame.size.x << " x " << frame.size.y << endl;

	glutMainLoop();
	return 0;
}