### Keypad OLED Project
Use case :- Keypad will be used to give inputs, OLED will be used to show those inputs. Inputs will be of the ON OFF period of a relay.


<img src = "Extras/IMG_20210924_195256.jpg" width = "100"> 
![](Extras/IMG_20210924_195256.jpg)

#### How to Use :-
- A is for going to the next line
- B is for viewing pressed number
- C is for clear and reset
- RED LED for power
- White LED for Relay ON OFF
- Blue LED will blink when there is an input - used for input confirmation.

#### Conditions :- 
- No. of digits should not exceed 4
- Keypads should be firmly pressed or else input is not detected.

#### 1.0.1 (code)
- OLED I2C working
- Keypad is working
- Used Arduino nano
- Three Indication LEDs

#### 1.0.2 (code)
- Added power led code.
- Added basic code for oled to show counts.
- Added code for keypad to give inputs.
- Added code to delete specific area in oled.

#### 1.0.3 (code)
- Added field for different Inputs like ON, OFF, Loop, Current Loop
- Added a switch case structure for different inputs
- Added A for going to next line.
- Added B for showing the input.
- Added C for clear and Reset.

#### 1.0.4 (code)
- Deleted the unused part in the code.
- Added some print commands in the code.
- made a function for displaying data.

#### 1.0.5 (code)
- Added code to truncate digits when its exceeds 4.
- Blue LED will blink during inputs.
- Deleting specific area is working fine.
- Will add * for starting and stopping the function

#### 1.0.6 (code)
- Added * to start the functioning of the system.
- couldnt configure the stopping of the system with * since it was in a while loop.
- need to change the 'line' in displayData func to 'y'. was creating issues in the 2nd line of UI.
- some problem in the 2nd input in UI couldnt resolve.
- added code to return to initial state after completetion.
- need to add some LED indication with blue LED of completition and starting function.

#### 1.0.7 (feature)
- Trying adding image to the github repository.











