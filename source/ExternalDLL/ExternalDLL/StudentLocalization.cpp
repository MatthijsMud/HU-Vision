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
	const double radius = chin.getY() - mouthCenter.getY();


	const double smallestOffsetRadiusFactor = 0.75;
	const double biggestOffsetRadiusFactor = 2;
	//

	// 180° matches half a circle.
	// 0° points to the east in goniometrics, where increasing angles are counter-clockwise.
	// Since the chin is usually on the bottompart of the image, the points either need to be
	// found clockwise (-180), or start looking at an offset.
	// 
	const int halfCircle = 180;
	const int angleStepSize = 10;
	// roughly 19 points need to be found.
	// 0 through 18 does just that.
	for (int i = 0; i <= halfCircle / angleStepSize; ++i)
	{
		// Determine the angle of the line among which we try to look for a point on the chin's contour.
		int angle = halfCircle + i * angleStepSize;
		
		// The size of a step in both the horizontal and verticical direction along the line with the current angle.
		double xDir = std::cos(angle * M_PI / 180.0);
		double yDir = -std::sin(angle * M_PI / 180.0);
		
		// Normalized size of a step that is made alongside the current angle.
		const double increment = 1;

		// Make multiple steps alongside the current angle within bounds where it is likely a contour for the chin.
		for (double distance = radius * smallestOffsetRadiusFactor; distance < radius * biggestOffsetRadiusFactor; distance += increment)
		{
			// Determine the location to check for a contour of the chin.
			double xCheck = mouthCenter.getX() + (xDir * distance);
			double yCheck = mouthCenter.getY() + (yDir * distance);
			// Image should be thresholded grayscale, where the pixels are eiher 0 or 255; check in the middle of it.
			const unsigned char treshhold = 128;
			if (image.getPixel(xCheck, yCheck) <= treshhold)
			{
				chinContour.addPoint(Point2D<double>(xCheck, yCheck));
				std::cout << "Found contour at: " << xCheck << "; " << yCheck << "\n";
				break;
			}
		}
	}

	return (chinContour.getPoints().size() > 0);
}

bool StudentLocalization::stepFindNoseEndsAndEyes(const IntensityImage &image, FeatureMap &features) const {
	
	return false;
}

bool StudentLocalization::stepFindExactEyes(const IntensityImage &image, FeatureMap &features) const {
	
	return false;
}