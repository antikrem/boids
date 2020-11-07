#ifndef __RENDERER__
#define __RENDERER__

#include "space.h"


void setUpRenderer(const Space& space);

void copyEnvironment(const Space& external, const Parameters& externalParameters);

#endif