/***********************************************************************
	filename: 	CEGUIEditbox.cpp
	created:	13/4/2004
	author:		Paul D Turner
	
	purpose:	Implementation of Editbox base class widget
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
#include "elements/CEGUIEditbox.h"
#include "CEGUITextUtils.h"
#include "CEGUIExceptions.h"
#include "CEGUIFont.h"
#include <pcre.h>
#include <string.h>


// Start of CEGUI namespace section
namespace CEGUI
{
const String Editbox::EventNamespace("Editbox");
const String Editbox::WidgetTypeName("CEGUI/Editbox");

/*!
\brief
	Internal struct to contain compiled regex string
*/
struct RegexValidator
{
	RegexValidator(void) : d_regex(0) {}
	~RegexValidator(void) { release(); }

	void release()
	{
		if (d_regex != 0)
		{
			pcre_free(d_regex);
			d_regex = 0;
		}

	}

	pcre* d_regex;
};

/*************************************************************************
    EditboxWindowRenderer
*************************************************************************/
EditboxWindowRenderer::EditboxWindowRenderer(const String& name) :
    WindowRenderer(name, Editbox::EventNamespace)
{
}

/*************************************************************************
	TODO:

	Clipboard support
	Undo support
*************************************************************************/
/*************************************************************************
	Definition of Properties
*************************************************************************/
EditboxProperties::ReadOnly					Editbox::d_readOnlyProperty;
EditboxProperties::MaskText					Editbox::d_maskTextProperty;
EditboxProperties::MaskCodepoint			Editbox::d_maskCodepointProperty;
EditboxProperties::ValidationString			Editbox::d_validationStringProperty;
EditboxProperties::CaratIndex				Editbox::d_caratIndexProperty;
EditboxProperties::SelectionStart			Editbox::d_selectionStartProperty;
EditboxProperties::SelectionLength			Editbox::d_selectionLengthProperty;
EditboxProperties::MaxTextLength			Editbox::d_maxTextLengthProperty;


/*************************************************************************
	Event name constants
*************************************************************************/
const String Editbox::EventReadOnlyModeChanged( "ReadOnlyChanged" );
const String Editbox::EventMaskedRenderingModeChanged( "MaskRenderChanged" );
const String Editbox::EventMaskCodePointChanged( "MaskCPChanged" );
const String Editbox::EventValidationStringChanged( "ValidatorChanged" );
const String Editbox::EventMaximumTextLengthChanged( "MaxTextLenChanged" );
const String Editbox::EventTextInvalidated( "TextInvalidated" );
const String Editbox::EventInvalidEntryAttempted( "InvalidInputAttempt" );
const String Editbox::EventCaratMoved( "TextCaratMoved" );
const String Editbox::EventTextSelectionChanged( "TextSelectChanged" );
const String Editbox::EventEditboxFull( "EditboxFull" );
const String Editbox::EventTextAccepted( "TextAccepted" );


/*************************************************************************
	Constructor for Editbox class.
*************************************************************************/
Editbox::Editbox(const String& type, const String& name) :
	Window(type, name),
	d_readOnly(false),
	d_maskText(false),
	d_maskCodePoint('*'),
	d_maxTextLen(String::max_size()),
	d_caratPos(0),
	d_selectionStart(0),
	d_selectionEnd(0),
    d_validator(new RegexValidator),
	d_dragging(false)
{
	addEditboxProperties();

	// default to accepting all characters
	setValidationString(".*");
}


/*************************************************************************
	Destructor for Editbox class.
*************************************************************************/
Editbox::~Editbox(void)
{
	delete d_validator;
}


/*************************************************************************
	return true if the Editbox has input focus.
*************************************************************************/
bool Editbox::hasInputFocus(void) const
{
	return isActive();
}


/*************************************************************************
	return true if the Editbox text is valid given the currently set
	validation string.
*************************************************************************/
bool Editbox::isTextValid(void) const
{
	return isStringValid(d_text);
}


