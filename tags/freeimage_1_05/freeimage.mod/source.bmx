' Copyright (c) 2007-2009 Bruce A Henderson
' 
' Permission is hereby granted, free of charge, to any person obtaining a copy
' of this software and associated documentation files (the "Software"), to deal
' in the Software without restriction, including without limitation the rights
' to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, subject to the following conditions:
' 
' The above copyright notice and this permission notice shall be included in
' all copies or substantial portions of the Software.
' 
' THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
' IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
' FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
' AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
' LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
' OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
' THE SOFTWARE.
'
SuperStrict


'Import Pub.libpng
Import Pub.zlib

Import "../../pub.mod/zlib.mod/*.h"
'Import "../../pub.mod/libpng.mod/*.h"

Import "src/*.h"
Import "src/FreeImage/*.h"
Import "src/FreeImageToolkit/*.h"
Import "src/LibMNG/*.h"
Import "src/LibJPEG/*.h"
Import "src/LibTIFF/*.h"
Import "src/Metadata/*.h"
Import "src/DeprecationManager/*.h"
Import "src/LibOpenJPEG/*.h"
Import "src/OpenEXR/*.h"
Import "src/OpenEXR/Imath/*.h"
Import "src/OpenEXR/IlmThread/*.h"
Import "src/OpenEXR/IlmImf/*.h"
Import "src/OpenEXR/Half/*.h"
Import "src/OpenEXR/Iex/*.h"


Import "src/FreeImage/BitmapAccess.cpp"
Import "src/FreeImage/CacheFile.cpp"
Import "src/FreeImage/ColorLookup.cpp"
Import "src/FreeImage/Conversion.cpp"
Import "src/FreeImage/Conversion16_555.cpp"
Import "src/FreeImage/Conversion16_565.cpp"
Import "src/FreeImage/Conversion24.cpp"
Import "src/FreeImage/Conversion32.cpp"
Import "src/FreeImage/Conversion4.cpp"
Import "src/FreeImage/Conversion8.cpp"
Import "src/FreeImage/ConversionRGBF.cpp"
Import "src/FreeImage/ConversionType.cpp"
Import "src/FreeImage/FreeImage.cpp"
Import "src/FreeImage/FreeImageC.c"
Import "src/FreeImage/FreeImageIO.cpp"
Import "src/FreeImage/GetType.cpp"
Import "src/FreeImage/Halftoning.cpp"
Import "src/FreeImage/MemoryIO.cpp"
Import "src/FreeImage/MultiPage.cpp"
Import "src/FreeImage/NNQuantizer.cpp"
Import "src/FreeImage/PixelAccess.cpp"
Import "src/FreeImage/Plugin.cpp"
Import "src/FreeImage/PluginBMP.cpp"
Import "src/FreeImage/PluginCUT.cpp"
Import "src/FreeImage/PluginDDS.cpp"
Import "src/FreeImage/PluginG3.cpp"
Import "src/FreeImage/PluginGIF.cpp"
Import "src/FreeImage/PluginHDR.cpp"
Import "src/FreeImage/PluginICO.cpp"
Import "src/FreeImage/PluginIFF.cpp"
Import "src/FreeImage/PluginJPEG.cpp"
Import "src/FreeImage/PluginKOALA.cpp"
Import "src/FreeImage/PluginMNG.cpp"
Import "src/FreeImage/PluginPCD.cpp"
Import "src/FreeImage/PluginPCX.cpp"
Import "src/FreeImage/PluginPNG.cpp"
Import "src/FreeImage/PluginPNM.cpp"
Import "src/FreeImage/PluginPSD.cpp"
Import "src/FreeImage/PluginRAS.cpp"
Import "src/FreeImage/PluginSGI.cpp"
Import "src/FreeImage/PluginTARGA.cpp"
Import "src/FreeImage/PluginTIFF.cpp"
Import "src/FreeImage/PluginWBMP.cpp"
Import "src/FreeImage/PluginXBM.cpp"
Import "src/FreeImage/PluginXPM.cpp"
Import "src/FreeImage/PluginJ2K.cpp"
Import "src/FreeImage/PluginEXR.cpp"
Import "src/FreeImage/PluginJP2.cpp"
Import "src/FreeImage/tmoColorConvert.cpp"
Import "src/FreeImage/tmoDrago03.cpp"
Import "src/FreeImage/tmoReinhard05.cpp"
Import "src/FreeImage/ToneMapping.cpp"
Import "src/FreeImage/WuQuantizer.cpp"
Import "src/FreeImage/ZLibInterface.cpp"
Import "src/FreeImage/J2KHelper.cpp"
Import "src/FreeImage/tmoFattal02.cpp"

