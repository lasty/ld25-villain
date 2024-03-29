/*
 * prim.h
 *
 *  For Ludum Dare 25:  You are the Villain
 *
 *  Created on: 15/12/2012
 *      Author: Lasty
 */

#ifndef PRIM_H_
#define PRIM_H_

#include "vertex.h"

class Image;

class Prim
{
protected:
	VertexArray &vbuff_ref;

	int offset = 0;  ///< offset into the vertex buffer
	int num = 0;  ///< number of elements
	int prim_type = 0;  ///< opengl primitive type


public:
	Prim(VertexArray &vtxbuff_ref);
	virtual ~Prim();

	Image *img_ref = nullptr;

	void Begin(int prim_type);

	void Vertex(const vertex &v);

	void End();


	void Draw();
};



class Quad : public Prim
{
public:
	Quad(VertexArray &vtxarr, float size);

	Quad(VertexArray &vtxarr, int divs, int x0, int y0, int x1, int y1);

};


#endif /* PRIM_H_ */
