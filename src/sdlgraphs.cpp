#include "sdlgraphs.h"

Graph(float xMin, float xMax, float xScale, yMin, yMax, yScale, int width, int height, Uint32 color) :
	m_xMin(xMin),
	m_xMax(xMax),
	m_xScale(xScale),
	m_yMin(yMin),
	m_yMax(yMax),
	m_yScale(yScale),
	m_width(width),
	m_height(height),
	m_color(color)
{
}

~Graph()
{
	SDL_FreeSurface(m_workingSurface);

	if (m_workingSurface)
		delete m_workingSurface;
}

SDL_Surface* getSurface() const
{

}

void drawGrid(int thickness, int length)
{
	int w, h;

	thickness = abs(thickness);
	length = abs(length);

	w = _getWidthFromCoordinate(0.f);
	h = _getHeightFromCoordinate(0.f);

	int countX, countY;

	int pitchX, pitchY;
	pitchX = _getWidthFromCoordinate(m_xScale) - width;
	pitchY = _getHeightFromCoordinate(m_yScale) - height;
}

void update()
{

}

void clear()
{

}

int writeBMP(const std::string& filename)
{

}

int Graph::_getWidthFromCoordinate(float x)
{
	int realWidth = (int)((float)m_width * (x - m_xMin) / (m_xMax - m_xMin));

	return realWidth;
}

int Graph::_getHeightFromCoordinate(float y)
{
	int realHeight = (int)((float)m_height - (float)m_height * (y - m_yMin) / (m_yMax - m_yMin));

	return realHeight;
}

Uint32* Graph::_getPixelFromCoordinates(float x, float y)
{
	Uint32 *pixel;

	int realWidth = _getWidthFromCoordinate(x);
	int relHeight = _getHeightFromCoordinate(y);

	if (realHeight < 0 || realHeight >= m_height || realWidth < 0 || realWidth >= m_width)
		return nullptr;
	else
	{
		pixel = m_workingSurface->pixels;

		Uint32 w, h;
		w = realWidth;
		h = realHeight * m_width;
		pixel += (w + h);

		return pixel;
	}
}

Uint32* Graph::_getPixelFromWindow(int x, int y)
{
	Uint32 *pixel;

	if (y < 0 || y >= m_height || x < 0 || x >= m_width)
		return nullptr;
	else
	{
		Uint32 w, h;
		w = x;
		height = y * m_width;
		pixel = (Uint32*)m_workingSurface->pixels + width + height;

		return pixel;
	}
}

int Graph::_writeBMPHeader(FILE *file, int width, int height)
{

}

int Graph::_writeBMPDate(FILE *file)
{

}
