6/27/2026

Current state:
- Narrative/invariants are still confusing.
- SampleSpooler is basically unit-testable and mostly settled.
- AudioPlayer needs a clearer state machine boundary.

Next step:
- Write the smallest AudioPlayer unit test for start(): valid start request moves Idle -> Prepare or Error on invalid arguments.


6/29/2026

Next step:
Turn SampleSpooler functions into booleans for error handling
Write code for AudioPlayer servicePrepare & servicePlayback
Rewrite markRefilled to automatically fill partial buffers with silence

7/3/2026

Current state:
- Added a silence-filling feature for partial buffers in spooler
- Fake sink and storage devices are unit tested and work
- Began adding basic behavior code to servicePrepare()
- Added refillOneBuffer to AudioPlayer.
- Added samplesRemaining_ to AudioPlayer as a way to track samples read from the storage device.

Next steps:
- Make refillOneBuffer functional by adding code to derive samplesRemaining_
- Make one unit test to test refillOneBuffer.
- Make unit tests to test AudioPlayer state machine.