/*************************************************************************
	return the current selection start point.
*************************************************************************/
size_t Editbox::getSelectionStartIndex(void) const
{
	return (d_selectionStart != d_selectionEnd) ? d_selectionStart : d_caratPos;
}


/*************************************************************************
	return the current selection end point.
*************************************************************************/
size_t Editbox::getSelectionEndIndex(void) const
{
	return (d_selectionStart != d_selectionEnd) ? d_selectionEnd : d_caratPos;
}


/*************************************************************************
	return the length of the current selection
	(in code points / characters).
*************************************************************************/
size_t Editbox::getSelectionLength(void) const
{
	return d_selectionEnd - d_selectionStart;
}


/*************************************************************************
	Specify whether the Editbox is read-only.
*************************************************************************/
void Editbox::setReadOnly(bool setting)
{
	// if setting is changed
	if (d_readOnly != setting)
	{
		d_readOnly = setting;
		WindowEventArgs args(this);
		onReadOnlyChanged(args);
	}

}


/*************************************************************************
	Specify whether the text for the Editbox will be rendered masked.
*************************************************************************/
void Editbox::setTextMasked(bool setting)
{
	// if setting is changed
	if (d_maskText != setting)
	{
		d_maskText = setting;
		WindowEventArgs args(this);
		onMaskedRenderingModeChanged(args);
	}

}


/*************************************************************************
	Set the text validation string.
*************************************************************************/
void Editbox::setValidationString(const String& validation_string)
{
	if (d_validationString != validation_string)
	{
		d_validationString = validation_string;
		d_validator->release();

		// try to compile this new regex string
		const char* prce_error;
		int pcre_erroff;
		d_validator->d_regex = pcre_compile(d_validationString.c_str(), PCRE_UTF8, &prce_error, &pcre_erroff, 0);

		// handle failure
		if (d_validator->d_regex == 0)
		{
			throw InvalidRequestException("The Editbox named '" + getName() + "' had the following bad validation expression set: '" + validation_string + "'.  Additional Information: " + prce_error);			
		}

		// notification
		WindowEventArgs args(this);
		onValidationStringChanged(args);

		if (!isTextValid())
		{
			// also notify if text is now invalid.
			onTextInvalidatedEvent(args);
		}

	}

}


/*************************************************************************
	Set the current position of the carat.
*************************************************************************/
void Editbox::setCaratIndex(size_t carat_pos)
{
	// make sure new position is valid
	if (carat_pos > d_text.length())
	{
		carat_pos = d_text.length();
	}

	// if new position is different
	if (d_caratPos != carat_pos)
	{
		d_caratPos = carat_pos;

		// Trigger "carat moved" event
		WindowEventArgs args(this);
		onCaratMoved(args);
	}

}


/*************************************************************************
	Define the current selection for the Editbox
*************************************************************************/
void Editbox::setSelection(size_t start_pos, size_t end_pos)
{
	// ensure selection start point is within the valid range
	if (start_pos > d_text.length())
	{
		start_pos = d_text.length();
	}

	// ensure selection end point is within the valid range
	if (end_pos > d_text.length())
	{
		end_pos = d_text.length();
	}

	// ensure start is before end
	if (start_pos > end_pos)
	{
		size_t tmp = end_pos;
		end_pos = start_pos;
		start_pos = tmp;
	}

	// only change state if values are different.
	if ((start_pos != d_selectionStart) || (end_pos != d_selectionEnd))
	{
		// setup selection
		d_selectionStart = start_pos;
		d_selectionEnd	 = end_pos;

		// Trigger "selection changed" event
		WindowEventArgs args(this);
		onTextSelectionChanged(args);
	}

}


/*************************************************************************
	set the utf32 code point used when rendering masked text.
*************************************************************************/
void Editbox::setMaskCodePoint(utf32 code_point)
{
	if (code_point != d_maskCodePoint)
	{
		d_maskCodePoint = code_point;

		// Trigger "mask code point changed" event
		WindowEventArgs args(this);
		onMaskCodePointChanged(args);
	}

}


