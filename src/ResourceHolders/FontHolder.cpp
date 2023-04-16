#include "FontHolder.h"

#include <cassert>
#include <iostream>

FontHolder::FontHolder() {
    for (int i = ROUNDING; i <= MAX_SIZE; i += ROUNDING)
        mResourceMap[i][FontID::None] = std::make_unique<Font>();
}

FontHolder::~FontHolder() {
    for (int i = ROUNDING; i <= MAX_SIZE; i += ROUNDING)
        for (auto& p : mResourceMap[i]) {
            UnloadFont(*p.second);
        }
}

FontHolder& FontHolder::getInstance() {
    static FontHolder instance;
    return instance;
}

void FontHolder::load(FontID id, const std::string& filename) {
    for (int i = ROUNDING; i <= MAX_SIZE; i += ROUNDING) {
        std::unique_ptr<Font> resource(new Font());
        *resource = LoadFontEx(filename.c_str(), i, NULL, 0);
        insertResource(i, id, std::move(resource));
    }
}

Font& FontHolder::get(FontID id, int size) {
    if (size > MAX_SIZE)
        size = MAX_SIZE;
    size = (size - 1) / ROUNDING * ROUNDING
         + ROUNDING; // Round to upper multiple of ROUNDING
    if (size > MAX_SIZE)
        size -= ROUNDING;

    auto found = mResourceMap[size].find(id);
    if (found == mResourceMap[size].end()) {
        return *mResourceMap[size][FontID::None];
    }
    SetTextureFilter(found->second->texture, TEXTURE_FILTER_BILINEAR);
    return *found->second;
}

const Font& FontHolder::get(FontID id, int size) const {
    if (size > MAX_SIZE)
        size = MAX_SIZE;
    size = (size - 1) / ROUNDING * ROUNDING
         + ROUNDING; // Round to upper multiple of ROUNDING
    if (size > MAX_SIZE)
        size -= ROUNDING;

    auto found = mResourceMap[size].find(id);
    if (found == mResourceMap[size].end()) {
        return *mResourceMap[size].at(FontID::None);
    }
    SetTextureFilter(found->second->texture, TEXTURE_FILTER_BILINEAR);
    return *found->second;
}

void FontHolder::insertResource(int size, FontID id,
                                std::unique_ptr<Font> resource) {
    auto insertStatus = mResourceMap[size].emplace(id, std::move(resource));
    assert(insertStatus.second == true);
}
