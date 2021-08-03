#include "GraphicsBuffer.h"
#include <iostream>
#include "Color.h"
//Creates a buffer
GraphicsBuffer::GraphicsBuffer(std::string fileName) 
{
	mBitmap = al_load_bitmap(fileName.c_str());
	mWidth = al_get_bitmap_width(mBitmap);
	mHeight = al_get_bitmap_height(mBitmap);
	assert(mBitmap);
}

GraphicsBuffer::GraphicsBuffer(GraphicsBuffer *buffer) {

}

GraphicsBuffer::~GraphicsBuffer() 
{}

//Creats a buffer based on the width and height 
GraphicsBuffer::GraphicsBuffer(int width, int height) 
{
	mBitmap = al_create_bitmap(width, height);
	mWidth = width;
	mHeight = height;
	assert(mBitmap);
}