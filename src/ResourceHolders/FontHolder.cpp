#include "FontHolder.h"

#include <cassert>
#include <iostream>

FontHolder::FontHolder() {
    mResourceMap[FontID::None] = std::make_unique<Font>();
}

FontHolder::~FontHolder() {
    for (auto& p : mResourceMap) {
        UnloadFont(*p.second);
    }
}

FontHolder& FontHolder::getInstance() {
    static FontHolder instance;
    return instance;
}

void FontHolder::load(FontID id, const std::string& filename) {
    std::unique_ptr<Font> resource(new Font());
    *resource = LoadFont(filename.c_str());
    insertResource(id, std::move(resource));
}

Font& FontHolder::get(FontID id) {
    auto found = mResourceMap.find(id);
    if (found == mResourceMap.end()) {
        return *mResourceMap[FontID::None];
    }
    return *found->second;
}

const Font& FontHolder::get(FontID id) const {
    auto found = mResourceMap.find(id);
    if (found == mResourceMap.end()) {
        return *mResourceMap.at(FontID::None);
    }
    return *found->second;
}

void FontHolder::insertResource(FontID id, std::unique_ptr<Font> resource) {
    auto insertStatus = mResourceMap.emplace(id, std::move(resource));
    assert(insertStatus.second == true);
}
