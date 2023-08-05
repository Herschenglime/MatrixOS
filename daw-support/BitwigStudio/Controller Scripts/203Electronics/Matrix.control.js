
loadAPI(1);

host.defineController("203Electronics", "Matrix", "1.0", "49f52cc9-e3c0-42cd-ba9f-7086842ec793");
host.defineMidiPorts(1, 1);

function init()

{
   host.getMidiInPort(0).setMidiCallback(onMidi);
   host.getMidiInPort(0).setSysexCallback(onSysex);

   noteIn = host.getMidiInPort(0).createNoteInput("Notes");
}

function exit()
{
   println("goodbye Matrix.");
}

function onMidi(status, data1, data2)
{
}

function onSysex(data)
{
}