/*************************************************************************
	set the maximum text length for this Editbox.
*************************************************************************/
void Editbox::setMaxTextLength(size_t max_len)
{
	if (d_maxTextLen != max_len)
	{
		d_maxTextLen = max_len;
		
		// Trigger max length changed event
		WindowEventArgs args(this);
		onMaximumTextLengthChanged(args);

		// trim string
		if (d_text.length() > d_maxTextLen)
		{
			d_text.resize(d_maxTextLen);
			onTextChanged(args);

			// see if new text is valid
			if (!isTextValid())
			{
				// Trigger Text is invalid event.
				onTextInvalidatedEvent(args);
			}

		}

	}

}


/*************************************************************************
	Clear the current selection setting	
*************************************************************************/
void Editbox::clearSelection(void)
{
	// perform action only if required.
	if (getSelectionLength() != 0)
	{
		setSelection(0, 0);
	}

}


/*************************************************************************
	Erase the currently selected text.
*************************************************************************/
void Editbox::eraseSelectedText(bool modify_text)
{
	if (getSelectionLength() != 0)
	{
		// setup new carat position and remove selection highlight.
		setCaratIndex(getSelectionStartIndex());
		clearSelection();

		// erase the selected characters (if required)
		if (modify_text)
		{
			d_text.erase(getSelectionStartIndex(), getSelectionLength());

			// trigger notification that text has changed.
			WindowEventArgs args(this);
			onTextChanged(args);
		}

	}

}


/*************************************************************************
	return true if the given string matches the validation regular
	expression.	
*************************************************************************/
bool Editbox::isStringValid(const String& str) const
{
	// if the regex is not valid, then an exception is thrown
	if (d_validator->d_regex == 0)
	{
		throw InvalidRequestException("Editbox::isStringValid - An attempt was made to use the invalid RegEx '" + d_validationString + "'.");
	}

	const char* utf8str = str.c_str();
	int	match[3];
	int len = static_cast<int>(strlen(utf8str));
	int result = pcre_exec(d_validator->d_regex, 0, utf8str, len, 0, 0, match, 3);

	if (result >= 0)
	{
		// this ensures that any regex match is for the entire string
		return (match[1] - match[0] == len);
	}
	// invalid string if there's no match or if string or regex is NULL.
	else if ((result == PCRE_ERROR_NOMATCH) || (result == PCRE_ERROR_NULL))
	{
		return false;
	}
	// anything else is an error.
	else
	{
		throw InvalidRequestException("Editbox::isStringValid - An internal error occurred while attempting to match the invalid RegEx '" + d_validationString + "'.");
	}

}


/*************************************************************************
	Handler for mouse button pushed events
*************************************************************************/
void Editbox::onMouseButtonDown(MouseEventArgs& e)
{
	// base class handling
	Window::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		// grab inputs
		if (captureInput())
		{
			// handle mouse down
			clearSelection();
			d_dragging = true;
			d_dragAnchorIdx = getTextIndexFromPosition(e.position);
			setCaratIndex(d_dragAnchorIdx);
		}

		e.handled = true;
	}

}

/*************************************************************************
	Handler for mouse button release events
*************************************************************************/
void Editbox::onMouseButtonUp(MouseEventArgs& e)
{
	// base class processing
	Window::onMouseButtonUp(e);

	if (e.button == LeftButton)
	{
		releaseInput();
		e.handled = true;
	}

}


/*************************************************************************
	Handler for mouse double-clicks
*************************************************************************/
void Editbox::onMouseDoubleClicked(MouseEventArgs& e)
{
	// base class processing
	Window::onMouseDoubleClicked(e);

	if (e.button == LeftButton)
	{
		// if masked, set up to select all
		if (isTextMasked())
		{
			d_dragAnchorIdx = 0;
			setCaratIndex(d_text.length());
		}
		// not masked, so select the word that was double-clicked.
		else
		{
			d_dragAnchorIdx = TextUtils::getWordStartIdx(d_text, (d_caratPos == d_text.length()) ? d_caratPos : d_caratPos + 1);
			d_caratPos		= TextUtils::getNextWordStartIdx(d_text, d_caratPos);
		}

		// perform actual selection operation.
		setSelection(d_dragAnchorIdx, d_caratPos);

		e.handled = true;
	}

}


