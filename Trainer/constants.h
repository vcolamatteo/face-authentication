#ifndef CONSTANTS_H
#define CONSTANTS_H

// Debugging
const bool kPlotVectorField = false;

// Size constants
//const int kEyePercentTop = 25;
const int kEyePercentTop = 25;
//const int kEyePercentSide = 13;
const int kEyePercentSide = 22;
//const int kEyePercentHeight = 30;
//const int kEyePercentHeight = 25;
const int kEyePercentHeight = 15;
//const int kEyePercentWidth = 35;
const int kEyePercentWidth = 20;

// Preprocessing
const bool kSmoothFaceImage = true;
const float kSmoothFaceFactor = 0.005;

// Algorithm Parameters
const int kFastEyeWidth = 30;
const int kWeightBlurSize = 5;
const bool kEnableWeight = true;
const float kWeightDivisor = 1.0;
const double kGradientThreshold = 5.0;

// Postprocessing
const bool kEnablePostProcess = false;
const float kPostProcessThreshold = 0.99;

// Eye Corner
const bool kEnableEyeCorner = false;

#endif
