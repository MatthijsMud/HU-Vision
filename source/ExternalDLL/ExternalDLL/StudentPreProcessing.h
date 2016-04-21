/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once
#include "PreProcessing.h"

//! @brief image's channel to base its intensity on.
enum class IntensityChannel
{
	None       = (0),

	Red        = (1<<0x0),
	Green      = (1<<0x1),
	Blue       = (1<<0x2),

	Cyan       = (1<<0x3),
	Magenta    = (1<<0x4),
	Yellow     = (1<<0x5),
	Black      = (1<<0x6),
	
	Hue        = (1<<0x7),
	Saturation = (1<<0x8),
	Value      = (1<<0x9),
};

const IntensityChannel operator|(const IntensityChannel & lhs, const IntensityChannel & rhs);
const IntensityChannel operator&(const IntensityChannel & lhs, const IntensityChannel & rhs);
const IntensityChannel operator~(const IntensityChannel & lhs);

IntensityChannel & operator|=(IntensityChannel & lhs, const IntensityChannel & rhs);
IntensityChannel & operator&=(IntensityChannel & lhs, const IntensityChannel & rhs);

class StudentPreProcessing : public PreProcessing 
{
	

private:
	IntensityChannel channels;
	void rgbToCmyk
		(
			const unsigned char & r,
			const unsigned char & g,
			const unsigned char & b,

			float & c,
			float & m,
			float & y,
			float & k
			) const;
	void rgbToHsv
		(
			const unsigned char & r,
			const unsigned char & g,
			const unsigned char & b,

			float & h,
			float & s,
			float & v
			) const;
	Intensity getPixelIntensity(const RGB & pixel) const;
public:
	void setChannel(const IntensityChannel & channel);
	void unsetChannel(const IntensityChannel & channel);
	StudentPreProcessing();

	IntensityImage * stepToIntensityImage(const RGBImage &image) const;
	IntensityImage * stepScaleImage(const IntensityImage &image) const;
	IntensityImage * stepEdgeDetection(const IntensityImage &image) const;
	IntensityImage * stepThresholding(const IntensityImage &image) const;
};