Import "src/FreeImageToolkit/BSplineRotate.cpp"
Import "src/FreeImageToolkit/Channels.cpp"
Import "src/FreeImageToolkit/ClassicRotate.cpp"
Import "src/FreeImageToolkit/Colors.cpp"
Import "src/FreeImageToolkit/CopyPaste.cpp"
Import "src/FreeImageToolkit/Display.cpp"
Import "src/FreeImageToolkit/Flip.cpp"
Import "src/FreeImageToolkit/JPEGTransform.cpp"
Import "src/FreeImageToolkit/Rescale.cpp"
Import "src/FreeImageToolkit/Resize.cpp"
Import "src/FreeImageToolkit/MultigridPoissonSolver.cpp"

Import "src/LibMNG/libmng_callback_xs.c"
Import "src/LibMNG/libmng_chunk_descr.c"
Import "src/LibMNG/libmng_chunk_io.c"
Import "src/LibMNG/libmng_chunk_prc.c"
Import "src/LibMNG/libmng_chunk_xs.c"
Import "src/LibMNG/libmng_cms.c"
Import "src/LibMNG/libmng_display.c"
Import "src/LibMNG/libmng_dither.c"
Import "src/LibMNG/libmng_error.c"
Import "src/LibMNG/libmng_filter.c"
Import "src/LibMNG/libmng_hlapi.c"
Import "src/LibMNG/libmng_jpeg.c"
Import "src/LibMNG/libmng_object_prc.c"
Import "src/LibMNG/libmng_pixels.c"
Import "src/LibMNG/libmng_prop_xs.c"
Import "src/LibMNG/libmng_read.c"
Import "src/LibMNG/libmng_trace.c"
Import "src/LibMNG/libmng_write.c"
Import "src/LibMNG/libmng_zlib.c"

Import "src/LibTIFF/mkg3states.c"
Import "src/LibTIFF/tif_aux.c"
Import "src/LibTIFF/tif_close.c"
Import "src/LibTIFF/tif_codec.c"
Import "src/LibTIFF/tif_color.c"
Import "src/LibTIFF/tif_compress.c"
Import "src/LibTIFF/tif_dir.c"
Import "src/LibTIFF/tif_dirinfo.c"
Import "src/LibTIFF/tif_dirread.c"
Import "src/LibTIFF/tif_dirwrite.c"
Import "src/LibTIFF/tif_dumpmode.c"
Import "src/LibTIFF/tif_error.c"
Import "src/LibTIFF/tif_extension.c"
Import "src/LibTIFF/tif_fax3.c"
Import "src/LibTIFF/tif_fax3sm.c"
Import "src/LibTIFF/tif_flush.c"
Import "src/LibTIFF/tif_getimage.c"
Import "src/LibTIFF/tif_jpeg.c"
Import "src/LibTIFF/tif_luv.c"
Import "src/LibTIFF/tif_lzw.c"
Import "src/LibTIFF/tif_next.c"
Import "src/LibTIFF/tif_open.c"
Import "src/LibTIFF/tif_packbits.c"
Import "src/LibTIFF/tif_pixarlog.c"
Import "src/LibTIFF/tif_predict.c"
Import "src/LibTIFF/tif_print.c"
Import "src/LibTIFF/tif_read.c"
Import "src/LibTIFF/tif_strip.c"
Import "src/LibTIFF/tif_swab.c"
Import "src/LibTIFF/tif_thunder.c"
Import "src/LibTIFF/tif_tile.c"
Import "src/LibTIFF/tif_version.c"
Import "src/LibTIFF/tif_warning.c"
Import "src/LibTIFF/tif_write.c"
Import "src/LibTIFF/tif_zip.c"

Import "src/Metadata/Exif.cpp"
Import "src/Metadata/FIRational.cpp"
Import "src/Metadata/FreeImageTag.cpp"
Import "src/Metadata/IPTC.cpp"
Import "src/Metadata/TagConversion.cpp"
Import "src/Metadata/TagLib.cpp"
Import "src/Metadata/XTIFF.cpp"
Import "src/DeprecationManager/DeprecationMgr.cpp"


