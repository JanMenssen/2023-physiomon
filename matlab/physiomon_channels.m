%
% physiomon_channels
%
%     contain the channel class. a channel contains informaation abouth the channel but
%     also 2 tempory buffers to push and get data
%    
%         - the device writes data to the channel
%         - the display and storage engine reads data from the channel
%
%     this class makes use of the <cyclicbuffer> class
%
% modifications
%   31-jan-2024   JM    initial version

classdef physiomon_channels

  properties (Access = private)
    m_buffers = []
    m_lengthInSeconds = [];
  end

  methods
  
    %% constructor

    function obj = physiomon_channels(nsec)
      
      % constructor of the class, some properties are initialised

      obj.m_lengthInSeconds = nsec;

    end

    %% configure

    function obj = configure(obj,mySettings,myDevice)

      % getting the information that is in instance of the classes <settings> and <device>
      % this method configures the classes buffers and set some properties
      %
      %     syntax : obj = configure(obj,settings,device)
      %
      % with <settings> and instance of the settings class and <device> an instance of the
      % device class

      numChan = length(mySettings.m_channels);
      obj.m_buffers = repmat(struct('sampleRate',[],"display",[],'store',[]),numChan,1);

      % perform for all channels
      
      for iChan = 1:numChan
      
        source = mySettings.m_channels(iChan).source;
        numAnalog = length(myDevice.m_analogIn);
        for iAnalog = 1:numAnalog

          % create the buffers if the source is found 
          
          if ((source+1) == iAnalog)

            sampleRate = myDevice.m_analogIn(iAnalog).sampleRate;
            buflen = obj.m_lengthInSeconds * sampleRate;
          
            obj.m_buffers(iChan).sampleRate = sampleRate;
            obj.m_buffers(iChan).display = cyclicbuffer(buflen,'double');
            obj.m_buffers(iChan).store = cyclicbuffer(buflen,'double');

          end

          % Note, other types should be implemented 
        
        end
      end
    end

    %% readDisplay

    function [obj,data] = readDisplay(obj,channel)
    
      % readDisplay reads the data from the <display> buffer for the appropriate channel.
      % Note, altough this is a read routine, indices in the buffers are updated and so it
      % is necessary to return the instance of the class
      %
      %     syntax : [obj,data] = readDisplay(obj,channel)
      %
      % with <channel> the channel number and <data> a vector with returned data

      data = obj.m_buffers(channel).store.read();
      
    end

    %% readStore
   
    function [obj,data] = readStore(obj,channel)
    
      % readStore reads the data from the <store> buffer for the appropriate channel.
      % Note, altough this is a read routine, indices in the buffers are updated and so it
      % is necessary to return the instance of the class
      %
      %     syntax : [obj,data] = readStore(obj,channel)
      %
      % with <channel> the channel number and <data> a vector with returned data

      data = obj.m_buffers(channel).store.read();
      
    end

    %% writeData

    function obj = writeData(obj,channel,data)
    
      % the method <writeData> writes <data> to the buffers (display and store) of channel
      % <channel>
      %
      %     syntax : obj = writeData(obj,channel,data)
      %
      % with <channel> the appropriate channel and <data> the data to be written (vector)

      obj.m_buffers(channel).display.write(data);
      obj.m_buffers(channel).store.write(data);

    end
  end

end
