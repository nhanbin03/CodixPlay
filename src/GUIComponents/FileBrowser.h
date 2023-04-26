#ifndef GUICOMPONENTS_FILEBROWSER_H
#define GUICOMPONENTS_FILEBROWSER_H

#include "Button.h"
#include "GUIComponent.h"

#include "raylib.h"
#include "tinyfiledialogs.h"

#include <functional>
#include <memory>
#include <string>

class FileBrowser : public GUIComponent {
public:
    typedef std::shared_ptr<FileBrowser> Ptr;

public:
    explicit FileBrowser(Rectangle bounds = {0, 0, 0, 0});
    ~FileBrowser();

    void reset();

    void update(float dt);
    void draw();

    void setBorderThickness(int thickness);

    void setCornerRoundness(float cornerRoundness);

    void setButtonColor(Color color);
    void setButtonContentColor(Color color);
    void setButtonBorderColor(Color color);

    std::string getInputPath() const;

private:
    std::string mInputPath;
    Color mTextColor{BLACK};

    float mCornerRoundness{0.5};

    Button mBrowseButton;
};

#endif // GUICOMPONENTS_FILEBROWSER_H
