SuperStrict

Framework BaH.OpenCL
Import BRL.StandardIO

Local devices:TCLDevice[] = TCLPlatform.GetDevices()

Print "~n"
Print "Device Count = " + devices.length
Print "~n"

For Local i:Int = 0 Until devices.length

	Local info:TCLDeviceInfo = devices[i].GetInfo()
	
	Print "OpenCL Device information :"
	
	Print "    deviceType               : " + GetDeviceType(devices[i].deviceType)

	Print "    vendorName               : " + info.vendorName
	Print "    deviceName               : " + info.deviceName
	Print "    driverVersion            : " + info.driverVersion
	Print "    deviceVersion            : " + info.deviceVersion
	Print "    maxComputeUnits          : " + info.maxComputeUnits
	Print "    maxWorkItemDimensions    : " + info.maxWorkItemDimensions
	
	Local s:String = "("
	For Local n:Int = 0 Until info.maxWorkItemSizes.length
		If n Then
			s:+ ", "
		End If
		s:+ info.maxWorkItemSizes[n]
	Next
	
	Print "    maxWorkItemSizes         : " + s + ")"
	Print "    maxWorkGroupSize         : " + info.maxWorkGroupSize
	Print "    maxClockFrequency        : " + info.maxClockFrequency
	Print "    maxMemAllocSize          : " + info.maxMemAllocSize
	Print "    imageSupport             : " + info.imageSupport
	Print "    maxReadImageArgs         : " + info.maxReadImageArgs
	Print "    maxWriteImageArgs        : " + info.maxWriteImageArgs
	Print "    image2dMaxWidth          : " + info.image2dMaxWidth
	Print "    image2dMaxHeight         : " + info.image2dMaxHeight
	Print "    image3dMaxWidth          : " + info.image3dMaxWidth
	Print "    image3dMaxHeight         : " + info.image3dMaxHeight
	Print "    image3dMaxDepth          : " + info.image3dMaxDepth
	Print "    maxSamplers              : " + info.maxSamplers
	Print "    maxParameterSize         : " + info.maxParameterSize
	Print "    globalMemCacheSize       : " + info.globalMemCacheSize
	Print "    globalMemSize            : " + info.globalMemSize
	Print "    maxConstantBufferSize    : " + info.maxConstantBufferSize
	Print "    maxConstantArgs          : " + info.maxConstantArgs
	Print "    localMemSize             : " + info.localMemSize
	Print "    errorCorrectionSupport   : " + info.errorCorrectionSupport
	Print "    profilingTimerResolution : " + info.profilingTimerResolution
	Print "    endianLittle             : " + info.endianLittle
	Print "    profile                  : " + info.profile
	
	Local extensions:String[] = info.extensions.Split(" ")
	
	Print "    extensions               : " + extensions[0]
	For Local n:Int = 1 Until extensions.length
		Print "                               " + extensions[n]
	Next
	
	Print "~n~n"
Next

End

Function GetDeviceType:String(deviceType:Int)
	Select deviceType
		Case CL_DEVICE_TYPE_DEFAULT
			Return "CL_DEVICE_TYPE_DEFAULT"
		Case CL_DEVICE_TYPE_CPU
			Return "CL_DEVICE_TYPE_CPU"
		Case CL_DEVICE_TYPE_GPU
			Return "CL_DEVICE_TYPE_GPU"
		Case CL_DEVICE_TYPE_ACCELERATOR
			Return "CL_DEVICE_TYPE_ACCELERATOR"
		Case CL_DEVICE_TYPE_ALL
			Return "CL_DEVICE_TYPE_ALL"
	End Select
End Function

