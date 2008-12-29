' Copyright (c) 2008 Bruce A Henderson
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

Rem
bbdoc: GraphicsMagick
about: The swiss army knife of image processing.
End Rem
Module BaH.Magick

ModuleInfo "Version: 1.00"
ModuleInfo "License: MIT"
ModuleInfo "Copyright: GraphicsMagick - 2002-2008 GraphicsMagick Group"
ModuleInfo "Copyright: Wrapper - 2008 Bruce A Henderson"

ModuleInfo "History: 1.00"
ModuleInfo "History: Initial Release."

ModuleInfo "CC_OPTS: -fexceptions -DLIBXML_STATIC"

Import BRL.Pixmap
Import BRL.Stream

Import "common.bmx"

' NOTES:
'
' Renamed coders/locale.c and map.c with prefix bmx_
' Renamed delegates/bzip2/compress.c with prefix bmx_
'
' Be careful not to overwrite magick_config.h !!
'
' Added windows.h include to tif_win32.c
'


Global _magick_initialized:Int = False

' set the config path
Function _init_magick()
	putenv_("MAGICK_CONFIGURE_PATH=" + MagickConfigPath)
	_magick_initialized = True
End Function

Rem
bbdoc: The path to magick.mgk
about: Can be set at runtime before calling any Magick functions.
End Rem
Global MagickConfigPath:String = "config"

Rem
bbdoc: 
End Rem
Function LoadMagickImage:TMImage( url:Object )

	Local imgStream:TStream = TStream(url)
	
	If Not imgStream
		imgStream = ReadStream( url )
	End If
	
	If Not imgStream Then
		Return Null
	End If
	
	Local fi:TMImage = TMImage.CreateFromStream(imgStream)
	
	imgStream.close()
	
	Return fi

End Function