Import "src/LibJPEG/jcapimin.c"
Import "src/LibJPEG/jcapistd.c"
Import "src/LibJPEG/jccoefct.c"
Import "src/LibJPEG/jccolor.c"
Import "src/LibJPEG/jcdctmgr.c"
Import "src/LibJPEG/jchuff.c"
Import "src/LibJPEG/jcinit.c"
Import "src/LibJPEG/jcmainct.c"
Import "src/LibJPEG/jcmarker.c"
Import "src/LibJPEG/jcmaster.c"
Import "src/LibJPEG/jcomapi.c"
Import "src/LibJPEG/jcparam.c"
Import "src/LibJPEG/jcphuff.c"
Import "src/LibJPEG/jcprepct.c"
Import "src/LibJPEG/jcsample.c"
Import "src/LibJPEG/jctrans.c"
Import "src/LibJPEG/jdapimin.c"
Import "src/LibJPEG/jdapistd.c"
Import "src/LibJPEG/jdatadst.c"
Import "src/LibJPEG/jdatasrc.c"
Import "src/LibJPEG/jdcoefct.c"
Import "src/LibJPEG/jdcolor.c"
Import "src/LibJPEG/jddctmgr.c"
Import "src/LibJPEG/jdhuff.c"
Import "src/LibJPEG/jdinput.c"
Import "src/LibJPEG/jdmainct.c"
Import "src/LibJPEG/jdmarker.c"
Import "src/LibJPEG/jdmaster.c"
Import "src/LibJPEG/jdmerge.c"
Import "src/LibJPEG/jdphuff.c"
Import "src/LibJPEG/jdpostct.c"
Import "src/LibJPEG/jdsample.c"
Import "src/LibJPEG/jdtrans.c"
Import "src/LibJPEG/jerror.c"
Import "src/LibJPEG/jfdctflt.c"
Import "src/LibJPEG/jfdctfst.c"
Import "src/LibJPEG/jfdctint.c"
Import "src/LibJPEG/jidctflt.c"
Import "src/LibJPEG/jidctfst.c"
Import "src/LibJPEG/jidctint.c"
Import "src/LibJPEG/jidctred.c"
Import "src/LibJPEG/jmemmgr.c"
Import "src/LibJPEG/jmemnobs.c"
Import "src/LibJPEG/jquant1.c"
Import "src/LibJPEG/jquant2.c"
Import "src/LibJPEG/jutils.c"
Import "src/LibJPEG/transupp.c"

Import "src/LibPNG/png.c"
Import "src/LibPNG/pngerror.c"
Import "src/LibPNG/pngget.c"
Import "src/LibPNG/pngmem.c"
Import "src/LibPNG/pngpread.c"
Import "src/LibPNG/pngread.c"
Import "src/LibPNG/pngrio.c"
Import "src/LibPNG/pngrtran.c"
Import "src/LibPNG/pngrutil.c"
Import "src/LibPNG/pngset.c"
Import "src/LibPNG/pngtrans.c"
Import "src/LibPNG/pngwio.c"
Import "src/LibPNG/pngwrite.c"
Import "src/LibPNG/pngwtran.c"
Import "src/LibPNG/pngwutil.c"
?MacosX86
Import "src/LibPNG/pnggccrd.c"
?

Import "src/LibOpenJPEG/bio.c"
Import "src/LibOpenJPEG/cio.c"
Import "src/LibOpenJPEG/dwt.c"
Import "src/LibOpenJPEG/event.c"
Import "src/LibOpenJPEG/image.c"
Import "src/LibOpenJPEG/j2k.c"
Import "src/LibOpenJPEG/j2k_lib.c"
Import "src/LibOpenJPEG/jp2.c"
Import "src/LibOpenJPEG/jpt.c"
Import "src/LibOpenJPEG/mct.c"
Import "src/LibOpenJPEG/mqc.c"
Import "src/LibOpenJPEG/openjpeg.c"
Import "src/LibOpenJPEG/pi.c"
Import "src/LibOpenJPEG/raw.c"
Import "src/LibOpenJPEG/t1.c"
Import "src/LibOpenJPEG/t2.c"
Import "src/LibOpenJPEG/tcd.c"
Import "src/LibOpenJPEG/tgt.c"

