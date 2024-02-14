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
%   12-feb-2024   JM    measure device now handle class

classdef devPhysioDaq < measuredevice

  properties (Constant)

    BAUDRATE = 115200;            % baudrate of the serial port
  
  end

  properties
    
    m_address = [];
    m_arduino = [];
    m_analogInfo = [];

  end

  methods
  
    %% constructor

    function obj = devPhysioDaq()

    end

    %% initialise

    function initialise(obj)
    
      % initialise starts the arduino controller. Baudrate is set and the port
      % adress is from read in <iniRead>
      %
      %     syntax : initialise(obj)

      obj.m_arduino = arduinocomm(obj.m_address,obj.BAUDRATE);

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

    function iniRead(obj,deviceName)

      % reads the settings, number of channels, gain, offset and sample frequency for each
      % channel that is acquired by teh firmware. These are read from the parent class,
      % only the address of the device is read by this child class
      %
      %     syntax : iniRead(obj,deviceName)
      %
      % with <deviceName> the name of the device  (= devPhysioDaq)

        if ismac(), filename = ['/Users/Jan/.config/Jansoft/' deviceName '.ini']; end
        if ispc(), filename = ['C:\users\z558043\appdata\roaming\Jansoft\' filename '.ini']; end

        obj.iniRead@measuredevice(deviceName);
       
        tmpStruct = ini2struct(filename);
        if isfield(tmpStruct.algemeen,'address'), obj.m_address = tmpStruct.algemeen.address; end

    end

    %% setStartStop

    function setStartStop(obj,started)

      % setStartStop starts or stops the sampling in the device. the argument <started>
      % must be true to start the device and false to stop the device
      %
      %     syntax : setStartStop(obj,state)
      %
      % with <state> is true (start) or false (stop)

      obj.m_arduino.startstop(started);
      obj.setStartStop@measuredevice(started);    

       % copy the analog information to be fast
       
      if (started),  obj.m_analogInfo = obj.getAnalogChannels(); end
    
    end

    %% isStarted

    function onoff = isStarted(obj)

      % returns the started state of the firmware. If a true is returned, the firmware is
      % started, else a false is returned
      %
      %    syntax : onoff = isStarted(obj)
      %
      % with onoff is true (started) or false (not started)

      onoff = obj.isStarted@measuredevice();

    end

    %% read

    function read(obj,myChannels)

      % reads the data from the device and store this data in the buffers of the connected
      % channels
      %
      %     syntax : read(obj,myChannels)
      %
      % with <myChannels> an instance of the channels class
      
      if obj.isStarted()
  
        cmd = '-';
        while ~isempty(cmd)

          [cmd,data] = obj.m_arduino.rcvMsg();

          % analog signale
 
          if (cmd == 'A')
            for i =1:length(data), obj.writeValuesToAllChannels(i,myChannels,data(i)); end
          end
         end
       end
    end
      
  end

  methods (Access = private)

    %% writeValuesToAllChannels

    function writeValuesToAllChannels(obj,i,myChannels,value)
    
      % writeAllChannels writes the data that is acquired by the analog port to all
      % connected channels, read from the myChannels instance of the channels class
      %
      %     syntax : writeValuesToAllChannels(obj,analogStruct,myChannels,data)
      %
      % with
      %   - analogStruct      : a structure containing gain, offset and selected channels
      %   - myChannels        : instance of myChannels class, output also because it is modified
      %   - value             : the acquired data

        analogInfo = obj.m_analogInfo(i);

        realValue = analogInfo.gain * double(value) + analogInfo.offset;
         
        numChan = length(analogInfo.channels);
        for i=1:numChan, myChannels.writeData(analogInfo.channels(i),realValue); end

      end

  end

end
