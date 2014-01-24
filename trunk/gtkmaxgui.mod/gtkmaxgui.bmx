' Copyright (c) 2006-2014 Bruce A Henderson
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
bbdoc: MaxGUI Linux GTK Driver
about: This modules provides a Linux GTK driver for #maxgui.maxgui.MAXGUI.
End Rem
Module BaH.GTKMaxGUI

ModuleInfo "Version: 1.21"
ModuleInfo "License: MIT"
ModuleInfo "Copyright: 2006-2014 Bruce A Henderson"
ModuleInfo "Modserver: BRL"

ModuleInfo "History: 1.21"
ModuleInfo "History: Fixed low-level event handling issues."
ModuleInfo "History: Added missing consts."
ModuleInfo "History: Removed pointer offsets!"
ModuleInfo "History: Fixed pango font desc issues."
ModuleInfo "History: Use ToUTF8String() method for string conversions."
ModuleInfo "History: Fixed applying tooltips to separators."
ModuleInfo "History: 1.20"
ModuleInfo "History: Changed to use new Maxgui namespace."
ModuleInfo "History: Removed pixmap field from TGTKIconStrip."
ModuleInfo "History: Fixed window activate showing window if not visible."
ModuleInfo "History: Added support for PANELPIXMAP_FIT2."
ModuleInfo "History: Fixed generation of radio button 'clicks' when calling SetGadgetState."
ModuleInfo "History: Modified number of action emits when radio button changed."
ModuleInfo "History: Added support for GetClass()."
ModuleInfo "History: Added basic sensitivity support."
ModuleInfo "History: Added SetPixmap support for menu items."
ModuleInfo "History: Added GetTooltip support."
ModuleInfo "History: Added LoadFontWithDouble support."
ModuleInfo "History: Fixed slowdown issues with BlitzMax 1.32."
ModuleInfo "History: Improved hotkey/menu item support."
ModuleInfo "History: Fixed menus not returning correct state."
ModuleInfo "History: Fixed tabber not setting extra data. Modified listbox and combobox for same."
ModuleInfo "History: Don't assume menuitem parent is attached to a menu."
ModuleInfo "History: 1.19"
ModuleInfo "History: Fixed x,y coords returned by Panel MouseMove events. Now calculated relative to parent widget."
ModuleInfo "History: 1.18"
ModuleInfo "History: Fixed generation of GADGETSELECT on TreeView creation."
ModuleInfo "History: Fixed loss of next text change event after setting empty text field to empty."
ModuleInfo "History: 1.17"
ModuleInfo "History: Added FormatTextAreaBackground support."
ModuleInfo "History: 1.16"
ModuleInfo "History: Added visible field to TGTKGadget to control generation of events."
ModuleInfo "History: 1.15"
ModuleInfo "History: UTF-8 fix for RequestFile filters and RequestDir path."
ModuleInfo "History: Added text attribute with GetText and SetText methods to TreeNode."
ModuleInfo "History: 1.14"
ModuleInfo "History: Fixed non-resizable window resizing problem with menus and statusbar changes."
ModuleInfo "History: Fixed ComboBox not clearing items."
ModuleInfo "History: Rewrite of UTF-8 handling... *sigh*"
ModuleInfo "History: Fixed UTF-8 issues with Notify, Confirm, Proceed, RequestFile and RequestDir."
ModuleInfo "History: 1.13"
ModuleInfo "History: New popupmenu functionality."
ModuleInfo "History: Added EVENT_MOUSEWHEEL events for canvas and active panels."
ModuleInfo "History: Added EVENT_KEYDOWN and EVENT_KEYUP events for active panels."
ModuleInfo "History: Added EVENT_KEYCHAR events for canvas and active panels."
ModuleInfo "History: Added EVENT_KEYREPEAT for Canvas and active panels."
ModuleInfo "History: Fixed canvas mouse up not reporting button data."
ModuleInfo "History: Fixed canvas generating double ACTIVATE_REDRAWs."
ModuleInfo "History: Fixed some key mappings."
ModuleInfo "History: Fixed PANELPIXMAP_TILE not resetting to 0,0."
ModuleInfo "History: Fixed panel redraw event handling."
ModuleInfo "History: 1.12"
ModuleInfo "History: Added mouse Down/Menu events for label."
ModuleInfo "History: Added Enter/Leave events for buttons."
ModuleInfo "History: Removed requester leaks. Code clean-up."
ModuleInfo "History: Added SetButtonPixmap function."
ModuleInfo "History: Panel now raises GADGETPAINT event when repaint required."
ModuleInfo "History: Gadget ACTIVATE_REDRAW now raises GADGETPAINT event."
ModuleInfo "History: 1.11"
ModuleInfo "History: Fixed listbox generating selection event on initialisation."
ModuleInfo "History: 1.10"
ModuleInfo "History: Fixes ActiveGadget crash if no active widget on a window."
ModuleInfo "History: Added Enter/Leave events for labels."
ModuleInfo "History: Fixed text color setting for labels and buttons."
ModuleInfo "History: Added GTK_USE_STOCK_ITEMS global int. Enabled by default. Set it to False to disable on-the-fly conversion of gadgets showing stock-items (image/text/shortcut)"
ModuleInfo "History: Fixed statusbar disappearing with no text."
ModuleInfo "History: 1.09"
ModuleInfo "History: i18n enhancement - GTKTextArea.areaText and gadgets GetText now return ISO8859 strings."
ModuleInfo "History: 1.08"
ModuleInfo "History: Split out HTML views into separate modules - see bah.gtkwebgtkhtml and bah.gtkwebmozilla."
ModuleInfo "History: Fixed double-ampersand text displaying."
ModuleInfo "History: Improved WINDOW_CLIENTCOORDS handling."
ModuleInfo "History: Improved gadget positioning - no negative coords!."
ModuleInfo "History: EVENT_MOUSEMOVE on panel/canvas now contain button-pressed value."
ModuleInfo "History: Improved gadgeted freeing."
ModuleInfo "History: 1.07"
ModuleInfo "History: Fixed framed panel height. Was too high."
ModuleInfo "History: HTMLView now uses gtkmozembed."
ModuleInfo "History: 1.06"
ModuleInfo "History: Removed statusbar handle - theme issues."
ModuleInfo "History: Improved button state handling."
ModuleInfo "History: OpenURL now calls native-driver openurl."
ModuleInfo "History: Added panel pixmap TILE support."
ModuleInfo "History: Panel pixmaps can now be cleared."
ModuleInfo "History: Removed libgnomecanvas dependency."
ModuleInfo "History: Stepper now uses pixbuf to draw onto buttons."
ModuleInfo "History: Added menu (EVENT_GADGETMENU) support to buttons and textfield."
ModuleInfo "History: 1.05"
ModuleInfo "History: Fixed radiobutton problem with groups of more than two buttons."
ModuleInfo "History: SetHotKey now working for buttons."
ModuleInfo "History: Window statusbar text now supports three positions based on tabs."
ModuleInfo "History: 1.04"
ModuleInfo "History: *Engine Rewrite* - Now uses GtkLayout instead of gnomecanvas. Fixes a LOT of rendering anomolies. Should also be faster."
ModuleInfo "History: Changed tabber redrawing back."
ModuleInfo "History: Fixed check-menu issues with mnemonics and checking a menu initially with UncheckMenu."
ModuleInfo "History: Fixed group panel not setting text on create."
ModuleInfo "History: 1.03"
ModuleInfo "History: Fixed textfield SetText raising event."
ModuleInfo "History: Added mnemonic functionality for buttons."
ModuleInfo "History: Tweaked window client width/height to work on certain window types. Also takes into account status/menu heights on initial client height testing."
ModuleInfo "History: Fixed crash on app end after freeing canvas."
ModuleInfo "History: Fixed label SetText visuals."
ModuleInfo "History: 1.02"
ModuleInfo "History: Added panel pixmaps : currently only FIT, STRETCH and CENTER are working."
ModuleInfo "History: Fixed some issues with SetGadgetShape on a window. Now attempts to ignore SetShape-driven events."
ModuleInfo "History: 1.01"
ModuleInfo "History: Enabled child/parent window relationships with WINDOW_CHILD."
ModuleInfo "History: Fixed listbox left-click to raise SELECT event. Added listbox double-click ACTION event."
ModuleInfo "History: Added list/tree right-click MENU events."
ModuleInfo "History: Fixed tabber redrawing frenzy - hopefully."
ModuleInfo "History: More panel layout tweaking."
ModuleInfo "History: 1.00"
ModuleInfo "History: Added label, textarea, progressbar tooltip support."
ModuleInfo "History: Added progressbar GetValue()."
ModuleInfo "History: Changed combobox to extend TGTKList. Added combobox icon support."
ModuleInfo "History: Fixed combobox missing 'extra' data."
ModuleInfo "History: Fixed treeview Free() crash."
ModuleInfo "History: Tweaked menu SetSelected to work in a more 'Max' way..."
ModuleInfo "History: Keymapping improvements."
ModuleInfo "History: Implemented ACTIVATE_REDRAW, SelectTreeViewNode()."
ModuleInfo "History: Default F10 accel remapped to alt-F10 if app requires F10 hot key."
ModuleInfo "History: Modified window/panel layout code based on source from Simon Armstrong."
ModuleInfo "History: Added TEXTFORMAT_UNDERLINE and TEXTFORMAT_STRIKETHROUGH."
ModuleInfo "History: Added lost-focus handling - only enabled for textfield and textarea for now."
ModuleInfo "History: Added SetText, GetText methods."
ModuleInfo "History: Implemented UTF8/unicode string handling."
ModuleInfo "History: Added working stepper. It works, but it ain't nice..."
ModuleInfo "History: 0.99"
ModuleInfo "History: Improved textarea SetStyle speed - added setFastUpdate() method."
ModuleInfo "History: HTMLView fixes. NONAVIGATE now *correctly* raises event on link-click."
ModuleInfo "History: Added Window maximize/minimize state awareness, and Window restore."
ModuleInfo "History: Added WINDOW_TOOL functionality."
ModuleInfo "History: Added window setIcon() method."
ModuleInfo "History: Enabled EVENT_WINDOWACTIVATE. Added x,y,w,h to window size / move events. Enabled ActivateWindow()."
ModuleInfo "History: Added SetGadgetToolTip() function."
ModuleInfo "History: Fixed Tabber visual issues. Added Tabber icon support."
ModuleInfo "History: 0.98"
ModuleInfo "History: Fixed Panel position bug."
ModuleInfo "History: Fixed menu SetText issue."
ModuleInfo "History: Changed window sizing/positioning *again*. Still not entirely happy with it."
ModuleInfo "History: 0.97"
ModuleInfo "History: Tabber now supports tooltips. Tabber will show scroller if too many tabs."
ModuleInfo "History: TextField (pressing return) can now activate Default Gadget."
ModuleInfo "History: Added SetPointer()."
ModuleInfo "History: Fixed excessive window SIZE events."
ModuleInfo "History: Fixed List missing 'extra' data."
ModuleInfo "History: Fixed some Gadget freeing issues."
ModuleInfo "History: 0.96"
ModuleInfo "History: Changed order of generated textarea change events - SELECT before ACTION."
ModuleInfo "History: 0.95"
ModuleInfo "History: Added key-filtering."
ModuleInfo "History: 0.94"
ModuleInfo "History: TGTKButtonCheckBox now extends TGTKToggleButton like it was meant to. SetSelected now works for it :-p"
ModuleInfo "History: Textarea background color now setable. Textarea SetStyle now creates tags on the fly - rather than caching them - dunno if this will be a memory issue."
ModuleInfo "History: 0.93"
ModuleInfo "History: Fixed textarea clipboard actions. Fixed textarea setText. Fixed RequestFile save button text. Fixed font size issues. Fixed Tab sizing."
ModuleInfo "History: 0.92"
ModuleInfo "History: Added Canvas. Canvas key-down is repeating for now. Fixed some gadget Free() stuff."
ModuleInfo "History: 0.91"
ModuleInfo "History: Added radio buttons, popup menus, textarea improvements, tree node expand / collapse... etc"
ModuleInfo "History: 0.90"
ModuleInfo "History: Very Alpha preview... Lots of things work, lots of things don't!"

?Linux
' glib
ModuleInfo "CC_OPTS: -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/lib/x86_64-linux-gnu/glib-2.0/include"
' gtk
ModuleInfo "CC_OPTS: -I/usr/include/gtk-2.0  -I/usr/lib/i386-linux-gnu/gtk-2.0/include -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include"
' cairo
ModuleInfo "CC_OPTS: -I/usr/include/cairo"
' pango
ModuleInfo "CC_OPTS: -I/usr/include/pango-1.0"
' gdk
ModuleInfo "CC_OPTS: -I/usr/include/gdk-pixbuf-2.0"

Import "gtkgui.bmx"
?
