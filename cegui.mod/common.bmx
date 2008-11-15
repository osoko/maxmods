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


Import "source.bmx"

Extern
	Function _strlen:Int(s:Byte Ptr) = "strlen"

	Function bmx_cegui_new_oglrenderer:Byte Ptr()
	Function bmx_cegui_new_system:Byte Ptr(renderer:Byte Ptr, resourceProvider:Byte Ptr)
	Function bmx_cegui_delete_system(system:Byte Ptr)
	Function bmx_cegui_delete_renderer(renderer:Byte Ptr)
	
	Function bmx_cegui_schememanager_loadScheme:Byte Ptr(scheme:Byte Ptr, resourceGroup:Byte Ptr)
	Function bmx_cegui_schememanager_isschemepresent:Int(scheme:Byte Ptr)
	Function bmx_cegui_schememanager_getscheme:Byte Ptr(name:Byte Ptr)
	Function bmx_cegui_schememanager_unloadallschemes()
	
	Function bmx_cegui_system_setDefaultFont(handle:Byte Ptr, font:Byte Ptr)
	Function bmx_cegui_system_setDefaultMouseCursor(handle:Byte Ptr, look:Byte Ptr, kind:Byte Ptr)
	Function bmx_cegui_system_renderGUI(handle:Byte Ptr)
	Function bmx_cegui_system_setGUISheet(handle:Byte Ptr, window:Byte Ptr)
	Function bmx_cegui_system_injectTimePulse:Int(handle:Byte Ptr, time:Float)
	Function bmx_cegui_system_injectMousePosition:Int(handle:Byte Ptr, x:Int, y:Int)
	Function bmx_cegui_system_injectMouseButtonUp:Int(handle:Byte Ptr, button:Int)
	Function bmx_cegui_system_injectMouseButtonDown:Int(handle:Byte Ptr, button:Int)
	Function bmx_cegui_system_injectMouseWheelChange:Int(handle:Byte Ptr, delta:Int)
	Function bmx_cegui_system_injectkeydown:Int(handle:Byte Ptr, key:Int)
	Function bmx_cegui_system_injectkeyup:Int(handle:Byte Ptr, key:Int)
	Function bmx_cegui_system_injectchar:Int(handle:Byte Ptr, key:Int)
	Function bmx_cegui_system_getDefaultFont:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_system_signalredraw(handle:Byte Ptr)
	Function bmx_cegui_system_isredrawrequested:Int(handle:Byte Ptr)
	Function bmx_cegui_system_getsingleclicktimeout:Double(handle:Byte Ptr)
	Function bmx_cegui_system_getmulticlicktimeout:Double(handle:Byte Ptr)
	Function bmx_cegui_system_getmulticlicktoleranceareasize(handle:Byte Ptr, width:Float Ptr, height:Float Ptr)
	Function bmx_cegui_system_setsingleclicktimeout(handle:Byte Ptr, timeout:Double)
	Function bmx_cegui_system_setmulticlicktimeout(handle:Byte Ptr, timeout:Double)
	Function bmx_cegui_system_setmulticlicktoleranceareasize(handle:Byte Ptr, width:Float, height:Float)
	
	Function bmx_cegui_windowmanager_getsingleton:Byte Ptr()
	Function bmx_cegui_windowmanager_loadWindowLayout:Object(handle:Byte Ptr, filename:Byte Ptr, namePrefix:Byte Ptr, resourceGroup:Byte Ptr)
	Function bmx_cegui_windowmanager_getwindow:Object(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_windowmanager_createwindow:Object(handle:Byte Ptr, windowType:Byte Ptr, name:Byte Ptr, prefix:Byte Ptr)
	Function bmx_cegui_windowmanager_iswindowpresent:Int(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_windowmanager_destroyallwindows(handle:Byte Ptr)
	Function bmx_cegui_windowmanager_destroywindowwindow(handle:Byte Ptr, window:Byte Ptr)
	Function bmx_cegui_windowmanager_destroywindowname(handle:Byte Ptr, window:Byte Ptr)
	Function bmx_cegui_windowmanager_renamewindowwindow(handle:Byte Ptr, window:Byte Ptr, newName:Byte Ptr)
	Function bmx_cegui_windowmanager_renamewindowname(handle:Byte Ptr, window:Byte Ptr, newName:Byte Ptr)

	'Function bmx_cegui_eventhandler_new:Byte Ptr()
	'Function bmx_cegui_eventhandler_delete(handle:Byte Ptr)
	Function bmx_cegui_eventcallback_new:Byte Ptr(handle:Object)

	Function bmx_cegui_eventargs_delete(handle:Byte Ptr)

	Function bmx_cegui_eventset_subscribeevent:Byte Ptr(handle:Byte Ptr, name:Byte Ptr, cb:Byte Ptr)

	Function bmx_cegui_window_settext(handle:Byte Ptr, text:Byte Ptr)
	Function bmx_cegui_window_deactivate(handle:Byte Ptr)
	Function bmx_cegui_window_setposition(handle:Byte Ptr, x:Float, y:Float)
	Function bmx_cegui_window_setxposition(handle:Byte Ptr, x:Float)
	Function bmx_cegui_window_setyposition(handle:Byte Ptr, y:Float)
	Function bmx_cegui_window_setsize(handle:Byte Ptr, width:Float, height:Float)
	Function bmx_cegui_window_setwidth(handle:Byte Ptr, width:Float)
	Function bmx_cegui_window_setheight(handle:Byte Ptr, height:Float)
	Function bmx_cegui_window_setmaxsize(handle:Byte Ptr, width:Float, height:Float)
	Function bmx_cegui_window_setminsize(handle:Byte Ptr, width:Float, height:Float)
	Function bmx_cegui_window_addchildwindowwindow(handle:Byte Ptr, window:Byte Ptr)
	Function bmx_cegui_window_addchildwindow(handle:Byte Ptr, window:Byte Ptr)
	Function bmx_cegui_window_hide(handle:Byte Ptr)
	Function bmx_cegui_window_show(handle:Byte Ptr)
	Function bmx_cegui_window_gettype:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_window_activate(handle:Byte Ptr)

	Function bmx_cegui_window_getname:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_window_getprefix:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_window_isdestroyedbyparent:Int(handle:Byte Ptr)
	Function bmx_cegui_window_isalwaysontop:Int(handle:Byte Ptr)
	Function bmx_cegui_window_isdisabled:Int(handle:Byte Ptr, localOnly:Int)
	Function bmx_cegui_window_isvisible:Int(handle:Byte Ptr, localOnly:Int	)
	Function bmx_cegui_window_isactive:Int(handle:Byte Ptr)
	Function bmx_cegui_window_isclippedbyparent:Int(handle:Byte Ptr)
	Function bmx_cegui_window_getid:Int(handle:Byte Ptr)
	Function bmx_cegui_window_getchildcount:Int(handle:Byte Ptr)
	Function bmx_cegui_window_ischild:Int(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_window_ischildid:Int(handle:Byte Ptr, ID:Int)
	Function bmx_cegui_window_ischildrecursive:Int(handle:Byte Ptr, ID:Int)
	Function bmx_cegui_window_ischildwindow:Int(handle:Byte Ptr, window:Byte Ptr)
	Function bmx_cegui_window_getchild:Object(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_window_recursivechildsearch:Object(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_window_getchildid:Object(handle:Byte Ptr, ID:Int)
	Function bmx_cegui_window_getchildrecursive:Object(handle:Byte Ptr, ID:Int)
	Function bmx_cegui_window_getchildatidx:Object(handle:Byte Ptr, idx:Int)
	Function bmx_cegui_window_getactivechild:Object(handle:Byte Ptr)
	Function bmx_cegui_window_isancestor:Int(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_window_isancestorid:Int(handle:Byte Ptr, ID:Int)
	Function bmx_cegui_window_isancestorwindow:Int(handle:Byte Ptr, window:Byte Ptr)
	Function bmx_cegui_window_gettext:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_window_inheritsalpha:Int(handle:Byte Ptr)
	Function bmx_cegui_window_getalpha:Float(handle:Byte Ptr)
	Function bmx_cegui_window_geteffectivealpha:Float(handle:Byte Ptr)
	Function bmx_cegui_window_getpixelrect(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_window_getinnerrect(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_window_getunclippedpixelrect(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_window_getunclippedinnerrect(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_window_iscapturedbythis:Int(handle:Byte Ptr)
	Function bmx_cegui_window_iscapturedbyancestor:Int(handle:Byte Ptr)
	Function bmx_cegui_window_iscapturedbychild:Int(handle:Byte Ptr)
	Function bmx_cegui_window_ishit:Int(handle:Byte Ptr, x:Float, y:Float)
	Function bmx_cegui_window_getchildatposition:Object(handle:Byte Ptr, x:Float, y:Float)
	Function bmx_cegui_window_gettargetchildatposition:Object(handle:Byte Ptr, x:Float, y:Float)
	Function bmx_cegui_window_getparent:Object(handle:Byte Ptr)
	Function bmx_cegui_window_getpixelsize(handle:Byte Ptr, width:Float Ptr, height:Float Ptr)
	Function bmx_cegui_window_restoresoldcapture:Int(handle:Byte Ptr)
	Function bmx_cegui_window_iszorderingenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_window_wantsmulticlickevents:Int(handle:Byte Ptr)
	Function bmx_cegui_window_ismouseautorepeatenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_window_getautorepeatdelay:Float(handle:Byte Ptr)
	Function bmx_cegui_window_getautorepeatrate:Float(handle:Byte Ptr)
	Function bmx_cegui_window_distributescapturedinputs:Int(handle:Byte Ptr)
	Function bmx_cegui_window_isusingdefaulttooltip:Int(handle:Byte Ptr)
	Function bmx_cegui_window_gettooltiptype:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_window_gettooltiptext:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_window_inheritstooltiptext:Int(handle:Byte Ptr)
	Function bmx_cegui_window_isriseonclickenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_window_testclassname:Int(handle:Byte Ptr, className:Byte Ptr)
	Function bmx_cegui_window_getverticalalignment:Int(handle:Byte Ptr)
	Function bmx_cegui_window_gethorizontalalignment:Int(handle:Byte Ptr)
	Function bmx_cegui_window_getlooknfeel:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_window_getmodalstate:Int(handle:Byte Ptr)
	Function bmx_cegui_window_getuserstring:Byte Ptr(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_window_isuserstringdefined:Int(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_window_getparentpixelwidth:Float(handle:Byte Ptr)
	Function bmx_cegui_window_getparentpixelheight:Float(handle:Byte Ptr)
	Function bmx_cegui_window_ismousepassthroughenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_window_isautowindow:Int(handle:Byte Ptr)
	Function bmx_cegui_window_iswritingxmlallowed:Int(handle:Byte Ptr)
	Function bmx_cegui_window_isdragdroptarget:Int(handle:Byte Ptr)

	Function bmx_cegui_window_setproperty(handle:Byte Ptr, name:Byte Ptr, value:Byte Ptr)

	Function bmx_cegui_connection_delete(handle:Byte Ptr)

	Function bmx_cegui_checkbox_isselected:Int(handle:Byte Ptr)
	Function bmx_cegui_checkbox_setselected(handle:Byte Ptr, selected:Int)

	Function bmx_cegui_progressbar_getprogress:Float(handle:Byte Ptr)
	Function bmx_cegui_progressbar_getstep:Float(handle:Byte Ptr)
	Function bmx_cegui_progressbar_setprogress(handle:Byte Ptr, progress:Float)
	Function bmx_cegui_progressbar_setstepsize(handle:Byte Ptr, stepVal:Float)
	Function bmx_cegui_progressbar_dostep(handle:Byte Ptr)
	Function bmx_cegui_progressbar_adjustprogress(handle:Byte Ptr, delta:Float)

	Function bmx_cegui_editbox_hasinputfocus:Int(handle:Byte Ptr)
	Function bmx_cegui_editbox_isreadonly:Int(handle:Byte Ptr)
	Function bmx_cegui_editbox_istextmasked:Int(handle:Byte Ptr)
	Function bmx_cegui_editbox_istextvalid:Int(handle:Byte Ptr)
	Function bmx_cegui_editbox_getvalidationstring:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_editbox_getcaratindex:Int(handle:Byte Ptr)
	Function bmx_cegui_editbox_getselectionstartindex:Int(handle:Byte Ptr)
	Function bmx_cegui_editbox_getselectionendindex:Int(handle:Byte Ptr)
	Function bmx_cegui_editbox_getselectionlength:Int(handle:Byte Ptr)
	Function bmx_cegui_editbox_getmaxtextlength:Int(handle:Byte Ptr)
	Function bmx_cegui_editbox_setreadonly(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_editbox_settextmasked(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_editbox_setvalidationstring(handle:Byte Ptr, validationString:Byte Ptr)
	Function bmx_cegui_editbox_setcaratindex(handle:Byte Ptr, caratPos:Int)
	Function bmx_cegui_editbox_setselection(handle:Byte Ptr, startPos:Int, endPos:Int)
	Function bmx_cegui_editbox_setmaxtextlength(handle:Byte Ptr, maxLen:Int)

	Function bmx_cegui_logger_setlogginglevel(level:Int)
	Function bmx_cegui_logger_setlogfilename(filename:Byte Ptr, append:Int)
	Function bmx_cegui_logger_logevent(message:Byte Ptr, level:Int)
	Function bmx_cegui_customlogger_create:Byte Ptr(handle:Object)
	Function bmx_cegui_customlogger_delete(handle:Byte Ptr)
	Function bmx_cegui_logger_getlogginglevel:Int()

	Function bmx_cegui_eventargs_gethandled:Int(handle:Byte Ptr)
	Function bmx_cegui_windoweventargs_getwindow:Object(handle:Byte Ptr)
	Function bmx_cegui_activationeventargs_getotherwindow:Object(handle:Byte Ptr)
	Function bmx_cegui_updateeventargs_gettimesincelastframe:Float(handle:Byte Ptr)

	Function bmx_cegui_framewindow_issizingenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_framewindow_isframeenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_framewindow_istitlebarenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_framewindow_isclosebuttonenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_framewindow_isrollupenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_framewindow_isrolledup:Int(handle:Byte Ptr)
	Function bmx_cegui_framewindow_getsizingborderthickness:Float(handle:Byte Ptr)
	Function bmx_cegui_framewindow_setsizingenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_framewindow_setframeenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_framewindow_settitlebarenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_framewindow_setclosebuttonenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_framewindow_rollupenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_framewindow_togglerollup(handle:Byte Ptr)
	Function bmx_cegui_framewindow_setsizingborderthickness(handle:Byte Ptr, pixels:Float)
	Function bmx_cegui_framewindow_isdragmovingenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_framewindow_setdragmovingenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_framewindow_ishit:Int(handle:Byte Ptr, x:Float, y:Float)
	Function bmx_cegui_framewindow_gettitlebar:Object(handle:Byte Ptr)
	Function bmx_cegui_framewindow_getclosebutton:Object(handle:Byte Ptr)

	Function bmx_cegui_titlebar_isdraggingenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_titlebar_setdraggingenabled(handle:Byte Ptr, setting:Int)

	Function bmx_cegui_buttonbase_ishovering:Int(handle:Byte Ptr)
	Function bmx_cegui_buttonbase_ispushed:Int(handle:Byte Ptr)

	Function bmx_cegui_radiobutton_isselected:Int(handle:Byte Ptr)
	Function bmx_cegui_radiobutton_getgroupid:Int(handle:Byte Ptr)
	Function bmx_cegui_radiobutton_getselectedbuttoningroup:Object(handle:Byte Ptr)
	Function bmx_cegui_radiobutton_setselected(handle:Byte Ptr, selected:Int)
	Function bmx_cegui_radiobutton_setgroupid(handle:Byte Ptr, group:Int)

	Function bmx_cegui_combodroplist_setarmed(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_combodroplist_isarmed:Int(handle:Byte Ptr)
	Function bmx_cegui_combodroplist_setautoarmenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_combodroplist_isautoarmenabled:Int(handle:Byte Ptr)

	Function bmx_cegui_multilineeditbox_hasinputfocus:Int(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_isreadonly:Int(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_getcaratindex:Int(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_getselectionstartindex:Int(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_getselectionendindex:Int(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_getselectionlength:Int(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_getmaxtextlength:Int(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_iswordwrapped:Int(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_getvertscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_isvertscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_gethorzscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_gettextrenderarea(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_multilineeditbox_getlinenumberfromindex:Int(handle:Byte Ptr, index:Int)
	Function bmx_cegui_multilineeditbox_setreadonly(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_multilineeditbox_setcaratindex(handle:Byte Ptr, caratPos:Int)
	Function bmx_cegui_multilineeditbox_setselection(handle:Byte Ptr, startPos:Int, endPos:Int)
	Function bmx_cegui_multilineeditbox_setmaxtextlength(handle:Byte Ptr, maxLen:Int)
	Function bmx_cegui_multilineeditbox_ensurecaratisvisible(handle:Byte Ptr)
	Function bmx_cegui_multilineeditbox_setwordwrapping(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_multilineeditbox_setshowvertscrollbar(handle:Byte Ptr, setting:Int)

	Function bmx_cegui_scrolleditemlistbase_isvertscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_scrolleditemlistbase_ishorzscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_scrolleditemlistbase_getvertscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_scrolleditemlistbase_gethorzscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_scrolleditemlistbase_setshowvertscrollbar(handle:Byte Ptr, mode:Int)
	Function bmx_cegui_scrolleditemlistbase_setshowhorzscrollbar(handle:Byte Ptr, mode:Int)

	Function bmx_cegui_itemlistbox_getselectedcount:Int(handle:Byte Ptr)
	Function bmx_cegui_itemlistbox_getlastselecteditem:Object(handle:Byte Ptr)
	Function bmx_cegui_itemlistbox_getfirstselecteditem:Object(handle:Byte Ptr, startIndex:Int)
	Function bmx_cegui_itemlistbox_getnextselecteditem:Object(handle:Byte Ptr)
	Function bmx_cegui_itemlistbox_getnextselecteditemafter:Object(handle:Byte Ptr, startItem:Byte Ptr)
	Function bmx_cegui_itemlistbox_ismultiselectenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_itemlistbox_isitemselected:Int(handle:Byte Ptr, index:Int)
	Function bmx_cegui_itemlistbox_setmultiselectenabled(handle:Byte Ptr, state:Int)
	Function bmx_cegui_itemlistbox_clearallselections(handle:Byte Ptr)
	Function bmx_cegui_itemlistbox_selectrange(handle:Byte Ptr, a:Int, z:Int)
	Function bmx_cegui_itemlistbox_selectallitems(handle:Byte Ptr)

	Function bmx_cegui_imagesetmanager_createimagesetfromimagefile:Byte Ptr(name:Byte Ptr, filename:Byte Ptr, resourceGroup:Byte Ptr)
	Function bmx_cegui_imagesetmanager_createimageset:Byte Ptr(filename:Byte Ptr, resourceGroup:Byte Ptr)
	Function bmx_cegui_imagesetmanager_createimagesetfromtexture:Byte Ptr(name:Byte Ptr, texture:Byte Ptr)
	Function bmx_cegui_imagesetmanager_destroyimageset(objectPtr:Byte Ptr)
	Function bmx_cegui_imagesetmanager_destroyimagesetname(imageset:Byte Ptr)
	Function bmx_cegui_imagesetmanager_destroyallimagesets()
	Function bmx_cegui_imagesetmanager_getimageset:Byte Ptr(name:Byte Ptr)
	Function bmx_cegui_imagesetmanager_isimagesetpresent:Int(name:Byte Ptr)
	Function bmx_cegui_imagesetmanager_notifyscreenresolution(width:Float, height:Float)

	Function bmx_cegui_fontmanager_createfont:Byte Ptr(filename:Byte Ptr, resourceGroup:Byte Ptr)
	Function bmx_cegui_fontmanager_isfontpresent:Int(name:Byte Ptr)

	Function bmx_cegui_spinner_getcurrentvalue:Float(handle:Byte Ptr)
	Function bmx_cegui_spinner_getstepsize:Float(handle:Byte Ptr)
	Function bmx_cegui_spinner_getmaximumvalue:Float(handle:Byte Ptr)
	Function bmx_cegui_spinner_getminimumvalue:Float(handle:Byte Ptr)
	Function bmx_cegui_spinner_gettextinputmode:Int(handle:Byte Ptr)
	Function bmx_cegui_spinner_setcurrentvalue(handle:Byte Ptr, value:Float)
	Function bmx_cegui_spinner_setstepsize(handle:Byte Ptr, stepSize:Float)
	Function bmx_cegui_spinner_setmaximumvalue(handle:Byte Ptr, maxValue:Float)
	Function bmx_cegui_spinner_setminimumvalue(handle:Byte Ptr, minValue:Float)
	Function bmx_cegui_spinner_settextinputmode(handle:Byte Ptr, mode:Int)

	Function bmx_cegui_scrollbar_getdocumentsize:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollbar_getpagesize:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollbar_getstepsize:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollbar_getoverlapsize:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollbar_getscrollposition:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollbar_getincreasebutton:Object(handle:Byte Ptr)
	Function bmx_cegui_scrollbar_getdecreasebutton:Object(handle:Byte Ptr)
	Function bmx_cegui_scrollbar_setdocumentsize(handle:Byte Ptr, documentSize:Float)
	Function bmx_cegui_scrollbar_setpagesize(handle:Byte Ptr, pageSize:Float)
	Function bmx_cegui_scrollbar_setstepsize(handle:Byte Ptr, stepSize:Float)
	Function bmx_cegui_scrollbar_setoverlapsize(handle:Byte Ptr, overlapSize:Float)
	Function bmx_cegui_scrollbar_setscrollposition(handle:Byte Ptr, position:Float)

	Function bmx_cegui_slider_getcurrentvalue:Float(handle:Byte Ptr)
	Function bmx_cegui_slider_getmaxvalue:Float(handle:Byte Ptr)
	Function bmx_cegui_slider_getclickstep:Float(handle:Byte Ptr)
	Function bmx_cegui_slider_setmaxvalue(handle:Byte Ptr, maxVal:Float)
	Function bmx_cegui_slider_setcurrentvalue(handle:Byte Ptr, value:Float)
	Function bmx_cegui_slider_setclickstep(handle:Byte Ptr, clickStep:Float)

	Function bmx_cegui_tooltip_gettargetwindow:Object(handle:Byte Ptr)
	Function bmx_cegui_tooltip_gethovertime:Float(handle:Byte Ptr)
	Function bmx_cegui_tooltip_setdisplaytime(handle:Byte Ptr, seconds:Float)
	Function bmx_cegui_tooltip_getfadetime:Float(handle:Byte Ptr)
	Function bmx_cegui_tooltip_sethovertime(handle:Byte Ptr, seconds:Float)
	Function bmx_cegui_tooltip_getdisplaytime:Float(handle:Byte Ptr)
	Function bmx_cegui_tooltip_setfadetime(handle:Byte Ptr, seconds:Float)
	Function bmx_cegui_tooltip_positionself(handle:Byte Ptr)
	Function bmx_cegui_tooltip_sizeself(handle:Byte Ptr)
	Function bmx_cegui_tooltip_gettextsize(handle:Byte Ptr, width:Float Ptr, height:Float Ptr)

	Function bmx_cegui_tabcontrol_gettabcount:Int(handle:Byte Ptr)
	Function bmx_cegui_tabcontrol_gettabpaneposition:Int(handle:Byte Ptr)
	Function bmx_cegui_tabcontrol_settabpaneposition(handle:Byte Ptr, pos:Int)
	Function bmx_cegui_tabcontrol_setselectedtab(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_tabcontrol_setselectedtabforid(handle:Byte Ptr, ID:Int)
	Function bmx_cegui_tabcontrol_setselectedtabatindex(handle:Byte Ptr, index:Int)
	Function bmx_cegui_tabcontrol_maketabvisible(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_tabcontrol_maketabvisibleforid(handle:Byte Ptr, ID:Int)
	Function bmx_cegui_tabcontrol_maketabvisibleatindex(handle:Byte Ptr, index:Int)
	Function bmx_cegui_tabcontrol_gettabcontentsatindex:Object(handle:Byte Ptr, index:Int)
	Function bmx_cegui_tabcontrol_gettabcontents:Object(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_tabcontrol_gettabcontentsforid:Object(handle:Byte Ptr, ID:Int)
	Function bmx_cegui_tabcontrol_istabcontentsselected:Int(handle:Byte Ptr, wnd:Byte Ptr)
	Function bmx_cegui_tabcontrol_getselectedtabindex:Int(handle:Byte Ptr)
	Function bmx_cegui_tabcontrol_gettabheight:Float(handle:Byte Ptr)
	Function bmx_cegui_tabcontrol_gettabtextpadding:Float(handle:Byte Ptr)
	Function bmx_cegui_tabcontrol_settabheight(handle:Byte Ptr, height:Float)
	Function bmx_cegui_tabcontrol_settabtextpadding(handle:Byte Ptr, padding:Float)
	Function bmx_cegui_tabcontrol_addtab(handle:Byte Ptr, wnd:Byte Ptr)
	Function bmx_cegui_tabcontrol_removetab(handle:Byte Ptr, name:Byte Ptr)
	Function bmx_cegui_tabcontrol_removetabforid(handle:Byte Ptr, ID:Int)

	Function bmx_cegui_renderer_createtexture:Object(handle:Byte Ptr, filename:Byte Ptr, resourceGroup:Byte Ptr)
	Function bmx_cegui_renderer_createtexturewithsize:Object(handle:Byte Ptr, size:Float)
	Function bmx_cegui_renderer_destroytexture(handle:Byte Ptr, texture:Byte Ptr)
	Function bmx_cegui_renderer_destroyalltextures(handle:Byte Ptr)
	Function bmx_cegui_renderer_isqueueingenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_renderer_getwidth:Float(handle:Byte Ptr)
	Function bmx_cegui_renderer_getheight:Float(handle:Byte Ptr)
	Function bmx_cegui_renderer_getsize(handle:Byte Ptr, width:Float Ptr, height:Float Ptr)
	Function bmx_cegui_renderer_getmaxtexturesize:Int(handle:Byte Ptr)
	Function bmx_cegui_renderer_gethorzscreendpi:Int(handle:Byte Ptr)
	Function bmx_cegui_renderer_getvertscreendpi:Int(handle:Byte Ptr)
	Function bmx_cegui_renderer_resetzvalue(handle:Byte Ptr)
	Function bmx_cegui_renderer_advancezvalue(handle:Byte Ptr)
	Function bmx_cegui_renderer_getcurrentz:Float(handle:Byte Ptr)
	Function bmx_cegui_renderer_getzlayer:Float(handle:Byte Ptr, layer:Int)
	Function bmx_cegui_renderer_getidentifierstring:Byte Ptr(handle:Byte Ptr)

	Function bmx_cegui_texture_getwidth:Int(handle:Byte Ptr)
	Function bmx_cegui_texture_getoriginalwidth:Int(handle:Byte Ptr)
	Function bmx_cegui_texture_getxscale:Float(handle:Byte Ptr)
	Function bmx_cegui_texture_getheight:Int(handle:Byte Ptr)
	Function bmx_cegui_texture_getoriginalheight:Int(handle:Byte Ptr)
	Function bmx_cegui_texture_getyscale:Float(handle:Byte Ptr)
	Function bmx_cegui_texture_loadfromfile(handle:Byte Ptr, filename:Byte Ptr, resourceGroup:Byte Ptr)
	Function bmx_cegui_texture_loadfrommemory(handle:Byte Ptr, buffer:Byte Ptr, width:Int, height:Int, pixelFormat:Int)

	Function bmx_cegui_scheme_loadresources(handle:Byte Ptr)
	Function bmx_cegui_scheme_unloadresources(handle:Byte Ptr)
	Function bmx_cegui_scheme_resourcesloaded:Int(handle:Byte Ptr)
	Function bmx_cegui_scheme_getname:Byte Ptr(handle:Byte Ptr)

	Function bmx_cegui_listboxitem_gettext:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_listboxitem_gettooltiptext:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_listboxitem_getid:Int(handle:Byte Ptr)
	Function bmx_cegui_listboxitem_isselected:Int(handle:Byte Ptr)
	Function bmx_cegui_listboxitem_isdisabled:Int(handle:Byte Ptr)
	Function bmx_cegui_listboxitem_isautodeleted:Int(handle:Byte Ptr)
	Function bmx_cegui_listboxitem_getownerwindow:Object(handle:Byte Ptr)
	Function bmx_cegui_listboxitem_settext(handle:Byte Ptr, text:Byte Ptr)
	Function bmx_cegui_listboxitem_settooltiptext(handle:Byte Ptr, text:Byte Ptr)
	Function bmx_cegui_listboxitem_setid(handle:Byte Ptr, itemId:Int)
	Function bmx_cegui_listboxitem_setselected(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_listboxitem_setdisabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_listboxitem_setautodeleted(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_listboxitem_setownerwindow(handle:Byte Ptr, owner:Byte Ptr)
	Function bmx_cegui_listboxitem_setuserdata(handle:Byte Ptr, itemData:Object)
	Function bmx_cegui_listboxitem_getselectioncolours:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_listboxitem_getselectionbrushimage:Object(handle:Byte Ptr)
	Function bmx_cegui_listboxitem_setselectioncolours(handle:Byte Ptr, cols:Byte Ptr)
	Function bmx_cegui_listboxitem_setselectioncoloursforcorners(handle:Byte Ptr, topLeftColour:Byte Ptr, topRightColour:Byte Ptr, bottomLeftColour:Byte Ptr, bottomRightColour:Byte Ptr)
	Function bmx_cegui_listboxitem_setselectioncoloursforcolour(handle:Byte Ptr, col:Byte Ptr)
	Function bmx_cegui_listboxitem_setselectionbrushimage(handle:Byte Ptr, image:Byte Ptr)
	Function bmx_cegui_listboxitem_setselectionbrushimagebyname(handle:Byte Ptr, imageset:Byte Ptr, image:Byte Ptr)
	Function bmx_cegui_listboxitem_getpixelsize(handle:Byte Ptr, width:Float Ptr, height:Float Ptr)

	Function bmx_cegui_multicolumnlist_isusersortcontrolenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_isusercolumnsizingenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_isusercolumndraggingenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getcolumncount:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getrowcount:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getsortcolumn:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getcolumnwithid:Int(handle:Byte Ptr, colId:Int)
	Function bmx_cegui_multicolumnlist_getcolumnwithheadertext:Int(handle:Byte Ptr, text:Byte Ptr)
	Function bmx_cegui_multicolumnlist_gettotalcolumnheaderswidth:Float(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getcolumnheaderwidth:Float(handle:Byte Ptr, colIdx:Int)
	Function bmx_cegui_multicolumnlist_getsortdirection:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getheadersegmentforcolumn:Object(handle:Byte Ptr, colIdx:Int)
	Function bmx_cegui_multicolumnlist_getitemrowindex:Int(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getitemcolumnindex:Int(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getitemgridreference(handle:Byte Ptr, item:Byte Ptr, row:Int Ptr, col:Int Ptr)
	Function bmx_cegui_multicolumnlist_getitematgridreference:Object(handle:Byte Ptr, row:Int, col:Int)
	Function bmx_cegui_multicolumnlist_islistboxitemincolumn:Int(handle:Byte Ptr, item:Byte Ptr, colIdx:Int)
	Function bmx_cegui_multicolumnlist_islistboxiteminrow:Int(handle:Byte Ptr, item:Byte Ptr, rowIdx:Int)
	Function bmx_cegui_multicolumnlist_islistboxiteminlist:Int(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_multicolumnlist_findcolumnitemwithtext:Object(handle:Byte Ptr, text:Byte Ptr, colIdx:Int, startItem:Byte Ptr)
	Function bmx_cegui_multicolumnlist_findrowitemwithtext:Object(handle:Byte Ptr, text:Byte Ptr, rowIdx:Int, startItem:Byte Ptr)
	Function bmx_cegui_multicolumnlist_findlistitemwithtext:Object(handle:Byte Ptr, text:Byte Ptr, startItem:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getfirstselecteditem:Object(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getnextselected:Object(handle:Byte Ptr, startItem:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getselectedcount:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_isitemselected:Int(handle:Byte Ptr, row:Int, col:Int)
	Function bmx_cegui_multicolumnlist_getnominatedselectioncolumnid:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getnominatedselectioncolum:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getnominatedselectionrow:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getselectionmode:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_isvertscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_ishorzscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getcolumnid:Int(handle:Byte Ptr, colIdx:Int)
	Function bmx_cegui_multicolumnlist_getrowid:Int(handle:Byte Ptr, rowIdx:Int)
	Function bmx_cegui_multicolumnlist_getrowwithid:Int(handle:Byte Ptr, rowId:Int)
	Function bmx_cegui_multicolumnlist_getlistrenderarea(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_multicolumnlist_getvertscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_gethorzscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getlistheader:Object(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_gettotalrowsheight:Float(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_getwidestcolumnitemwidth:Float(handle:Byte Ptr, colIdx:Int)
	Function bmx_cegui_multicolumnlist_gethighestrowitemheight:Float(handle:Byte Ptr, rowIdx:Int)
	Function bmx_cegui_multicolumnlist_resetlist(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_addcolumn(handle:Byte Ptr, text:Byte Ptr, colId:Int, width:Float)
	Function bmx_cegui_multicolumnlist_insertcolumn(handle:Byte Ptr, text:Byte Ptr, colId:Int, width:Float, position:Int)
	Function bmx_cegui_multicolumnlist_removecolumn(handle:Byte Ptr, colIdx:Int)
	Function bmx_cegui_multicolumnlist_removecolumnwithid(handle:Byte Ptr, colId:Int)
	Function bmx_cegui_multicolumnlist_movecolumn(handle:Byte Ptr, colIdx:Int, position:Int)
	Function bmx_cegui_multicolumnlist_movecolumnwithid(handle:Byte Ptr, colId:Int, position:Int)
	Function bmx_cegui_multicolumnlist_addrow:Int(handle:Byte Ptr, rowId:Int)
	Function bmx_cegui_multicolumnlist_addrowitem:Int(handle:Byte Ptr, item:Byte Ptr, colId:Int, rowId:Int)
	Function bmx_cegui_multicolumnlist_insertrow:Int(handle:Byte Ptr, rowIdx:Int, rowId:Int)
	Function bmx_cegui_multicolumnlist_insertrowitem:Int(handle:Byte Ptr, item:Byte Ptr, colId:Int, rowIdx:Int, rowId:Int)
	Function bmx_cegui_multicolumnlist_removerow(handle:Byte Ptr, rowIdx:Int)
	Function bmx_cegui_multicolumnlist_setitemforgridref(handle:Byte Ptr, item:Byte Ptr, row:Int, col:Int)
	Function bmx_cegui_multicolumnlist_setitem(handle:Byte Ptr, item:Byte Ptr, colId:Int, rowIdx:Int)
	Function bmx_cegui_multicolumnlist_setselectionmode(handle:Byte Ptr, selMode:Int)
	Function bmx_cegui_multicolumnlist_setnominatedselectioncolumnid(handle:Byte Ptr, colId:Int)
	Function bmx_cegui_multicolumnlist_setnominatedselectioncolumn(handle:Byte Ptr, colIdx:Int)
	Function bmx_cegui_multicolumnlist_setnominatedselectionrow(handle:Byte Ptr, rowIdx:Int)
	Function bmx_cegui_multicolumnlist_setsortdirection(handle:Byte Ptr, direction:Int)
	Function bmx_cegui_multicolumnlist_setsortcolumn(handle:Byte Ptr, colIdx:Int)
	Function bmx_cegui_multicolumnlist_setsortcolumnbyid(handle:Byte Ptr, colId:Int)
	Function bmx_cegui_multicolumnlist_setshowvertscrollbar(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_multicolumnlist_setshowhorzscrollbar(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_multicolumnlist_clearallselections(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_setitemselectstate(handle:Byte Ptr, item:Byte Ptr, state:Int)
	Function bmx_cegui_multicolumnlist_setitemselectstateforgridref(handle:Byte Ptr, row:Int, col:Int, state:Int)
	Function bmx_cegui_multicolumnlist_handleupdateditemdata(handle:Byte Ptr)
	Function bmx_cegui_multicolumnlist_setcolumnheaderwidth(handle:Byte Ptr, colIdx:Int, width:Float)
	Function bmx_cegui_multicolumnlist_setusersortcontrolenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_multicolumnlist_setusercolumnsizingenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_multicolumnlist_setusercolumndraggingenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_multicolumnlist_autosizecolumnheader(handle:Byte Ptr, colIdx:Int)
	Function bmx_cegui_multicolumnlist_setrowid(handle:Byte Ptr, rowIdx:Int, rowId:Int)

	Function bmx_cegui_dragcontainer_isdraggingenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_dragcontainer_setdraggingenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_dragcontainer_isbeingdragged:Int(handle:Byte Ptr)
	Function bmx_cegui_dragcontainer_getpixeldragthreshold:Float(handle:Byte Ptr)
	Function bmx_cegui_dragcontainer_setpixeldragthreshold(handle:Byte Ptr, pixels:Float)
	Function bmx_cegui_dragcontainer_getdragalpha:Float(handle:Byte Ptr)
	Function bmx_cegui_dragcontainer_setdragalpha(handle:Byte Ptr, alpha:Float)
	Function bmx_cegui_dragcontainer_getdragcursorimage:Object(handle:Byte Ptr)
	Function bmx_cegui_dragcontainer_setdragcursorimage(handle:Byte Ptr, image:Byte Ptr)
	Function bmx_cegui_dragcontainer_setdragcursorimagemode(handle:Byte Ptr, image:Int)
	Function bmx_cegui_dragcontainer_setdragcursorimagebyname(handle:Byte Ptr, imageset:Byte Ptr, image:Byte Ptr)
	Function bmx_cegui_dragcontainer_getcurrentdroptarget:Object(handle:Byte Ptr)

	Function bmx_cegui_colour_create:Byte Ptr(red:Float, green:Float, blue:Float, alpha:Float)
	Function bmx_cegui_colour_delete(handle:Byte Ptr)
	Function bmx_cegui_colour_getargb:Int(handle:Byte Ptr)
	Function bmx_cegui_colour_getalpha:Float(handle:Byte Ptr)
	Function bmx_cegui_colour_getred:Float(handle:Byte Ptr)
	Function bmx_cegui_colour_getgreen:Float(handle:Byte Ptr)
	Function bmx_cegui_colour_getblue:Float(handle:Byte Ptr)
	Function bmx_cegui_colour_gethue:Float(handle:Byte Ptr)
	Function bmx_cegui_colour_getsaturation:Float(handle:Byte Ptr)
	Function bmx_cegui_colour_getlumination:Float(handle:Byte Ptr)
	Function bmx_cegui_colour_setargb(handle:Byte Ptr, argb:Int)
	Function bmx_cegui_colour_setalpha(handle:Byte Ptr, alpha:Float)
	Function bmx_cegui_colour_setred(handle:Byte Ptr, red:Float)
	Function bmx_cegui_colour_setgreen(handle:Byte Ptr, green:Float)
	Function bmx_cegui_colour_setblue(handle:Byte Ptr, blue:Float)
	Function bmx_cegui_colour_set(handle:Byte Ptr, red:Float, green:Float, blue:Float, alpha:Float)
	Function bmx_cegui_colour_setrgb(handle:Byte Ptr, red:Float, green:Float, blue:Float)
	Function bmx_cegui_colour_sethsl(handle:Byte Ptr, hue:Float, saturation:Float, luminance:Float, alpha:Float)
	Function bmx_cegui_colour_inverColour(handle:Byte Ptr)
	Function bmx_cegui_colour_invertColourWithAlpha(handle:Byte Ptr)


	Function bmx_cegui_colourrect_create:Byte Ptr(colour:Byte Ptr)
	Function bmx_cegui_colourrect_setalpha(handle:Byte Ptr, alpha:Float)
	Function bmx_cegui_colourrect_settopalpha(handle:Byte Ptr, alpha:Float)
	Function bmx_cegui_colourrect_setbottomalpha(handle:Byte Ptr, alpha:Float)
	Function bmx_cegui_colourrect_setleftalpha(handle:Byte Ptr, alpha:Float)
	Function bmx_cegui_colourrect_setrightalpha(handle:Byte Ptr, alpha:Float)
	Function bmx_cegui_colourrect_ismonochromatic:Int(handle:Byte Ptr)
	Function bmx_cegui_colourrect_getsubrectangle:Byte Ptr(handle:Byte Ptr, _left:Float, _right:Float, _top:Float, _bottom:Float)
	Function bmx_cegui_colourrect_getcolouratpoint:Byte Ptr(handle:Byte Ptr, x:Float, y:Float)
	Function bmx_cegui_colourrect_setcolours(handle:Byte Ptr, col:Byte Ptr)
	Function bmx_cegui_colourrect_modulatealpha(handle:Byte Ptr, alpha:Float)
	Function bmx_cegui_colourrect_settopleft(handle:Byte Ptr, colour:Byte Ptr)
	Function bmx_cegui_colourrect_settopright(handle:Byte Ptr, colour:Byte Ptr)
	Function bmx_cegui_colourrect_setbottomleft(handle:Byte Ptr, colour:Byte Ptr)
	Function bmx_cegui_colourrect_setbottomright(handle:Byte Ptr, colour:Byte Ptr)
	Function bmx_cegui_colourrect_gettopleft:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_colourrect_gettopright:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_colourrect_getbottomleft:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_colourrect_getbottomright:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_colourrect_delete(handle:Byte Ptr)

	Function bmx_cegui_menubase_getitemspacing:Float(handle:Byte Ptr)
	Function bmx_cegui_menubase_ismultiplepopupsallowed:Int(handle:Byte Ptr)
	Function bmx_cegui_menubase_getpopupmenuitem:Object(handle:Byte Ptr)
	Function bmx_cegui_menubase_setitemspacing(handle:Byte Ptr, spacing:Float)
	Function bmx_cegui_menubase_changepopupmenuitem(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_menubase_setallowmultiplepopups(handle:Byte Ptr, setting:Int)

	Function bmx_cegui_popupmenu_getfadeintime:Float(handle:Byte Ptr)
	Function bmx_cegui_popupmenu_getfadeouttime:Float(handle:Byte Ptr)
	Function bmx_cegui_popupmenu_ispopupmenuopen:Int(handle:Byte Ptr)
	Function bmx_cegui_popupmenu_setfadeintime(handle:Byte Ptr, fadetime:Float)
	Function bmx_cegui_popupmenu_setfadeouttime(handle:Byte Ptr, fadetime:Float)
	Function bmx_cegui_popupmenu_openpopupmenu(handle:Byte Ptr, _notify:Int)
	Function bmx_cegui_popupmenu_closepopupmenu(handle:Byte Ptr, _notify:Int)

	Function bmx_cegui_itementry_getitempixelsize(handle:Byte Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_itementry_getownerlist:Object(handle:Byte Ptr)
	Function bmx_cegui_itementry_isselected:Int(handle:Byte Ptr)
	Function bmx_cegui_itementry_isselectable:Int(handle:Byte Ptr)
	Function bmx_cegui_itementry_setselected(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_itementry_selectentry(handle:Byte Ptr)
	Function bmx_cegui_itementry_deselect(handle:Byte Ptr)
	Function bmx_cegui_itementry_setselectable(handle:Byte Ptr, setting:Int)

	Function bmx_cegui_menuitem_ishovering:Int(handle:Byte Ptr)
	Function bmx_cegui_menuitem_ispushed:Int(handle:Byte Ptr)
	Function bmx_cegui_menuitem_isopened:Int(handle:Byte Ptr)
	Function bmx_cegui_menuitem_getpopupmenu:Object(handle:Byte Ptr)
	Function bmx_cegui_menuitem_setpopupmenu(handle:Byte Ptr, popup:Byte Ptr)
	Function bmx_cegui_menuitem_openpopupmenu(handle:Byte Ptr, _notify:Int)
	Function bmx_cegui_menuitem_closepopupmenu(handle:Byte Ptr, _notify:Int)
	Function bmx_cegui_menuitem_togglepopupmenu:Int(handle:Byte Ptr)

	Function bmx_cegui_treeitem_settextcolours(handle:Byte Ptr, cols:Byte Ptr)
	Function bmx_cegui_treeitem_settextcoloursforcorners(handle:Byte Ptr, topLeftColour:Byte Ptr, topRightColour:Byte Ptr, bottomLeftColour:Byte Ptr, bottomRightColour:Byte Ptr)
	Function bmx_cegui_treeitem_settextcoloursforcolour(handle:Byte Ptr, col:Byte Ptr)
	Function bmx_cegui_treeitem_gettext:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_treeitem_gettooltiptext:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_treeitem_getid:Int(handle:Byte Ptr)
	Function bmx_cegui_treeitem_getuserdata:Object(handle:Byte Ptr)
	Function bmx_cegui_treeitem_isselected:Int(handle:Byte Ptr)
	Function bmx_cegui_treeitem_isdisabled:Int(handle:Byte Ptr)
	Function bmx_cegui_treeitem_isautodeleted:Int(handle:Byte Ptr)
	Function bmx_cegui_treeitem_getownerwindow:Object(handle:Byte Ptr)
	Function bmx_cegui_treeitem_getselectioncolours:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_treeitem_getselectionbrushimage:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_treeitem_settext(handle:Byte Ptr, text:Byte Ptr)
	Function bmx_cegui_treeitem_settooltiptext(handle:Byte Ptr, text:Byte Ptr)
	Function bmx_cegui_treeitem_setid(handle:Byte Ptr, itemId:Int)
	Function bmx_cegui_treeitem_setuserdata(handle:Byte Ptr, itemData:Object)
	Function bmx_cegui_treeitem_setselected(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_treeitem_setdisabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_treeitem_setautodeleted(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_treeitem_setownerwindow(handle:Byte Ptr, owner:Byte Ptr)
	Function bmx_cegui_treeitem_setselectioncolours(handle:Byte Ptr, col:Byte Ptr)
	Function bmx_cegui_treeitem_setselectioncoloursforcorners(handle:Byte Ptr, topLeftColour:Byte Ptr, topRightColour:Byte Ptr, bottomLeftColour:Byte Ptr, bottomRightColour:Byte Ptr)
	Function bmx_cegui_treeitem_setselectioncoloursforcolour(handle:Byte Ptr, col:Byte Ptr)
	Function bmx_cegui_treeitem_setselectionbrushimage(handle:Byte Ptr, image:Byte Ptr)
	Function bmx_cegui_treeitem_setselectionbrushimagebyname(handle:Byte Ptr, imageset:Byte Ptr, image:Byte Ptr)
	Function bmx_cegui_treeitem_setbuttonlocation(handle:Byte Ptr, x:Float, y:Float, w:Float, h:Float)
	Function bmx_cegui_treeitem_getbuttonlocation(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_treeitem_getisopen:Int(handle:Byte Ptr)
	Function bmx_cegui_treeitem_toggleisopen(handle:Byte Ptr)
	Function bmx_cegui_treeitem_gettreeitemfromindex:Object(handle:Byte Ptr, itemIndex:Int)
	Function bmx_cegui_treeitem_getitemcount:Int(handle:Byte Ptr)
	Function bmx_cegui_treeitem_additem(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_treeitem_seticon(handle:Byte Ptr, theIcon:Byte Ptr)
	Function bmx_cegui_treeitem_getpixelsize(handle:Byte Ptr, width:Float Ptr, height:Float Ptr)

	Function bmx_cegui_listboxtextitem_getfont:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_listboxtextitem_gettextcolours:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_listboxtextitem_setfont(handle:Byte Ptr, font:Byte Ptr)
	Function bmx_cegui_listboxtextitem_setfontbyname(handle:Byte Ptr, fontName:Byte Ptr)
	Function bmx_cegui_listboxtextitem_settextcolours(handle:Byte Ptr, cols:Byte Ptr)
	Function bmx_cegui_listboxtextitem_settextcoloursforcorner(handle:Byte Ptr, topLeftColour:Byte Ptr, topRightColour:Byte Ptr, bottomLeftColour:Byte Ptr, bottomRightColour:Byte Ptr)
	Function bmx_cegui_listboxtextitem_settextcoloursforcolour(handle:Byte Ptr, col:Byte Ptr)
	Function bmx_cegui_listboxtextitem_getpixelsize(handle:Byte Ptr, width:Float Ptr, height:Float Ptr)

	Function bmx_cegui_scrollablepane_getcontentpane:Object(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_isvertscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_setshowvertscrollbar(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_scrollablepane_ishorzscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_setshowhorzscrollbar(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_scrollablepane_iscontentpaneautosized:Int(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_setcontentpaneautosized(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_scrollablepane_getcontentpanearea(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_scrollablepane_setcontentpanearea(handle:Byte Ptr, x:Float, y:Float, w:Float, h:Float)
	Function bmx_cegui_scrollablepane_gethorizontalstepsize:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_sethorizontalstepsize(handle:Byte Ptr, stepSize:Float)
	Function bmx_cegui_scrollablepane_gethorizontaloverlapsize:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_sethorizontaloverlapsize(handle:Byte Ptr, overlap:Float)
	Function bmx_cegui_scrollablepane_gethorizontalscrollposition:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_sethorizontalscrollposition(handle:Byte Ptr, position:Float)
	Function bmx_cegui_scrollablepane_getverticalstepsize:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_setverticalstepsize(handle:Byte Ptr, stepSize:Float)
	Function bmx_cegui_scrollablepane_getverticaloverlapsize:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_setverticaloverlapsize(handle:Byte Ptr, overlap:Float)
	Function bmx_cegui_scrollablepane_getverticalscrollposition:Float(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_setverticalscrollposition(handle:Byte Ptr, position:Float)
	Function bmx_cegui_scrollablepane_getviewablearea(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_scrollablepane_getvertscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_scrollablepane_gethorzscrollbar:Object(handle:Byte Ptr)

	Function bmx_cegui_tree_getitemcount:Int(handle:Byte Ptr)
	Function bmx_cegui_tree_getselectedcount:Int(handle:Byte Ptr)
	Function bmx_cegui_tree_getfirstselecteditem:Object(handle:Byte Ptr)
	Function bmx_cegui_tree_getlastselecteditem:Object(handle:Byte Ptr)
	Function bmx_cegui_tree_getnextselected:Object(handle:Byte Ptr, startItem:Byte Ptr)
	Function bmx_cegui_tree_issortenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_tree_setitemrenderarea(handle:Byte Ptr, x:Float, y:Float, w:Float, h:Float)
	Function bmx_cegui_tree_getvertscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_tree_gethorzscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_tree_ismultiselectenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_tree_isitemtooltipsenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_tree_findfirstitemwithtext:Object(handle:Byte Ptr, text:Byte Ptr)
	Function bmx_cegui_tree_findnextitemwithtext:Object(handle:Byte Ptr, text:Byte Ptr, startItem:Byte Ptr)
	Function bmx_cegui_tree_findfirstitemwithid:Object(handle:Byte Ptr, searchID:Int)
	Function bmx_cegui_tree_findnextitemwithid:Object(handle:Byte Ptr, searchID:Int, startItem:Byte Ptr)
	Function bmx_cegui_tree_istreeiteminlist:Int(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_tree_isvertscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_tree_ishorzscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_tree_resetlist(handle:Byte Ptr)
	Function bmx_cegui_tree_additem(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_tree_insertitem(handle:Byte Ptr, item:Byte Ptr, position:Byte Ptr)
	Function bmx_cegui_tree_removeitem(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_tree_clearallselections(handle:Byte Ptr)
	Function bmx_cegui_tree_setsortingenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_tree_setmultiselectenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_tree_setshowvertscrollbar(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_tree_setshowhorzscrollbar(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_tree_setitemtooltipsenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_tree_setitemselectstate(handle:Byte Ptr, item:Byte Ptr, state:Int)
	Function bmx_cegui_tree_setitemselectstateindex(handle:Byte Ptr, itemIndex:Int, state:Int)
	Function bmx_cegui_tree_setlooknfeel(handle:Byte Ptr, look:Byte Ptr)
	Function bmx_cegui_tree_handleupdateditemdata(handle:Byte Ptr)
	Function bmx_cegui_tree_ensureitemisvisible(handle:Byte Ptr, item:Byte Ptr)

	Function bmx_cegui_tabbutton_setselected(handle:Byte Ptr, selected:Int)
	Function bmx_cegui_tabbutton_isselected:Int(handle:Byte Ptr)
	Function bmx_cegui_tabbutton_settargetwindow(handle:Byte Ptr, wnd:Byte Ptr)
	Function bmx_cegui_tabbutton_gettargetwindow:Object(handle:Byte Ptr)

	Function bmx_cegui_resourceprovider_create:Byte Ptr(handle:Object)
	Function bmx_cegui_resourceprovider_delete(handle:Byte Ptr)
	Function bmx_cegui_rawdatacontainer_delete(handle:Byte Ptr)

	Function bmx_cegui_rawdatacontainer_setdata(handle:Byte Ptr, data:Byte Ptr)
	Function bmx_cegui_rawdatacontainer_getdataptr:Byte Ptr(handle:Byte Ptr)
	Function bmx_cegui_rawdatacontainer_setsize(handle:Byte Ptr, size:Int)
	Function bmx_cegui_rawdatacontainer_getsize:Int(handle:Byte Ptr)

	Function bmx_cegui_listbox_getitemcount:Int(handle:Byte Ptr)
	Function bmx_cegui_listbox_getselectedcount:Int(handle:Byte Ptr)
	Function bmx_cegui_listbox_getfirstselecteditem:Object(handle:Byte Ptr)
	Function bmx_cegui_listbox_getnextselected:Object(handle:Byte Ptr, startItem:Byte Ptr)
	Function bmx_cegui_listbox_getlistboxitemfromindex:Object(handle:Byte Ptr, index:Int)
	Function bmx_cegui_listbox_getitemindex:Int(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_listbox_issortenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_listbox_ismultiselectenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_listbox_isitemtooltipsenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_listbox_isitemselected:Int(handle:Byte Ptr, index:Int)
	Function bmx_cegui_listbox_finditemwithtext:Object(handle:Byte Ptr, text:Byte Ptr, startItem:Byte Ptr)
	Function bmx_cegui_listbox_islistboxiteminlist:Int(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_listbox_isvertscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_listbox_ishorzscrollbaralwaysshown:Int(handle:Byte Ptr)
	Function bmx_cegui_listbox_resetlist(handle:Byte Ptr)
	Function bmx_cegui_listbox_additem(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_listbox_insertitem(handle:Byte Ptr, item:Byte Ptr, position:Byte Ptr)
	Function bmx_cegui_listbox_removeitem(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_listbox_clearallselections(handle:Byte Ptr)
	Function bmx_cegui_listbox_setsortingenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_listbox_setmultiselectenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_listbox_setshowvertscrollbar(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_listbox_setshowhorzscrollbar(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_listbox_setitemtooltipsenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_listbox_setitemselectstate(handle:Byte Ptr, item:Byte Ptr, state:Int)
	Function bmx_cegui_listbox_setitemselectstateforindex(handle:Byte Ptr, itemIndex:Int, state:Int)
	Function bmx_cegui_listbox_handleupdateditemdata(handle:Byte Ptr)
	Function bmx_cegui_listbox_ensureitemisvisibleforindex(handle:Byte Ptr, itemIndex:Int)
	Function bmx_cegui_listbox_ensureitemisvisible(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_listbox_getlistrenderarea(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_listbox_getvertscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_listbox_gethorzscrollbar:Object(handle:Byte Ptr)
	Function bmx_cegui_listbox_gettotalitemsheight:Float(handle:Byte Ptr)
	Function bmx_cegui_listbox_getwidestitemwidth:Float(handle:Byte Ptr)

	Function bmx_cegui_itemlistbase_getitemcount:Int(handle:Byte Ptr)
	Function bmx_cegui_itemlistbase_getitemfromindex:Object(handle:Byte Ptr, index:Int)
	Function bmx_cegui_itemlistbase_getitemindex:Int(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_itemlistbase_finditemwithtext:Object(handle:Byte Ptr, text:Byte Ptr, startItem:Byte Ptr)
	Function bmx_cegui_itemlistbase_isiteminlist:Int(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_itemlistbase_isautoresizeenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_itemlistbase_issortenabled:Int(handle:Byte Ptr)
	Function bmx_cegui_itemlistbase_getsortmode:Int(handle:Byte Ptr)
	Function bmx_cegui_itemlistbase_resetlist(handle:Byte Ptr)
	Function bmx_cegui_itemlistbase_additem(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_itemlistbase_insertitem(handle:Byte Ptr, item:Byte Ptr, position:Byte Ptr)
	Function bmx_cegui_itemlistbase_removeitem(handle:Byte Ptr, item:Byte Ptr)
	Function bmx_cegui_itemlistbase_handleupdateditemdata(handle:Byte Ptr, resort:Int)
	Function bmx_cegui_itemlistbase_setautoresizeenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_itemlistbase_sizetocontent(handle:Byte Ptr)
	Function bmx_cegui_itemlistbase_endinitialisation(handle:Byte Ptr)
	Function bmx_cegui_itemlistbase_performchildwindowlayout(handle:Byte Ptr)
	Function bmx_cegui_itemlistbase_getitemrenderarea(handle:Byte Ptr, x:Float Ptr, y:Float Ptr, w:Float Ptr, h:Float Ptr)
	Function bmx_cegui_itemlistbase_getcontentpane:Object(handle:Byte Ptr)
	Function bmx_cegui_itemlistbase_setsortenabled(handle:Byte Ptr, setting:Int)
	Function bmx_cegui_itemlistbase_setsortmode(handle:Byte Ptr, mode:Int)
	Function bmx_cegui_itemlistbase_sortlist(handle:Byte Ptr, relayout:Int)

	Function bmx_cegui_globaleventset_getinstance:Byte Ptr()
	Function bmx_cegui_globaleventset_subscribeevent:Byte Ptr(handle:Byte Ptr, name:Byte Ptr, cb:Byte Ptr)

	Function bmx_cegui_windowfactory_create:Byte Ptr(handle:Object, typeName:Byte Ptr)

End Extern

' converts a UTF character array from byte-size characters to short-size characters
' based on the TextStream UTF code...
Function _convertUTF8ToMax:String(s:Byte Ptr)
	If s Then
		Local l:Int = _strlen(s)
		Local b:Short[] = New Short[l]
		Local bc:Int = -1
		Local c:Int
		Local d:Int
		Local e:Int
		For Local i:Int = 0 Until l
			bc:+1
			c = s[i]
			If c<128 
				b[bc] = c
				Continue
			End If
			i:+1
			d=s[i]
			If c<224 
				b[bc] = (c-192)*64+(d-128)
				Continue
			End If
			i:+1
			e = s[i]
			If c < 240 
				b[bc] = (c-224)*4096+(d-128)*64+(e-128)
				Continue
			End If
		Next
	
		Return String.fromshorts(b, bc + 1)
	End If
	
	Return ""
	
End Function

' converts a Max short-based String to a byte-based UTF-8 String.
' based on the TextStream UTF code...
Function _convertMaxToUTF8:String(text:String)
	If Not text Then
		Return ""
	End If
	
	Local l:Int = text.length
	If l = 0 Then
		Return ""
	End If
	
	Local count:Int = 0
	Local s:Byte[] = New Byte[l * 3] ' max possible is 3 x original size.
	
	For Local i:Int = 0 Until l
		Local char:Int = text[i]

		If char < 128 Then
			s[count] = char
			count:+ 1
			Continue
		Else If char<2048
			s[count] = char/64 | 192
			count:+ 1
			s[count] = char Mod 64 | 128
			count:+ 1
			Continue
		Else
			s[count] =  char/4096 | 224
			count:+ 1
			s[count] = char/64 Mod 64 | 128
			count:+ 1
			s[count] = char Mod 64 | 128
			count:+ 1
			Continue
		EndIf
		
	Next

	Return String.fromBytes(s, count)
End Function

Rem
bbdoc: Log Errors.
about: Only actual error conditions will be logged.
End Rem
Const LOG_ERRORS:Int = 0
Rem
bbdoc: Log Warnings.
about: Warnings will be logged as well.
End Rem
Const LOG_WARNINGS:Int = 1
Rem
bbdoc: Log Standard.
about: Basic events will be logged (Default level).
End Rem
Const LOG_STANDARD:Int = 2
Rem
bbdoc: Log informative.
about: Useful tracing (Object creations etc) information will be logged.
End Rem
Const LOG_INFORMATIVE:Int = 3
Rem
bbdoc: Log Insane.
about: Mostly everything gets logged (use For heavy tracing only, Log WILL be big).
End Rem
Const LOG_INSANE:Int = 4

