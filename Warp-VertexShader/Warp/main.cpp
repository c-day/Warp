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

bool wire_frame = false;
int window_width = 1250;
int window_height = 1000;
int image_1_w;
int image_1_h;
int image_2_w;
int image_2_h;
int tex_h;
int tex_w;

Shader shader;
FrameBufferObject frame;
FrameBufferObject fire;
vector<glm::vec2> sh_vertices;
vector<glm::vec2> tex_vertices;
GLuint vertex_coordinate_handle;
GLuint vertex_array_handle;
GLuint tex_coord_handle;
GLuint image_1_handle;
GLuint image_2_handle;
GLuint tex_handle;
glm::vec2 mouse(0,0);
glm::vec2 mouse_start(0, 0);


void RenderIntoBuffer(FrameBufferObject fbo, GLuint handle) 
{


}

void DisplayFunc()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10);

	if (sh_vertices.size() == 0)
	{
		for (float i = -1.0; i <= 1.0; i += 0.01)
		{
			for (float j = -1.0; j <= 1.0; j += 0.01 )
			{
				sh_vertices.push_back(glm::vec2( j, i ));
				sh_vertices.push_back(glm::vec2( j + 0.01, i ));
				sh_vertices.push_back(glm::vec2( j + 0.01, i + 0.01));
				sh_vertices.push_back(glm::vec2( j, i + 0.01));

				tex_vertices.push_back(glm::vec2( (j+1)/2.0f, (i+1)/2.0f ));
				tex_vertices.push_back(glm::vec2( ((j + 0.01)+1)/2.0f, (i+1)/2.0f ));
				tex_vertices.push_back(glm::vec2( ((j + 0.01)+1)/2.0f, ((i + 0.01)+1)/2.0f));
				tex_vertices.push_back(glm::vec2( (j+1)/2.0f, ((i + 0.01)+1)/2.0f));
				/*
				cout << "Vertex Coords: " << i << ", " << j << " - ";
				cout << i + 0.01 << ", " << j << " - ";
				cout << i + 0.01 << ", " << j + 0.01 << " - ";
				cout << i << ", " << j + 0.01 << endl;
				//*/
			}
		}

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
	
	shader.Use();
	glUniform2i(shader.size_handle, window_width, window_height);
	glUniform2f(shader.mouse_handle, mouse.x, mouse.y);
	glUniform2f(shader.mouse_start_handle, mouse_start.x, mouse_start.y);

	glBindTexture(GL_TEXTURE_2D, image_1_handle);
	glUniform1i(shader.image_handle, GL_TEXTURE0 + image_1_handle);

	glViewport(0, 0, window_width, window_height);

	glClearColor(0, 0, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	assert(vertex_array_handle != (GLuint) -1);
	glBindVertexArray(vertex_array_handle);
	glDrawArrays(GL_QUADS, 0, (GLsizei) sh_vertices.size());

	glBindVertexArray(0);
	glUseProgram(0);
	
	/*
	RenderIntoBuffer(frame, image_1_handle);
	RenderIntoBuffer(fire, image_2_handle);
	
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(15, double(window_width) / double(window_height), 1, 10);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, frame.texture_handles[0]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	/*
	glBindTexture(GL_TEXTURE_2D, tex_handle);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	

	glBindTexture(GL_TEXTURE_2D, frame.texture_handles[0]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-0.40f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.4f, 0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.4f, 0.8f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-0.40f, 0.8f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	
	/*
	glBindTexture(GL_TEXTURE_2D, fire.texture_handles[0]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-0.20f, -0.55f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.195f, -0.55f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.195f, -0.235f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-0.20f, -0.235f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	*/
	
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

	case 27:
	case 'x':
		glutLeaveMainLoop();
		return;

	}
}

void MouseFunc(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouse_start.x = (2*x - window_width)/float(window_width);
		mouse_start.y = (-2*y + window_height)/float(window_height);
		cout << "Mouse Start: " << mouse_start.x << ", " << mouse_start.y << endl;
	}
	
	mouse.x = (2*x - window_width)/float(window_width);
	mouse.y = (-2*y + window_height)/float(window_height);
	
}

void MotionFunc(int x, int y)
{
	
	mouse.x = (2*x - window_width)/float(window_width);
	mouse.y = (-2*y + window_height)/float(window_height);

	cout << "Mouse: " << mouse.x << ", " << mouse.y << endl;
	
}

void CloseFunc()
{
	shader.TakeDown();
	frame.TakeDown();
	fire.TakeDown();
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



	image_1_handle = ilutGLLoadImage("lotr1.jpg");
	image_1_w = ilGetInteger(IL_IMAGE_WIDTH);
	image_1_h = ilGetInteger(IL_IMAGE_HEIGHT);
	image_2_handle = ilutGLLoadImage("fire.jpg");
	image_2_w = ilGetInteger(IL_IMAGE_WIDTH);
	image_2_h = ilGetInteger(IL_IMAGE_HEIGHT);
	tex_handle = ilutGLLoadImage("fireplace.jpg");
	tex_w = ilGetInteger(IL_IMAGE_WIDTH);
	tex_h = ilGetInteger(IL_IMAGE_HEIGHT);

	cout << "Image 1: " << image_1_w << " x " << image_1_h << endl;
	cout << "Image 2: " << image_2_w << " x " << image_2_h << endl;
	cout << "Background: " << tex_w << " x " << tex_h << endl;

	if (!frame.Initialize(glm::ivec2(image_1_w/3, image_1_h/2), 1, true))
	{
		cerr << "Frame buffer 1 failed to initialize." << endl;
		return 0;
	}

	if (!fire.Initialize(glm::ivec2(image_2_w, image_2_h), 1, true))
	{
		cerr << "Frame buffer 2 failed to initialize." << endl;
		return 0;
	}

	cout << "Window Size: " << window_width << " x " << window_height << endl;
	cout << "Frame buffer 1 size: " << frame.size.x << " x " << frame.size.y << endl;

	glutMainLoop();
	return 0;
}