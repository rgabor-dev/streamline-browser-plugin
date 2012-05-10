#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "StreamlineAnnotation.h"
#include "streamline_annotate.h"

#ifndef H_StreamlineAnnotationAPI
#define H_StreamlineAnnotationAPI

class StreamlineAnnotationAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn StreamlineAnnotationAPI::StreamlineAnnotationAPI(const StreamlineAnnotationPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    StreamlineAnnotationAPI(const StreamlineAnnotationPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
	ANNOTATE_SETUP;
        registerMethod("startAnnotate", make_method(this, &StreamlineAnnotationAPI::startAnnotate));
	registerMethod("startColorizedAnnotate", make_method(this, &StreamlineAnnotationAPI::startColorizedAnnotate));
	registerMethod("stopAnnotate", make_method(this, &StreamlineAnnotationAPI::stopAnnotate));
        
        // Read-only property
        registerProperty("version",
                         make_property(this,
                                       &StreamlineAnnotationAPI::get_version));
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn StreamlineAnnotationAPI::~StreamlineAnnotationAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~StreamlineAnnotationAPI() {};

    StreamlineAnnotationPtr getPlugin();

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method annotate
    void startAnnotate(const std::string& text);
    void startColorizedAnnotate(const std::string& color, const std::string& text);
    void stopAnnotate();

private:
    
    StreamlineAnnotationWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

#endif // H_StreamlineAnnotationAPI

