%
% devPhysioDaq.m
%
%     device driver for the simple analog convertor used in the arduino. Max 6 analog
%     channels are available
%
%     the class makes use of the <arduinocomm> class and protocol
%
% modifications
%   01-feb-2024   JM    initial version

classdef devPhysioDaq < measuredevice

  properties
    m_adress = [];
    m_arduino = [];
  end

  methods
  
    %% constructor

    function obj = devPhysioDaq()
    end

    %% initialise

    function obj = initialise(obj)
    
      % initialise starts the arduino controller. Baudrate is set and the port
      % adress is from read in <iniRead>
      %
      %     syntax : obj = initialise(obj)

      obj.m_arduino = arduinocomm(obj.m_address,115200);

    end
      
    %% isConnected

    function devInfo = isConnected(obj)

      % checks if the device is connected. If connected, a string is returned with
      % name and version of the firmware of the device
      %
      %     syntax : devInfo = isConnected(obj)

      devInfo = obj.m_arduino.isConnected(obj);

    end

    %% setSampleRate

    function setSampleRate(obj,ms)

      % sets the samplerate for the device. The input must be in ms.
      %
      %     syntax : setSampleRate(obj,ms)
      %
      % with <ms> in milliseconds

      data = int16(ms);
      obj.m_arduino.sendMsg('c',1,data)
     
    end

    %% iniRead

    function obj = iniRead(obj,deviceName)

      % reads the settings, number of channels, gain, offset and sample frequency for each
      % channel that is acquired by teh firmware. These are read from the parent class,
      % only the address of the device is read by this child class
      %
      %     syntax : obj = iniRead(obj,deviceName)
      %
      % with <deviceName> the name of the device  (= devPhysioDaq)

        if ismac(), filename = ['/Users/Jan/.config/Jansoft/' deviceName '.ini']; end
        if ispc(), filename = ['C:\users\z558043\appdata\roaming\Jansoft\' filename '.ini']; end

        obj = obj.iniRead@measuredevice();

        tmpStruct = ini2struct(filename);
        if isfield(tmpStruct,'address'), obj.m_address = tmpStruct.address; end

    end

    %% setStartStop

    function obj = setStartStop(obj,started)

      % setStartStop starts or stops the sampling in the device. the argument <started>
      % must be true to start the device and false to stop the device
      %
      %     syntax : obj = setStartStop(obj,state)
      %
      % with <state> is true (start) or false (stop)

        obj.m_arduino.startstop(started);
        obj = setStartStop@measuredevice(started);    
    end

    %% isStarted

    function onoff = isStarted(~)

      % returns the started state of the firmware. If a true is returned, the firmware is
      % started, else a false is returned
      %
      %    syntax : onoff = isStarted(obj)
      %
      % with onoff is true (started) or false (not started)

      onoff = isStarted@measuredevice();

    end

    %% read

    function myChannels = read(obj,myChannels)

      % reads the data from the device and store this data in the buffers of the connected
      % channels
      %
      %     syntax : myChannels = read(obj,myChannels)
      %
      % with <myChannels> an instance of the channels class

      if obj.isStarted()
        msgOK = true;

        while (msgOK == true)
          [msgOK,cmd,data] = obj.m_arduino.rcvMsg();
          if (cmd == 1)
            for i =1:length(data)
              myChannels = obj.writeValueToAllChannels(obj.m_analogIn(i),myChannels,data(i));
            end
          end
        end
      end
    end
      
  end

  methods (Access = private)

    %% writeValuesToAllChannels

    function myChannels = writeValuesToAllChannels(~,analogStruct,myChannels,value)
    
      % writeAllChannels writes the data that is acquired by the analog port to all
      % connected channels, read from the myChannels instance of the channels class
      %
      %     syntax : myChannels = writeValuesToAllChannels(obj,analogStruct,myChannels,data)
      %
      % with
      %   - analogStruct      : a structure containing gain, offset and selected channels
      %   - myChannels        : instance of myChannels class, output also because it is modified
      %   - value             : the acquired data

        realValue = analogStruct.gain * value + analogStruct.offset;

        numChan = length(analogStruct.channels);
        for i=1:numChan
          ichan = analogStruct.channels(i);
          myChannels.writeData(ichan,realValue);
        end
    end

  end

end
