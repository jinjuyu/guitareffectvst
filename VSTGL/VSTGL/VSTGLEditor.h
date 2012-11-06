//	VSTGLEditor.h - Editor window for a VST plugin using OpenGL to handle all
//					the drawing.
//	---------------------------------------------------------------------------
//	Copyright (c) 2005-2006 Niall Moody
//	
//	Permission is hereby granted, free of charge, to any person obtaining a
//	copy of this software and associated documentation files (the "Software"),
//	to deal in the Software without restriction, including without limitation
//	the rights to use, copy, modify, merge, publish, distribute, sublicense,
//	and/or sell copies of the Software, and to permit persons to whom the
//	Software is furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//	DEALINGS IN THE SOFTWARE.
//	---------------------------------------------------------------------------
#pragma once
#pragma warning( disable : 4996 4819)


#include "aeffeditor.h"

#include <windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

///	Editor window for VST plugins, using OpenGL to handle all the drawing.
/*!
	This is a fairly basic implementation - it'll set up an opengl context
	for you, and provides a couple of options (vertical sync, antialiasing)
	for that context, and the usual mouse and key event methods.

	It's derived from AEffEditor, so that class' methods are available, but
	note that VSTGLEditor subclasses should not use the open() and close()
	methods - to make the interface a bit more object-oriented, and hopefully,
	easier to use, subclasses should use guiOpen() and guiClose() instead.
	VSTGLEditor uses open() and close() to set up and clean up various
	platform-specific variables, and call the aforementioned methods when
	it's safe to do so.  This means you no longer have to put the ugly
	VSTGLEditor::open(ptr); line at the top of your open() method.

	If you're upgrading from the previous version of VSTGL, please make sure
	you move your open() and close() code to guiOpen() and guiClose(),
	respectively.  The other change is that idle() is no longer hardwired to
	update the gui - it's now up to your subclass to decide if you want to
	do it that way (I've included a simple message-based timer class to
	provide a better update frequency as an alternative).  To update the
	opengl context, call refreshGraphics() - this will make sure the context's
	set up, call draw(), and then swap the buffers to display your changes
	on screen.

	\sa Timer

	\todo Shared contexts?
	\todo Implement simple Mouse class (so we can hide and show the cursor,
	mainly).
	\todo Test key events.
 */
class VSTGLEditor : public AEffEditor
{
  public:
	///	Enum containing various flags to set certain properties of the window.
	typedef enum
	{
		DefaultFlags = 0,	///<Specifies a default opengl window.
		WaitForVerticalSync,///<Specifies that drawing may only take place between the monitor's vertical refreshes.
		Antialias2x,		///<Specifies the drawing should use 2x hardware antialiasing if the graphics card supports it.
		Antialias4x,		///<Specifies the drawing should use 4x hardware antialiasing if the graphics card supports it.
		Antialias6x			///<Specifies the drawing should use 6x hardware antialiasing if the graphics card supports it.
	} WindowFlags;

	///	Constructor.
	/*!
		\param effect Pointer to the plugin class.
		\param flags An OR-ed combination of flags to set certain attributes
		of the opengl window.  The antialias flags are mutually exclusive.
		Note: I have observed very high cpu usage on my windows laptop if I
		have multiple VSTGL windows open with the WaitForVerticalSync flag
		set.  I suspect it's probably a graphics card issue (mine's an ATI
		Mobility Radeon 9600/9700 series apparently), but not having another
		windows machine to test on I don't know for sure - it works fine on
		my macmini.  Also note that not all graphics cards can support
		hardware antialiasing - it might be safest to use 2x or 4x just in
		case.

		\sa WindowFlags
	 */
	VSTGLEditor(AudioEffect *effect, WindowFlags flags=DefaultFlags);
	///	Destructor.
	virtual ~VSTGLEditor();

	///	Returns the size of the editor, so the host can provide the correct-sized window.
	bool getRect(ERect **rect) {*rect = &_rect; return true;};
	///	Called by the host once the window's been created, so we can set stuff up in it.
	/*!
		We hide this from subclasses, because we need to do platform-specific
		stuff in it.  Subclasses can use guiOpen() to be informed of the
		editor's window is opened.

		DO NOT ATTEMPT TO OVERRIDE THIS!!!!  (The compiler probably won't
		throw up an error, but the opengl context will not be set up,
		resulting in a blank window, and possibly a crash.)
	 */
	bool open(void *ptr);
	///	Called when the editor's window is opened.
	virtual void guiOpen() = 0;
	///	Called by the host just before the window is destroyed/closed.
	/*!
		We hide this from subclasses, because we need to do platform-specific
		stuff in it.  Subclasses can use guiClose() to be informed of the
		editor's window being closed.

		DO NOT ATTEMPT TO OVERRIDE THIS!!!!  (The compiler probably won't
		throw up an error, but the opengl context will not be cleaned up,
		which could be very bad.)
	 */
	void close();
	///	Called when the editor's window is closed.
	virtual void guiClose() = 0;

