#include "TextureHolder.h"

#include <cassert>

TextureHolder::TextureHolder() {
    mResourceMap[TextureID::None] = std::make_unique<Texture2D>();
}

void TextureHolder::load(TextureID id, const std::string& filename) {
    std::unique_ptr<Texture2D> resource(new Texture());
    *resource = LoadTexture(filename.c_str());
    insertResource(id, std::move(resource));
}

Texture2D& TextureHolder::get(TextureID id) {
    auto found = mResourceMap.find(id);
    if (found == mResourceMap.end()) {
        return *mResourceMap[TextureID::None];
    }
    return *found->second;
}

const Texture2D& TextureHolder::get(TextureID id) const {
    auto found = mResourceMap.find(id);
    if (found == mResourceMap.end()) {
        return *mResourceMap.at(TextureID::None);
    }
    return *found->second;
}

void TextureHolder::insertResource(TextureID id,
                                   std::unique_ptr<Texture2D> resource) {
    auto insertStatus = mResourceMap.emplace(id, std::move(resource));
    assert(insertStatus.second == true);
}
