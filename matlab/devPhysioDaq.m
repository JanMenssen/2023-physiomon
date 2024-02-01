%
% devPhysioDaq.m
%
%     device driver for the simple analog convertor used in the arduino. Max 6 analog
%     channels are available
%
%     the class makes use of the <arduinocomm> class and protocol
% modifications
%   01-feb-2024   JM    initial version

classdef devPhysioDaq < measuredevice

  properties
    m_adress = [];
    m_arduino = []
  end

  methods
  
    %% constructor

    function obj = devPhysioDaq()
    end

    %% isConnected

    function state = isConnected(obj)
    end

    %% setSampleRate

    function obj = setSampleRate(obj,rate)
    end

    %% iniRead

    function obj = iniRead(obj,devicename)
    end

    %% setStartStop

    function obj = setStartStop(obj,started)
    end

    %% isStarted

    function state = isStarted(obj)
    end

    %% read

    function obj = readobj,myChannels)
    end
    
  end

  methods (Access = private)

    %% writeValuesToAllChannels
end
