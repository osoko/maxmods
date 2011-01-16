/***********************************************************************
	filename: 	CEGUIPropertyHelper.h
	created:	21/11/2010
	author:		Martin Preisler (reworked from code by Paul D Turner)
	
	purpose:	Interface to the PropertyHelper class
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2006 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#ifndef _CEGUIPropertyHelper_h_
#define _CEGUIPropertyHelper_h_

#include "CEGUIString.h"
#include "CEGUISize.h"
#include "CEGUIVector.h"
#include "CEGUIQuaternion.h"
#include "CEGUIColour.h"
#include "CEGUIColourRect.h"
#include "CEGUIUDim.h"

#include <cstdio>

#include <sstream>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

// Start of CEGUI namespace section
namespace CEGUI
{
/*!
\brief
	Helper class used to convert various data types to and from the format expected in Propery strings

\par
    Usage:

    float value = PropertyHelper<float>::fromString("0.1");
    String value = PropertyHelper<float>::toString(0.1);
*/
template<typename T>
class PropertyHelper;

// this redirects PropertyHelper<const T> to PropertyHelper<T>
template<typename T>
class PropertyHelper<const T>
{
public:
    typedef typename PropertyHelper<T>::return_type return_type;
    typedef typename PropertyHelper<T>::pass_type pass_type;
    typedef typename PropertyHelper<T>::string_return_type string_return_type;

    static inline const String& getDataTypeName()
    {
        return PropertyHelper<T>::getDataTypeName();
    }

    static inline return_type fromString(const String& str)
    {
        return PropertyHelper<T>::fromString(str);
    }

    static inline String toString(pass_type val)
    {
        return PropertyHelper<T>::toString(val);
    }
};

// this redirects PropertyHelper<const T&> to PropertyHelper<T>
template<typename T>
class PropertyHelper<const T&>
{
public:
    typedef typename PropertyHelper<T>::return_type return_type;
    typedef typename PropertyHelper<T>::pass_type pass_type;
    typedef typename PropertyHelper<T>::string_return_type string_return_type;

    static inline const String& getDataTypeName()
    {
        return PropertyHelper<T>::getDataTypeName();
    }

    static inline return_type fromString(const String& str)
    {
        return PropertyHelper<T>::fromString(str);
    }

    static inline String toString(pass_type val)
    {
        return PropertyHelper<T>::toString(val);
    }
};

// this redirects PropertyHelper<const T*> to PropertyHelper<T*>
template<typename T>
class PropertyHelper<const T*>
{
public:
    typedef typename PropertyHelper<T*>::return_type return_type;
    typedef typename PropertyHelper<T*>::pass_type pass_type;
    typedef typename PropertyHelper<T*>::string_return_type string_return_type;

    static inline const String& getDataTypeName()
    {
        return PropertyHelper<T>::getDataTypeName();
    }

    static inline return_type fromString(const String& str)
    {
        return PropertyHelper<T*>::fromString(str);
    }

    static inline String toString(pass_type val)
    {
        return PropertyHelper<T*>::toString(val);
    }
};

template<>
class PropertyHelper<String>
{
public:
    typedef const String& return_type;
    typedef const String& pass_type;
    typedef const String& string_return_type;

    static const String& getDataTypeName()
    {
        static String type("String");

        return type;
    }

    static inline return_type fromString(const String& str)
    {
        return str;
    }

    static inline string_return_type toString(pass_type val)
    {
        return val;
    }
};

template<>
class PropertyHelper<float>
{
public:
    typedef float return_type;
    typedef const float pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("float");

        return type;
    }

    static inline return_type fromString(const String& str)
    {
        float val = 0;
        sscanf(str.c_str(), " %g", &val);
        
        return val;
    }

    static inline string_return_type toString(pass_type val)
    {
        char buff[64];
        snprintf(buff, sizeof(buff), "%g", val);

        return String(buff);
    }
};

template<>
class PropertyHelper<int>
{
public:
    typedef int return_type;
    typedef const int pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("int");

        return type;
    }

    static inline return_type fromString(const String& str)
    {
        int val = 0;
        sscanf(str.c_str(), " %d", &val);

        return val;
    }

    static inline string_return_type toString(pass_type val)
    {
        char buff[64];
        snprintf(buff, sizeof(buff), "%d", val);

        return String(buff);
    }
};

template<>
class PropertyHelper<uint>
{
public:
    typedef uint return_type;
    typedef const uint pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("uint");

        return type;
    }

    static return_type fromString(const String& str)
    {
        uint val = 0;
        sscanf(str.c_str(), " %u", &val);

        return val;
    }

    static string_return_type toString(pass_type val)
    {
        char buff[64];
        snprintf(buff, sizeof(buff), "%u", val);

        return String(buff);
    }
};