/*************************************************************************
	Handler for mouse triple-clicks
*************************************************************************/
void Editbox::onMouseTripleClicked(MouseEventArgs& e)
{
	// base class processing
	Window::onMouseTripleClicked(e);

	if (e.button == LeftButton)
	{
		d_dragAnchorIdx = 0;
		setCaratIndex(d_text.length());
		setSelection(d_dragAnchorIdx, d_caratPos);
		e.handled = true;
	}

}


/*************************************************************************
	Handler for mouse movements
*************************************************************************/
void Editbox::onMouseMove(MouseEventArgs& e)
{
	// base class processing
	Window::onMouseMove(e);

	if (d_dragging)
	{
		setCaratIndex(getTextIndexFromPosition(e.position));
		setSelection(d_caratPos, d_dragAnchorIdx);
	}

	e.handled = true;
}

/*************************************************************************
	Handler for when input capture is lost
*************************************************************************/
void Editbox::onCaptureLost(WindowEventArgs& e)
{
	d_dragging = false;

	// base class processing
	Window::onCaptureLost(e);

	e.handled = true;
}

/*************************************************************************
	Handler for type characters
*************************************************************************/
void Editbox::onCharacter(KeyEventArgs& e)
{
	// base class processing
	Window::onCharacter(e);

	// only need to take notice if we have focus
	if (hasInputFocus() && getFont()->isCodepointAvailable(e.codepoint) && !isReadOnly())
	{
		// backup current text
		String tmp(d_text);
		tmp.erase(getSelectionStartIndex(), getSelectionLength());

		// if there is room
		if (tmp.length() < d_maxTextLen)
		{
			tmp.insert(getSelectionStartIndex(), 1, e.codepoint);

			if (isStringValid(tmp))
			{
				// erase selection using mode that does not modify d_text (we just want to update state)
				eraseSelectedText(false);

                // advance carat (done first so we can "do stuff" in event handlers!)
                d_caratPos++;

                // set text to the newly modified string
				setText(tmp);

                // char was accepted into the Editbox - mark event as handled.
                e.handled = true;
			}
			else
			{
				// Trigger invalid modification attempted event.
				WindowEventArgs args(this);
				onInvalidEntryAttempted(args);
			}

		}
		else
		{
			// Trigger text box full event
			WindowEventArgs args(this);
			onEditboxFullEvent(args);
		}

	}

    // event was (possibly) not handled
}


/*************************************************************************
	Handler for key-down events
*************************************************************************/
void Editbox::onKeyDown(KeyEventArgs& e)
{
	// base class processing
	Window::onKeyDown(e);

	if (hasInputFocus() && !isReadOnly())
	{
		WindowEventArgs args(this);
		switch (e.scancode)
		{
		case Key::LeftShift:
		case Key::RightShift:
			if (getSelectionLength() == 0)
			{
				d_dragAnchorIdx = getCaratIndex();
			}
			break;

		case Key::Backspace:
			handleBackspace();
			break;

		case Key::Delete:
			handleDelete();
			break;

		case Key::Tab:
		case Key::Return:
		case Key::NumpadEnter:
			// Fire 'input accepted' event
			onTextAcceptedEvent(args);
			break;

		case Key::ArrowLeft:
			if (e.sysKeys & Control)
			{
				handleWordLeft(e.sysKeys);
			}
			else
			{
				handleCharLeft(e.sysKeys);
			}
			break;

		case Key::ArrowRight:
			if (e.sysKeys & Control)
			{
				handleWordRight(e.sysKeys);
			}
			else
			{
				handleCharRight(e.sysKeys);
			}
			break;

		case Key::Home:
			handleHome(e.sysKeys);
			break;

		case Key::End:
			handleEnd(e.sysKeys);
			break;

        // default case is now to leave event as (possibly) unhandled.
        default:
            return;
		}

		e.handled = true;
	}

}


