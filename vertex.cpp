/*
 * vertex.cpp
 *
 *  For Ludum Dare 25:  You are the Villain
 *
 *  Created on: 15/12/2012
 *      Author: Lasty
 */

#include "vertex.h"
#include "globals.h"
#include "program.h"

VertexArray::VertexArray()
{
	glGenBuffers(1, &vbo_id);
}


VertexArray::~VertexArray()
{
	//ClearPointers();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo_id);
}

void VertexArray::Bind()
{
	static int last_vbo_used = -1;

	if (last_vbo_used != vbo_id)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
		last_vbo_used = vbo_id;
	}
}

void VertexArray::SetupArrays()
{
	//TODO: copy to VBO
	Bind();
	int datasize = sizeof(vertex) * this->size();
	auto usage = GL_STATIC_DRAW;
	GLvoid* data = this->data();

	glBufferData(GL_ARRAY_BUFFER, datasize, data, usage);
}

void VertexArray::SetPointers(Program *prog)
{
	Bind();

	constexpr auto stride = sizeof(vertex);

	ASSERT(prog->a_position != -1);
	//ASSERT(prog->a_texcoord != -1);
	glVertexAttribPointer(prog->a_position, 3, GL_FLOAT, GL_FALSE, stride, (void*) offsetof(vertex, x));
//	glVertexAttribPointer(prog->a_position, 3, GL_FLOAT, GL_FALSE, stride, (void*) &operator[](0).x);

	if (prog->a_texcoord != -1)
	{
		glVertexAttribPointer(prog->a_texcoord, 2, GL_FLOAT, GL_FALSE, stride, (void*) offsetof(vertex, u));
//		glVertexAttribPointer(prog->a_texcoord, 2, GL_FLOAT, GL_FALSE, stride, (void*) &operator[](0).u);
	}

	if (prog->a_normal != -1)
	{
		glVertexAttribPointer(prog->a_normal, 3, GL_FLOAT, GL_FALSE, stride, (void*) offsetof(vertex, nx));
//		glVertexAttribPointer(prog->a_normal, 3, GL_FLOAT, GL_FALSE, stride, (void*) &operator[](0).nx);
	}

	glEnableVertexAttribArray(prog->a_position);
	if (prog->a_texcoord != -1) glEnableVertexAttribArray(prog->a_texcoord);
	if (prog->a_normal != -1) glEnableVertexAttribArray(prog->a_normal);
}

void VertexArray::ClearPointers(Program *prog)
{
	glBindBuffer(GL_VERTEX_ARRAY, 0);

	glDisableVertexAttribArray(prog->a_position);
	glDisableVertexAttribArray(prog->a_texcoord);
	glDisableVertexAttribArray(prog->a_normal);
}

