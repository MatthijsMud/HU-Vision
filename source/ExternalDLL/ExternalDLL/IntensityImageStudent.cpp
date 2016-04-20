#include "IntensityImageStudent.h"

IntensityImageStudent::IntensityImageStudent() 
	: IntensityImage() 
	, imageData{0}
{
}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) 
	: IntensityImage(other.getWidth(), other.getHeight()) 
	, imageData{other.imageData}
{
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) 
	: IntensityImage(width, height) 
	, imageData{(width * height)}
{
}

IntensityImageStudent::~IntensityImageStudent() 
{
	// Vector clears its data when it goes out of scope.
}

void IntensityImageStudent::set(const int width, const int height) 
{
	IntensityImage::set(width, height);
	imageData.resize(width * height);

	// TODO: rearrange certain elements so the original image is maintained; possibly cropped.
}

void IntensityImageStudent::set(const IntensityImageStudent &other) 
{
	IntensityImage::set(other.getWidth(), other.getHeight());
	imageData = other.imageData;
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) 
{
	setPixel(x + (y * getWidth()), pixel);
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) 
{
	imageData[i] = pixel;
}

Intensity IntensityImageStudent::getPixel(int x, int y) const 
{
	return getPixel(x + (y * getWidth()));
}

Intensity IntensityImageStudent::getPixel(int i) const 
{
	return imageData[i];
}