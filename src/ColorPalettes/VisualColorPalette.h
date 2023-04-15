#ifndef COLORPALETTES_VISUALCOLORPALETTE_H
#define COLORPALETTES_VISUALCOLORPALETTE_H

#include "raylib.h"

class VisualColor {
public:
    enum ColorID {
        Green,
        Yellow,
        Red,
        Blue
    };

public:
    static const int OPTIONS_SIZE = 4;
    static const Color OPTIONS[];

public:
    static Color getPrimaryColor();
    static Color getSecondaryColor();
    static Color getTertiaryColor();
    static Color getReferenceColor();

    static void setPrimaryColor(ColorID id);
    static void setSecondaryColorr(ColorID id);
    static void setTertiaryColor(ColorID id);
    static void setReferenceColor(ColorID id);

private:
    static Color mColors[OPTIONS_SIZE];

private:
    static void replaceColor(Color src, int index);
};

#endif // COLORPALETTES_VISUALCOLORPALETTE_H
