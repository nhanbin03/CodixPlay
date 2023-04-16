#ifndef RESOURCEHOLDERS_FONTHOLDER_H
#define RESOURCEHOLDERS_FONTHOLDER_H

#include "ResourceIdentifiers.h"

#include "raylib.h"

#include <map>
#include <memory>
#include <string>

// Singelton
class FontHolder {
public:
    static const int MAX_SIZE = 60;
    static const int ROUNDING = 3; // Save loading time

public:
    static FontHolder& getInstance();

    void load(FontID id, const std::string& filename);

    Font& get(FontID id, int size);
    const Font& get(FontID id, int size) const;

private:
    FontHolder();
    FontHolder(FontHolder const&) = delete;
    void operator= (FontHolder const&) = delete;
    ~FontHolder();

    std::map<FontID, std::unique_ptr<Font>> mResourceMap[MAX_SIZE + 1];

private:
    void insertResource(int size, FontID id, std::unique_ptr<Font> resource);
};

#endif // RESOURCEHOLDERS_FONTHOLDER_H
