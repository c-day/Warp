#include "bowl.h"


Bowl::Bowl()
{
	// set up some basic bowl characteristics
	count = 0;
	filled = true;
}

void Bowl::setTex(GLuint tex)
{
	// lets us define the texture to be used on this vertex array.
	this->pop_handle = tex;
}

void Bowl::bowlbot()
{
	// give some constant value for conversion and then make sure vertices are empty.
	double toRad = 3.14159265359 / 180.0;
	if(va_vertices.size() == 0) {
	for(double i = 0; i < 360; i++)
	{
		// go from 0 to 360 for degrees
		for(double j = 0; j <= 100; j++)
		{
				// go from 0 to 100 (really 0 to 0.5) in vertical distance.
				double j_tmp = j/200;
				double radius = 0.2;
				double scale = j_tmp/5.0;


				// First triangle
				// Vertex 0 - initial point.
				this->va_texture.push_back(i/360.0);
				this->va_texture.push_back(j/100.0);
				
				this->va_vertices.push_back(cos(i*toRad)*(scale+radius));	//x
				this->va_vertices.push_back(j_tmp);	//y
				this->va_vertices.push_back(sin(i*toRad)*(scale+radius));	//z
				
				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));			//z
			
				this->va_indices.push_back(count);
				count++;

				// Vertex 1 - moving up the y-axis (slope of cylinder)
				this->va_texture.push_back(i/360.0);
				this->va_texture.push_back(j/100.0+1.0/200.0);
			
				this->va_vertices.push_back(cos(i*toRad)*(scale+radius));	//x
				this->va_vertices.push_back(j_tmp+0.005);	//y
				this->va_vertices.push_back(sin(i*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));		
			
				this->va_indices.push_back(count);
				count++;

				// Vertex 1 - moving up the y-axis (slope of cylinder)
				this->va_texture.push_back(i/360.0);
				this->va_texture.push_back(j/100.0+1.0/200.0);

				this->va_vertices.push_back(cos(i*toRad)*(scale+radius));	//x
				this->va_vertices.push_back((j_tmp+0.005));	//y
				this->va_vertices.push_back(sin(i*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));		

				this->va_indices.push_back(count);
				count++;

				// Vertex 2 - moving up the y-axis (slope of cylinder) and increasing theta by 1 for x and z
				this->va_texture.push_back((i+1)/360.0);
				this->va_texture.push_back(j/100.0+1.0/200.0);
			
				this->va_vertices.push_back(cos((i+1)*toRad)*(scale+radius));	//x
				this->va_vertices.push_back((j_tmp+0.005));	//y
				this->va_vertices.push_back(sin((i+1)*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));				//z
			
				this->va_indices.push_back(count);
				count++;

				// Vertex 2 - moving up the y-axis (slope of cylinder) and increasing theta by 1 for x and z
				this->va_texture.push_back((i+1)/360.0);
				this->va_texture.push_back(j/100.0+1.0/200.0);
			
				this->va_vertices.push_back(cos((i+1)*toRad)*(scale+radius));	//x
				this->va_vertices.push_back((j_tmp+0.005));	//y
				this->va_vertices.push_back(sin((i+1)*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));		
			
				this->va_indices.push_back(count);
				count++;

				// Vertex 0 - back to our start
				this->va_texture.push_back(i/360.0);
				this->va_texture.push_back(j/100.0);
			
				this->va_vertices.push_back(cos((i)*toRad)*(scale+radius));	//x
				this->va_vertices.push_back(j_tmp);	//y
				this->va_vertices.push_back(sin((i)*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));		

				this->va_indices.push_back(count);
				count++;

				// Second triangle
				// Vertex 0 - the initial point
				this->va_texture.push_back(i/360.0);
				this->va_texture.push_back(j/100.0);
			
				this->va_vertices.push_back(cos((i)*toRad)*(scale+radius));	//x
				this->va_vertices.push_back(j_tmp);	//y
				this->va_vertices.push_back(sin((i)*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));		

				this->va_indices.push_back(count);
				count++;

				// Vertex 2 - moving up the y-axis (slope of cylinder) and increasing theta by 1 for x and z
				this->va_texture.push_back((i+1)/360.0);
				this->va_texture.push_back(j/100.0+1.0/200.0);
			
				this->va_vertices.push_back(cos((i+1)*toRad)*(scale+radius));	//x
				this->va_vertices.push_back((j_tmp+0.005));	//y
				this->va_vertices.push_back(sin((i+1)*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));		
			
				this->va_indices.push_back(count);
				count++;

				// Vertex 2 - moving up the y-axis (slope of cylinder) and increasing theta by 1 for x and z
				this->va_texture.push_back((i+1)/360.0);
				this->va_texture.push_back(j/100.0+1.0/200.0);
			
				this->va_vertices.push_back(cos((i+1)*toRad)*(scale+radius));	//x
				this->va_vertices.push_back((j_tmp+0.005));	//y
				this->va_vertices.push_back(sin((i+1)*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));		
			
				this->va_indices.push_back(count);
				count++;

				// Vertex 3 - Increasing theta by 1 for x and z
				this->va_texture.push_back((i+1)/360.0);
				this->va_texture.push_back(j/100.0);
			
				this->va_vertices.push_back(cos((i+1)*toRad)*(scale+radius));	//x
				this->va_vertices.push_back((j_tmp));	//y
				this->va_vertices.push_back(sin((i+1)*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));		
			
				this->va_indices.push_back(count);
				count++;

				// Vertex 3 - Increasing theta by 1 for x and z
				this->va_texture.push_back((i+1)/360.0);
				this->va_texture.push_back(j/100.0);
			
				this->va_vertices.push_back(cos((i+1)*toRad)*(scale+radius));	//x
				this->va_vertices.push_back((j_tmp));	//y
				this->va_vertices.push_back(sin((i+1)*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));		
			
				this->va_indices.push_back(count);
				count++;

				// Vertex 0 - back to our start
				this->va_texture.push_back(i/360.0);
				this->va_texture.push_back(j/100.0);
			
				this->va_vertices.push_back(cos((i)*toRad)*(scale+radius));	//x
				this->va_vertices.push_back(j_tmp);	//y
				this->va_vertices.push_back(sin((i)*toRad)*(scale+radius));	//z

				this->va_normals.push_back((5.0*j_tmp+0.2)*cos(i * toRad) );	//x
				this->va_normals.push_back(j_tmp/scale );	//y
				this->va_normals.push_back((5.0*j_tmp+0.2)*sin(i*toRad));		

				this->va_indices.push_back(count);
				count++;
		}
	}
	}
}

void Bowl::bowlmake()
{
	glPushMatrix();
	// draw the bowl.
	bowlbot();

	// begin to bind the picture of the popcorn to the bucket.
	glBindTexture(GL_TEXTURE_2D, pop_handle);
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// enable and utilize the vertex array system to give the vertices of the object and place the texture on those points.
	glVertexPointer(3 , GL_DOUBLE , 0 , &this->va_vertices[0]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_DOUBLE, 0 , &this->va_texture[0]);
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glNormalPointer(GL_DOUBLE, 0, &this->va_normals[0]);
	glEnableClientState(GL_NORMAL_ARRAY);

	// draw the vertices created
	glDrawElements(GL_QUADS , va_indices.size() , GL_UNSIGNED_INT , &this->va_indices[0]);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
}


vector<glm::vec3> Bowl::getVertArray()
{
	if(bowl_vertices.size() == 0)
		{
		for(int i = 0; i < this->va_vertices.size()/3; i += 3)
		{
			bowl_vertices.push_back(glm::vec3(va_vertices[i], va_vertices[i+1], va_vertices[i+2]));
		}
	}
	return bowl_vertices;
}