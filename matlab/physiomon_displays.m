%
% physiomon_displays
%
%     a class which is responsible for the displaying of the acquired data
%
% modifications
%   02-feb-2024   JM    initial version
%   12-feb-2024   JM    now derivated from handle class (pointer logic)

classdef physiomon_displays <handle

  properties (Constant)
  
    PIXELS_TOP = 40;
    PIXELS_LEFT = 50;
    PIXELS_BOTTOM = 80;
    PIXELS_RIGHT = 50;

  end

  properties (Access = private)

    m_chart = {};
    defs = defines()              % defines 
  
  end

  methods

    %% constructor

    function obj = physiomon_displays()
    
      % constructor of the class, members are initialised
      %
      %     syntax : obj = displays(;
    end

    %% initialise

    function initialise(~)
    
      % this is a stub method, nothing is done in this method
      %
      %     syntax : initialise(obj)

    end

    %% configure
   
    function configure(obj,settings,channels,canvasHandle)
    
      % in configure, the displays are configured using the information from an instance
      % of the <physiomon_settings> class. The number of displays are placed on the canvas
      % on the desired place and scaling is done. 
      %
      %     syntax : configure(obj,mySettings,myChannels,canvasHandle)
      %
      % with <mySettings> a "filled" instance of the <phsyiomon_settings> class, myChannels an 
      % instance of the channels <canvasHandle> a handle to the canvas (figure)
 
      % first remove the the exisiting charts

      obj.m_chart = {};
      used_axes = findobj(canvasHandle,'type','axes');
      delete(used_axes);

      % now create each display on the canvas, but before we must known the size of the
      % figure

      allDisplays = settings.getDisplays();
      allChannels = settings.getChannels();

      canvasWidth = canvasHandle.Position(3) - (obj.PIXELS_LEFT);
      canvasHeight = canvasHandle.Position(4) - (obj.PIXELS_BOTTOM);

      for idisp = 1:length(allDisplays)

        curDisp = allDisplays(idisp);

        % create a list of channels that are in the current display

        chanlist = cell([]);

        i = 1;
        for ichan = 1:length(allChannels)
          if (allChannels(ichan).display == idisp)
            chanlist{i} = ichan;
            i = i + 1;
          end     
        end

        % and create the current display (position is different compared to Qt). around
        % the borders, 10 pixels are used for a nicer layout. Note Matlab starts in the
        % lower left corner so modify it

        curDisp.top = 1 - curDisp.top - curDisp.height;

        left = ceil(curDisp.left * canvasWidth) + obj.PIXELS_LEFT;
        top = ceil(curDisp.top * canvasHeight) + obj.PIXELS_BOTTOM;
        width = floor(curDisp.width * canvasWidth - obj.PIXELS_RIGHT);
        height = floor(curDisp.height * canvasHeight) - obj.PIXELS_TOP;

        handle = uiaxes(parent = canvasHandle, InnerPosition = [left top width height],Color = canvasHandle.Color);
        switch curDisp.mode
          
          case obj.defs.DISPLAY_MODE_STRIP
            obj.m_chart{idisp} = stripchart(handle,chanlist);
            obj.m_chart{idisp}.setYaxis(curDisp.ymin,curDisp.ymax);
            obj.m_chart{idisp}.setTimeAxis(curDisp.timescale);
          
          case obj.defs.DISPLAY_MODE_SWEEP
            obj.m_chart{idisp} = sweepchart(handle,chanlist);
            obj.m_chart{idisp}.setYaxis(curDisp.ymin,curDisp.ymax);
            obj.m_chart{idisp}.setTimeAxis(curDisp.timescale);
          
          case obj.defs.DISPLAY_MODE_SCOPE
            obj.m_chart{idisp} = scopechart(handle,chanlist);
            obj.m_chart{idisp}.setYaxis(curDisp.ymin,curDisp.ymax);
            obj.m_chart{idisp}.setTimeAxis(curDisp.timescale);
        end

        % and initialise the chart to prepare for plotting, add labels and so on 

        obj.m_chart{idisp}.initPlot(channels);
      
      end
    end

    %% plot

    function plot(obj,channels)
    
      % using the new data from the buffers in the instance of the <physiomon_channels> class 
      % (written by the read method of the instance of <measuredevice>, this method plots
      % this new data on the charts, using the method thas is selected (strip, scope,
      % sweep or numeric)
      %
      %     syntax : plot(obj,channels)
      %
      % with <channels> and instance of the <physiomon_channels> 
      
      for iDisp = 1:length(obj.m_chart)
        
        % a display could have more channels, so we need the data for all channels in this
        % display
        
        obj.m_chart{iDisp}.initUpdate();
        
        for iChan = 1:length(obj.m_chart{iDisp}.m_channels)

          % get the channel number and get the data and update display

          curChannel = obj.m_chart{iDisp}.m_channels(iChan);
          data = channels.readDisplay(curChannel);
          obj.m_chart{iDisp}.update(iChan,data);
          
        end

        obj.m_chart{iDisp}.finishUpdate();

      end

    end

  end
end
