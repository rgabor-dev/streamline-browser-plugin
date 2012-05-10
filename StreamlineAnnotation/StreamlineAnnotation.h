/**********************************************************\

  Auto-generated StreamlineAnnotation.h

  This file contains the auto-generated main plugin object
  implementation for the StreamlineAnnotation project

\**********************************************************/
#ifndef H_StreamlineAnnotationPLUGIN
#define H_StreamlineAnnotationPLUGIN

#include "PluginWindow.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/AttachedEvent.h"

#include "PluginCore.h"


FB_FORWARD_PTR(StreamlineAnnotation)
class StreamlineAnnotation : public FB::PluginCore
{
public:
    static void StaticInitialize();
    static void StaticDeinitialize();

public:
    StreamlineAnnotation();
    virtual ~StreamlineAnnotation();

public:
    void onPluginReady();
    void shutdown();
    virtual FB::JSAPIPtr createJSAPI();
    // If you want your plugin to always be windowless, set this to true
    // If you want your plugin to be optionally windowless based on the
    // value of the "windowless" param tag, remove this method or return
    // FB::PluginCore::isWindowless()
    virtual bool isWindowless() { return true; }

    BEGIN_PLUGIN_EVENT_MAP()
    END_PLUGIN_EVENT_MAP()

};


#endif

