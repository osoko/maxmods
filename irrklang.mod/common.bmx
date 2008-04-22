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

Import "-lirrKlang"

Import "include/*.h"
Import "glue.cpp"



Extern

	Function bmx_createIrrKlangDevice:Byte Ptr(driver:Int, options:Int, deviceID:Byte Ptr)

	Function bmx_soundengine_play2d:Byte Ptr(handle:Byte Ptr, s:Byte Ptr, playLooped:Int, startPaused:Int, track:Int, streamMode:Int, enableSoundEffects:Int)
	Function bmx_soundengine_drop:Int(handle:Byte Ptr)
	Function bmx_soundengine_stopallsounds(handle:Byte Ptr)
	Function bmx_soundengine_setallsoundspaused(handle:Byte Ptr, paused:Int)
	Function bmx_soundengine_removeallsoundsources(handle:Byte Ptr)
	Function bmx_soundengine_setsoundvolume(handle:Byte Ptr, volume:Float)
	Function bmx_soundengine_getsoundvolume:Float(handle:Byte Ptr)
	Function bmx_soundengine_update(handle:Byte Ptr)
	Function bmx_soundengine_setdefault3dsoundmindistance(handle:Byte Ptr, minDistance:Float)
	Function bmx_soundengine_getdefault3dsoundmindistance:Float(handle:Byte Ptr)
	Function bmx_soundengine_setdefault3dsoundmaxdistance(handle:Byte Ptr, maxDistance:Float)
	Function bmx_soundengine_getdefault3dsoundmaxdistance:Float(handle:Byte Ptr)
	Function bmx_soundengine_setrollofffactor(handle:Byte Ptr, rolloff:Float)
	Function bmx_soundengine_setdopplereffectparameters(handle:Byte Ptr, dopplerFactor:Float, distanceFactor:Float)
	Function bmx_soundengine_addsoundsourcefromfile:Byte Ptr(handle:Byte Ptr, filename:Byte Ptr, mode:Int, preload:Int)
	Function bmx_soundengine_addsoundsourcefrommemory:Byte Ptr(handle:Byte Ptr, memory:Byte Ptr, sizeInBytes:Int, name:Byte Ptr, copyMemory:Int)
	Function bmx_soundengine_play2dsource:Byte Ptr(handle:Byte Ptr, source:Byte Ptr, playLooped:Int, startPaused:Int, track:Int, enableSoundEffects:Int)

	Function bmx_sound_setispaused(handle:Byte Ptr, paused:Int)
	Function bmx_sound_getispaused:Int(handle:Byte Ptr)
	Function bmx_sound_stop(handle:Byte Ptr)
	Function bmx_sound_getvolume:Float(handle:Byte Ptr)
	Function bmx_sound_setvolume(handle:Byte Ptr, volume:Float)
	Function bmx_sound_setpan(handle:Byte Ptr, pan:Float)
	Function bmx_sound_getpan:Float(handle:Byte Ptr)
	Function bmx_sound_islooped:Int(handle:Byte Ptr)
	Function bmx_sound_setislooped(handle:Byte Ptr, looped:Int)
	Function bmx_sound_isfinished:Int(handle:Byte Ptr)
	Function bmx_sound_setmindistance(handle:Byte Ptr, minDistance:Float)
	Function bmx_sound_getmindistance:Float(handle:Byte Ptr)
	Function bmx_sound_setmaxdistance(handle:Byte Ptr, maxDistance:Float)
	Function bmx_sound_getmaxdistance:Float(handle:Byte Ptr)
	Function bmx_sound_getplayposition:Int(handle:Byte Ptr)
	Function bmx_sound_setplayposition:Int(handle:Byte Ptr, pos:Int)
	Function bmx_sound_setplaybackspeed:Int(handle:Byte Ptr, speed:Float)
	Function bmx_sound_getplaybackspeed:Float(handle:Byte Ptr)
	Function bmx_sound_getplaylength:Int(handle:Byte Ptr)
	Function bmx_sound_getsoundeffectcontrol:Byte Ptr(handle:Byte Ptr)
	Function bmx_sound_drop(handle:Byte Ptr)

	Function bmx_soundsource_getname:Byte Ptr(handle:Byte Ptr)
	Function bmx_soundsource_setstreammode(handle:Byte Ptr, mode:Int)
	Function bmx_soundsource_getstreammode:Int(handle:Byte Ptr)
	Function bmx_soundsource_getplaylength:Int(handle:Byte Ptr)
	Function bmx_soundsource_getaudioformat:Byte Ptr(handle:Byte Ptr)
	Function bmx_soundsource_isseekingsupported:Int(handle:Byte Ptr)
	Function bmx_soundsource_setdefaultvolume(handle:Byte Ptr, volume:Float)
	Function bmx_soundsource_getdefaultvolume:Float(handle:Byte Ptr)
	Function bmx_soundsource_setdefaultmindistance(handle:Byte Ptr, minDistance:Float)
	Function bmx_soundsource_getdefaultmindistance:Float(handle:Byte Ptr)
	Function bmx_soundsource_setdefaultmaxdistance(handle:Byte Ptr, maxDistance:Float)
	Function bmx_soundsource_getdefaultmaxdistance:Float(handle:Byte Ptr)
	Function bmx_soundsource_forcereloadatnextuse(handle:Byte Ptr)
	Function bmx_soundsource_setforcedstreamingthreshold(handle:Byte Ptr, thresholdBytes:Int)
	Function bmx_soundsource_getforcedstreamingthreshold:Int(handle:Byte Ptr)

End Extern



Const ESOD_AUTO_DETECT:Int = 0
Const ESOD_DIRECT_SOUND_8:Int = 1
Const ESOD_DIRECT_SOUND:Int = 2
Const ESOD_WIN_MM:Int = 3
Const ESOD_ALSA:Int = 4
Const ESOD_CORE_AUDIO:Int = 5
Const ESOD_NULL:Int = 6

Const ESEO_MULTI_THREADED:Int = $01
Const ESEO_MUTE_IF_NOT_FOCUSED:Int = $02
Const ESEO_LOAD_PLUGINS:Int = $04
Const ESEO_USE_3D_BUFFERS:Int = $08
Const ESEO_PRINT_DEBUG_INFO_TO_DEBUGGER:Int = $10
Const ESEO_PRINT_DEBUG_INFO_TO_STDOUT:Int = $20
Const ESEO_LINEAR_ROLLOFF:Int = $40
Const ESEO_DEFAULT_OPTIONS:Int = ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS | ..
	ESEO_PRINT_DEBUG_INFO_TO_DEBUGGER | ESEO_PRINT_DEBUG_INFO_TO_STDOUT

Const ESM_AUTO_DETECT:Int = 0
Const ESM_STREAMING:Int = 1
Const ESM_NO_STREAMING:Int = 2