/*************************************************************************
	Processing for backspace key	
*************************************************************************/
void Editbox::handleBackspace(void)
{
	if (!isReadOnly())
	{
		String tmp(d_text);

		if (getSelectionLength() != 0)
		{
			tmp.erase(getSelectionStartIndex(), getSelectionLength());

			if (isStringValid(tmp))
			{
				// erase selection using mode that does not modify d_text (we just want to update state)
				eraseSelectedText(false);

				// set text to the newly modified string
				setText(tmp);
			}
			else
			{
				// Trigger invalid modification attempted event.
				WindowEventArgs args(this);
				onInvalidEntryAttempted(args);
			}

		}
		else if (getCaratIndex() > 0)
		{
			tmp.erase(d_caratPos - 1, 1);

			if (isStringValid(tmp))
			{
				setCaratIndex(d_caratPos - 1);

				// set text to the newly modified string
				setText(tmp);
			}
			else
			{
				// Trigger invalid modification attempted event.
				WindowEventArgs args(this);
				onInvalidEntryAttempted(args);
			}

		}

	}

}


/*************************************************************************
	Processing for Delete key	
*************************************************************************/
void Editbox::handleDelete(void)
{
	if (!isReadOnly())
	{
		String tmp(d_text);

		if (getSelectionLength() != 0)
		{
			tmp.erase(getSelectionStartIndex(), getSelectionLength());

			if (isStringValid(tmp))
			{
				// erase selection using mode that does not modify d_text (we just want to update state)
				eraseSelectedText(false);

				// set text to the newly modified string
				setText(tmp);
			}
			else
			{
				// Trigger invalid modification attempted event.
				WindowEventArgs args(this);
				onInvalidEntryAttempted(args);
			}

		}
		else if (getCaratIndex() < tmp.length())
		{
			tmp.erase(d_caratPos, 1);

			if (isStringValid(tmp))
			{
				// set text to the newly modified string
				setText(tmp);
			}
			else
			{
				// Trigger invalid modification attempted event.
				WindowEventArgs args(this);
				onInvalidEntryAttempted(args);
			}

		}

	}

}


