#include "textUtlis.h"

extern TFT_eSPI tft;

String truncateText(TextProps* props, int maxWidth){
    uint16_t x = 0;
    FontLoader fl(x, props);

    String ret = props->text;

    // Split the text into lines (if it has new lines)
    std::vector<String> lines;
    lines.reserve(4);
    int prev = 0;

    for (int i = 0; i < props->text.length(); i++){
        if (props->text.charAt(i) == '\n'){
            lines.push_back(props->text.substring(prev, i - 1));
            prev = i + 1;
        }
    }
    lines.push_back(props->text.substring(prev, props->text.length()));

    if (lines.size() == 1)
    {
        auto width = tft.textWidth(props->text);
        auto diff =  width - maxWidth;
        if (diff > 0){
            auto scale = (double)diff / (double)width;
            auto letters = ret.length()*scale;
            ret = ret.substring(0, ret.length() - letters - 2);
            ret += "...";
        }
    }
    
    // If that's multiline text, then we don't need to truncate it
    return ret;
}

String _textWrapper(TextProps* props, int maxWidth){
    String ret = props->text;
    auto width = tft.textWidth(props->text);
    auto diff =  width - maxWidth;
    if (diff > 0){
        auto scale = (double)diff / (double)width;
        auto letters = ret.length()*scale;
        ret = ret.substring(letters + 1, ret.length());
    } 
    return ret;
}

String textWrapper(TextProps* props, int maxWidth, bool fontLoaded){
    if (!fontLoaded){
        uint16_t x = 0;
        FontLoader fl(x, props);
        return _textWrapper(props, maxWidth);
    }  
    return _textWrapper(props, maxWidth);
}

String _textWrapperNewLine(TextProps* props, int startX, int offsetX){
    std::vector<String> ret;
    std::vector<String> tempLines;        

    int prev = 0;

    // Look for already new lines in text, and put them on vector
    for (int i = 0; i < props->text.length(); i++){
        if (props->text.charAt(i) == '\n'){
            ret.push_back(props->text.substring(prev, i - 1));
            prev = i + 1;
        }
    }    
    // Put last line on vector
    ret.push_back(props->text.substring(prev, props->text.length()));

    // Iterate through lines and check if they have proper text width
    for (int i = 0; i < ret.size(); i++){
        String 
            temp = "",
            sliced = ret.at(i);

        // If the line is too long, we need to slice it
        int endIndex = 0;
        int width = tft.textWidth(sliced);
        auto diff =  width - (320 - startX);
        
        // While the line is too long, we need to slice it
        while (diff > 0)
        {
            // Calculate the ratio of the max width to the current width (will be always less than 1)
            auto scale = (320 - offsetX) / (double)width;
            // get the valid number of letters
            endIndex = scale * sliced.length();

            if (sliced[endIndex] != ' ') {
                // If the endIndex is not a space, we need to find the last space
                // (we are trying to avoid cutting words)
                while (endIndex > 0 && sliced[endIndex] != ' '){
                    endIndex--;
                }

                // If we didn't find a space, we need to slice the text at the endIndex
                if (endIndex == 0) {
                    endIndex = scale * sliced.length();
                }
            }

            // push the sliced text to the vector
            temp = sliced.substring(0, endIndex);
            tempLines.push_back(temp);

            // remove the sliced text from the original string
            // and calculate the new width
            sliced = sliced.substring(endIndex, sliced.length());
            width -= tft.textWidth(temp);
            diff = width - (320 - offsetX);
        }

        // If the line is not too long, we can just push it to the vector
        tempLines.push_back(sliced.substring(0, sliced.length()));
    }

    // Return the wrapped text
    String wrapped;
    for (int i = 0; i < tempLines.size(); i++){
        if (i != 0){
            wrapped += "\n";
        }
        wrapped += tempLines[i];
    }
    return wrapped;
}

String textWrapToNewLine(TextProps* props, int startX, int offsetX, bool fontLoaded){
    if (!fontLoaded){
        uint16_t x = startX;
        FontLoader fl(x, props);
        return _textWrapperNewLine(props, startX, offsetX);
    }
    return _textWrapperNewLine(props, startX, offsetX);
}