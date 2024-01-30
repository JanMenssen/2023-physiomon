%
% settings
%
%       creates a cyclic buffer
%
% modifications
%   25-jan-2024   JM    initial version

classdef settings

  properties (Access = private)
    
    m_filename = [];
    m_channels = [];
    m_displays = [];
    m_events = [];

  end

  methods 
  
    %% constructor

    function obj = settings()
    
      % constructor of the class, sets the filename. location is dependent of the
      % operating system

      if ismac(), obj.m_filename = '/Users/jan/.config/JanSoft/physiomon.ini'; end
    end

    %% iniRead

    function obj = iniRead(obj)
    
      % reads the *.INI file and make 3 structures, depending on the information in the *.INI
      % file
      %     - m_channels    : containing information about channels
      %     - m_displays    : contains the event settings
      %     - m_events      : contains information for the events
      %
      %
      %   syntax : obj = iniRead(obj)
      %
      % this method differs from the one used in Qt (python and C++). No defaults values
      % are given except for the event structure

      tmpStruct = ini2struct(obj.m_filename);
      
      numChan = tmpStruct.algemeen.numchan;
      numDisp = tmpStruct.algemeen.numdisp;
      numEvents = 10;

      obj = obj.readDisplays(tmpStruct,numDisp);
      obj = obj.readChannels(tmpStruct,numChan);
      obj = obj.readEvents(tmpStruct,numEvents);
      
    end

  end

  methods (Access = private)
  
    % readChannels

    function obj = readChannels(obj,tmpStruct,numChannels)
      
      % readChannels decodes the <tmpStruct>, containing the whole *.INI file in an array
      % of <m_channels> with size <numChannels
      %
      %   syntax : obj = readChannels(obj,tmpStruct,numChannels)
      %
      % <m_channels> is an internal private member of the class

      obj.m_channels = repmat(struct('name',[],'type',[],'source',[],'display',[]),numChannels);

      for iChan = 1:numChannels

        field = ['channel' numstr(ichan)];

        obj.m_channels(iChan).name = tmpStruct.(field).name;
        switch lower(tmpStruct.(field).type) 

          case "analog in" 
            obj.m_channels(iChan).type = 1;
        end

        obj.m_channels(iChan).source = tmpStruct.(field).source;
        obj.m_channels(iChan).display = tmpStruct.(field).display;
      
      end
    end

    % readDisplays

    function obj = readDisplays(obj,tmpStruct,numDisplays)

      % readDisplay decodes the <tmpStruct>, containing the whole *.INI file in an array
      % of <m_displays> with size <numDisplays
      %
      %   syntax : obj = readDisplays(obj,tmpStruct,numDisplays)
      %
      % <m_displays> is an internal private member of the class

      obj.m_displays = repmat(struct('top',[],'left',[],'width',[],'height',[],'ymin',[],'ymax',[],'timescale',[]),numDisplays);

      for iDisplay = 1:numDisplays
      
        field = ['displays' num2str(iDisplay)];

        obj.m_displays(iDisplay).top = tmpStruct.(field).top;
        obj.m_displays(iDisplay).left = tmpStruct.(field).left;
        obj.m_displays(iDisplay).width = tmpStruct.(field).width;
        obj.m_displays(iDisplay).height = tmpStruct.(field).height;
        obj.m_displays(iDisplay).ymin = tmpStruct.(field).ymin;        
        obj.m_displays(iDisplay).ymax = tmpStruct.(field).ymax;        
        obj.m_displays(iDisplay).timescale = tmpStruct.(field).timescale;

      end

    end
        
    % readEvents

    function obj = readEvents(obj,tmpStruct,numEvents)
    
      % readEvents decodes the <tmpStruct>, containing the whole *.INI file in an array
      % of <m_events> with size <numEvents>
      %
      %   syntax : obj = readEvents(obj,tmpStruct,numEvents)
      %
      % <m_events> is an internal private member of the class. If the event number in the
      % *.INI file is not found a default string "this is event <nr>" is added

      for iEvent = 1:numEvents

        field = ['x' numstr(iEvents)];

        if isfield(tmpStruct.events,field)
          obj.m_events(iEvent) = tmpStruct.events.(field);
        else
          obj.m_events(iEvent) = ['this is event ' numstr(iEvent)];
        end
      
      end

    end

  end
end