/*************************************************************************
	Move the carat one character to the left.
*************************************************************************/
void Editbox::handleCharLeft(uint sysKeys)
{
	if (d_caratPos > 0)
	{
		setCaratIndex(d_caratPos - 1);
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}


/*************************************************************************
	Move the carat one word to the left
*************************************************************************/
void Editbox::handleWordLeft(uint sysKeys)
{
	if (d_caratPos > 0)
	{
		setCaratIndex(TextUtils::getWordStartIdx(d_text, getCaratIndex()));
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}


/*************************************************************************
	Move the carat one character to the right.
*************************************************************************/
void Editbox::handleCharRight(uint sysKeys)
{
	if (d_caratPos < d_text.length())
	{
		setCaratIndex(d_caratPos + 1);
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}


/*************************************************************************
	Move the carat one word to the right
*************************************************************************/
void Editbox::handleWordRight(uint sysKeys)
{
	if (d_caratPos < d_text.length())
	{
		setCaratIndex(TextUtils::getNextWordStartIdx(d_text, getCaratIndex()));
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}


/*************************************************************************
	Move the carat to the start of the text
*************************************************************************/
void Editbox::handleHome(uint sysKeys)
{
	if (d_caratPos > 0)
	{
		setCaratIndex(0);
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}


/*************************************************************************
	Move the carat to the end of the text.	
*************************************************************************/
void Editbox::handleEnd(uint sysKeys)
{
	if (d_caratPos < d_text.length())
	{
		setCaratIndex(d_text.length());
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}


/*************************************************************************
	Event fired internally when the read only state of the Editbox has
	been changed
*************************************************************************/
void Editbox::onReadOnlyChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventReadOnlyModeChanged, e, EventNamespace);
}


/*************************************************************************
	Event fired internally when the masked rendering mode (password mode)
	has been changed
*************************************************************************/
void Editbox::onMaskedRenderingModeChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventMaskedRenderingModeChanged , e, EventNamespace);
}


/*************************************************************************
	Event fired internally when the code point to use for masked
	rendering has been changed.
*************************************************************************/
void Editbox::onMaskCodePointChanged(WindowEventArgs& e)
{
	// if we are in masked mode, trigger a GUI redraw.
	if (isTextMasked())
	{
		requestRedraw();
	}

	fireEvent(EventMaskCodePointChanged , e, EventNamespace);
}


/*************************************************************************
	Event fired internally when the validation string is changed.	
*************************************************************************/
void Editbox::onValidationStringChanged(WindowEventArgs& e)
{
	fireEvent(EventValidationStringChanged , e, EventNamespace);
}


/*************************************************************************
	Event fired internally when the maximum text length for the edit box
	is changed.	
*************************************************************************/
void Editbox::onMaximumTextLengthChanged(WindowEventArgs& e)
{
	fireEvent(EventMaximumTextLengthChanged , e, EventNamespace);
}


/*************************************************************************
	Event fired internally when something has caused the current text to
	now fail validation	
*************************************************************************/
void Editbox::onTextInvalidatedEvent(WindowEventArgs& e)
{
	fireEvent(EventTextInvalidated, e, EventNamespace);
}


/*************************************************************************
	Event fired internally when the user attempted to make a change to
	the edit box that would have caused it to fail validation.
*************************************************************************/
void Editbox::onInvalidEntryAttempted(WindowEventArgs& e)
{
	fireEvent(EventInvalidEntryAttempted , e, EventNamespace);
}


/*************************************************************************
	Event fired internally when the carat (insert point) position changes.	
*************************************************************************/
void Editbox::onCaratMoved(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventCaratMoved , e, EventNamespace);
}


/*************************************************************************
	Event fired internally when the current text selection changes.	
*************************************************************************/
void Editbox::onTextSelectionChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventTextSelectionChanged , e, EventNamespace);
}


/*************************************************************************
	Event fired internally when the edit box text has reached the set
	maximum length.	
*************************************************************************/
void Editbox::onEditboxFullEvent(WindowEventArgs& e)
{
	fireEvent(EventEditboxFull, e, EventNamespace);
}


/*************************************************************************
	Event fired internally when the user accepts the edit box text by
	pressing Return, Enter, or Tab.	
*************************************************************************/
void Editbox::onTextAcceptedEvent(WindowEventArgs& e)
{
	fireEvent(EventTextAccepted, e, EventNamespace);
}


/*************************************************************************
	Handler for when text is changed programmatically
*************************************************************************/
void Editbox::onTextChanged(WindowEventArgs& e)
{
	// base class processing
	Window::onTextChanged(e);

	// clear selection
	clearSelection();

	// make sure carat is within the text
	if (getCaratIndex() > d_text.length())
	{
		setCaratIndex(d_text.length());
	}

	e.handled = true;
}

/*************************************************************************
	Add properties
*************************************************************************/
void Editbox::addEditboxProperties(void)
{
	addProperty(&d_readOnlyProperty);
	addProperty(&d_maskTextProperty);
	addProperty(&d_maskCodepointProperty);
	addProperty(&d_validationStringProperty);
	addProperty(&d_caratIndexProperty);
	addProperty(&d_selectionStartProperty);
	addProperty(&d_selectionLengthProperty);
	addProperty(&d_maxTextLengthProperty);
}

/*************************************************************************
    Return the text code point index that is rendered closest to the
    given screen position
*************************************************************************/
size_t Editbox::getTextIndexFromPosition(const Point& pt) const
{
    if (d_windowRenderer != 0)
    {
        EditboxWindowRenderer* wr = (EditboxWindowRenderer*)d_windowRenderer;
        return wr->getTextIndexFromPosition(pt);
    }
    else
    {
        //return getTextIndexFromPosition_impl(pt);
        throw InvalidRequestException("Editbox::getTextIndexFromPosition - This function must be implemented by the window renderer");
    }
}

} // End of  CEGUI namespace section