template<>
class PropertyHelper<bool>
{
public:
    typedef bool return_type;
    typedef const bool pass_type;
    typedef const String& string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("bool");

        return type;
    }

    static return_type fromString(const String& str)
    {
        return (str == "True" || str == "true");
    }

    static string_return_type toString(pass_type val)
    {
        // yeah I am that awesome ;-D
        
        static String True("True");
        static String False("False");
        
        return val ? True : False;
    }
};

template<>
class PropertyHelper<Size>
{
public:
    typedef Size return_type;
    typedef const Size& pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("Size");

        return type;
    }

    static return_type fromString(const String& str)
    {
        Size val(0, 0);
        sscanf(str.c_str(), " w:%g h:%g", &val.d_width, &val.d_height);

        return val;
    }

    static string_return_type toString(pass_type val)
    {
        char buff[128];
        snprintf(buff, sizeof(buff), "w:%g h:%g", val.d_width, val.d_height);

        return String(buff);
    }
};

template<>
class PropertyHelper<Vector2>
{
public:
    typedef Vector2 return_type;
    typedef const Vector2& pass_type;
    typedef String string_return_type;

    static const String& getDataTypeName()
    {
        static String type("Vector2");

        return type;
    }

    static return_type fromString(const String& str)
    {
        Vector2 val(0, 0) ;
        sscanf(str.c_str(), " x:%g y:%g", &val.d_x, &val.d_y);

        return val;
    }

    static string_return_type toString(pass_type val)
    {
        char buff[128];
        snprintf(buff, sizeof(buff), "x:%g y:%g", val.d_x, val.d_y);

        return String(buff);
    }
};

template<>
class PropertyHelper<Vector3>
{
public:
    typedef Vector3 return_type;
    typedef const Vector3& pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("Vector3");

        return type;
    }

    static return_type fromString(const String& str)
    {
        Vector3 val(0, 0, 0);
        sscanf(str.c_str(), " x:%g y:%g z:%g", &val.d_x, &val.d_y, &val.d_z);

        return val;
    }

    static string_return_type toString(pass_type val)
    {
        char buff[128];
        snprintf(buff, sizeof(buff), "x:%g y:%g z:%g", val.d_x, val.d_y, val.d_z);

        return String(buff);
    }
};

template<>
class PropertyHelper<Quaternion>
{
public:
    typedef Quaternion return_type;
    typedef const Quaternion& pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("Quaternion");

        return type;
    }

    static return_type fromString(const String& str)
    {
        Quaternion val(1, 0, 0, 0);
        sscanf(str.c_str(), " w:&g x:%g y:%g z:%g", &val.d_w, &val.d_x, &val.d_y, &val.d_z);

        return val;
    }

    static string_return_type toString(pass_type val)
    {
        char buff[128];
        snprintf(buff, sizeof(buff), "w:&g x:%g y:%g z:%g", val.d_w, val.d_x, val.d_y, val.d_z);

        return String(buff);
    }
};

template<>
class PropertyHelper<Rect>
{
public:
    typedef Rect return_type;
    typedef const Rect& pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("Rect");

        return type;
    }

    static return_type fromString(const String& str)
    {
        Rect val(0, 0, 0, 0);
        sscanf(str.c_str(), " l:%g t:%g r:%g b:%g", &val.d_left, &val.d_top, &val.d_right, &val.d_bottom);

        return val;
    }

    static string_return_type toString(pass_type val)
    {
        char buff[256];
        snprintf(buff, sizeof(buff), "l:%g t:%g r:%g b:%g",
                 val.d_left, val.d_top, val.d_right, val.d_bottom);

        return String(buff);
    }
};

template<>
class CEGUIEXPORT PropertyHelper<Image*>
{
public:
    typedef const Image* return_type;
    typedef const Image* const pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("Image*");

        return type;
    }

    static return_type fromString(const String& str);

    static string_return_type toString(pass_type val);
};

template<>
class PropertyHelper<Colour>
{
public:
    typedef Colour return_type;
    typedef const Colour& pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("Colour");

        return type;
    }

    static return_type fromString(const String& str)
    {
        argb_t val = 0xFF000000;
        sscanf(str.c_str(), " %8X", &val);

        return Colour(val);
    }

    static string_return_type toString(pass_type val)
    {
        char buff[16];
        sprintf(buff, "%.8X", val.getARGB());

        return String(buff);
    }
};

template<>
class PropertyHelper<ColourRect>
{
public:
    typedef ColourRect return_type;
    typedef const ColourRect& pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("ColourRect");

