#pragma once
struct intergerPosition {
	intergerPosition() {
		x = 0;
		y = 0;
	}
	intergerPosition(int v, int u) {
		x = v;
		y = u;
	}
	int x, y;
};