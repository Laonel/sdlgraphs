#include "sdlgraphs.h"

Graph::Graph(float xMin, float xMax, float xScale, float yMin, float yMax, float yScale, int width, int height, SDL_Window* wnd) :
	m_xMin(xMin),
	m_xMax(xMax),
	m_xScale(xScale),
	m_yMin(yMin),
	m_yMax(yMax),
	m_yScale(yScale),
	m_width(width),
	m_height(height)
{

	setColor(0xFF, 0xFF, 0xFF);
}

Graph::~Graph()
{
	SDL_FreeSurface(m_workingSurface);

	if (m_workingSurface)
		delete m_workingSurface;
}

SDL_Surface* Graph::getSurface() const
{
	return m_workingSurface;
}

void Graph::drawGrid(int thickness, int length)
{
	int w, h;

	thickness = abs(thickness);
	length = abs(length);

	w = _getWidthFromCoordinate(0.f);
	h = _getHeightFromCoordinate(0.f);

	int countX, countY;

	int pitchX, pitchY;
	pitchX = _getWidthFromCoordinate(m_xScale) - w;
	pitchY = _getHeightFromCoordinate(m_yScale) - h;

	for (countX = 0; countX < m_width; ++countX)
	{
		if ((countX - w) % pitchX == 0)
		{
			for (countY = h - length; countY <= h + length; ++countY)
				printPixelByWindow(countX, countY);
		}
		else
		{
			for (countY = h - thickness; countY <= h + thickness; ++countY)
				printPixelByWindow(countX, countY);
		}
	}

	for (countY = 0; countY < m_height; ++countY)
	{
		if (((countY - h) % pitchY) == 0)
		{
			for (countX = w - length; countX <= w + length; ++countX)
				printPixelByWindow(countX, countY);
		}
		else
		{
			for (countX = w - thickness; countX <= w + thickness; ++countX)
				printPixelByWindow(countX, countY);
		}
	}
}

void Graph::update()
{
	SDL_UpdateWindowSurface(m_window);
}

void Graph::clear()
{
	SDL_FillRect(m_workingSurface, NULL, 0x00000000);
	update();
}

void Graph::printPixel(float x, float y)
{
	Uint32 *pixel;

	pixel = _getPixelFromCoordinates(x, y);
	if (pixel != nullptr)
		*pixel = m_color;
}

void Graph::printPixelByWindow(int x, int y)
{
	Uint32 *pixel;

	pixel = _getPixelFromWindow(x, y);

	if (pixel != nullptr)
		*pixel = m_color;
}

void Graph::printPixelColor(float x, float y, Uint32 color)
{
	Uint32 *pixel;

	pixel = _getPixelFromCoordinates(x, y);

	if (pixel != nullptr)
		*pixel = m_color;
}

void Graph::printPixelByWindowColor(int x, int y, Uint32 color)
{
	Uint32 *pixel;

	pixel = _getPixelFromWindow(x, y);

	if (pixel != nullptr)
		*pixel = m_color;
}

int Graph::writeBMP(const std::string& filename)
{

}

void Graph::setTargetWindow(SDL_Window *wnd)
{
	if (!wnd)
		return;

	m_window = wnd;
	m_workingSurface = SDL_GetWindowSurface(wnd);
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
	int realHeight = _getHeightFromCoordinate(y);

	if (realHeight < 0 || realHeight >= m_height || realWidth < 0 || realWidth >= m_width)
		return nullptr;
	else
	{
		pixel = (Uint32*)m_workingSurface->pixels;

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
		h = y * m_width;
		pixel = (Uint32*)m_workingSurface->pixels + w + h;

		return pixel;
	}
}

int Graph::_writeBMPHeader(FILE *file, int width, int height)
{

}

int Graph::_writeBMPDate(FILE *file)
{

}
