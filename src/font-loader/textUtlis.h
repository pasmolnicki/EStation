#pragma once

#include "FontLoader.h"

/// @brief Wraps text from the begging to the maxWidth, adds '...' at the end if text width exceeds maxWidth
/// @param props 
/// @param maxWidth 
/// @return Truncated text
String truncateText(TextProps* props, int maxWidth);

/// @brief Wraps text from the end to the maxWidth
/// @param props 
/// @param maxWidth 
/// @return Wrapped text
String textWrapper(TextProps* props, int maxWidth, bool fontLoaded = false);

String textWrapToNewLine(TextProps* props, int startX, int offsetX, bool fontLoaded = false);