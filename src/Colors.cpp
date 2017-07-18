#include "Colors.h"
#include "mathematics.h"

namespace Johnny
{
	namespace Colors
	{
		SDL_Color* m_COLOR_KEY = new SDL_Color;

		SDL_Color RAND(Uint8 r, Uint8 g, Uint8 b)
		{
			SDL_Color col;
			col.r = (r == -1 ? getRand(0,255) : r);
			col.g = (g == -1 ? getRand(0,255) : g);
			col.b = (b == -1 ? getRand(0,255) : b);
			col.a = 255;

			return col;
		}
		SDL_Color* KEY(Uint8 r, Uint8 g, Uint8 b)
		{
			m_COLOR_KEY->r = r;
			m_COLOR_KEY->g = g;
			m_COLOR_KEY->b = b;
			m_COLOR_KEY->a = 255;

			return m_COLOR_KEY;
		}
	}
}
