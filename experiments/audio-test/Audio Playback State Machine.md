# Audio Playback State Machine

## Narrative

This system sits idle until the main program requests playback from a particular sample at an index. Then, it initializes by preparing the SD card for read access, preparing spooler buffers to be filled, and preparing the PWM output for playback. It will play back until it reaches the number of samples that the main program said was the length of the sample. Then, it will go back to the idle state. If SD card transactions are slow or stop and buffers aren't getting full during playback, the system will enter the Underrun state. In this state, it will attempt to refill the buffers until a certain amount of time has passed, then enter the Error state. Impossible conditions, such as variables outside of their maximum values, lead to the Error state.

## Invariants

Global Invariants:
    playBuf_ < NumBuffers
    playPos_ < SamplesPerBuffer
    samplesLeft_ >= 0
    state_ is a valid State value
    current buffer index is never used unless it is in range

Idle:
    No playback is active
    All errors are cleared
    A valid play command may transition to Prepare

Prepare:
    Has a valid playback request
    Has a valid start sector
    Has a valid sample length
    Buffers are treated as invalid until filled
    Exit to Playing only after required buffers are valid

Playback:
    Current playback buffer must be valid
    samplesLeft_ > 0
    playPos_ < number of valid samples in current buffer
    There must be a valid file length for the current file listed
    Empty buffers are marked for refill

Underrun:
    The next buffer to be played is marked for refill
    No invalid data is sent to PWM
    Exit to playing when the next 2 buffers to be played are valid

Error:
    Audio output is in a safe silent state
    No further SD/PWM assumptions are trusted

## The State Machine

* Idle
    (Do nothing)
    
    * play command -> Prepare

* Prepare
    acquire SD access
    seek to sample start sector
    prime first playback buffers
    configure PWM/timer
    start playback timer only after buffers are valid
    Prime spooler
    Setup pin for PWM output
    
    * success -> Playback
    * failure -> Error

* Playback
    Take a sample from Spooler and put it onto PWM
    Fill any empty buffers with samples from SD
    Pad extra space after current file with silence
    Fault if invariants are violated
    Complete if samplesPlayed >= totalSamples
    
    * complete -> Finished (silence / stop PWM, clear playback)
    * buffer unexpectedly empty -> Underrun
    * fault -> Error **
    * stop command -> Idle

* Underrun
    Put PWM in "safe" state (hold last sample or silence)
    SD card read -> buffer
    If fails, wait x ms and try again.
    After y ms, timeout.
    
    * data arrives -> Playback
    * timeout -> Error

* Finished
    Silence on playback
    
    * reset -> Idle
    
* Error
    Notify main program and wait for clear.

    cleared/reset -> Idle
