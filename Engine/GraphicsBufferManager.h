#pragma once

#include "GraphicsBuffer.h"
#include "Trackable.h"
#include <map>

typedef std::string BufferName;

class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager();
	~GraphicsBufferManager();

	void addBuffer(BufferName name, GraphicsBuffer* buffer);
	void removeBuffer(BufferName name);
	GraphicsBuffer* getBuffer(BufferName name);

	void clear();

private:
	std::map<BufferName, GraphicsBuffer*> mBuffMap;
};