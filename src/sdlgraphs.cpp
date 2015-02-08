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

void Graph::writeBMP(const std::string& filename)
{
	FILE *file = fopen(filename.c_str(), "wb");
	if (file == nullptr)
	{
		fprintf(stderr, "Error opening file\n");
		exit(1);
	}
	if (!_writeBMPHeader(file, m_width, m_height))
	{
		fprintf(stderr, "Error writing BMP header\n");
		exit(2);
	}
	if (!_writeBMPData(file))
	{
		fprintf(stderr, "Error writing BMP data\n");
		exit(3);
	}

	fclose(file);
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
	int size;
	if (width % 4 == 0)
		size = 54 + 3 * width * height;
	else
		size = 54 + 3 * width * height + height * (4 - width % 4);

	int temp[0x36] = 
	{
		0x42, 0x4D, // magic number
		size%0x100, size/0x100, size/0x10000, size/0x1000000, // size of BMP file
		0x00, 0x00,
		0x00, 0x00,
		0x36, 0x00, 0x00, 0x00,
		0x28, 0x00, 0x00, 0x00,
		width%0x100, width/0x100, width/0x10000, width/0x1000000, // width of bitmap in pixels
		height%0x100, height/0x100, height/0x10000, height/0x1000000, // height of the bitmap in pixels
		0x01, 0x00, // number color planes being used
		0x18, 0x00, // number of bits/pixel
		0x00, 0x00, 0x00, 0x00, // BI_RBG, no compression
		0x10, 0x00, 0x00, 0x00,	// size of raw BMP data (after header)
		0x13, 0x0B, 0x00, 0x00,	// horizontal reso (pixels/meter)
		0x13, 0x0B, 0x00, 0x00,	// vertical reso (pixels/meter)
		0x00, 0x00, 0x00, 0x00,	// number of colors in the palette
		0x00, 0x00, 0x00, 0x00	// all colors are important
	};

	for (int i = 0; i < 0x36; ++i)
		if (fputc(temp[i], file) == EOF)
			return 0;

	return 1;
}

int Graph::_writeBMPData(FILE *file)
{
	int padding;
	if (m_width % 4 == 0)
		padding = 0;
	else
		padding = 4 - (3 * m_width) % 4;

	Uint32 *pixel;
	Uint8 *subpixel;

	int widthCount, heightCount;

	for (heightCount = 0; heightCount < m_height; ++heightCount)
	{
		for (widthCount = 0; widthCount < m_width; ++widthCount)
		{
			pixel = _getPixelFromWindow(widthCount, m_height - heightCount - 1);
			if (pixel != nullptr)
			{
				subpixel = (Uint8*)pixel;
				if (fputc(subpixel[0], file) == EOF)
					return 0;
				if (fputc(subpixel[1], file) == EOF)
					return 0;
				if (fputc(subpixel[2], file) == EOF)
					return 0;
			}
		}

		for (int i = 0; i < padding; ++i)
			if (fputc(0x00, file) == EOF)
				return 0;
	}

	return 1;
}
