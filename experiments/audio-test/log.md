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
- Make refillOneBuffer functional by adding code to derive samplesRemainingToRead_
- Make one unit test to test refillOneBuffer.
- Make unit tests to test AudioPlayer state machine.

7/4/2026

Current state:
- Fake sink extended to include initialization steps
- AudioPlayer::refillOneBuffer(uint8_t index) defined and written
- Added samplesRemainingToRead_ to track the number of samples to read left from storage for the given clip.
- AudioPlayer servicePrepare code outline written
- Began creating a test harness for the AudioPlayer

Next steps:
- Begin initialization tests for AudioPlayer

7/5/2026

Current state:
- AudioPlayer test code compiles without error
- Basic AudioPlayer initialization tests run without error
- Created test handles struct to easily initialize fake sink, fake storage, and AudioPlayer.

Next steps:
- Write tests for playback state
- Write tests for error states
- Fill in code for servicePlayback

7/7/2026

Current state:
- Wrote servicePlayback code

Next steps:
- Write tests for playback state
- Write tests for error states

7/8/2026

Current state:
- Listed several successful-path unit tests to write in test_audio_player.cpp

Next steps:
- Write successful-path unit tests and get them to pass
- List failure unit tests

7/9/2026

Current state:
- Wrote and successfully ran several happy-path unit tests in test_audio_player.cpp:
    - test_start_while_playing_stops_current_playback_first()
    - test_start_from_finished_enters_prepare_without_stopping()
    - test_service_playback_consumes_samples()
    - test_samples_played_equals_samples_written()
    - test_successful_playback_enters_finished()
    
Next steps:
- Practical and underrun unit tests
- Error-path tests
- Begin tests on real hardware

7/12/2026

Current state:
- Wrote unit test showing that storage sectors are written to the spooler successfully.

Next steps:
- Error-path tests
- Begin tests on real hardware

7/13/2026

Current state:
- Added player read error test and functionality
- Added storage read status functionality
- Added player underrun test (which fails)

Next steps:
- Get the underrun test to pass.

7/14/2026

Current state:
- Wired amplifier on breadboard
- Configured STM32 for 25MHz clock
- Set up TIM4 for 200kHz PWM
- Confirmed 200kHz square wave with USB scope

Next steps:
- Make underrun test pass—trace expected transition and identify where the fake readiness behavior diverges.
- solder pins to speaker
- generate 500Hz sine wave table at 44.1kHz sample rate
- Use a timer interrupt at 44.1 kHz to update TIM4 CCR to the next sine wave sample (+- 10).

7/15/2026

Current State:
- AudioPlayer happy path, error handling, and underrun behavior are tested and work in fake environment.

Next Steps:
- solder pins to speaker
- generate 500Hz sine wave table at 44.1kHz sample rate
- Use a timer interrupt at 44.1 kHz to update TIM4 CCR to the next sine wave sample (+- 10).

7/16/2026

Current state:
- Made a working LM386 amplifier circuit on a breadboard.
- Used STM32 PWM and timers to play a sine wave on the amplifier
- The cat screwed it up.

Next steps:
- Fix the circuit and make it play sound again
- Write PwmAudioSink to interface the PWM audio with the AudioPlayer
- Use hal_callbacks.cpp in App/Src folder to hold a callback for the timer interrupt which updates the PWM sample.


7/17/2026

Current state:
- Created hal_callbacks.cpp to handle all interrupt callbacks that the program may have
- Filled out pwm_audio_sink.h sufficiently to begin implementation
- Created empty function implementations in pwm_audio_sink.cpp

Next steps:
- Implement prepare, start, and interrupt / sample functionality.
- Mind error handling and return false when invariants are violated.

7/20/2026

Current State:
- PwmAudioSink is functional enough to create arbitrary waveforms with expected distortion.
- Tested on Analog Discovery 2.

Next steps:
- Implement PwmAudioSink interrupt failure detection (i.e. timeout / watchdog)
- Reduce amplifier gain with a pot.
- Complete sd_card storage_device implementation
- Test sd_card storage_device implementation
- Test AudioPlayer with SDcard -> PwmAudioSink pipeline in place

7/25/2026

Current State:
- Created 48000 Hz Signed 16-bit PCM test file with Audacity.
- Tested AudioPlayer functionality with SD card storage and PWM audio sink.
- Spotted shadowed variable in AudioSink (isSampleNeeded_).
- AudioPlayer can successfully play an audio clip from storage on a functioning audio sink.

Next Steps:
- Design SSM2518 / EEPROM interface board.
- Configure and verify the SSM2518 over I2C.
- Produce a simple I2S tone.
- Stream a PCM buffer through I2S DMA.
- Connect that sink to the existing AudioPlayer.
- Implement ADPCM compression to optimize for limited EEPROM capacity.

~7/31/2026

Current State:
- Wrote ADPCM codec

Next Steps:
- Testing and integration of ADPCM codec.

8/8/2026

Current State:
- Successfully tested ADPCM codec on PC
- Wrote headers for SampleSource, StorageSampleSource, and PCM/ADPCM sources to convert data into samples
- Refactored AudioPlayer to use SampleSource instead of StorageDevice.
    - Consistently use size_t instead of uint32_t for variable indexes / counts
    - Refactored refillOneBuffer per the SampleSource contract
- Put some code from audio_player.cpp into PCMSampleSource (bookkeeping & some code from refillOneBuffer)

Next Steps:
- Write PCMSampleSource implementation
- Test PCMSampleSource implementation

8/13/2026

Current State:
- Wrote PCMSampleSource.
- Need to assert invariants after the fact

Next Steps:
- Write down PCMSampleSource invariants (esp. getSamples)
- Test PCMSampleSource

8/24/2026

Current State:
- PCMSampleSource is tested
- In process of tesing AudioPlayer with new source_ interface

Next Steps:
- The first sector of storage is being read twice, once by source_.start and once by source_.getSamples. It seems to be a bookkeeping problem at start but I have not traced it through yet.
- Underruns are not being tracked by AudioPlayer at this time.
