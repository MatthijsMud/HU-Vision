#include "RGBImageStudent.h"

RGBImageStudent::RGBImageStudent() 
	: RGBImage()
	, imageData{0} 
{
}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) 
	: RGBImage(other.getWidth(), other.getHeight())
	, imageData{other.imageData} 
{
}


RGBImageStudent::RGBImageStudent(const int width, const int height) 
	: RGBImage(width, height)
	, imageData{width * height} 
{
}

RGBImageStudent::~RGBImageStudent() 
{
}

void RGBImageStudent::set(const int width, const int height) 
{
	RGBImage::set(width, height);
	imageData.resize(width * height);

	// TODO: rearrange certain elements so the original image is maintained; possibly cropped.
}

void RGBImageStudent::set(const RGBImageStudent &other) 
{
	RGBImage::set(other.getWidth(), other.getHeight());
	imageData = other.imageData;
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) 
{
	setPixel(x + (y * getWidth()), pixel);
}

void RGBImageStudent::setPixel(int i, RGB pixel) 
{
	if (static_cast<unsigned int>(i) < imageData.size())
	{
		imageData[i] = pixel;
	}
}

RGB RGBImageStudent::getPixel(int x, int y) const 
{
	return getPixel(x + (y * getWidth()));
}

RGB RGBImageStudent::getPixel(int i) const 
{
	return (static_cast<unsigned int>(i) < imageData.size())
		? imageData[i]
		: RGB(0, 0, 0);
}