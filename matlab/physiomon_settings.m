%
% physiomon_settings
%
%   reads the <physiomon> *.ini file and stores this information into 
%          - m_channels
%          - m_displays
%          - m_events
%
%   to avoid conflicts with the matlab <settings> this class is named <physiomon_settings>
%
% modifications
%   25-jan-2024   JM    initial version
%   11-feb-2024   JM    now derivated from a handle class (pointer logic)
%   28-feb-2024   JM    numeric display added

classdef physiomon_settings < handle

  properties (Access = private)
    
    m_filename = [];
    m_channels = [];
    m_displays = [];
    m_events = [];

    defs = defines();       % load the defines

  end

  methods 
  
    %% constructor

    function obj = physiomon_settings()
    
      % constructor of the class, sets the filename. location is dependent of the
      % operating system

      if ismac(), obj.m_filename = '/Users/jan/.config/JanSoft/physiomon.ini'; end
      
      obj.m_events = repmat("",obj.defs.MAX_EVENTS,1);
    
    end

    %% getChannels

    function channels = getChannels(obj)
    
      % this method returns the private property <m_channels>
      %
      %     syntax : channels = getChannels(obj)
      %
      % with <channels> a copy of the private member m_channels

      channels = obj.m_channels;

    end

    %% getEvents

    function events = getEvents(obj)
    
      % this method returns the private property <m_events>
      %
      %     syntax : events = getEvents(obj)
      %
      % with <events> a copy of the private member m_events
      
      events = obj.m_events;

    end  

    %% getDisplays

    function displays = getDisplays(obj)
    
      % this method returns the private property <m_displays>
      %
      %     syntax : displays = getDisplays(obj)
      %
      % with <displays> a copy of the private member m_displays
      
      displays = obj.m_displays;

    end  

    %% setChannels

    function setChannels(obj,channels)
    
      % the method <setChannels> copies information from <channels> to the internal
      % private propertie <m_channels> This method is used in the dialog boxes
      %
      %     syntax : setChannels(obj,channels)
      %
      % with <channels> an vector of a channelStruct

      obj.m_channels = channels;

    end

    %% setDisplays

    function setDisplays(obj,displays)

      % the method <setDisplays> copies information from <displays> to the internal
      % private propertie <m_displays> This method is used in the dialog boxes
      %
      %     syntax : setDisplays(obj,displays)
      %
      % with <displays> an vector of a displayStruct

      obj.m_displays = displays;

    end

    %% setEvents

    function setEvents(obj,events)

      % the method <setEvents> copies an list of events (<events>) to the internal
      % private propertie <m_events> This method is used in the dialog boxes
      %
      %     syntax : setEvents(obj,events)
      %
      % with <events> a list of events
      
      obj.m_events = events;
    
    end

    %% iniRead

    function devicename = iniRead(obj)
    
      % reads the *.INI file and make 3 structures, depending on the information in the *.INI
      % file
      %     - m_channels    : containing information about channels
      %     - m_displays    : contains the event settings
      %     - m_events      : contains information for the events
      %
      %   syntax : devicdename = iniRead(obj)
      %
      % this method differs from the one used in Qt (python and C++). No defaults values
      % are given except for the event structure. <devicename> is returned, the name of
      % the device (and so the device *.INI file)

      tmpStruct = ini2struct(obj.m_filename);
      
      numChan = round(str2double(tmpStruct.algemeen.numchan));
      numDisp = round(str2double(tmpStruct.algemeen.numdisp));

      obj.readDisplays(tmpStruct,numDisp);
      obj.readChannels(tmpStruct,numChan);
      obj.readEvents(tmpStruct,obj.defs.MAX_EVENTS);
      
      devicename = tmpStruct.algemeen.device;
    end

  end

  methods (Access = private)
  
    % readChannels

    function readChannels(obj,tmpStruct,numChannels)
      
      % readChannels decodes the <tmpStruct>, containing the whole *.INI file in an array
      % of <m_channels> with size <numChannels
      %
      %   syntax : readChannels(obj,tmpStruct,numChannels)
      %
      % <m_channels> is an internal private member of the class

      obj.m_channels = repmat(struct('name',[],'type',[],'source',[],'display',[],'precision',[]),numChannels,1);

      for iChan = 1:numChannels

        section = ['channel' num2str(iChan)];

        obj.m_channels(iChan).name = tmpStruct.(section).name;
        switch lower(tmpStruct.(section).type) 

          case "analog in" 
            obj.m_channels(iChan).type = obj.defs.TYPE_ANALOG_IN;
        end

        obj.m_channels(iChan).source = str2double(tmpStruct.(section).source);
        obj.m_channels(iChan).display = str2double(tmpStruct.(section).display);
        obj.m_channels(iChan).precision = str2double(tmpStruct.(section).precision);
      
      end
    end

    % readDisplays

    function readDisplays(obj,tmpStruct,numDisplays)

      % readDisplay decodes the <tmpStruct>, containing the whole *.INI file in an array
      % of <m_displays> with size <numDisplays
      %
      %   syntax : readDisplays(obj,tmpStruct,numDisplays)
      %
      % <m_displays> is an internal private member of the class

      obj.m_displays = repmat(struct('top',[],'left',[],'width',[],'height',[],'ymin',[],'ymax',[],'timescale',[],'mode',[]),numDisplays,1);

      for iDisplay = 1:numDisplays
      
        section = ['display' num2str(iDisplay)];

        obj.m_displays(iDisplay).top = str2double(tmpStruct.(section).top);
        obj.m_displays(iDisplay).left = str2double(tmpStruct.(section).left);
        obj.m_displays(iDisplay).width = str2double(tmpStruct.(section).width);
        obj.m_displays(iDisplay).height = str2double(tmpStruct.(section).height);
        obj.m_displays(iDisplay).ymin = str2double(tmpStruct.(section).ymin);        
        obj.m_displays(iDisplay).ymax = str2double(tmpStruct.(section).ymax);        
        obj.m_displays(iDisplay).timescale = str2double(tmpStruct.(section).timescale);

        switch (lower(tmpStruct.(section).updatemode))
          
          case 'strip'
            obj.m_displays(iDisplay).mode = obj.defs.DISPLAY_MODE_STRIP;
          case 'sweep'
            obj.m_displays(iDisplay).mode = obj.defs.DISPLAY_MODE_SWEEP;
          case 'scope'
            obj.m_displays(iDisplay).mode = obj.defs.DISPLAY_MODE_SCOPE;
          case 'numeric'
            obj.m_displays(iDisplay).mode = obj.defs.DISPLAY_MODE_NUMERIC;
          otherwise
            error('unknown display mode');
        end

      end

    end
        
    % readEvents

    function readEvents(obj,tmpStruct,numEvents)
    
      % readEvents decodes the <tmpStruct>, containing the whole *.INI file in an array
      % of <m_events> with size <numEvents>
      %
      %   syntax : readEvents(obj,tmpStruct,numEvents)
      %
      % <m_events> is an internal private member of the class. If the event number in the
      % *.INI file is not found a default string "this is event <nr>" is added

      for iEvent = 1:numEvents, obj.m_events(iEvent) = ['this is event ' num2str(iEvent)]; end

      for iEvent = 1:numEvents
        field = ['x' num2str(iEvent)];
        if isfield(tmpStruct.events,field), obj.m_events(iEvent) = tmpStruct.events.(field); end
      end
    end


  end
end