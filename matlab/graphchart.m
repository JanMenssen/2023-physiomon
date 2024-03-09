%
% graphchart
%
%     this is an abstract class for handling the displays. Children of this class are
%
%         - stripchart
%         - scopechart
%         - sweepchart
%
%   In the base chart the <downSampler is initialise, which reduces the number of points to
%   plot in the display
%
% modifications
%     02-feb-2024  JM initial version
%     28-feb-2024  JM renamed to graphchart with introduction of numeric chart

% some defines

classdef graphchart < basechart

  properties
    
    m_lineHandles = [];           % handles to the lines (for every channel a line) in the graph
    m_downSampler = [];           % downsample class
    m_pntsInGraph = [];           % number of points in the graph
    
    m_dataBuffer = [];            % buffer containing xData points
    m_indx = [];                  % current position of plot
    m_firstScreen = [];           % true if the first screen is plotted

    m_labelTxt = [];              % cell containing the labels for the legend
    m_usedColors = [];
    m_legendFontSize = 9;         % size of the legend

  end

  methods

    %% constructor

    function obj = graphchart(axisHandle,channels)

      % the constructor set the current axis handle which is used in the plotting and a
      % list with channels that should be plotted into this chart
      %
      %     syntax : obj = graphchart(axisHandle,channels)
      %
      % with <axisHandle> a handle that is created and channels a list of channels that
      % should be plotted

      obj@basechart(axisHandle,channels)
      
      for i=1:obj.m_numchan, obj.m_lineHandles{i} = plot(obj.m_axisHandle,NaN); end
       
      obj.m_dataBuffer = repmat(struct('x',[],'y',[]),obj.m_numchan,1);
      obj.m_indx = ones(obj.m_numchan,1);      

      for i=1:obj.m_numchan, obj.m_downSampler{i} = downsampler(); end
      obj.m_firstScreen = true;

      obj.m_labelTxt = cell(obj.m_numchan,1);

    end

    %% setYaxis

    function setYaxis(obj,ymin,ymax)
      
      % setYaxis sets the limit of the y-axis
      %
      %     syntax : setAxis(obj,ymin,ymax)
      %
      % with <ymin> the lower boundary and <ymax> the upper boundary of the y-axis

      obj.m_axisHandle.YLim = [ymin ymax];

    end

    %% setTimeAxis

    function setTimeAxis(obj,nsec)

      % set the time scale (x-axis on the screen
      %
      %     syntax : setTimeAxis(nsec)
      %
      % with <nsec> the number of seconds on the axis

      obj.m_axisHandle.XLim = [0 nsec];

    end

    %% initPlot

    function initPlot(obj, channels)
      
      % configures the x-data using time on the x-axis and the sampleRate. To speed up the
      % process, we limit the number of points in the graph and use a downsampler if the
      % needed
      %
      %     syntax : initPlot(obj,channels)
      %
      % with <channels> an instance of the channels object

      % get the sample frequency for each of the channels

      sampleRate = zeros(obj.m_numchan,1);
      for ichan = 1:obj.m_numchan
        sampleRate(ichan) = channels.getSampleRate(obj.m_channels(ichan));
      end

      % based on the time on the x-axis, calculate the number of points in the graph 

      nsec = obj.m_axisHandle.XLim(2);

      rate = round((nsec .* sampleRate) ./ obj.MAX_POINTS_IN_GRAPH);
      rate(rate == 0) = 1;
      obj.m_pntsInGraph = round(nsec * sampleRate) ./ rate;
      
      for i=1:obj.m_numchan  
        obj.m_downSampler{i}.setRate(rate(i)); 
        obj.m_dataBuffer(i).x = (1:obj.m_pntsInGraph(i)) * (rate(i) / sampleRate(i));
      end
      
      % and place the legend on the screen

      legend(obj.m_axisHandle,obj.m_labelTxt,'Location','northeast','Box','off','FontSize',obj.m_legendFontSize);
      
    end

    %% initUpdatePlot

    function endReached = initUpdatePlot(obj)
    
      % the method <initUpdate> checks if the end of the screen is reached for all
      % channels in the display and take action depending on the display mode
      %
      %     syntax : endReached = initUpdatePlot
      %
      % with <endReached> true if the end of the screen is reached, else false

      endReached = all(obj.m_indx >= obj.m_pntsInGraph);
      
      if (endReached)
        obj.m_firstScreen = false; 
        obj.m_indx(:) = 1;
      end

    end

    %% finishUpdatePlot
  
    function finishUpdatePlot(obj)
    
      % this methods performs the actual plotting of the data in the channels. This is a
      % seperate method to avoid time delays between the different channels
      %
      %   syntax : finishUpdatePlot

      for i=1:obj.m_numchan
        len = length(obj.m_dataBuffer(i).y);
        set(obj.m_lineHandles{i},xdata = obj.m_dataBuffer(i).x(1:len),ydata = obj.m_dataBuffer(i).y,color = obj.m_usedColors{i});
      end
    end

    %% setLabels

    function obj = setLabels(obj,allChannels)
    
      % given the structure with the channel information, this methods finds the names of
      % the channels that are in this graph. The method <initPlot> is used to place these
      % names (labels) on the screen
      %
      %   syntax : setLabels(allChannels)
      %
      % with <allChannels> the channels structure

      for ichan = 1:obj.m_numchan
        curchan = obj.m_channels(ichan);
        obj.m_labelTxt{ichan} = allChannels(curchan).name;
      end

    end

    %% setColors

    function setColors(obj,allChannels)
    
      % given the structure with the channel information, this methods finds the colors for
      % the channels that are selected for the graph
      %
      %     syntax : setColors(allChannels)
      %
      % with <allChannels>< the channel structure
  
      obj.m_usedColors = cell(obj.m_numchan);
      for ichan=1:obj.m_numchan
      
        curchan = obj.m_channels(ichan);
        switch (allChannels(curchan).color)
  
          case obj.defs.COLOR_RED
            obj.m_usedColors{ichan} = [1,0,0];
          case obj.defs.COLOR_GREEN
            obj.m_usedColors{ichan} = [0,1,0];
          case obj.defs.COLOR_BLUE
            obj.m_usedColors{ichan} = [0,0,1];
          case obj.defs.COLOR_CYAN
            obj.m_usedColors{ichan} = [0,1,1];
          case obj.defs.COLOR_MAGENTA
            obj.m_usedColors{ichan} = [1,0,1];
          case obj.defs.COLOR_YELLOW
            obj.m_usedColors{ichan} = [1,1,0];
          case obj.defs.COLOR_BLACK
            obj.m_usedColors{ichan} = [0,0,0];
          case obj.defs.COLOR_WHITE
            obj.m_usedColors{ichan} = [1,1,1];

        end     
      end
    end

  end

  methods (Access = private)
  
  %% calcLabelPos

  function pos = calcLabelPosition(~)
  
    % the method <calcLabelPosition> calculates the position of the label, this is
    % standard
    %   - on 80% of the x-axis
    %   - on 110% of the yaxis
    %
    %     syntax : [x,y] = calcLabelPosition
    %
    % with <pos> a structure with an x- and y-coordinate

    pos.x = 0.8;
    pos.y = 1.1;
    
  end

  end

end

