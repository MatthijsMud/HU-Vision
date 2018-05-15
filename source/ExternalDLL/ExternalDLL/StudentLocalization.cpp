#include "StudentLocalization.h"
#define _USE_MATH_DEFINES
#include <math.h>


bool StudentLocalization::stepFindHead(const IntensityImage &image, FeatureMap &features) const {
	
	return false;
}

bool StudentLocalization::stepFindNoseMouthAndChin(const IntensityImage &image, FeatureMap &features) const {
	
	return false;
}

bool StudentLocalization::stepFindChinContours(const IntensityImage &image, FeatureMap &features) const {
	
	const Feature & mouthCenter = features.getFeature(Feature::FEATURE_MOUTH_CENTER);
	const Feature & chin = features.getFeature(Feature::FEATURE_CHIN);
	Feature & chinContour = features.getFeature(Feature::FEATURE_CHIN_CONTOUR);

	// The mouth could interfere with the localization of the chin contours.
	// Therefore use an offset based on which mouthcorner is the furthest away.
	// This however could still prove troublesome, so add a slight margin; 
	// represented by the 'magic' number. 
	const double radius = chin.getY() - mouthCenter.getY(); //+ std::fmax(\
		mouthRight.getX() - mouthCenter.getX(),\
		mouthCenter.getX() - mouthLeft.getX());

	// 180° matches half a circle.
	// 0° points to the east in goniometrics, where increasing angles are counter-clockwise.
	// Since the chin is usually on the bottompart of the image, the points either need to be
	// found clockwise (-180), or start looking at an offset.
	// 
	const int halfCircle = 180;
	const int angleStepSize = 10;
	// roughly 19 points need to be found.
	// 0 through 18 does just that.
	for (int i = 0; i <= halfCircle; i+=angleStepSize)
	{
		int angle = halfCircle + (i * angleStepSize);
		
		double xDir = std::cos(angle * M_PI / 180.0);
		double yDir = -std::sin(angle * M_PI / 180.0);
		mouthCenter.getX();
		mouthCenter.getY();
		const double increment = 1;

		for (double distance = radius * 0.7; distance < radius * 2; distance += increment)
		{
			double xCheck = mouthCenter.getX() + (xDir * distance);
			double yCheck = mouthCenter.getY() + (yDir * distance);
			const unsigned char treshhold = 32;
			if (image.getPixel(xCheck, yCheck) <= treshhold)
			{
				chinContour.addPoint(Point2D<double>(xCheck, yCheck));
				std::cout << "Found contour at: " << xCheck << "; " << yCheck << std::endl;
				break;
			}
		}
	}

	return chinContour.getPoints().size();
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	
	return false;
}