Rem
bbdoc: TMImage is the primary object in Magick and represents a single image frame.
End Rem
Type TMImage

	Field imagePtr:Byte Ptr
	
	' this is PRIVATE.... you should use getPixmap() to retrieve it!!!!
	Field pixmap:TPixmap

	Rem
	bbdoc: The image width
	End Rem
	Field width:Int
	
	Rem
	bbdoc: The image height
	End Rem
	Field height:Int
	
	Rem
	bbdoc: Bits per pixel
	End Rem
	Field bitsPerPixel:Int

	Rem
	bbdoc: The image pitch
	End Rem
	Field pitch:Int
	
	Field imageChanged:Int = True
	
	Method New()
		If Not _magick_initialized Then
			_init_magick()
		End If
	End Method

	Function _create:TMImage(imagePtr:Byte Ptr)
		If imagePtr Then
			Local this:TMImage = New TMImage
			this.imagePtr = imagePtr
			this._calc()
			Return this
		End If
	End Function

	Rem
	bbdoc: 
	End Rem
	Function Create:TMImage()
		If Not _magick_initialized Then
			_init_magick()
		End If
		Return TMImage._create(bmx_magick_create())
	End Function

	Rem
	bbdoc: 
	End Rem
	Function CreateFromFile:TMImage(imageSpec:String)
		If Not _magick_initialized Then
			_init_magick()
		End If
		Return TMImage._create(bmx_magick_createfromspec(imageSpec))
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Function CreateFromBlob:TMImage(blob:TMBlob)
		Local this:TMImage = New TMImage
		this.imagePtr = bmx_magick_image_createfromblob(blob.blobPtr)
		this._calc()
		Return this
	End Function

	Rem
	bbdoc: 
	End Rem
	Function CreateFromStream:TMImage(stream:TStream)
		
		Local size:Int = stream.Size()
		Local buffer:Byte Ptr = MemAlloc(size)
		
		stream.ReadBytes(buffer, size)
		Local blob:TMBlob = TMBlob.CreateFromData(buffer, size)
		
		Local image:TMImage = TMImage.CreateFromBlob(blob)
		
		MemFree(buffer)
		
		Return image
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Function CreateFromPixmap:TMImage(pixmap:TPixmap)
	
	End Function

	'internal method
	Method _calc()
		bmx_magick_image_getsize(imagePtr, Varptr width, Varptr height)
		bitsPerPixel = bmx_magick_image_getdepth(imagePtr)
		pitch = width * (bitsPerPixel / 8)
	End Method
	
	'internal method
	Method _invertalpha()
		Local offset:Byte Ptr = pixmap.pixels + 3
		For Local i:Int = 0 Until width * height
			offset[0] = 255 - offset[0]
			offset:+ 4
		Next
	End Method
	
	'internal method
	Method _updatePixmap()
		' (re)calculate image size
		_calc()
		
		' do we need a brand new pixmap?
		If Not pixmap Or pixmap.width <> width Or pixmap.height <> height Then
			pixmap = CreatePixmap(width, height, PF_RGBA8888)
		End If
		
		' copy pixel data to pixmap
		bmx_magick_image_writedata(imagePtr, 0, 0, width, height, "RGBA", 0, pixmap.pixels)
		' invert the alpha - magick uses opposite, where 0 is opaque, 1 is transparent
		_invertalpha()
	End Method
	
	Rem
	bbdoc: Returns a pixmap representation of the image.
	End Rem
	Method getPixmap:TPixmap()
	
		If imageChanged Then
			_updatePixmap()
		End If
		
		Return pixmap
	End Method

	Rem
	bbdoc: Apply adaptive thresholding to the image.
	about: Adaptive thresholding is useful if the ideal threshold level is not known in advance, or if the illumination
	gradient is not constant across the image. Adaptive thresholding works by evaulating the mean (average) of a pixel
	region (size specified by @width and @height) and using the mean as the thresholding value. In order to remove residual
	noise from the background, the threshold may be adjusted by subtracting a constant @offset (default zero) from the mean
	to compute the threshold.
	End Rem
	Method adaptiveThreshold(width:Int, height:Int, offset:Int = 0)
		bmx_magick_image_adaptivethreshold(imagePtr, width, height, offset)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Add noise to image with specified @noiseType.
	about: One of NOISE_UNIFORMNOISE, NOISE_GAUSSIANNOISE, NOISE_MULTIPLICATIVEGAUSSIANNOISE, NOISE_IMPULSENOISE,
	NOISE_LAPLACIANNOISE or NOISE_POISSONNOISE.
	End Rem
	Method addNoise(noiseType:Int)
		bmx_magick_image_addnoise(imagePtr, noiseType)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Add noise to an image channel with the specified noise type.
	about: The @channel parameter specifies the channel to add noise to.  The @noiseType parameter
	specifies the type of noise. One of, NOISE_UNIFORMNOISE, NOISE_GAUSSIANNOISE, NOISE_MULTIPLICATIVEGAUSSIANNOISE, NOISE_IMPULSENOISE,
	NOISE_LAPLACIANNOISE or NOISE_POISSONNOISE.
	End Rem
	Method addNoiseChannel(channel:Int, noiseType:Int)
		bmx_magick_image_addnoisechannel(imagePtr, channel, noiseType)
		imageChanged = True
	End Method
	
	'method bmx_magick_image_affinetransform(, const DrawableAffine &affine )
	' TODO
	'End Method
	
	Rem
	bbdoc: Annotates using specified @text, and placement @location.
	End Rem
	Method annotate(text:String, location:Object )
		If TMGeometry(location) Then
			bmx_magick_image_annotate(imagePtr, text, TMGeometry(location).geometryPtr)
		Else If String(location) Then
			bmx_magick_image_annotatetxt(imagePtr, text, String(location))
		End If
	End Method
	
	Rem
	bbdoc: Blur image.
	about: The @radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.
	The @sigma parameter specifies the standard deviation of the Laplacian, in pixels.
	End Rem
	Method blur(radius:Double = 1.0, sigma:Double = 0.5)
		bmx_magick_image_blur(imagePtr, radius, sigma)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Blur an image channel.
	about: The @channel parameter specifies the channel to blur. The @radius parameter specifies the radius
	of the Gaussian, in pixels, not counting the center pixel.  The @sigma parameter specifies the standard
	deviation of the Laplacian, in pixels.
	End Rem
	Method blurChannel(channel:Int, radius:Double = 0.0, sigma:Double = 1.0 )
		bmx_magick_image_blurchannel(imagePtr, channel, radius, sigma)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Border image (add border to image). 
	about: The color of the border is specified by setting borderColor().
	End Rem
	Method border(geometry:Object)
		If TMGeometry(geometry) Then
			bmx_magick_image_border(imagePtr, TMGeometry(geometry).geometryPtr)
		Else If String(geometry) Then
			bmx_magick_image_bordertxt(imagePtr, String(geometry))
		End If
	End Method
	
	Rem
	bbdoc: Extracts channel from image.
	about: Use this option to extract a particular channel from  the image.
	MatteChannel for example, is useful for extracting the opacity values from an image.
	End Rem
	Method channel(channel:Int)
		bmx_magick_image_channel(imagePtr, channel)
	End Method
	
	Rem
	bbdoc: Charcoal effects image (looks like charcoal sketch).
	about: The @radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.
	The @sigma parameter specifies the standard deviation of the Laplacian, in pixels.
	End Rem
	Method charcoal(radius:Double = 1.0, sigma:Double = 0.5)
		bmx_magick_image_charcoal(imagePtr, radius, sigma)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Chops image (remove vertical or horizontal subregion of image)
	End Rem
	Method chop(geometry:Object)
		If TMGeometry(geometry) Then
			bmx_magick_image_chop(imagePtr, TMGeometry(geometry).geometryPtr)
			imageChanged = True
		Else If String(geometry) Then
			bmx_magick_image_choptxt(imagePtr, String(geometry))
			imageChanged = True
		End If
	End Method
	
	Rem
	bbdoc: Colorize image with pen color, using specified percent opacity for red, green, and blue quantums.
	End Rem
	Method colorize(opacityRed:Int, opacityGreen:Int, opacityBlue:Int, penColor:Object)
		If TMColor(penColor) Then
			bmx_magick_image_colorize(imagePtr, opacityRed, opacityGreen, opacityBlue, TMColor(penColor).colorPtr)
			imageChanged = True
		ElseIf String(penColor)
			bmx_magick_image_colorizetxt(imagePtr, opacityRed, opacityGreen, opacityBlue, String(penColor))
			imageChanged = True
		EndIf
	End Method
	
	Rem
	bbdoc: Colorize image with pen color, using specified percent opacity.
	End Rem
	Method colorizeColor(opacity:Int, penColor:Object)
		If TMColor(penColor) Then
			bmx_magick_image_colorizecolor(imagePtr, opacity, TMColor(penColor).colorPtr)
			imageChanged = True
		ElseIf String(penColor)
			bmx_magick_image_colorizecolortxt(imagePtr, opacity, String(penColor))
			imageChanged = True
		End If
	End Method
	
	Rem
	bbdoc: Comment image (add comment string to image).
	about: By default, each image is commented with its file name. Use  this  method to  assign a specific comment
	to the image.  Optionally you can include the image filename, type, width, height, or other
	image  attributes by embedding special format characters.
	End Rem
	Method comment(comment:String)
		bmx_magick_image_comment(imagePtr, comment)
	End Method
	
	Rem
	bbdoc: Compare current image with another image.
	about: Sets meanErrorPerPixel , normalizedMaxError , and normalizedMeanError in the current image. False
	is returned if the images are identical. An ErrorOption exception is thrown if the reference image columns, rows,
	colorspace, or matte differ from the current image.
	End Rem
	Method compareImage:Int(image:TMImage)
	' TODO
	End Method
	
	Method composite(compositeImage:TMImage, xOffset:Int, yOffset:Int, operator:Int = COMPOSITE_INCOMPOSITEOP)
	'TODO
	End Method

	Method compositeGeometry(compositeImage:TMImage, geometry:Object, operator:Int = COMPOSITE_INCOMPOSITEOP)
	'TODO
	End Method

	Method compositeGravity(compositeImage:TMImage, gravity:Int, operator:Int = COMPOSITE_INCOMPOSITEOP)
	'TODO
	End Method
	
	Rem
	bbdoc: Returns a copy of the image.
	End Rem
	Method copy:TMImage()
		Return TMImage._create(bmx_magick_image_copy(imagePtr))
	End Method
	
	Rem
	bbdoc: Contrast image (enhance intensity differences in image)
	End Rem
	Method contrast(sharpen:Int)
		bmx_magick_image_contrast(imagePtr, sharpen)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method convolve(order:Int, kernel:Double[])
	'TODO
	End Method
	
	Rem
	bbdoc: Crop image (subregion of original image)
	End Rem
	Method crop(geometry:Object)
		If TMGeometry(geometry) Then
			bmx_magick_image_crop(imagePtr, TMGeometry(geometry).geometryPtr)
			imageChanged = True
		ElseIf String(geometry) Then
			bmx_magick_image_croptxt(imagePtr, String(geometry))
			imageChanged = True
		End If
	End Method
	
	Rem
	bbdoc: Cycle image colormap.
	End Rem
	Method cycleColormap(amount:Int)
		bmx_magick_image_cyclecolormap(imagePtr, amount)
	End Method
	
	Rem
	bbdoc: Despeckle image (reduce speckle noise).
	End Rem
	Method despeckle()
		bmx_magick_image_despeckle(imagePtr)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method draw(drawable:TMDrawable)
	'TODO
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method drawList(drawables:TList)
	'TODO
	End Method
	
	Rem
	bbdoc: Edges image (hilight edges in image).
	about: The radius is the radius of the pixel neighborhood.. Specify a radius of zero for automatic radius selection.
	End Rem
	Method edge(radius:Double = 0.0)
		bmx_magick_image_edge(imagePtr, radius)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Emboss image (hilight edges with 3D effect).
	about: The $radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.
	The @sigma parameter specifies the standard deviation of the Laplacian, in pixels.
	End Rem
	Method emboss(radius:Double = 1.0, sigma:Double = 0.5)
		bmx_magick_image_emboss(imagePtr, radius, sigma)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Enhance image (minimize noise).
	End Rem
	Method enhance()
		bmx_magick_image_enhance(imagePtr)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Equalize image (histogram equalization).
	End Rem
	Method equalize()
		bmx_magick_image_equalize(imagePtr)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Set all image pixels to the current background color.
	End Rem
	Method erase()
		bmx_magick_image_erase(imagePtr)
		imageChanged = True
	End Method
	
	
	Rem
	bbdoc: Flip image (reflect each scanline in the vertical direction).
	End Rem
	Method Flip()
		bmx_magick_image_flip(imagePtr)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Flood-fill color across pixels that match the color of the target pixel and are neighbors of the target pixel and optionally stopping at pixels matching specified border color.
	about: Uses current fuzz setting when determining color match
	End Rem
	Method floodFillColor(x:Int, y:Int, fillColor:Object, borderColor:Object = Null)
		If borderColor Then
			If TMColor(borderColor) Then
				If TMColor(fillColor) Then
					bmx_magick_image_floodfillcolorcc(imagePtr, x, y, TMColor(fillColor).colorPtr, TMColor(borderColor).colorPtr)
				ElseIf String(fillColor) Then
					bmx_magick_image_floodfillcolorsc(imagePtr, x, y, String(fillColor), TMColor(borderColor).colorPtr)
				End If
			ElseIf String(borderColor) Then
				If TMColor(fillColor) Then
					bmx_magick_image_floodfillcolorcs(imagePtr, x, y, TMColor(fillColor).colorPtr, String(borderColor))
				ElseIf String(fillColor) Then
					bmx_magick_image_floodfillcolorss(imagePtr, x, y, String(fillColor), String(borderColor))
				End If
			End If
		Else
			If TMColor(fillColor) Then
				bmx_magick_image_floodfillcolorcc(imagePtr, x, y, TMColor(fillColor).colorPtr, Null)
			ElseIf String(fillColor) Then
				bmx_magick_image_floodfillcolorsc(imagePtr, x, y, String(fillColor), Null)
			End If
		End If
	End Method
	
	Method floodFillColorGeom(point:Object, fillColor:Object, borderColor:Object = Null)
	'TODO
	End Method

	Method floodFillOpacity(x:Int, y:Int, opacity:Int, paintMethod:Int)
	'TODO
	End Method
	
	Method floodFillTexture(x:Int, y:Int, texture:TMImage, borderColor:Object = Null)
	'TODO
	End Method
	
	Method floodFillTextureGeom(point:Object, texture:TMImage, borderColor:Object = Null)
	'TODO
	End Method
	
	Rem
	bbdoc: Flop image (reflect each scanline in the horizontal direction).
	End Rem
	Method flop()
		bmx_magick_image_flop(imagePtr)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method frame(geometry:Object)
		If TMGeometry(geometry) Then
			bmx_magick_image_frame(imagePtr, TMGeometry(geometry).geometryPtr)
		ElseIf String(geometry)
			bmx_magick_image_frametxt(imagePtr, String(geometry))
		End If
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method frameBevel(width:Int, height:Int, innerBevel:Int = 6, outerBevel:Int = 6)
		bmx_magick_image_framebevel(imagePtr, width, height, innerBevel, outerBevel)
	End Method
	
	Rem
	bbdoc: Gamma correct image (uniform red, green, and blue correction).
	End Rem
	Method gamma(g:Double)
		bmx_magick_image_gamma(imagePtr, g)
	End Method
	
	Rem
	bbdoc: Gamma correct red, green, and blue channels of image.
	End Rem
	Method gammaRGB(r:Double, g:Double, b:Double)
		bmx_magick_image_gammargb(imagePtr, r, g, b)
	End Method

	Rem
	bbdoc: Gaussian blur image.
	about: The number of neighbor pixels to be included in the convolution mask is specified by @width.
	For example, a width of one gives a (standard) 3x3 convolution mask. The standard deviation of the gaussian bell curve
	is specified by @sigma.
	End Rem
	Method gaussianBlur(width:Double, sigma:Double)
		bmx_magick_image_gaussianblur(imagePtr, width, sigma)
	End Method
	
	Rem
	bbdoc: Gaussian blur an image channel.
	about: The @channel parameter specifies the channel to blur. The number of neighbor pixels to be included in the
	convolution mask is specified by @width.  For example, a width of one gives a (standard) 3x3 convolution mask. The
	standard deviation of the gaussian bell curve is specified by @sigma.
	End Rem
	Method gaussianBlurChannel(channel:Int, width:Double = 0.0, sigma:Double = 1.0)
		bmx_magick_image_gaussianblurchannel(imagePtr, channel, width, sigma)
	End Method
	
	Rem
	bbdoc: Implodes image (special effect).
	End Rem
	Method implode(factor:Double)
		bmx_magick_image_implode(imagePtr, factor)
	End Method
	
	Rem
	bbdoc: Assigns a label to an image.
	about: Use this option to  assign  a  specific label to the image. Optionally you can include the image filename, type,
	width, height, or scene number in the label by embedding  special format characters. If the first character of
	string is @, the image label is read from a file titled by the remaining characters in the string. When converting to
	Postscript, use this  option to specify a header string to print above the image.
	End Rem
	Method label(text:String)
		bmx_magick_image_label(imagePtr, text)
	End Method
	
	Rem
	bbdoc: Levels image.
	about: Adjusts the levels of the image by scaling the colors falling between specified white and black points to the full
	available quantum range. The parameters provided represent the black, mid (gamma), and white points.  The black point
	specifies the darkest color in the image. Colors darker than the black point are set to zero. Mid point (gamma) specifies
	a gamma correction to apply to the image. White point specifies the lightest color in the image.  Colors brighter than
	the white point are set to the maximum quantum value. The black and white point have the valid range 0 to MaxRGB while
	mid (gamma) has a useful range of 0 to ten.
	End Rem
	Method level(blackPoint:Double, whitePoint:Double, midPoint:Double = 1.0)
		bmx_magick_image_level(imagePtr, blackPoint, whitePoint, midPoint)
	End Method
	
	Rem
	bbdoc: Levels image channel.
	about: Adjust the levels of the image channel by scaling the values falling between specified white and black points
	to the full available quantum range. The parameters provided represent the black, mid (gamma), and white points. The
	black point specifies the darkest color in the image. Colors darker than the black point are set to zero. Mid point
	(gamma) specifies a gamma correction to apply to the image. White point specifies the lightest color in the image.
	Colors brighter than the white point are set to the maximum quantum value. The black and white point have the valid
	range 0 to MaxRGB while mid (gamma) has a useful range of 0 to ten.
	End Rem
	Method levelChannel(channel:Int, blackPoint:Double, whitePoint:Double, midPoint:Double = 1.0)
		bmx_magick_image_levelchannel(imagePtr, channel, blackPoint, whitePoint, midPoint)
	End Method
	
	Rem
	bbdoc: Magnifies image by integral size.
	End Rem
	Method magnify()
		bmx_magick_image_magnify(imagePtr)
	End Method
	
	Method map(mapImage:TMImage, dither:Int = False)
	'TODO
	End Method
	
	Method matteFloodfill(target:Object, opacity:Int, x:Int, y:Int, paintMethod:Int)
	'TODO
	End Method
	
	Rem
	bbdoc: Filters image by replacing each pixel component with the median color in a circular neighborhood.
	End Rem
	Method medianFilter(radius:Double = 0.0)
		bmx_magick_image_medianfilter(imagePtr, radius)
	End Method
	
	Rem
	bbdoc: Reduces image by integral size.
	End Rem
	Method minify()
		bmx_magick_image_minify(imagePtr)
	End Method
	
	Rem
	bbdoc: Prepares to update image.
	about: Ensures that there is only one reference to the underlying image so that the underlying image may be
	safely modified without effecting previous generations of the image. Copies the underlying image to a new image
	if necessary.
	End Rem
	Method modifyImage()
		bmx_magick_image_modifyImage(imagePtr)
	End Method
	
	Rem
	bbdoc: Modulates percent hue, saturation, and brightness of an image.
	about: Modulation of saturation and brightness is as a ratio of the current value (1.0 for no change). Modulation of
	hue is an absolute rotation of -180 degrees to +180 degrees from the current position corresponding to an argument
	range of 0 to 2.0 (1.0 for no change).
	End Rem
	Method modulate(brightness:Double, saturation:Double, hue:Double)
		bmx_magick_image_modulate(imagePtr, brightness, saturation, hue)
	End Method
	
	Rem
	bbdoc: Motion blurs image with specified blur factor.
	The @radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.
	The @sigma parameter specifies the standard deviation of the Laplacian, in pixels. The @angle parameter specifies
	the angle the object appears to be comming from (zero degrees is from the right).
	End Rem
	Method motionBlur(radius:Double, sigma:Double, angle:Double)
		bmx_magick_image_motionblur(imagePtr, radius, sigma, angle)
	End Method
	
	Rem
	bbdoc: Negates colors in image.
	about: Replaces every pixel with its complementary color (white becomes black, yellow becomes blue, etc.).  Set
	grayscale to only negate grayscale values in image.
	End Rem
	Method negate(grayscale:Int = False)
		bmx_magick_image_negate(imagePtr, grayscale)
	End Method
	
	Rem
	bbdoc: Normalizes image (increase contrast by normalizing the pixel values to span the full range of color values).
	End Rem
	Method normalize()
		bmx_magick_image_normalize(imagePtr)
	End Method
	
	Rem
	bbdoc: Oilpaint image (image looks like oil painting).
	End Rem
	Method oilPaint(radius:Double = 3.0)
		bmx_magick_image_oilpaint(imagePtr, radius)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: Set or attenuate the opacity channel in the image.
	about: If the image pixels are opaque then they are set to the specified opacity value, otherwise
	they are blended with the supplied opacity value.  The value of @opacity ranges from 0
	(completely opaque) to MaxRGB . The defines OpaqueOpacity and TransparentOpacity are available
	to specify completely opaque or completely transparent, respectively.
	End Rem
	Method opacity(value:Int)
		bmx_magick_image_opacity(imagePtr, value)
		imageChanged = True
	End Method
	
	Method opaque(opaqueColor:Object, penColor:Object)
	'TODO
	End Method
	
	Rem
	bbdoc: Ping is similar to read except only enough of the image is read to determine the image columns, rows, and filesize.
	about: The columns , rows , and fileSize attributes are valid after invoking ping.  The image data is not valid after
	calling ping.
	End Rem
	Method ping(imageSpec:String)
		bmx_magick_image_ping(imagePtr, imageSpec)
	End Method
	
	Rem
	bbdoc: Quantizes image (reduce number of colors).
	about: Set @measureError to true in order to calculate error attributes.
	End Rem
	Method quantize(measureError:Int = False)
		bmx_magick_image_quantize(imagePtr, measureError)
	End Method
	
	Method raise(geometry:Object)
	'TODO
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method read(imageSpec:String)
		bmx_magick_image_read(imagePtr, imageSpec)
		imageChanged = True
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method readGeom(geometry:Object, imageSpec:String)
		If TMGeometry(geometry) Then
			bmx_magick_image_readgeom(imagePtr, TMGeometry(geometry).geometryPtr, imageSpec)
			imageChanged = True
		Else If String(geometry) Then
			bmx_magick_image_readgeomtxt(imagePtr, String(geometry), imageSpec)
			imageChanged = True
		End If
	End Method
	
	Rem
	bbdoc: Reduces noise in image using a noise peak elimination filter.
	End Rem
	Method reduceNoise(order:Double = 3.0)
		bmx_magick_image_reducenoise(imagePtr, order)
	End Method
	
	Method randomThreshold(thresholds:Object)
	'TODO
	End Method
	
	Method randomThresholdChannel(thresholds:Object, channel:Int)
	'TODO
	End Method
	
	Rem
	bbdoc: Rolls image (rolls image vertically and horizontally by specified number of columnms and rows).
	End Rem
	Method roll(columns:Int, rows:Int)
		bmx_magick_image_roll(imagePtr, columns, rows)
	End Method
	
	Rem
	bbdoc: Rotate image counter-clockwise by specified number of degrees.
	End Rem
	Method rotate(degrees:Double)
		bmx_magick_image_rotate(imagePtr, degrees)
		imageChanged = True
	End Method
	
	Method sample(geometry:Object)
	'TODO
	End Method
	
	Method scale(geometry:Object)
	'TODO
	End Method
	
	Method segment(clusterThreshold:Double = 1.0, smoothingThreshold:Double = 1.5)
	'TODO
	End Method
	
	Rem
	bbdoc: Shades image using distant light source.
	about: Specify @azimuth and @elevation as the  position  of  the light source. By default, the shading results as a
	grayscale image. Set @colorShading to true to shade the red, green, and blue components of the image.
	End Rem
	Method shade(azimuth:Double = 30, elevation:Double = 30, colorShading:Int = False)
		bmx_magick_image_shade(imagePtr, azimuth, elevation, colorShading)
	End Method
	
	Rem
	bbdoc: Sharpens pixels in image.
	about: The @radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.
	The @sigma parameter specifies the standard deviation of the Laplacian, in pixels.
	End Rem
	Method sharpen(radius:Double = 1.0, sigma:Double = 0.5)
		bmx_magick_image_sharpen(imagePtr, radius, sigma)
	End Method
	
	Rem
	bbdoc: Sharpens pixel quantums in an image channel
	about: The @channel parameter specifies the channel to sharpen. The @radius parameter specifies the radius of the
	Gaussian, in pixels, not counting the center pixel. The @sigma parameter specifies the standard deviation of the
	Laplacian, in pixels.
	End Rem
	Method sharpenChannel(channel:Int, radius:Double = 0.0, sigma:Double = 1.0)
		bmx_magick_image_sharpenchannel(imagePtr, channel, radius, sigma)
	End Method
	
	Method shave(geometry:Object)
	'TODO
	End Method
	
	Rem
	bbdoc: Shears image (creates parallelogram by sliding image by X or Y axis). 
	about: Shearing slides one edge of an image along the X  or  Y axis,  creating  a parallelogram.  An
	X direction shear slides an edge along the X axis, while  a  Y  direction shear  slides  an edge along the Y axis.
	The amount of the shear is controlled by a shear angle.  For X direction  shears,  x  degrees is measured relative to
	the Y axis, and similarly, for Y direction shears  y  degrees is measured relative to the X axis. Empty triangles
	left over from shearing the  image  are filled  with  the  color  defined as borderColor. 
	End Rem
	Method shear(xShearAngle:Double, yShearAngle:Double)
		bmx_magick_image_shear(imagePtr, xShearAngle, yShearAngle)
	End Method
	
	Rem
	bbdoc: Solarizes image (similar to effect seen when exposing a photographic film to light during the development process).
	End Rem
	Method solarize(factor:Double = 50.0)
		bmx_magick_image_solarize(imagePtr, factor)
	End Method
	
	Rem
	bbdoc: Spreads pixels randomly within image by specified amount.
	End Rem
	Method spread(amount:Int = 3)
		bmx_magick_image_spread(imagePtr, amount)
	End Method
	
	Method stegano(watermark:TMImage)
	'TODO
	End Method
	
	Method stereo(rightImage:TMImage)
	'TODO
	End Method
	
	Rem
	bbdoc: Swirls image (image pixels are rotated by degrees).
	End Rem
	Method swirl(degrees:Double)
		bmx_magick_image_swirl(imagePtr, degrees)
	End Method
	
	Method texture(txt:TMImage)
	'TODO
	End Method
	
	Rem
	bbdoc: Threshold image
	End Rem
	Method threshold(value:Double)
		bmx_magick_image_threshold(imagePtr, value)
	End Method
	
	Method transform(imageGeometry:Object, cropGeometry:Object = Null)
	'TODO
	End Method
	
	Method transparent(color:Object)
	'TODO
	End Method
	
	Rem
	bbdoc: Trims edges that are the background color from the image.
	End Rem
	Method Trim()
		bmx_magick_image_trim(imagePtr)
	End Method
	
	Rem
	bbdoc: Sharpens the image using the unsharp mask algorithm.
	about: The @radius parameter specifies the radius of the Gaussian, in pixels, not counting the center pixel.
	The @sigma parameter specifies the standard deviation of the Gaussian, in pixels. The @amount parameter specifies
	the percentage of the difference between the original and the blur image that is added back into the original. The
	@threshold parameter specifies the threshold in pixels needed to apply the diffence amount.
	End Rem
	Method unsharpmask(radius:Double, sigma:Double, amount:Double, threshold:Double)
		bmx_magick_image_unsharpmask(imagePtr, radius, sigma, amount, threshold)
	End Method
	
	Rem
	bbdoc: Sharpens an image channel using the unsharp mask algorithm.
	about: The @channel parameter specifies the channel to sharpen. The @radius parameter specifies the radius
	of the Gaussian, in pixels, not counting the center pixel. The @sigma parameter specifies the standard deviation
	of the Gaussian, in pixels. The @amount parameter specifies the percentage of the difference between the original
	and the blur image that is added back into the original. The @threshold parameter specifies the threshold in pixels
	needed to apply the diffence amount.
	End Rem
	Method unsharpmaskChannel(channel:Int, radius:Double, sigma:Double, amount:Double, threshold:Double)
		bmx_magick_image_unsharpmaskchannel(imagePtr, channel, radius, sigma, amount, threshold)
	End Method
	
	Rem
	bbdoc: Alters an image along a sine wave.
	End Rem
	Method wave(amplitude:Double = 25.0, wavelength:Double = 150.0)
		bmx_magick_image_wave(imagePtr, amplitude, wavelength)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method WriteFile(imageSpec:String)
		bmx_magick_image_writefile(imagePtr, imageSpec)
	End Method

	Rem
	bbdoc: Zooms image to specified size.
	End Rem
	Method zoom(geometry:Object)
		If TMGeometry(geometry) Then
			bmx_magick_image_zoom(imagePtr, TMGeometry(geometry).geometryPtr)
			imageChanged = True
		ElseIf String(geometry) Then
			bmx_magick_image_zoomtxt(imagePtr, String(geometry))
			imageChanged = True
		End If
	End Method

