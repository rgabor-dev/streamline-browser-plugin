#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "StreamlineAnnotationAPI.h"

ANNOTATE_DEFINE;

///////////////////////////////////////////////////////////////////////////////
/// @fn StreamlineAnnotationPtr StreamlineAnnotationAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
StreamlineAnnotationPtr StreamlineAnnotationAPI::getPlugin()
{
    StreamlineAnnotationPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read-only property version
std::string StreamlineAnnotationAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

void StreamlineAnnotationAPI::startAnnotate(const std::string& text)
{
    ANNOTATE(const_cast<char*>(text.c_str()));
}

void StreamlineAnnotationAPI::startColorizedAnnotate(const std::string& color, const std::string& text)
{
    char* str = const_cast<char*>(text.c_str());
    int annotation_color = 0;

    if (color.compare("red") == 0 || color.compare("RED") == 0)
        annotation_color = ANNOTATE_RED;
    else if (color.compare("blue") == 0 || color.compare("BLUE") == 0)
        annotation_color = ANNOTATE_BLUE;
    else if (color.compare("green") == 0 || color.compare("GREEN") == 0)
        annotation_color = ANNOTATE_GREEN;
    else if (color.compare("purple") == 0 || color.compare("PURPLE") == 0)
        annotation_color = ANNOTATE_PURPLE;
    else if (color.compare("yellow") == 0 || color.compare("YELLOW") == 0)
        annotation_color = ANNOTATE_YELLOW;
    else if (color.compare("cyan") == 0 || color.compare("CYAN") == 0)
        annotation_color = ANNOTATE_CYAN;
    else if (color.compare("white") == 0 || color.compare("WHITE") == 0)
        annotation_color = ANNOTATE_WHITE;
    else if (color.compare("ltgray") == 0 || color.compare("LTGRAY") == 0)
        annotation_color = ANNOTATE_LTGRAY;
    else if (color.compare("dkgray") == 0 || color.compare("DKGRAY") == 0)
        annotation_color = ANNOTATE_DKGRAY;
    else if (color.compare("black") == 0 || color.compare("BLACK") == 0)
        annotation_color = ANNOTATE_BLACK;

    if (!annotation_color)
        ANNOTATE(str);
    else
        ANNOTATE_COLOR(annotation_color, str);
}

void StreamlineAnnotationAPI::stopAnnotate()
{
    ANNOTATE_END();
}
