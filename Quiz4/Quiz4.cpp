#define _USE_MATH_DEFINES
#define TRUE 1
#define FALSE 0
#include "CoalaMOD.h"
#include "stdio.h"
#include "math.h"
#pragma comment(lib, "CoalaMOD.lib")

void build(int centerX, int centerY, int centerZ);
double degToRad(double degrees);

int main()
{
	int px, py, pz;
	getPlayerLocation(&px, &py, &pz);
	const double playerDirection = getPlayerDirection();
	printf("Direction : %f", playerDirection);
	const double playerDirectionRad = degToRad(playerDirection);// z축을 기준으로 시계방향의 각도

	const int distance = 30;
	build(px + -distance * sin(playerDirectionRad), py, pz + distance * cos(playerDirectionRad));
}

double degToRad(double degrees) {
	return degrees * M_PI / 180;
}

void build(int centerX, int centerY, int centerZ) {
	BlockID ironBlock = createBlock(BLOCK_IRON);
	BlockID glassBlock = createBlock(BLOCK_GLASS);
	BlockID goldBlock = createBlock(BLOCK_GOLD);
	BlockID diamondBlock = createBlock(BLOCK_DIAMOND);
	BlockID emeraldBlock = createBlock(BLOCK_EMERALD);
	BlockID airBlock = createBlock(BLOCK_AIR);
	BlockID tntBlock = createBlock(BLOCK_TNT);
	char isGlass = FALSE; // 유리와 철 블럭을 번갈아 배치할 것임.
	float degs = 0; // 콜라병같은 디자인을 위해서.
	for (int y = 0; y < 90; y++) {
		for (int x = -2; x < 3; x++) {
			for (int z = -2; z < 3; z++) {
				if (abs(x) + abs(z) == 4)
					continue;
				locateBlock((abs(x) != 2 && abs(z) != 2) ? tntBlock : goldBlock, centerX + x, centerY + y, centerZ + z);
			}
		}
		const int depth = 10 + abs(10 * cos(degToRad(degs)));
		for (float circleDeg = 0; circleDeg < 360; circleDeg += 1.0) {
			locateBlock(isGlass ? glassBlock : ironBlock, centerX + sin(circleDeg) * depth, centerY + y, centerZ + cos(circleDeg) * depth);
			if (depth < 13) {
				const int diamondDepth = depth + 10;
				locateBlock(isGlass ? glassBlock : diamondBlock, centerX + sin(circleDeg) * diamondDepth, centerY + y, centerZ + cos(circleDeg) * diamondDepth);
			}
		}
		degs += 2;
		isGlass = !isGlass;
	}
	for (float circleDeg = 0; circleDeg < 360; circleDeg += 1.0) {
		int maxX = sin(circleDeg) * 20;
		int maxZ = cos(circleDeg) * 20;
		for (int x = 0; maxX > 0 ? x < maxX : x > maxX; maxX > 0 ? x++ : x--)
			for (int z = 0; maxZ > 0 ? z < maxZ : z > maxZ; maxZ > 0 ? z++ : z--)
				locateBlock(emeraldBlock, centerX + x, centerY + 90, centerZ + z);
	}
}