	///	Called when there's a MouseDown event.
	/*!
		The buttons are numbered 1=left, 2=right, 3=middle.
	 */
	virtual void onMouseDown(int button, int x, int y) {};
	///	Called when there's a MouseMove event.
	/*!
		Note that you may find (on Windows anyway) that the x and y values
		passed in are outside the bounds of your editor if you drag the mouse
		outside it.
	 */
	virtual void onMouseMove(int x, int y) {};
	///	Called when there's a MouseUp event.
	/*!
		The buttons are numbered 1=left, 2=right, 3=middle.
	 */
	virtual void onMouseUp(int button, int x, int y) {};
	///	Called when there's a MouseWheel event.
	virtual void onMouseWheel(int wheel, int x, int y) {};
	///	Called when there's a KeyDown event (GL because the VST headers already use onKeyDown).
	/*!
		\todo test whether the key mapping's correct.
	 */
	virtual void onGLKeyDown(const VstKeyCode& key) {};
	///	Called when there's a KeyUp event (GL because the VST headers already use onKeyUp).
	/*!
		\todo test whether the key mapping's correct.
	 */
	virtual void onGLKeyUp(const VstKeyCode& key) {};

	///	This is the method where everything gets drawn.
	/*!
		It's into here that you'll want to put your drawing code in
		subclasses.
	 */
	virtual void draw() = 0;
	///	This method wraps draw().
	/*!
		This method performs necessary setup and cleanup for a draw()
		operation - what it does is call setupContext(), draw(),
		swapBuffers().  If you want to update your graphics repeatedly, the
		simplest thing to do is just stick this in idle().
	 */
	void refreshGraphics();

	///	You'd call this from your plugin if you wanted to update the gui when your parameters change.
	/*!
		\todo Is it really necessary to have this in VSTGLEditor?
	 */
	virtual void setParameter(int index, float value) {};

	///	Returns the x position of the window/context.
	int getX() const {return _rect.left;};
	///	Returns the y position of the window/context.
	int getY() const {return _rect.top;};
	///	Returns the width of the window/context.
	int getWidth() const {return _rect.right-_rect.left;};
	///	Returns the height of the window/context.
	int getHeight() const {return _rect.bottom-_rect.top;};
	///	Windows: Message loop - we use this to intercept mouse messages, among other things.
	static LONG WINAPI GLWndProc(HWND hwnd,
								 UINT message,
								 WPARAM wParam,
								 LPARAM lParam);

  protected:
	///	Helper method, needs to be called before any drawing takes place.
	void setupContext();
	///	Helper method, needs to be called after drawing has taken place.
	void swapBuffers();

	///	Call this to set your window's bounds in subclass constructors.
	void setRect(int x, int y, int width, int height);
  private:
	///	Used to create the actual window when open() is called.
	/*!
		Only necessary on Windows (and only really for Tracktion, which does
		things kind of strange).
	 */
	void createWindow();

	///	Helper method:  Used to setup Vertical Sync.
	/*!
		Checks if Vertical Sync is supported, and switches it on if it is.
		This method is only called if the user specified WaitForVerticalSync
		as one of the flags to the class' constructor.
	 */
	void setupVSync();
	///	Helper method: Tries to set up hardware antialiasing.
	/*!
		Checks if hardware antialiasing is supported, and switches it on if
		it is.  This method is only called if the user specified one of the
		Antialias WindowFlags in the class' constructor.

		Because of the different way the OS' work, this only sets up
		antialiasing on Windows - for OSX it's done in open().
	 */
	void setupAntialiasing();

	///	Windows: Windows rendering context.
	HGLRC glRenderingContext;
	///	Windows: Holds a handle to the window we created in createWindow().
	HWND tempHWnd;
	///	Windows: Device context for our window.
	HDC dc;
	///	Windows: The pixel format we want to use for the window.
	PIXELFORMATDESCRIPTOR pixelformat;
	///	The rect our opengl context is contained within.
	ERect _rect;

	///	Whether or not to use Vertical Sync.
	bool useVSync;
	///	The level of antialiasing to use.
	int antialiasing;
};


//Documentation Main Page.
/*!
	\mainpage
	VSTGL is a simple AEffEditor subclass which provides basic opengl support
	for VST plugins on Windows and OSX.

	For this release I've refactored the code substantially, so you'll have to
	alter any code you had that used the previous version - it should be a lot
	nicer now though.  Make sure you read the VSTGLEditor documentation to
	see what's changed.  Major additions include a simple message-based timer,
	so you don't have to rely on the host's (generally rubbish, in my
	experience) idle() implementation for screen updates, and support for
	vertical sync and hardware antialiasing.

	This version is also compatible with VST 2.4 (while remaining
	backward-compatible with VST 2.3).

	- Niall Moody (04/03/2006).
 */

