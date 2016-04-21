#include "StudentPreProcessing.h"
#include "ImageFactory.h"
#include <algorithm>
#include <iostream>
#include <limits>

inline const IntensityChannel operator|(const IntensityChannel & lhs, const IntensityChannel & rhs)
{
	return static_cast<IntensityChannel>(static_cast<long long>(lhs) | static_cast<long long>(rhs));
}

inline const IntensityChannel operator&(const IntensityChannel & lhs, const IntensityChannel & rhs)
{
	return static_cast<IntensityChannel>(static_cast<long long>(lhs) & static_cast<long long>(rhs));
}

inline const IntensityChannel operator~(const IntensityChannel & lhs)
{
	return static_cast<IntensityChannel>(~static_cast<long long>(lhs));
}

inline IntensityChannel & operator|=(IntensityChannel & lhs, const IntensityChannel & rhs)
{
	return (lhs = (lhs | rhs));
}

inline IntensityChannel & operator&=(IntensityChannel & lhs, const IntensityChannel & rhs)
{
	return (lhs = (lhs & rhs));
}


void StudentPreProcessing::rgbToCmyk(const unsigned char & r, const unsigned char & g, const unsigned char & b, float & c, float & m, float & y, float & k ) const
{
	auto rA = r / 255.0f;
	auto gA = g / 255.0f;
	auto bA = b / 255.0f;
	k = (1 - std::max(rA, std::max(gA, bA)));
	c = (1 - rA - k) / (1 - k);
	m = (1 - gA - k) / (1 - k);
	y = (1 - bA - k) / (1 - k);
}

void StudentPreProcessing::rgbToHsv(const unsigned char & r, const unsigned char & g, const unsigned char & b, float & h, float & s, float & v) const
{
	const auto rA = r / 255.0f;
	const auto gA = g / 255.0f;
	const auto bA = b / 255.0f;

	const auto cMax = std::max(rA, std::max(gA, bA));
	const auto cMin = std::min(rA, std::min(gA, bA));
	const auto delta = cMax - cMin;
	v = cMax;
	if (cMax > std::numeric_limits<float>::epsilon())
	{
		s = delta / cMax;
		if (rA == cMax)
		{
			h = ((gA - bA)/delta);
		}
		else if (gA == cMax)
		{
			h = (2 + ((bA - rA)/delta));
		}
		else
		{
			h = (4 + ((rA - gA)/delta));
		}
		h *= 60;
		if (h < 0)
		{
			h += 360;
		}
	}
	else
	{
		s = 0;
		h = 0;
	}
}

Intensity StudentPreProcessing::getPixelIntensity(const RGB & pixel) const
{
	const IntensityChannel channelz[] =
	{
		IntensityChannel::Red,
		IntensityChannel::Green,
		IntensityChannel::Blue,

		IntensityChannel::Cyan,
		IntensityChannel::Magenta,
		IntensityChannel::Yellow,
		IntensityChannel::Black,

		IntensityChannel::Hue,
		IntensityChannel::Saturation,
		IntensityChannel::Value,
	};
	int total = 0;
	int nChannels = 0;

	float c, m, y, k;
	float h, s, v;

	rgbToCmyk(pixel.r, pixel.g, pixel.b, c, m, y, k);
	rgbToHsv(pixel.r, pixel.g, pixel.b, h, s, v);

	for (const auto & channel : channelz)
	{
		switch (channel & channels)
		{
		case IntensityChannel::Red: total += pixel.r; break;
		case IntensityChannel::Green: total += pixel.g; break;
		case IntensityChannel::Blue: total += pixel.b; break;

		case IntensityChannel::Cyan: total += static_cast<int>(c * 255); break;
		case IntensityChannel::Magenta: total += static_cast<int>(m * 255); break;
		case IntensityChannel::Yellow: total += static_cast<int>(y * 255); break;
		case IntensityChannel::Black: total += static_cast<int>(k * 255); break;

		case IntensityChannel::Hue: total += static_cast<int>((h / 360.0f) * 255);break;
		case IntensityChannel::Saturation: total += static_cast<int>(s * 255); break;
		case IntensityChannel::Value: total += static_cast<int>(v * 255); break;
		default:
			continue;
		}
		++nChannels;
	}
	if (nChannels)
	{
		return static_cast<Intensity>(total / nChannels);
	}
	//std::cerr << "No channels were specified." << std::endl;
	return static_cast<Intensity>(0);
}

void StudentPreProcessing::setChannel(const IntensityChannel & channel)
{
	channels |= channel;
	std::cout << "Channels: [" << (int)(channels) << ']' << std::endl;
}

void StudentPreProcessing::unsetChannel(const IntensityChannel & channel)
{
	channels &= ~channel;
	std::cout << "Channels: [" << (int)(channel & channels) << ']' << std::endl;
}

StudentPreProcessing::StudentPreProcessing()
	: channels{IntensityChannel::None}
{
}



IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const
{
	const int width = image.getWidth();
	const int height = image.getHeight();
	auto & output = *ImageFactory::newIntensityImage(width, height);

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			RGB rgb = image.getPixel(x, y);
			output.setPixel(x, y, getPixelIntensity(rgb));
		}
	}

	return &output;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}