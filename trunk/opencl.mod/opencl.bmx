' Copyright (c) 2009 Bruce A Henderson
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
bbdoc: 
End Rem
Module BaH.OpenCL

ModuleInfo "Version: 1.00"
ModuleInfo "Author: Bruce A Henderson"
ModuleInfo "License: MIT"
ModuleInfo "Copyright: (opencl) 2008-2009 The Khronos Group Inc."
ModuleInfo "Copyright: (wrapper) 2009 Bruce A Henderson"

ModuleInfo "History: 1.00 Initial Release"

?win32
ModuleInfo "LD_OPTS: -L%PWD%/lib/win32"
?

Import "common.bmx"


Extern
	Function bmx_ocl_platform_getdevices:TCLDevice[](deviceType:Int)
End Extern

Rem
bbdoc: The platform allows the host program to discover OpenCL devices and their capabilities and to create contexts.
End Rem
Type TCLPlatform

	Field platformPtr:Byte Ptr
	Field device:TCLDevice
	
	Rem
	bbdoc: Initialises the platform using the specified device.
	End Rem
	Function InitPlatform:TCLPlatform(device:TCLDevice)
		Local this:TCLPlatform = New TCLPlatform
		this.platformPtr = bmx_ocl_platform_init(this, device.devicePtr)
		this.device = device
		Return this
	End Function
	
	Rem
	bbdoc: Initialises the platform using a given device type.
	about: If @deviceType refers to more than one device, the first available device is used.
	<p>
	@deviceType is a bitfield that identifies the type of OpenCL device. The valid values for @deviceType are, 
	#CL_DEVICE_TYPE_CPU, #CL_DEVICE_TYPE_GPU, #CL_DEVICE_TYPE_ACCELERATOR, #CL_DEVICE_TYPE_DEFAULT and #CL_DEVICE_TYPE_ALL.
	</p>
	End Rem
	Function InitDevice:TCLPlatform(deviceType:Int)
		Local devices:TCLDevice[] = GetDevices(deviceType)
		If devices.length > 0 Then
			Local device:TCLDevice = devices[0]
	
			Local this:TCLPlatform = New TCLPlatform
			this.platformPtr = bmx_ocl_platform_init(this, device.devicePtr)
			this.device = device
			Return this
		End If
	End Function
	
	Rem
	bbdoc: Returns the list of devices available on the platform.
	about: @deviceType is a bitfield that identifies the type of OpenCL device.
	The @deviceType can be used to query specific OpenCL devices or all OpenCL devices available. The valid values for @deviceType are, 
	#CL_DEVICE_TYPE_CPU, #CL_DEVICE_TYPE_GPU, #CL_DEVICE_TYPE_ACCELERATOR, #CL_DEVICE_TYPE_DEFAULT and #CL_DEVICE_TYPE_ALL.
	End Rem
	Function GetDevices:TCLDevice[](deviceType:Int = CL_DEVICE_TYPE_ALL)
		Return bmx_ocl_platform_getdevices(deviceType)
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Method LoadProgram:TCLProgram(source:Object)
		Local text:String
		If String(source) Then
			text = String(source)
		Else If TStream(source) Then
			text = LoadString(source)
		End If
		
		Return TCLProgram.Load(Self, text) 
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CreateBuffer:TCLBuffer(flags:Int, size:Int, hostPtr:Byte Ptr = Null)
		Return TCLBuffer.Create(Self, flags, size, hostPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CreateImage2D:TCLImage(flags:Int, channelOrder:Int, imageType:Int, width:Int, height:Int, rowPitch:Int, hostPtr:Byte Ptr)
		Return TCLImage.Create2D(Self, flags, channelOrder, imageType, width, height, rowPitch, hostPtr)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CreateImage3D:TCLImage(flags:Int, channelOrder:Int, imageType:Int, width:Int, height:Int, depth:Int, rowPitch:Int, slicePitch:Int, hostPtr:Byte Ptr)
		Return TCLImage.Create3D(Self, flags, channelOrder, imageType, width, height, depth, rowPitch, slicePitch, hostPtr)
	End Method
	
	Rem
	bbdoc: Issues all previously queued OpenCL commands in the queue to the device.
	returns: CL_SUCCESS if the call was executed successfully. It returns CL_INVALID_COMMAND_QUEUE if queue is not a valid command-queue and returns CL_OUT_OF_HOST_MEMORY if there is a failure to allocate resources required by the OpenCL implementation on the host.
	about: Flush only guarantees that all queued commands to to the queue get issued to the appropriate device.
	There is no guarantee that they will be complete after Flush returns.
	<p>
	Any blocking commands queued in a command-queue such as EnqueueRead{Image|Buffer} with blockingRead set to TRUE, EnqueueWrite{Image|Buffer} with
	blockingWrite set to True, EnqueueMap{Buffer|Image} with blockingMap set to True or WaitForEvents perform an implicit flush of the command-queue.
	</p>
	<p>
	To use event objects that refer to commands enqueued in a command-queue as event objects to wait on by commands enqueued in a different
	command-queue, the application must call a Flush or any blocking commands that perform an implicit flush of the command-queue where the
	commands that refer to these event objects are enqueued.
	</p>
	End Rem
	Method Flush()
		bmx_ocl_platform_flush(platformPtr)
	End Method
	
	Rem
	bbdoc: Blocks until all previously queued OpenCL commands in the queue are issued to the associated device and have completed.
	returns: CL_SUCCESS if the call was executed successfully.	It returns CL_INVALID_COMMAND_QUEUE if the queue is not a valid command-queue and returns CL_OUT_OF_HOST_MEMORY if there is a failure to allocate resources required by the OpenCL implementation on the host.
	about: Finish does not return until all queued commands in the queue have been processed and completed. Finish is also a synchronization point.
	End Rem
	Method Finish()
		bmx_ocl_platform_finish(platformPtr)
	End Method
	
End Type

Rem
bbdoc: 
End Rem
Type TCLDevice

	Field devicePtr:Byte Ptr
	Field deviceType:Int
	
	Function _create:TCLDevice(devicePtr:Byte Ptr)
		If devicePtr Then
			Local this:TCLDevice = New TCLDevice
			this.devicePtr = devicePtr
			Return this
		End If
	End Function
	
	Function _newDeviceList:TCLDevice[](count:Int)
		Return New TCLDevice[count]
	End Function
	
	Function _setDevice:TCLDevice(list:TCLDevice[], index:Int, devicePtr:Byte Ptr, deviceType:Int)
		Local device:TCLDevice = _create(devicePtr)
		device.deviceType = deviceType
		list[index] = device
		Return device
	End Function

	Rem
	bbdoc: 
	End Rem
	Method GetInfo:TCLDeviceInfo()
		Return TCLDeviceInfo(bmx_ocl_device_getinfo(devicePtr))
	End Method

	Method Delete()
		If devicePtr Then
			bmx_ocl_device_free(devicePtr)
			devicePtr = Null
		End If
	End Method
	
End Type

Rem
bbdoc: Device information
End Rem
Type TCLDeviceInfo

	Rem
	bbdoc: Vendor name.
	End Rem
	Field vendorName:String
	Rem
	bbdoc: Device name.
	End Rem
	Field deviceName:String
	Rem
	bbdoc: OpenCL software driver version in the form major_number.minor_number.
	End Rem
	Field driverVersion:String
	Rem
	bbdoc: OpenCL version.
	about: Returns the OpenCL version supported by the device.
	This version string has the following format:
	</pre>
	OpenCL&lt;space&gt;&lt;major_version.min or_version&gt;&lt;space&gt;&lt;vendor-specific information&gt;
	</pre>
	The major_version.minor_version value returned will be 1.0.
	End Rem
	Field deviceVersion:String
	Rem
	bbdoc: The number of parallel compute cores on the OpenCL device.
	about: The minimum value is 1.
	End Rem
	Field maxComputeUnits:Int
	Rem
	bbdoc: Maximum dimensions that specify the global and local work-item IDs used by the data parallel execution model.
	about: (Refer to clEnqueueNDRangeKernel). The minimum value is 3.
	End Rem
	Field maxWorkItemDimensions:Int
	Rem
	bbdoc: Maximum number of work-items that can be specified in each dimension of the work-group to clEnqueueNDRangeKernel.
	about: Returns @n entries, where @n equals the value of #maxWorkItemDimensions.
	The minimum value is (1, 1, 1).
	End Rem
	Field maxWorkItemSizes:Int[]
	Rem
	bbdoc: Maximum number of work-items in a work-group executing a kernel using the data parallel execution model.
	End Rem
	Field maxWorkGroupSize:Int
	Rem
	bbdoc: Maximum configured clock frequency of the device in MHz.
	End Rem
	Field maxClockFrequency:Int
	Rem
	bbdoc: Max size of memory object allocation in bytes.
	about: The minimum value is max (1/4th of #globalMemSize , 128*1024*1024)
	End Rem
	Field maxMemAllocSize:Long
	Rem
	bbdoc: Is True if images are supported by the OpenCL device and False otherwise.
	End Rem
	Field imageSupport:Int
	Rem
	bbdoc: Max number of simultaneous image objects that can be read by a kernel.
	about: The minimum value is 128 if #imageSupport is True.
	End Rem
	Field maxReadImageArgs:Int
	Rem
	bbdoc: Max number of simultaneous image objects that can be written to by a kernel.
	about: The minimum value is 8 if #imageSupport is True.
	End Rem
	Field maxWriteImageArgs:Int
	Rem
	bbdoc: Max width of 2D image in pixels.
	about: The minimum value is 8192 if #imageSupport is True.
	End Rem
	Field image2dMaxWidth:Int
	Rem
	bbdoc: Max height of 2D image in pixels.
	about: The minimum value is 8192 if #imageSupport is True.
	End Rem
	Field image2dMaxHeight:Int
	Rem
	bbdoc: Max width of 3D image in pixels.
	about: The minimum value is 2048 if #imageSupport is True.
	End Rem
	Field image3dMaxWidth:Int
	Rem
	bbdoc: Max height of 3D image in pixels.
	about: The minimum value is 2048 if #imageSupport is True.
	End Rem
	Field image3dMaxHeight:Int
	Rem
	bbdoc: Max depth of 3D image in pixels.
	about: The minimum value is 2048 if #imageSupport is True.
	End Rem
	Field image3dMaxDepth:Int
	Rem
	bbdoc: Maximum number of samplers that can be used in a kernel.
	about: Refer to section 6.11.8 for a detailed description on samplers. The minimum value is 16 if #imageSupport is True.
	End Rem
	Field maxSamplers:Int
	Rem
	bbdoc: Max size in bytes of the arguments that can be passed to a kernel.
	about: The minimum value is 256.
	End Rem
	Field maxParameterSize:Int
	Rem
	bbdoc: Size of global memory cache in bytes.
	End Rem
	Field globalMemCacheSize:Long
	Rem
	bbdoc: Size of global device memory in bytes.
	End Rem
	Field globalMemSize:Long
	Rem
	bbdoc: Max size in bytes of a constant buffer allocation.
	about: The minimum value is 64 KB.
	End Rem
	Field maxConstantBufferSize:Long
	Rem
	bbdoc: Max number of arguments declared with the __constant qualifier in a kernel.
	about: The minimum value is 8.
	End Rem
	Field maxConstantArgs:Int
	Rem
	bbdoc: Size of local memory arena in bytes.
	about: The minimum value is 16 KB.
	End Rem
	Field localMemSize:Int
	Rem
	bbdoc: Is True if the device implements error correction for the memories, caches, registers etc. in the device.
	about: Is False if the device does not implement error correction. This can be a requirement for certain clients of OpenCL.
	End Rem
	Field errorCorrectionSupport:Int
	Rem
	bbdoc: Describes the resolution of device timer.
	about: This is measured in nanoseconds.
	End Rem
	Field profilingTimerResolution:Int
	Rem
	bbdoc: Is True if the OpenCL device is a little endian device and False otherwise.
	End Rem
	Field endianLittle:Int
	Rem
	bbdoc: OpenCL profile.
	about: Returns the profile name supported by the device. The profile name returned can be one of the following strings:
	<ul>
	<li>FULL_PROFILE – if the device supports the OpenCL specification (functionality defined as part of the core specification and
	does not require any extensions to be supported).</li>
	<li>EMBEDDED_PROFILE - if the device supports the OpenCL embedded profile.</li>
	</ul>
	End Rem
	Field profile:String
	Rem
	bbdoc: Returns a space separated list of extension names (the extension names themselves do not contain any spaces).
	about: The list of extension names returned currently can include one or more of the following approved extension names:
	<ul>
	<li>cl_khr_fp64</li>
	<li>cl_khr_select_fprounding_mode</li>
	<li>cl_khr_global_int32_base_atomics</li>
	<li>cl_khr_global_int32_extended_atomics</li>
	<li>cl_khr_local_int32_base_atomics</li>
	<li>cl_khr_local_int32_extended_atomics</li>
	<li>cl_khr_int64_base_atomics</li>
	<li>cl_khr_int64_extended_atomics</li>
	<li>cl_khr_3d_image_writes</li>
	<li>cl_khr_byte_addressable_store</li>
	<li>cl_khr_fp16</li>
	<li>cl_khr_gl_sharing</li>
	</ul>
	End Rem
	Field extensions:String

	Function _create:TCLDeviceInfo(vendorName:String, deviceName:String, driverVersion:String, deviceVersion:String, ..
			maxComputeUnits:Int, maxWorkItemDimensions:Int, maxWorkItemSizes:Int[], maxWorkGroupSize:Int, maxClockFrequency:Int, ..
			maxMemAllocSize:Long, imageSupport:Int, maxReadImageArgs:Int, maxWriteImageArgs:Int, image2dMaxWidth:Int, ..
			image2dMaxHeight:Int, image3dMaxWidth:Int, image3dMaxHeight:Int, image3dMaxDepth:Int, maxSamplers:Int, maxParameterSize:Int, ..
			globalMemCacheSize:Long, globalMemSize:Long, maxConstantBufferSize:Long, maxConstantArgs:Int, localMemSize:Int, ..
			errorCorrectionSupport:Int, profilingTimerResolution:Int, endianLittle:Int, profile:String, extensions:String )

		Local this:TCLDeviceInfo = New TCLDeviceInfo
		this.vendorName = vendorName
		this.deviceName = deviceName
		this.driverVersion = driverVersion
		this.deviceVersion = deviceVersion
		this.maxComputeUnits = maxComputeUnits
		this.maxWorkItemDimensions = maxWorkItemDimensions
		this.maxWorkItemSizes = maxWorkItemSizes
		this.maxWorkGroupSize = maxWorkGroupSize
		this.maxClockFrequency = maxClockFrequency
		this.maxMemAllocSize = maxMemAllocSize
		this.imageSupport = imageSupport
		this.maxReadImageArgs = maxReadImageArgs
		this.maxWriteImageArgs = maxWriteImageArgs
		this.image2dMaxWidth = image2dMaxWidth
		this.image2dMaxHeight = image2dMaxHeight
		this.image3dMaxWidth = image3dMaxWidth
		this.image3dMaxHeight = image3dMaxHeight
		this.image3dMaxDepth = image3dMaxDepth
		this.maxSamplers = maxSamplers
		this.maxParameterSize = maxParameterSize
		this.globalMemCacheSize = globalMemCacheSize
		this.globalMemSize = globalMemSize
		this.maxConstantBufferSize = maxConstantBufferSize
		this.maxConstantArgs = maxConstantArgs
		this.localMemSize = localMemSize
		this.errorCorrectionSupport = errorCorrectionSupport
		this.profilingTimerResolution = profilingTimerResolution
		this.endianLittle = endianLittle
		this.profile = profile
		this.extensions = extensions

		Return this
	End Function	

End Type


Rem
bbdoc: A kernel is a function declared in a program.
about: A kernel is identified by the __kernel qualifier applied to any function in a program. A kernel object encapsulates the specific __kernel
function declared in a program and the argument values to be used when executing this __kernel function.
End Rem
Type TCLKernel

	Field kernelPtr:Byte Ptr
	Field program:TCLProgram
	
	Function Load:TCLKernel(name:String, program:TCLProgram)
		Local this:TCLKernel = New TCLKernel
		this.kernelPtr = bmx_ocl_kernel_create(this, name, program.programPtr)
		this.program = program
		Return this
	End Function

	Rem
	bbdoc: 
	End Rem
	Method SetArg:Int(index:Int, mem:TCLMem)
		If TCLBuffer(mem)
			Return bmx_ocl_kernel_setargbuffer(kernelPtr, index, mem.memPtr)
		Else
			'Return bmx_ocl_kernel_setargimage(kernelPtr, index, buffer.memPtr)
		End If
	End Method
	
	Method SetArgInt:Int(index:Int, value:Int)
	' TODO
	End Method
	
	Method SetArgFloat:Int(index:Int, value:Float)
	' TODO
	End Method
	
	Method SetArgLong:Int(index:Int, value:Long)
	' TODO
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method Execute:Int(workDim:Int, globalWorkSize:Int, localWorkSize:Int = 0)
		Return bmx_ocl_kernel_execute(kernelPtr, workDim, globalWorkSize, localWorkSize)
	End Method
	
End Type

Rem
bbdoc: 
End Rem
Type TCLProgram

	Field programPtr:Byte Ptr
	Field platform:TCLPlatform

	' private
	Function Load:TCLProgram(platform:TCLPlatform, text:String)
		Local this:TCLProgram = New TCLProgram
		this.programPtr = bmx_ocl_program_create(this, platform.platformPtr, text)
		this.platform = platform
		
		Return this
	End Function
	
	Rem
	bbdoc: 
	End Rem
	Method LoadKernel:TCLKernel(name:String)
		Return TCLKernel.Load(name, Self)
	End Method

	Method Delete()
		If programPtr Then
			bmx_ocl_program_free(programPtr)
			programPtr = Null
		End If
	End Method
	
End Type

Type TCLMem

	Field memPtr:Byte Ptr
	
End Type

Rem
bbdoc: 
End Rem
Type TCLBuffer Extends TCLMem

	' private
	Function Create:TCLBuffer(platform:TCLPlatform, flags:Int, size:Int, data:Byte Ptr)
		Local this:TCLBuffer = New TCLBuffer
		
		If data Then
			this.memPtr = bmx_ocl_membuff_create(this, platform.platformPtr, flags, size, data)
		Else
			this.memPtr = bmx_ocl_membuff_create(this, platform.platformPtr, flags, size, Null)
		End If
		
		Return this
	End Function

	Rem
	bbdoc: Enqueues commands to write to the buffer object from host memory.
	End Rem
	Method Write:Int(size:Int, data:Byte Ptr, blockingWrite:Int = True)
		Return bmx_ocl_membuff_enqueuewrite(memPtr, blockingWrite, size, data)
	End Method
	
	Rem
	bbdoc: Enqueues commands to read from the buffer object to host memory.
	End Rem
	Method Read:Int(size:Int, data:Byte Ptr, blockingRead:Int = True)
		Return bmx_ocl_membuff_enqueueread(memPtr, blockingRead, size, data)
	End Method
	
	Rem
	bbdoc: Enqueues a command to copy the buffer object to another buffer object.
	End Rem
	Method Copy:Int(dest:TCLBuffer, offset:Int, destOffset:Int, size:Int)
		Return bmx_ocl_membuff_enqueuecopy(memPtr, dest.memPtr, offset, destOffset, size)
	End Method
	
	Rem
	bbdoc: 
	End Rem
	Method CopyToImage:Int(dest:TCLImage, offset:Int, destOrigin:Int[], destregion:Int[])
	End Method
	
End Type

Rem
bbdoc: 
End Rem
Type TCLImage Extends TCLMem

	' private
	Function Create2D:TCLImage(platform:TCLPlatform, flags:Int, channelOrder:Int, imageType:Int, width:Int, height:Int, rowPitch:Int, hostPtr:Byte Ptr)
		Local this:TCLImage = New TCLImage
		
		If hostPtr Then
			this.memPtr = bmx_ocl_memimage_create2d(this, platform.platformPtr, flags, channelOrder, imageType, width, height, rowPitch, hostPtr)
		Else
			this.memPtr = bmx_ocl_memimage_create2d(this, platform.platformPtr, flags, channelOrder, imageType, width, height, rowPitch, Null)
		End If
		
		Return this
	End Function

	' private
	Function Create3D:TCLImage(platform:TCLPlatform, flags:Int, channelOrder:Int, imageType:Int, width:Int, height:Int, depth:Int, rowPitch:Int, slicePitch:Int, hostPtr:Byte Ptr)
		Local this:TCLImage = New TCLImage
		
		If hostPtr Then
			this.memPtr = bmx_ocl_memimage_create3d(this, platform.platformPtr, flags, channelOrder, imageType, width, height, depth, rowPitch, slicePitch, hostPtr)
		Else
			this.memPtr = bmx_ocl_memimage_create3d(this, platform.platformPtr, flags, channelOrder, imageType, width, height, depth, rowPitch, slicePitch, Null)
		End If
		
		Return this
	End Function

	Method Read:Int(blockingRead:Int, originX:Int, originY:Int, originZ:Int = 0, regionX:Int, regionY:Int, regionZ:Int = 1, rowPitch:Int, slicePitch:Int = 0, data:Byte Ptr)
		Return bmx_ocl_memimage_enqueueread(memPtr, blockingRead, originX, originY, originZ, regionX, regionY, regionZ, rowPitch, slicePitch, data)
	End Method
	
	Method Write:Int(blockingWrite:Int, originX:Int, originY:Int, originZ:Int = 0, regionX:Int, regionY:Int, regionZ:Int = 1, rowPitch:Int, slicePitch:Int = 0, data:Byte Ptr)
		Return bmx_ocl_memimage_enqueuewrite(memPtr, blockingWrite, originX, originY, originZ, regionX, regionY, regionZ, rowPitch, slicePitch, data)
	End Method
	
	Method Copy:Int(dest:TCLImage, originX:Int, originY:Int, originZ:Int = 0, destOriginX:Int, destOriginY:Int, destOriginZ:Int = 0, regionX:Int, regionY:Int, regionZ:Int = 1, rowPitch:Int, slicePitch:Int = 0)
	End Method
	
	Method CopyToBuffer:Int()
	End Method

End Type


