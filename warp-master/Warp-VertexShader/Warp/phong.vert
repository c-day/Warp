/*	

*/

#version 400

layout (location = 0) in vec2 Vertex;
layout (location = 1) in vec3 Normals;
layout (location = 2) in 

varying vec3 N;
varying vec3 v;

void main(void)
{
v = vec3(modelview_matrix * Vertex);
N = normalize(normal_matrix * Normals);
gl_Position = mvp_matrix * Vertex;
}