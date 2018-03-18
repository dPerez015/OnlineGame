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

	friend bool operator==(intergerPosition const& lhs, intergerPosition const& rhs) {
		if (lhs.x == rhs.x && lhs.y == rhs.y) {
			return true;
		}
		return false;
	}
	int x, y;
};