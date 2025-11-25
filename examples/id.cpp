#include "mat.hpp"

inline constexpr int spiral(int w, int h, int x, int y)
{
	return y ? w + spiral(h - 1, w, y -1, w - x - 1) : x;
}

int main(int argc, char** argv)
{
	mat<int,16> dst;

	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			dst[i][j] = spiral(16, 16, j, i);
			printf("\x1b[48;5:%hhum %03hhu \x1b[0m", dst[i][j], dst[i][j]);
		}
		printf("%22s\n"," ");
	}

	exit(EXIT_SUCCESS);
}
