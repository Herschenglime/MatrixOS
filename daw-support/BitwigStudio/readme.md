# Setting up

By default, you can just use the generic controller script and select the Matrix MIDI 1 input and it'll work, but a MIDI out is not available, and as such you can't control the lights in performance mode. This controller script fixes that, but is pretty barebones otherwise.

## Adding Controller Script
Full, official instructions are [here](https://www.bitwig.com/support/technical_support/how-do-i-add-a-controller-extension-or-script-17/), but in short, copy the `203Electronics` folder and its contents to any of these locations:

macOS: 
Documents/Bitwig Studio/Controller Scripts

Windows: 
%USERPROFILE%\Documents\Bitwig Studio\Controller Scripts

Linux: 
~/Bitwig Studio/Controller Scripts 

Once it's there, you should be able to select the Matrix from the controllers menu, where you can set its MIDI in and out to the Matrix.

## Sending MIDI to the Matrix

Add a `HW Instrument` to your devices list. Select the Matrix MIDI 1 as the output, and any MIDI events you play through that instrument should light up the Matrix.

# Future Goals
Eventually, I'd like to be able to make it so that the touch strips on either side can be used to control knobs and such within the DAW. Additionally, it would be nice to develop an app on MatrixOS to allow transport controls and so on from the Matrix itself without having to manually set MIDI mappings.
