#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for StreamlineAnnotation
#
#\**********************************************************/

set(PLUGIN_NAME "StreamlineAnnotation")
set(PLUGIN_PREFIX "SAN")
set(COMPANY_NAME "UniversityofSzeged")

# ActiveX constants:
set(FBTYPELIB_NAME StreamlineAnnotationLib)
set(FBTYPELIB_DESC "StreamlineAnnotation 1.0 Type Library")
set(IFBControl_DESC "StreamlineAnnotation Control Interface")
set(FBControl_DESC "StreamlineAnnotation Control Class")
set(IFBComJavascriptObject_DESC "StreamlineAnnotation IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "StreamlineAnnotation ComJavascriptObject Class")
set(IFBComEventSource_DESC "StreamlineAnnotation IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID babc4b61-df7c-50b4-8381-7203e8f81c0c)
set(IFBControl_GUID 848b8979-d2b4-5ae2-a2d9-4a940b526a60)
set(FBControl_GUID b027f3cc-a0cc-5340-a871-66cee8b3ea5f)
set(IFBComJavascriptObject_GUID de245562-8c6d-57f0-b69f-a726808a4a89)
set(FBComJavascriptObject_GUID 4b3027dc-c7a1-5909-89e6-f266b20ef5c1)
set(IFBComEventSource_GUID 5d687294-b0f0-558f-b787-73fbd0948dc9)

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "UniversityofSzeged.StreamlineAnnotation")
set(MOZILLA_PLUGINID "u-szeged.hu/StreamlineAnnotation")

# strings
set(FBSTRING_CompanyName "University of Szeged")
set(FBSTRING_FileDescription "Plugin for annotate Streamline profile data")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2012 University of Szeged")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "StreamlineAnnotation")
set(FBSTRING_FileExtents "")
set(FBSTRING_PluginName "StreamlineAnnotation")
set(FBSTRING_MIMEType "application/x-streamlineannotation")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 0)
set(FBMAC_USE_COREGRAPHICS 0)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
