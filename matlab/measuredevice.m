%
% measuredevice
%
%     this is the abstract class for the measuring device. Device drivers should be
%     inherited from this class. Most methods of this class are overwritten by the
%     children classes
%
% modifications
%   31-jan-2024   JM    initial version


classdef measuredevice

  properties(Access = private)
    m_started = [];
    m_analogIn = [];
  end

  methods
  
    %% constructor

    function obj = measuredevice()
      
      % the constructor initialises the class. This is done by settings the properties to
      % their initial values

      obj.m_started = false;
    end

    %% initialise

    function obj = initialise(obj)
    
      % initialise is an abstract method that should be overwritten by thc children
      % classes
      %
      %     syntax : obj = initialise(obj)

    end

    %% isStarted

    function state = isStarted(obj)
    
      % isStarted returns a true if the device is started, else a false is returned
      %
      %     syntax : state = isStarted(obj)

      state = obj.m_started;

    end

    %% setStartStop

    function obj = setStartStop(obj,state)

      % setStartStop starts or stops the device
      %
      %     syntax : obj = setStartStop(obj,state)
      %
      % with <state> is true to start the device and false to stop the device

      obj.m_started = state;

    end

    %% iniRead

    function obj = iniRead(obj,name)
    
      % iniRead reads the driver *.INI file. 
      % This are number of channels, channel names and gain and offset. These settings 
      % are stored in 
      %   - m_analogIn  : for analog channels
      %   - m_numeric   : for numeric channels
      %
      %     syntax obj = iniRead(obj,name)
      %
      % with <name> the name of the device (ini file name
    
      if ismac(), filename = ['/Users/Jan/.config/Jansoft/' name '.ini']; end
      if ispc(), filename =['c:/users/z558043/appdata/JanSoft' name '.ini']; end

      tmpStruct = ini2struct(filename);

      % currently only analog channels are handled

      numAnalog = round(str2double(tmpStruct.algemeen.numanalogin));
      
      obj.m_analogIn = repmat(struct('name',[],'sampleRate',[],'gain',[],'offset',[],'channels',[]),numAnalog,1);
      for iAnalog = 1:numAnalog
      
        section = ['analog_in' num2str(iAnalog)];

        if isfield(tmpStruct.(section),'name'), obj.m_analogIn(iAnalog).name = tmpStruct.(section).name; end
        if isfield(tmpStruct.(section),'frequency'), obj.m_analogIn(iAnalog).sampleRate = str2double(tmpStruct.(section).frequency); end
        if isfield(tmpStruct.(section),'gain'), obj.m_analogIn(iAnalog).gain = str2double(tmpStruct.(section).gain); end
        if isfield(tmpStruct.(section),'offset'), obj.m_analogIn(iAnalog).offset = str2double(tmpStruct.(section).offset); end

      end
    end

    %% configure

    function obj = configure(obj,mySettings)
    
      % the <configure> method connects channels to the appropriate analog channel.
      %
      %       syntax : obj = configure(obj,mySettings)
      %
      % with <mySettings> an instance of the <physiomon_settings> class (after iniRead)

      % source is 0 based

      numChan = length(mySettings.m_channels);
      for iChan = 1:numChan      
        source = mySettings.m_channels(iChan).source;
        if (mySettings.m_channels(iChan).type ==1 ), obj.m_analogIn(source+1).channels = [obj.m_analogIn(source+1).channels iChan]; end
      end

    end


  end
end
