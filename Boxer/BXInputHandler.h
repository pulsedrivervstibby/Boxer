/* 
 Boxer is copyright 2010 Alun Bestor and contributors.
 Boxer is released under the GNU General Public License 2.0. A full copy of this license can be
 found in this XCode project at Resources/English.lproj/GNU General Public License.txt, or read
 online at [http://www.gnu.org/licenses/gpl-2.0.txt].
 */


//BXInputHandler is a generic class for responding to input. It expects OS X key and modifier
//constants, but does not directly accept NSEvents or interact with the OS X event framework:
//instead, it receives specific signals from Boxer's controller classes.

#import <Cocoa/Cocoa.h>

@class BXEmulator;

@interface BXInputHandler : NSObject
{
	BXEmulator *emulator;
	BOOL mouseActive;
}
@property (assign) BXEmulator *emulator;
//Whether we are responding to mouse input.
@property (assign) BOOL mouseActive;

//Called whenever we lose keyboard input focus. Clears all DOSBox events.
- (void) lostFocus;

//Press/release the specified mouse button, with the specified modifiers.
- (void) mouseButtonPressed: (NSInteger)button withModifiers: (NSUInteger)modifierFlags;
- (void) mouseButtonReleased: (NSInteger)button withModifiers: (NSUInteger) modifierFlags;

//Move the mouse to a relative point on the specified canvas, by the relative delta.
- (void) mouseMovedToPoint: (NSPoint)point
				  byAmount: (NSPoint)delta
				  onCanvas:	(NSRect)canvas
			   whileLocked: (BOOL)locked;

//Sends a key up/down event with the specified parameters to DOSBox.
- (void) sendKeyEventWithCode: (unsigned short)keyCode
					  pressed: (BOOL)pressed
				withModifiers: (NSUInteger)modifierFlags;

//Sends a key up/down event with the specified code, using the current modifier flags.
- (void) sendKeyEventWithCode: (unsigned short)keyCode pressed: (BOOL)pressed;

//Sends a keyup and a keydown event for the specified code, using the current modifier flags.
- (void) sendKeypressWithCode: (unsigned short)keyCode;

//Sends various fake events to DOS.
- (void) sendTab;
- (void) sendDelete;
- (void) sendSpace;
- (void) sendEnter;
- (void) sendF1;
- (void) sendF2;
- (void) sendF3;
- (void) sendF4;
- (void) sendF5;
- (void) sendF6;
- (void) sendF7;
- (void) sendF8;
- (void) sendF9;
- (void) sendF10;


//Returns the DOS keyboard layout code for the currently-active input method in OS X.
//Returns [BXInputHandler defaultKeyboardLayout] if no appropriate layout could be found.
- (NSString *)keyboardLayoutForCurrentInputMethod;

//Returns a dictionary mapping OSX InputServices input method names to DOS keyboard layout codes. 
+ (NSDictionary *)keyboardLayoutMappings;

//The default DOS keyboard layout that should be used if no more specific one can be found.
+ (NSString *)defaultKeyboardLayout;

@end


#if __cplusplus
//Hide SDL nastiness from Objective C classes

#import <SDL/SDL.h>

@interface BXInputHandler (BXInputHandlerInternals)

//Analoguous to [[NSApp currentEvent] modifierFlags], only for SDL-style modifiers.
- (SDLMod) currentSDLModifiers;

//Generates and returns an SDL key event with the specified parameters.
+ (SDL_Event) _SDLKeyEventForKeyCode: (CGKeyCode)keyCode
							 pressed: (BOOL)pressed
					   withModifiers: (NSUInteger)modifierFlags;

//Returns the SDL key constant corresponding to the specified OS X virtual keycode.
+ (SDLKey) _convertToSDLKeyCode: (CGKeyCode)keyCode;	
	
//Returns the appropriate SDL modifier bitmask for the specified NSEvent modifier flags.
+ (SDLMod) _convertToSDLModifiers: (NSUInteger)modifierFlags;

@end
#endif