Import "src/OpenEXR/IlmImf/b44ExpLogTable.cpp"
Import "src/OpenEXR/IlmImf/ImfAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfB44Compressor.cpp"
Import "src/OpenEXR/IlmImf/ImfBoxAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfChannelList.cpp"
Import "src/OpenEXR/IlmImf/ImfChannelListAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfChromaticities.cpp"
Import "src/OpenEXR/IlmImf/ImfChromaticitiesAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfCompressionAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfCompressor.cpp"
Import "src/OpenEXR/IlmImf/ImfConvert.cpp"
Import "src/OpenEXR/IlmImf/ImfCRgbaFile.cpp"
Import "src/OpenEXR/IlmImf/ImfDoubleAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfEnvmap.cpp"
Import "src/OpenEXR/IlmImf/ImfEnvmapAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfFloatAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfFrameBuffer.cpp"
Import "src/OpenEXR/IlmImf/ImfFramesPerSecond.cpp"
Import "src/OpenEXR/IlmImf/ImfHeader.cpp"
Import "src/OpenEXR/IlmImf/ImfHuf.cpp"
Import "src/OpenEXR/IlmImf/ImfInputFile.cpp"
Import "src/OpenEXR/IlmImf/ImfIntAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfIO.cpp"
Import "src/OpenEXR/IlmImf/ImfKeyCode.cpp"
Import "src/OpenEXR/IlmImf/ImfKeyCodeAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfLineOrderAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfLut.cpp"
Import "src/OpenEXR/IlmImf/ImfMatrixAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfMisc.cpp"
Import "src/OpenEXR/IlmImf/ImfOpaqueAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfOutputFile.cpp"
Import "src/OpenEXR/IlmImf/ImfPizCompressor.cpp"
Import "src/OpenEXR/IlmImf/ImfPreviewImage.cpp"
Import "src/OpenEXR/IlmImf/ImfPreviewImageAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfPxr24Compressor.cpp"
Import "src/OpenEXR/IlmImf/ImfRational.cpp"
Import "src/OpenEXR/IlmImf/ImfRationalAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfRgbaFile.cpp"
Import "src/OpenEXR/IlmImf/ImfRgbaYca.cpp"
Import "src/OpenEXR/IlmImf/ImfRleCompressor.cpp"
Import "src/OpenEXR/IlmImf/ImfScanLineInputFile.cpp"
Import "src/OpenEXR/IlmImf/ImfStandardAttributes.cpp"
Import "src/OpenEXR/IlmImf/ImfStdIO.cpp"
Import "src/OpenEXR/IlmImf/ImfStringAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfTestFile.cpp"
Import "src/OpenEXR/IlmImf/ImfThreading.cpp"
Import "src/OpenEXR/IlmImf/ImfTileDescriptionAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfTiledInputFile.cpp"
Import "src/OpenEXR/IlmImf/ImfTiledMisc.cpp"
Import "src/OpenEXR/IlmImf/ImfTiledOutputFile.cpp"
Import "src/OpenEXR/IlmImf/ImfTiledRgbaFile.cpp"
Import "src/OpenEXR/IlmImf/ImfTileOffsets.cpp"
Import "src/OpenEXR/IlmImf/ImfTimeCode.cpp"
Import "src/OpenEXR/IlmImf/ImfTimeCodeAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfVecAttribute.cpp"
Import "src/OpenEXR/IlmImf/ImfVersion.cpp"
Import "src/OpenEXR/IlmImf/ImfWav.cpp"
Import "src/OpenEXR/IlmImf/ImfZipCompressor.cpp"
Import "src/OpenEXR/Imath/ImathBox.cpp"
Import "src/OpenEXR/Imath/ImathColorAlgo.cpp"
Import "src/OpenEXR/Imath/ImathFun.cpp"
Import "src/OpenEXR/Imath/ImathMatrixAlgo.cpp"
Import "src/OpenEXR/Imath/ImathRandom.cpp"
Import "src/OpenEXR/Imath/ImathShear.cpp"
Import "src/OpenEXR/Imath/ImathVec.cpp"
Import "src/OpenEXR/Iex/IexBaseExc.cpp"
Import "src/OpenEXR/Iex/IexThrowErrnoExc.cpp"
Import "src/OpenEXR/Half/half.cpp"
Import "src/OpenEXR/IlmThread/IlmThread.cpp"
Import "src/OpenEXR/IlmThread/IlmThreadMutex.cpp"
Import "src/OpenEXR/IlmThread/IlmThreadPool.cpp"
Import "src/OpenEXR/IlmThread/IlmThreadSemaphore.cpp"