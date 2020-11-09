#include "renderer.h"

#include <simple2d.h>

S2D_Window* window;

// Parameter copy
Parameters parameters;
// Space copy
Space space({ 0,0 });

// cycle currently up to
int cycleCount = 0;

void copyEnvironment(const Space& external, const Parameters& externalParameters) {
	space = external;
	parameters = externalParameters;
}

void render() {
	for (auto& i : space.getBoids()) {
		Point2 position = i.getPosition();
		Point2 velocity = i.getVelocity();
		velocity.normalise();
		Point2 fOffset = (velocity * 10);
		Point2 lOffset = fOffset.rotate(-90);
		Point2 rOffset = fOffset.rotate(90);
		fOffset = fOffset + position;
		lOffset = lOffset * 0.5 + position;
		rOffset = rOffset * 0.5 + position;

		S2D_DrawTriangle(
			(float)fOffset.x, (float)fOffset.y, 1, 1, 1, 1,
			(float)lOffset.x, (float)lOffset.y, 1, 1, 1, 1,
			(float)rOffset.x, (float)rOffset.y, 1, 1, 1, 1
		);
	}
	
}

void update() {
	space.cycle(parameters, cycleCount);
	cycleCount++;

}

void setUpRenderer(const Space& space) {
	window = S2D_CreateWindow(
		"View", (int)space.getSize().x, (int)space.getSize().y, update, render, 0
	);
	S2D_Show(window);
}