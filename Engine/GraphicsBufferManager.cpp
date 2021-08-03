#include "GraphicsBufferManager.h"

using namespace std;

GraphicsBufferManager::GraphicsBufferManager()
{

}

GraphicsBufferManager::~GraphicsBufferManager()
{

}

void GraphicsBufferManager::addBuffer(BufferName name, GraphicsBuffer* buffer)
{
	map<BufferName, GraphicsBuffer*>::iterator iter = mBuffMap.find(name);

	if (iter == mBuffMap.end())
		mBuffMap[name] = buffer;
	else
		cout << "Name already taken, could not create" << endl;
}

void GraphicsBufferManager::removeBuffer(BufferName name)
{
	map<BufferName, GraphicsBuffer*>::iterator iter = mBuffMap.find(name);

	if (iter != mBuffMap.end())
	{
		delete iter->second;
		mBuffMap.erase(iter);
	}
	
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(BufferName name)
{
	map<BufferName, GraphicsBuffer*>::iterator iter = mBuffMap.find(name);

	if (iter != mBuffMap.end())
		return iter->second;
	else
		return NULL;
}

void GraphicsBufferManager::clear()
{
	map<BufferName, GraphicsBuffer*>::iterator iter;

	for (iter = mBuffMap.begin(); iter != mBuffMap.end(); ++iter)
	{
		GraphicsBuffer* pGB = iter->second;
		delete pGB;
	}

	mBuffMap.clear();
}