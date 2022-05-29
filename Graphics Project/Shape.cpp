#include "Shape.h"

Shape::Shape(ShapeData* shapeData, ShapeDrawer* shapeDrawer) {
	this->shapeData = shapeData;
	this->shapeDrawer = shapeDrawer;
}

void Shape::draw() {
	shapeDrawer->draw(shapeData);
}

Shape::~Shape() {
	delete this->shapeData;
	delete this->shapeDrawer;
}