' Copyright (c) 2009 Bruce A Henderson
' All rights reserved.
'
' Redistribution and use in source and binary forms, with or without
' modification, are permitted provided that the following conditions are met:
'     * Redistributions of source code must retain the above copyright
'       notice, this list of conditions and the following disclaimer.
'     * Redistributions in binary form must reproduce the above copyright
'       notice, this list of conditions and the following disclaimer in the
'       documentation and/or other materials provided with the distribution.
'     * Neither the name of Bruce A Henderson nor the
'       names of its contributors may be used to endorse or promote products
'       derived from this software without specific prior written permission.
'
' THIS SOFTWARE IS PROVIDED BY Bruce A Henderson ``AS IS'' AND ANY
' EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
' WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
' DISCLAIMED. IN NO EVENT SHALL Bruce A Henderson BE LIABLE FOR ANY
' DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
' (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
' LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
' ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
' (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
' SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
'
SuperStrict


Import BaH.Boost
Import BRL.Blitz

Import "../boost.mod/src/*.hpp"

Import "glue.cpp"


Extern

	Function bmx_sharedmemoryobject_create:Byte Ptr(access:Int, name:String, mode:Int)
	Function bmx_sharedmemoryobject_free(handle:Byte Ptr)
	Function bmx_sharedmemoryobject_remove:Int(name:String)
	Function bmx_sharedmemoryobject_truncate(handle:Byte Ptr, offset:Long)
	Function bmx_sharedmemoryobject_getname:String(handle:Byte Ptr)
	Function bmx_sharedmemoryobject_getsize:Int(handle:Byte Ptr, size:Long Ptr)
	Function bmx_sharedmemoryobject_getmode:Int(handle:Byte Ptr)

	Function bmx_mapped_region_createshm:Byte Ptr(mapping:Byte Ptr, mode:Int, offset:Long, size:Int, address:Byte Ptr)
	Function bmx_mapped_region_getsize:Int(handle:Byte Ptr)
	Function bmx_mapped_region_getaddress:Byte Ptr(handle:Byte Ptr)
	Function bmx_mapped_region_getoffset(handle:Byte Ptr, v:Long Ptr)
	Function bmx_mapped_region_getmode:Int(handle:Byte Ptr)
	Function bmx_mapped_region_flush:Int(handle:Byte Ptr, mappingOffset:Int, numBytes:Int)
	Function bmx_mapped_region_free(handle:Byte Ptr)

End Extern

Rem
bbdoc: 
End Rem
?Not win32
Const MODE_RO:Int = 0
?win32
Const MODE_RO:Int = $80000000
?
Rem
bbdoc: 
End Rem
?Not win32
Const MODE_RW:Int = 2
?win32
Const MODE_RW:Int = MODE_RO | $40000000
?
Rem
bbdoc: 
End Rem
?Not win32
Const MODE_COW:Int = 3
?win32
Const MODE_COW:Int = MODE_RW + 1
?

Type TInterprocessException Extends TRuntimeException
	Field message:String
	Field nativeError:Int
	Field errorCode:Int
	
	Method CreateException:TInterprocessException(message:String, errorCode:Int, nativeError:Int)
		Self.message = message
		Self.errorCode = errorCode
		Self.nativeError = nativeError
		Return Self
	End Method

	Function _create:TInterprocessException(message:String, errorCode:Int, nativeError:Int)
		Return New TInterprocessException.CreateException(message, errorCode, nativeError)
	End Function
	
	Method ToString:String()
		Return "Interprocess Exception : " + message + " : " + errorCode + " (" + nativeError + ")"
	End Method
End Type
