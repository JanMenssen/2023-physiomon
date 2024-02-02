%
% displays
%
%     a class which is responsible for the displaying of the acquired data
%
% modifications
%   02-feb-2024   JM    initial version

classdef displays

  properties (Access = private)
    m_chart = [];
  end

  methods

    %% constructor

    function obj = displays()
    
      % constructor of the class, members are initialised
      %
      %     syntax : obj = displays(;
    end

    %% initialise

    function obj = initialise(obj)
    
      % this is a stub method, nothing is done in this method
      %
      %     syntax : obj = initialise(obj)

    end

    %% configure
   
    function obj = configure(obj,mySettings,cansvasHandle)
    
      % in configure, the displays are configured using the information from an instance
      % of the <physiomon_settings> class. The number of displays are placed on the canvas
      % on the desired place and scaling is done. 
      %
      %     syntax : obj = configure(obj,mySettings,canvasHandle)
      %
      % with <mySettings> a "filled" instance of the <phsyiomon_settings> class and
      % <canvasHandle> a handle to the canvas (figure)
 
      % first remove the the exisiting charts

      obj.m_chart = [];
      axes = findobj(cansvasHandle,'type','axes');
      delete(axes);

      % now create each display on the canvas, but before we must known the size of the
      % figure

      canvasWidth = h.Position(3);
      canvasHeight = h.Position(4);

      for iDisp = 1:length(mySettings.m_displays)

        curDisp = mySettings.m_displays(iDisp);

        top = canvasWidth * curDisp.top;
        left = canvasHeight * curDisp.left;
        width = canvasWidth * curDisp.width;
        height = canvasHeight * curDisp.height;

        % get the channels which should be on the current display, currently
        % max 3 channels are allowed

        channels = zeros(3,1);
        i = 1;
        for iChan = 1:length(mySettings.m_channels)
          if (mySettings.m_channels(iChan).display == iDisp)
            channels(i) = iChan;
            i = i + 1;
          end     
        end
        channels((i-1):3) = [];

        % and create the current display

        handle = subplot('position',[top left width height]);
        switch curDisp.mode
          case 1
            obj.m_chart(iDisp) = stripchart(handle,channels);
          case 2
            obj.m_chart(iDisp) = sweepchart(handle,channels);
          case 3
            obj.m_chart(iDisp) = scopeChart(handle,channels);
        end

        % and set the Y-axis and time axis for the current chart

        chart.setYaxis(curDisp.ymin,curDisp.ymax);
        chart.setTimeAxis(curDisp.timeScale);
      
      end
    end

    %% plot

    function myChannels = plot(obj,myChannels)
    
      % using the new data from the buffers in the instance of the <physiomon_channels> class 
      % (written by the read method of the instance of <measuredevice>, this method plots
      % this new data on the charts, using the method thas is selected (strip, scope,
      % sweep or numeric)
      %
      %     syntax : myChannels = plot(obj,myChannels)
      %
      % with <myChannels> and instance of the <physiomon_channels> 
      
      numDisp = length(obj.m_chart);
      for iDisp = 1:numDisp
      
        % a display could have more channels, so we need the data for all channels in this
        % display

        for iChan = 1:length(obj.m_chart.m_channels)
        
          % get the channel number and get the data

          curChannel = obj.m_chart.m_channels(iChan);
          data = myChannels.readDisplay(curChannel);
          
          % update the display

          obj.m_chart(iDisp).update(iChan,data);
       
        end
        obj.m_chart.finishUpdate();
      end

      drawnow limitrate
    end

  end

end