' attributes
	Rem
	bbdoc: Sets whether to join images into a single multi-image file.
	End Rem
	Method adjoin(flag:Int)
		bmx_magick_image_adjoin(imagePtr, flag)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getAdjoin:Int()
		Return bmx_magick_image_getadjoin(imagePtr)
	End Method
	
	Rem
	bbdoc: Controls antialiasing of rendered Postscript and Postscript or TrueType fonts.
	about: Enabled by default.
	End Rem
	Method AntiAlias(flag:Int)
		bmx_magick_image_antialias(imagePtr, flag)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getAntiAlias:Int()
		Return bmx_magick_image_getantialias(imagePtr)
	End Method
	
	Rem
	bbdoc: Sets the time in 1/100ths of a second (0 to 65535) which must expire before displaying the next image in an animated sequence.
	about: This option is useful for regulating the animation of a sequence  of GIF images within Netscape.
	End Rem
	Method animationDelay(_delay:Int)
		bmx_magick_image_animationdelay(imagePtr, _delay)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getAnimationDelay:Int() 
		Return bmx_magick_image_getanimationdelay(imagePtr)
	End Method
	
	Rem
	bbdoc: Sets the number of iterations to loop an animation (e.g. Netscape loop extension) for.
	End Rem
	Method animationIterations(iterations:Int)
		bmx_magick_image_animationiterations(imagePtr, iterations)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getAnimationIterations:Int()
		Return bmx_magick_image_getanimationiterations(imagePtr)
	End Method
	
	Rem
	bbdoc: Sets an arbitrary named image attribute. Any number of named attributes may be attached to the image.
	about: For example, the image comment is a named image attribute with the name "comment". EXIF tags are
	attached to the image as named attributes. Use the syntax "EXIF:<tag>" to request an EXIF tag similar
	to "EXIF:DateTime".
	End Rem
	Method attribute(name:String, value:String)
		bmx_magick_image_attribute(imagePtr, name, value)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getAttribute:String(name:String)
		Return bmx_magick_image_getattribute(imagePtr, name)
	End Method
	
	Rem
	bbdoc: Sets the image background color.
	End Rem
	Method backgroundColor(color:Object)
		If TMColor(color) Then
			bmx_magick_image_backgroundcolor(imagePtr, TMColor(color).colorPtr)
		ElseIf String(color)
			bmx_magick_image_backgroundcolortxt(imagePtr, String(color))
		End If
	End Method
	
	Method getBackgroundColor:TMColor()
		' TODO
	End Method
	
	Rem
	bbdoc: Sets the image file name to use as the background texture.
	about: Does not modify image pixels.
	End Rem
	Method backgroundTexture(backgroundTexture:String)
		bmx_magick_image_backgroundtexture(imagePtr, backgroundTexture)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getBackgroundTexture:String()
		Return bmx_magick_image_getbackgroundtexture(imagePtr)
	End Method
	
	Rem
	bbdoc: Gets the base image width (before transformations).
	End Rem
	Method getBaseColumns:Int()
		Return bmx_magick_image_getbasecolumns(imagePtr)
	End Method
	
	Rem
	bbdoc: Gets the base image filename (before transformations).
	End Rem
	Method getBaseFilename:String()
		Return bmx_magick_image_getbasefilename(imagePtr)
	End Method
	
	Rem
	bbdoc: Gets the base image height (before transformations).
	End Rem
	Method getBaseRows:Int()
		Return bmx_magick_image_getbaserows(imagePtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method borderColor(color:Object)
		If TMColor(color) Then
			bmx_magick_image_bordercolor(imagePtr, TMColor(color).colorPtr)
		ElseIf String(color)
			bmx_magick_image_bordercolortxt(imagePtr, String(color))
		End If
	End Method
	
	Method getBorderColor:TMColor()
	' TODO
	End Method

	Method getBoundingBox:TMGeometry()
	' TODO
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method boxColor(boxColor:Object)
		If TMColor(boxColor) Then
	' TODO
		ElseIf String(boxColor)
	' TODO
		End If
	End Method
	
	Method getBoxColor:TMColor()
	' TODO
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Function cacheThreshold(threshold:Int)
		bmx_magick_image_cachethreshold(threshold)
	End Function
	
	Rem
	bbdoc: Channel modulus depth.
	about: The channel modulus depth represents the minimum number of bits required to support the channel
	without loss. Setting the channel's modulus depth modifies the channel (i.e. discards resolution) if the
	requested modulus depth is less than the current modulus depth, otherwise the channel is not altered.
	There is no attribute associated with the modulus depth so the current modulus depth is obtained by
	inspecting the pixels. As a result, the depth returned may be less than the most recently set channel
	depth. Subsequent image processing may result in increasing the channel depth.
	End Rem
	Method channelDepth(channel:Int, depth:Int)
		bmx_magick_image_channeldepth(imagePtr, channel, depth)
	End Method
	
	Rem
	bbdoc: Returns the channel modulus depth.
	End Rem
	Method getChannelDepth:Int(channel:Int)
		Return bmx_magick_image_getchanneldepth(imagePtr, channel)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method chromaBluePrimary(x:Double, y:Double)
		bmx_magick_image_chromablueprimary(imagePtr, x, y)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getChromaBluePrimary(x:Double Var, y:Double Var)
		bmx_magick_image_getchromablueprimary(imagePtr, Varptr x, Varptr y)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method chromaGreenPrimary(x:Double, y:Double)
		bmx_magick_image_chromagreenprimary(imagePtr, x, y)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getChromaGreenPrimary(x:Double Var, y:Double Var)
		bmx_magick_image_getchromagreenprimary(imagePtr, Varptr x, Varptr y)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method chromaRedPrimary(x:Double, y:Double)
		bmx_magick_image_chromaredprimary(imagePtr, x, y)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getChromaRedPrimary(x:Double Var, y:Double Var)
		bmx_magick_image_getchromaredprimary(imagePtr, Varptr x, Varptr y)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method chromaWhitePoint(x:Double, y:Double)
		bmx_magick_image_chromawhitepoint(imagePtr, x, y)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getChromaWhitePoint(x:Double Var, y:Double Var)
		bmx_magick_image_getchromawhitepoint(imagePtr, Varptr x, Varptr y)
	End Method

	Rem
	bbdoc: 
	End Rem
	Method classType(class:Int)
		bmx_magick_image_classtype(imagePtr, class)
	End Method
	
	Method getClassType:Int()
	' TODO
	End Method
	
	Method clipMask(clipMask:TMImage)
	' TODO
	End Method
	
	Method getClipMask:TMImage()
	' TODO
	End Method
	
	Method colorFuzz(fuzz:Double)
		bmx_magick_image_colorfuzz(imagePtr, fuzz)
	End Method
	
	Method getColorFuzz:Double()
	' TODO
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method colorMap(index:Int, color:Object)
		If TMColor(color) Then
			bmx_magick_image_colormap(imagePtr, index, TMColor(color).colorPtr)
		ElseIf String(color)
			bmx_magick_image_colormaptxt(imagePtr, index, String(color))
		End If
	End Method
	
	Method getColorMap:TMColor(index:Int)
	' TODO
	End Method
	
	Method colorMapSize(entries:Int)
	' TODO
	End Method
	
	Method getColorMapSize:Int()
	' TODO
	End Method
	
	Method colorSpace(colorSpace:Int)
	' TODO
	End Method
	
	Method getColorSpace:Int()
	' TODO
	End Method
	
	Method getColumns:Int()
	' TODO
	End Method
	
	Method getComment:String()
	' TODO
	End Method

	Rem
	bbdoc: 
	End Rem
	Method compose(compose:Int)
		bmx_magick_image_compose(imagePtr, compose)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method getComposite:Int()
		Return bmx_magick_image_getcomposite(imagePtr)
	End Method
	
	Method compressType(_type:Int)
	' TODO
	End Method
	
	Method getCompressType:Int()
	' TODO
	End Method
	
	Method defineValue(magick:String, key:String, value:String)
	' TODO
	End Method
	
	Method getDefinedValue:String(magick:String, key:String)
	' TODO
	End Method
	
	Method defineSet(magick:String, key:String, flag:Int)
	' TODO
	End Method
	
	Method getDefinedSet:Int(magick:String, key:String)
	' TODO
	End Method
	
	Method density(geometry:Object)
	' TODO
	End Method
	
	Method getDensity:TMGeometry()
	' TODO
	End Method
	
	Method depth(depth:Int)
	' TODO
	End Method
	
	Method getDepth:Int()
	' TODO
	End Method
	
	Method directory:String()
	' TODO
	End Method
	
	Method endian(endian:Int)
	' TODO
	End Method
	
	Method getEndian:Int()
	' TODO
	End Method
	
	Method filename(filename:String)
	' TODO
	End Method
	
	Method getFilename:String()
	' TODO
	End Method
	
	Method FileSize:Int()
	' TODO
	End Method
	
	Method fillColor(color:Object)
	' TODO
	End Method
	
	Method getFillColor:TMColor()
	' TODO
	End Method
	
	Method fillRule(rule:Int)
	' TODO
	End Method
	
	Method getFillRule:Int()
	' TODO
	End Method
	
	Method fillPattern(pattern:TMImage)
	' TODO
	End Method
	
	Method getFillPattern:TMImage()
	' TODO
	End Method
	
	Method filterType(filterType:Int)
	' TODO
	End Method
	
	Method getFilterType:Int()
	' TODO
	End Method
	
	Method font(font:String)
	' TODO
	End Method
	
	Method getFont:String()
	' TODO
	End Method
	
	Method fontPointSize(pointSize:Double)
	' TODO
	End Method
	
	Method getFontPointSize:Double()
	' TODO
	End Method
	
	'Method fontTypeMetrics(text:String, metrics...)
	' TODO
	'End Method
	
	Method getFormat:String()
	' TODO
	End Method
	
	Method getGamma:Double()
	' TODO
	End Method
	
	Method getGeometry:TMGeometry()
	' TODO
	End Method
	
	Method gifDisposeMethod(disposeMethod:Int)
	' TODO
	End Method
	
	Method getGifDisposeMethod:Int()
	' TODO
	End Method
	
	Method iccColorProfile(profile:TMBlob)
	' TODO
	End Method
	
	Method getIccColorProfile:TMBlob()
	' TODO
	End Method
	
	Method interlaceType(interlace:Int)
	' TODO
	End Method
	
	Method getInterlaceType:Int()
	' TODO
	End Method
	
	Method iptcProfile(profile:TMBlob)
	' TODO
	End Method
	
	Method getIptcProfile:TMBlob()
	' TODO
	End Method
	
	Method isValid(isValid:Int)
	' TODO
	End Method
	
	Method getIsValid:Int()
	' TODO
	End Method
	
	Method getLabel:String()
	' TODO
	End Method
	
	Method lineWidth(width:Double)
	' TODO
	End Method
	
	Method GetLineWidth:Double()
	' TODO
	End Method
	
	Method magick(magick:String)
	' TODO
	End Method
	
	Method getMagick:String()
	' TODO
	End Method
	
	Method matte(matteFlag:Int)
	' TODO
	End Method
	
	Method getMatte:Int()
	' TODO
	End Method
	
	Method matteColor(color:Object)
	' TODO
	End Method
	
	Method getMatteColor:TMColor()
	' TODO
	End Method
	
	Method getMeanErrorPerPixel:Double()
	' TODO
	End Method
	
	Method modulusDepth(depth:Int)
	' TODO
	End Method
	
	Method getModulusDepth:Int()
	' TODO
	End Method

	Method monochrome(flag:Int)
	' TODO
	End Method
	
	Method getMonochrome:Int()
	' TODO
	End Method
	
	Method getNormalizedMaxError:Double()
	' TODO
	End Method
	
	Method getNormalizedMeanError:Double()
	' TODO
	End Method
	
	Method orientation(orientation:Int)
	' TODO
	End Method
	
	Method getOrientation:Int()
	' TODO
	End Method
	
	Method page(pageSize:Object)
	' TODO
	End Method
	
	Method getPage:TMGeometry()
	' TODO
	End Method
	
	Method penColor(color:Object)
	' TODO
	End Method
	
	Method getPenColor:TMColor()
	' TODO
	End Method
	
	Method penTexture(texture:TMImage)
	' TODO
	End Method
	
	Method getPenTexture:TMImage()
	' TODO
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method pixelColor(x:Int, y:Int, color:Object)
		If TMColor(color) Then
			bmx_magick_image_pixelcolor(imagePtr, x, y, TMColor(color).colorPtr)
		ElseIf String(color) Then
			bmx_magick_image_pixelcolortxt(imagePtr, x, y, String(color))
		End If
	End Method
	
	Method getPixelColor:TMColor(x:Int, y:Int)
	' TODO
	End Method
	
	Method profile(name:String, colorProfile:TMBlob)
	' TODO
	End Method
	
	Method getProfile:TMBlob(name:String)
	' TODO
	End Method
	
	Method quality(value:Int)
	' TODO
	End Method
	
	Method getQuality:Int()
	' TODO
	End Method
	
	Method quantizeColors(colors:Int)
	' TODO
	End Method

	Method getQuantizeColors:Int()
	' TODO
	End Method
	
	Method quantizeColorSpace(colorSpace:Int)
	' TODO
	End Method

	Method getQuantizeColorSpace:Int()
	' TODO
	End Method
	
	Method quantizeDither(flag:Int)
	' TODO
	End Method

	Method getQuantizeDither:Int()
	' TODO
	End Method
	
	Method quantizeTreeDepth(treeDepth:Int)
	' TODO
	End Method

	Method getQuantizeTreeDepth:Int()
	' TODO
	End Method
	
	Method renderingIntent(intent:Int)
	' TODO
	End Method
	
	Method getRenderingIntent:Int()
	' TODO
	End Method
	
	Method resolutionUnits(units:Int)
	' TODO
	End Method
	
	Method getResolutionUnits:Int()
	' TODO
	End Method
	
	Method getRows:Int()
	' TODO
	End Method
	
	Method scene(scene:Int)
	' TODO
	End Method
	
	Method getScene:Int()
	' TODO
	End Method
	
	Method getSignature:String(force:Int = False)
	' TODO
	End Method
	
	Rem
	bbdoc: Width and height of a raw image (an image which does not support width and height information).
	about: Size may also be used to affect the image size read from a multi-resolution format (e.g. Photo CD, JBIG, or JPEG.)
	End Rem
	Method size(geometry:Object)
		If TMGeometry(geometry) Then
			bmx_magick_image_size(imagePtr, TMGeometry(geometry).geometryPtr)
		Else If String(geometry) Then
			bmx_magick_image_sizetxt(imagePtr, String(geometry))
		End If
	End Method
	
	Method strokeAntiAlias(flag:Int)
	' TODO
	End Method
	
	Method getStrokeAntiAlias:Int()
	' TODO
	End Method
	
	Method strokeColor(color:Object)
		If TMColor(color) Then
			bmx_magick_image_strokecolor(imagePtr, TMColor(color).colorPtr)
		ElseIf String(color) Then
			bmx_magick_image_strokecolortxt(imagePtr, String(color))
		End If
	End Method
	
	Method getStrokeColor:TMColor()
	' TODO
	End Method
	
	Method strokeDashArray(array:Double[])
	' TODO
	End Method
	
	Method getStrokeDashArray:Double[]()
	' TODO
	End Method
	
	Method strokeDashOffset(offset:Double)
	' TODO
	End Method
	
	Method getStrokeDashOffset:Double()
	' TODO
	End Method
	
	Method strokeLineCap(lineCap:Int)
	' TODO
	End Method
	
	Method getStrokeLineCap:Int()
	' TODO
	End Method
	
	Method strokeLineJoin(lineJoin:Int)
	' TODO
	End Method
	
	Method getStrokeLineJoin:Int()
	' TODO
	End Method
	
	Method strokeMiterLimit(miterLimit:Int)
	' TODO
	End Method
	
	Method getStrokeMiterLimit:Int()
	' TODO
	End Method
	
	Method strokePattern(pattern:TMImage)
	' TODO
	End Method
	
	Method getStrokePattern:TMImage()
	' TODO
	End Method
	
	Method strokeWidth(width:Double)
	' TODO
	End Method
	
	Method getStrokeWidth:Double()
	' TODO
	End Method
	
	Method subImage(subImage:Int)
	' TODO
	End Method
	
	Method getSubImage:Int()
	' TODO
	End Method
	
	Method subRange(subRange:Int)
	' TODO
	End Method
	
	Method getSubRange:Int()
	' TODO
	End Method
	
	Method textEncoding(encoding:String)
	' TODO
	End Method
	
	Method getTextEncoding:String()
	' TODO
	End Method

	Method tileName(name:String)
	' TODO
	End Method
	
	Method getTileName:String()
	' TODO
	End Method
	
	Method getTotalColors:Int()
	' TODO
	End Method
	
	Method transformOrigin(x:Double, y:Double)
	' TODO
	End Method
	
	Method transformRotation(angle:Double)
	' TODO
	End Method
	
	Method transformReset()
	' TODO
	End Method
	
	Method transformScale(sx:Double, sy:Double)
	' TODO
	End Method
	
	Method transformSkewX(skew:Double)
	' TODO
	End Method
	
	Method transformSkewY(skew:Double)
	' TODO
	End Method
	
	Method getType:Int()
	' TODO
	End Method
	
	Method getXResolution:Double()
	' TODO
	End Method
	
	Method getYResolution:Double()
	' TODO
	End Method
	
End Type

Rem
bbdoc: 
End Rem
Type TMGeometry

	Field geometryPtr:Byte Ptr
	
	Function _create:TMGeometry(geometryPtr:Byte Ptr)
		If geometryPtr Then
			Local this:TMGeometry = New TMGeometry
			this.geometryPtr = geometryPtr
			Return this
		End If
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Method Create:TMGeometry(geometry:String)
	' TODO
	End Method
	
	Method CreateAttr:TMGeometry(width:Int, height:Int, xOffset:Int = 0, yOffset:Int = 0, xNegative:Int = False, yNegative:Int = False)
	' TODO
	End Method
	
	Method setWidth(width:Int)
	' TODO
	End Method
	
	Method getWidth:Int()
	' TODO
	End Method
	
	Method setHeight(height:Int)
	' TODO
	End Method
	
	Method getHeight:Int()
	' TODO
	End Method
	
	Method setXOffset(offset:Int)
	' TODO
	End Method
	
	Method getXOffset:Int()
	' TODO
	End Method
	
	Method setYOffset(offset:Int)
	' TODO
	End Method
	
	Method getYOffset:Int()
	' TODO
	End Method
	
	Method setXNegative(value:Int)
	' TODO
	End Method
	
	Method isXNegative:Int()
	' TODO
	End Method
	
	Method setYNegative(value:Int)
	' TODO
	End Method
	
	Method isYNegative:Int()
	' TODO
	End Method
	
	Method setPercent(value:Int)
	' TODO
	End Method
	
	Method getPercent:Int()
	' TODO
	End Method
	
	Method setAspect(value:Int)
	' TODO
	End Method
	
	Method getAspect:Int()
	' TODO
	End Method
	
	Method setGreater(value:Int)
	' TODO
	End Method
	
	Method getGreater:Int()
	' TODO
	End Method
	
	Method setLess(value:Int)
	' TODO
	End Method
	
	Method getLess:Int()
	' TODO
	End Method
	
	Method setIsValid(value:Int)
	' TODO
	End Method
	
	Method isValid:Int()
	' TODO
	End Method

	Method toString:String()
	' TODO
	End Method
	
End Type

Rem
bbdoc: 
End Rem
Type TMColor

	Field colorPtr:Byte Ptr


End Type

Rem
bbdoc: 
End Rem
Type TMDrawable

	Field drawablePtr:Byte Ptr
	
End Type

Rem
bbdoc: 
End Rem
Type TMDrawableAffine Extends TMDrawable

	Method Create:TMDrawableAffine(sx:Double = 1.0, sy:Double = 1.0, rx:Double = 0, ry:Double = 0, tx:Double = 0, ty:Double = 0)
	End Method
	
End Type

Type TMDrawableAngle Extends TMDrawable

	Method Create:TMDrawableAngle(angle:Double)
	End Method
	
End Type

Type TMDrawableArc Extends TMDrawable

	Method Create:TMDrawableArc(startX:Double, startY:Double, endX:Double, endY:Double, startDegrees:Double, endDegrees:Double)
	End Method
	
End Type

Type TMDrawableBezier Extends TMDrawable

	Method Create:TMDrawableBezier()
	End Method
	
End Type

Type TMDrawableClipPath Extends TMDrawable

	Method Create:TMDrawableClipPath(id:String)
	End Method
	
End Type

Type TMDrawableCircle Extends TMDrawable

	Method Create:TMDrawableCircle(originX:Double, originY:Double, perimX:Double, perimY:Double)
	End Method
	
End Type

Rem
bbdoc: Color image according to paintMethod.
about: The point method recolors the target pixel.  The replace method recolors any pixel that matches
the color of the target pixel.  Floodfill recolors any pixel that matches the color of the target pixel
and is a neighbor,  whereas filltoborder recolors any neighbor pixel that is not the border color. Finally,
reset recolors all pixels.
End Rem
Type TMDrawableColor Extends TMDrawable

	Method Create:TMDrawableColor(x:Double, y:Double, paintMethod:Int)
	End Method
	
End Type

Type TMDrawableCompositeImage Extends TMDrawable

	Method Create:TMDrawableCompositeImage()
	End Method
	
End Type

Type TMDrawableDashArray Extends TMDrawable

	Method Create:TMDrawableDashArray()
	End Method
	
End Type

Type TMDrawableDashOffset Extends TMDrawable

	Method Create:TMDrawableDashOffset()
	End Method
	
End Type

Type TMDrawableEllipse Extends TMDrawable

	Method Create:TMDrawableEllipse(originX:Double, originY:Double, radiusX:Double, radiusY:Double, arcStart:Double, arcEnd:Double)
	End Method
	
End Type

Type TMDrawableFillColor Extends TMDrawable

	Method Create:TMDrawableFillColor(color:TMColor)
	End Method
	
End Type

Type TMDrawableFillRule Extends TMDrawable

	Method Create:TMDrawableFillRule(fillRule:Int)
	End Method
	
End Type

Type TMDrawableFillOpacity Extends TMDrawable

	Method Create:TMDrawableFillOpacity(opacity:Double)
	End Method
	
End Type

Rem
bbdoc: 
End Rem
Type TMDrawableFont Extends TMDrawable

	Rem
	bbdoc: 
	End Rem
	Method Create:TMDrawableFont(font:String)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CreateWithAttributes:TMDrawableFont(family:String, style:Int, weight:Int, stretch:Int)
	End Method
	
End Type

Rem
bbdoc: 
End Rem
Type TMDrawableGravity Extends TMDrawable

	Method Create:TMDrawableGravity(gravity:Int)
	End Method
	
End Type

Rem
bbdoc: 
End Rem
Type TMDrawableLine Extends TMDrawable

	Method Create:TMDrawableLine(startX:Double, startY:Double, endX:Double, endY:Double)
	End Method
	
End Type

Rem
bbdoc: 
End Rem
Type TMDrawableMatte Extends TMDrawable

	Method Create:TMDrawableMatte(x:Double, y:Double, paintMethod:Int)
	End Method
	
End Type

Type TMDrawableMiterLimit Extends TMDrawable

	Method Create:TMDrawableMiterLimit(miterLimit:Int)
	End Method
	
End Type

Type TMDrawablePath Extends TMDrawable

	Method Create:TMDrawablePath()
	End Method
	
End Type

Rem
bbdoc: 
End Rem
Type TMBlob

	Field blobPtr:Byte Ptr

	Method New()
		If Not _magick_initialized Then
			_init_magick()
		End If
	End Method
	
	Function CreateFromData:TMBlob(data:Byte Ptr, size:Int)
		Local this:TMBlob = New TMBlob
		this.blobPtr = bmx_magick_blob_createfromdata(data, size)
		Return this
	End Function

End Type

Rem
bbdoc: Obtains information about the image formats supported by GraphicsMagick.
End Rem
Function coderInfoList:TList(isReadable:Int = TMCoderInfo.AnyMatch, isWritable:Int = TMCoderInfo.AnyMatch, isMultiFrame:Int = TMCoderInfo.AnyMatch)
	Local list:TList = New TList
	bmx_magick_coderinfolist(list, isReadable, isWritable, isMultiFrame)
	Return list
End Function

Rem
bbdoc: The TMCoderInfo type provides the means to provide information regarding GraphicsMagick support for an image format (designated by a magick string).
about: It may be used to provide support for a specific named format (provided as an argument to the
constructor), or as an element of a TList when format support is queried using the coderInfoList() function.
End Rem
Type TMCoderInfo

	Rem
	bbdoc: match any coder
	End Rem
	Const AnyMatch:Int = 0
	Rem
	bbdoc: match coder if true
	End Rem
	Const TrueMatch:Int = 1
	Rem
	bbdoc: match coder if false
	End Rem
	Const FalseMatch:Int = 2

	Rem
	bbdoc: Format name (e.g. "GIF").
	End Rem
	Field name:String
	Rem
	bbdoc: Format description (e.g. "CompuServe graphics interchange format").
	End Rem
	Field description:String
	Rem
	bbdoc: Format is readable.
	End Rem
	Field isReadable:Int
	Rem
	bbdoc: Format is writeable.
	End Rem
	Field isWritable:Int
	Rem
	bbdoc: Format supports multiple frames.
	End Rem
	Field isMultiFrame:Int
	
	Function _create:TMCoderInfo(name:String, description:String, isReadable:Int, isWritable:Int, isMultiFrame:Int)
		Local this:TMCoderInfo = New TMCoderInfo
		this.name = name
		this.description = description
		this.isReadable = isReadable
		this.isWritable = isWritable
		this.isMultiFrame = isMultiFrame
		Return this
	End Function
	
	Function _addToList(list:TList, coderInfo:TMCoderInfo)
		list.AddLast(coderInfo)
	End Function

	Rem
	bbdoc: 
	End Rem
	Function info:TMCoderInfo(format:String)
	End Function
	
End Type


' our pixmap loader :-)
Type TPixmapLoaderM Extends TPixmapLoader

	Method New()
	End Method

	Method LoadPixmap:TPixmap( stream:TStream )

		Local image:TMImage = TMImage.CreateFromStream(stream)

		If image Then
			Return image.GetPixmap()
		End If

		Return Null
	End Method
	
End Type


New TPixmapLoaderM
