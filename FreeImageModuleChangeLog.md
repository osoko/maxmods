| **Version** | **Date** | **Comments** |
|:------------|:---------|:-------------|
| 1.05 | 29 Apr 2009 |  Fixed conversion issue with 4-bit paletted images. |
|  |  | Fixed GC problems when loading large anim images. |
|  |  | Fixed problem with creation of new multi-page images. |
| 1.04 | 20 Apr 2008 | Fixed problem with TIFF images not loading if there are more than 1 alpha channel in the image. (fredborg) |
|  |  | Added GetBitmap(), GetScanLine() and ConvertToRGBF() methods. (fredborg) |
|  |  | Added GetFormatFromFile(), GetLoadFormats() and GetSaveFormats() helper functions. (fredborg) |
|  |  | Win32 now compiles as a module, rather than using a DLL :-) |
| 1.03 | 22 Dec 2007 | Updated to FreeImage 3.10.0. Adds OpenEXR and OpenJPG(2000) formats. |
|  |  | Win32 now compiles as a module, rather than using a DLL :-) |
|  |  | Fixed colour problems when saving an image. |
|  |  | Fixed seek->end not seeking from the end. |
|  |  | Fixed multi-image bug where filename wasn't kept long enough. |
|  |  | Fixed TIFF save issue. (A freeimage bug, most likely) |
|  |  | Fixed win32 TIFF load issue. (Another freeimage bug, most likely) |
| 1.02 | 21 Aug 2007 | Hacked MNG plugin to validate images using the .mng header. |
|  |  | Re-applied internal LibPNG support. Do not Import Pub.Libpng |
|  |  | Loaded TFreeImages bitmaps are now not y-flipped at load-time. Therefore when saving they should now be in the correct orientation. |
|  |  | New `TMultiFreeImage` type for multi-page image support (gif, ico and tiff). |
|  |  | New `LoadAnimFreeImage()` function to create a multi-frame TImage from a multi-page image. |
| 1.01 | n/a | Added `CreateFromPixmap()` function. |
|  |  | Added colorQuantize, dither, threshold, toneMapping, tmoDrago03 and tmoReinhard05 methods. |
|  |  | Added convertTo 4, 8, 16 methods. |
|  |  | Added more documentation. |
| 1.00 | n/a | Initial Release. (FreeImage 3.9.3). |