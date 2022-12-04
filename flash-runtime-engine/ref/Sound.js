function FlashSound() {
    let _runtime = null;
    let _context = null;

    let _channels = [ ];
    let _channelMixer = null;
    let _sounds = [ ];

    const SoundEventType = {
        COMPLETE:   0,
        ERROR:      1
    };

    function FlashSoundData(callback, instance) {
        let _soundCallback = callback;
        let _soundInstance = instance;
        let _soundBuffer = null;

        function decodeStatusHandler(response) {
            _soundBuffer = response;
            _soundCallback(_soundInstance, SoundEventType.COMPLETE, 0, 0);
        }
        function decodeFailedHandler(response) {
            _soundCallback(_soundInstance, SoundEventType.ERROR, 0, 0);
        }

        this.composeSource = function(source) {
            _context.decodeAudioData(source).then(
                decodeStatusHandler
            ).catch(
                decodeFailedHandler
            );
        };
        this.disposeSource = function() {
            _soundBuffer = null;
        };
        this.content = function() {
            return _soundBuffer;
        };

        return this;
    }

    function FlashSoundChannel(source, callback, instance) {
        let _channelCallback = callback;
        let _channelInstance = instance;
        let _panning = _context.createStereoPanner();
        let _gaining = _context.createGain();
        let _content = _context.createBufferSource();

        _gaining.connect(_channelMixer.source());
        _panning.connect(_gaining);

        _content.buffer = source.content();
        _content.connect(_panning);
        _content.onended = function(response) {
            _channelCallback(_channelInstance, SoundEventType.COMPLETE, 0, 0);
        };

        this.changeGaining = function(value) {
            _gaining.gain.setValueAtTime(value, _context.currentTime);
        };
        this.changePanning = function(value) {
            _panning.pan.setValueAtTime(value, _context.currentTime);
        };

        this.play = function(offset) {
            _content.start(offset);
        };
        this.stop = function() {
            _content.stop();
        };

        return this;
    }

    function FlashSoundMixer(context) {
        let _context = context;
        let _panning = _context.createStereoPanner();
        let _gaining = _context.createGain();

        _gaining.connect(_context.destination);
        _panning.connect(_gaining);

        this.changeGaining = function(value) {
            _gaining.gain.setValueAtTime(value, _context.currentTime);
        };
        this.changePanning = function(value) {
            _panning.pan.setValueAtTime(value, _context.currentTime);
        };
        this.source = function() {
            return _panning;
        };

        return this;
    }

    this.createSound = function(soundCallbackPtr, soundPtr) {
        return _sounds.push(new FlashSoundData(_runtime.readHandle(soundCallbackPtr), soundPtr)) - 1;
    };
    this.deleteSound = function(soundID) {
        _sounds[soundID] = null;
    };
    this.bindSoundSource = function(soundID, bufferPtr, bufferLen) {
        _sounds[soundID].composeSource(_runtime.readSource(bufferPtr, bufferLen));
    };

    this.createSoundChannel = function(soundID, channelCallbackPtr, channelPtr) {
        return _channels.push(new FlashSoundChannel(_sounds[soundID], _runtime.readHandle(channelCallbackPtr), channelPtr)) - 1;
    };
    this.deleteSoundChannel = function(channelID) {
        _channels[channelID] = null;
    };
    this.changeChannelTransform = function(channelID, gaining, panning) {
        _channels[channelID].changeGaining(gaining);
        _channels[channelID].changePanning(panning);
    };
    this.playSoundChannel = function(channelID, offset) {
        _channels[channelID].play(offset);
    };
    this.stopSoundChannel = function(channelID) {
        _channels[channelID].stop();
    };

    this.changeMixerTransform = function(gaining, panning) {
        _channelMixer.changeGaining(gaining);
        _channelMixer.changePanning(panning);
    };

    this.compose = function(runtime) {
        _context = new AudioContext();
        _channelMixer = new FlashSoundMixer(_context);
        _runtime = runtime;
    };
    this.dispose = function() {
        _context.close();
        _context = null;
    };

    return this;
}