        return type;
    }

    static return_type fromString(const String& str)
    {
        if (str.length() == 8)
        {
            argb_t all = 0xFF000000;
            sscanf(str.c_str(), "%8X", &all);
            return ColourRect(all);
        }

        argb_t topLeft = 0xFF000000, topRight = 0xFF000000, bottomLeft = 0xFF000000, bottomRight = 0xFF000000;
        sscanf(str.c_str(), "tl:%8X tr:%8X bl:%8X br:%8X", &topLeft, &topRight, &bottomLeft, &bottomRight);

        return ColourRect(topLeft, topRight, bottomLeft, bottomRight);
    }

    static string_return_type toString(pass_type val)
    {
        char buff[64];
        sprintf(buff, "tl:%.8X tr:%.8X bl:%.8X br:%.8X", val.d_top_left.getARGB(), val.d_top_right.getARGB(), val.d_bottom_left.getARGB(), val.d_bottom_right.getARGB());

        return String(buff);
    }
};

template<>
class PropertyHelper<UDim>
{
public:
    typedef UDim return_type;
    typedef const UDim& pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("UDim");

        return type;
    }

    static return_type fromString(const String& str)
    {
        UDim ud;
        sscanf(str.c_str(), " { %g , %g }", &ud.d_scale, &ud.d_offset);

        return ud;
    }

    static string_return_type toString(pass_type val)
    {
        char buff[128];
        snprintf(buff, sizeof(buff), "{%g,%g}", val.d_scale, val.d_offset);

        return String(buff);
    }
};

template<>
class PropertyHelper<UVector2>
{
public:
    typedef UVector2 return_type;
    typedef const UVector2& pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("UVector2");

        return type;
    }

    static return_type fromString(const String& str)
    {
        UVector2 uv;
        sscanf(str.c_str(), " { { %g , %g } , { %g , %g } }",
               &uv.d_x.d_scale, &uv.d_x.d_offset,
               &uv.d_y.d_scale, &uv.d_y.d_offset);

        return uv;
    }

    static string_return_type toString(pass_type val)
    {
        char buff[256];
        snprintf(buff, sizeof(buff), "{{%g,%g},{%g,%g}}",
                 val.d_x.d_scale, val.d_x.d_offset, val.d_y.d_scale, val.d_y.d_offset);

        return String(buff);
    }
};

template<>
class PropertyHelper<URect>
{
public:
    typedef URect return_type;
    typedef const URect& pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("URect");

        return type;
    }

    static return_type fromString(const String& str)
    {
        URect ur;
        sscanf(
            str.c_str(),
            " { { %g , %g } , { %g , %g } , { %g , %g } , { %g , %g } }",
            &ur.d_min.d_x.d_scale, &ur.d_min.d_x.d_offset,
            &ur.d_min.d_y.d_scale, &ur.d_min.d_y.d_offset,
            &ur.d_max.d_x.d_scale, &ur.d_max.d_x.d_offset,
            &ur.d_max.d_y.d_scale, &ur.d_max.d_y.d_offset
        );

        return ur;
    }

    static string_return_type toString(pass_type val)
    {
        char buff[512];
        snprintf(buff, sizeof(buff), "{{%g,%g},{%g,%g},{%g,%g},{%g,%g}}",
                 val.d_min.d_x.d_scale, val.d_min.d_x.d_offset,
                 val.d_min.d_y.d_scale, val.d_min.d_y.d_offset,
                 val.d_max.d_x.d_scale, val.d_max.d_x.d_offset,
                 val.d_max.d_y.d_scale, val.d_max.d_y.d_offset);

        return String(buff);
    }
};

template<>
class PropertyHelper<UBox>
{
public:
    typedef UBox return_type;
    typedef const UBox& pass_type;
    typedef String string_return_type;
    
    static const String& getDataTypeName()
    {
        static String type("UBox");

        return type;
    }

    static return_type fromString(const String& str)
    {
        UBox ret;
        sscanf(
            str.c_str(),
            " { top: { %g , %g } , left: { %g , %g } , bottom: { %g , %g } , right: { %g , %g } }",
            &ret.d_top.d_scale, &ret.d_top.d_offset,
            &ret.d_left.d_scale, &ret.d_left.d_offset,
            &ret.d_bottom.d_scale, &ret.d_bottom.d_offset,
            &ret.d_right.d_scale, &ret.d_right.d_offset
        );

        return ret;
    }

    static string_return_type toString(pass_type val)
    {
        char buff[512];
        snprintf(buff, sizeof(buff), "{top:{%g,%g},left:{%g,%g},bottom:{%g,%g},right:{%g,%g}}",
                 val.d_top.d_scale, val.d_top.d_offset,
                 val.d_left.d_scale, val.d_left.d_offset,
                 val.d_bottom.d_scale, val.d_bottom.d_offset,
                 val.d_right.d_scale, val.d_right.d_offset);

        return String(buff);
    }
};

} // End of  CEGUI namespace section

#endif	// end of guard _CEGUIPropertyHelper_h_
