%
% basechart
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

% some defines

classdef basechart < handle

  properties (Constant)

    MAX_POINTS_IN_GRAPH = 2500;
  end

  properties
  
    m_channels = []               % list with channels that should be plotted in the display
    m_axisHandle = []             % handle to the axis 
    m_lineHandles = [];           % handles to the lines (for every channel a line) in the graph
    m_downSampler = [];           % downsample class
    m_pntsInGraph = [];           % number of points in the graph
    m_numchan = [];               % number of channels in graphs (used to speed up things)
    m_dataBuffer = [];            % buffer containing xData points
    m_indx = [];                  % current position of plot
    m_firstScreen = [];           % true if the first screen is plotted

    defs = defines();             % load the defines

  end

  methods

    %% constructor

    function obj = basechart(axisHandle,channels)

      % the constructor set the current axis handle which is used in the plotting and a
      % list with channels that should be plotted into this chart
      %
      %     syntax : obj = basechart(axisHandle,channels)
      %
      % with <axisHandle> a handle that is created and channels a list of channels that
      % should be plotted
      
      obj.m_axisHandle = axisHandle;
      obj.m_axisHandle.NextPlot = "add";

      obj.m_numchan = length(channels);
      obj.m_channels = zeros(obj.m_numchan,1);
      for i=1:obj.m_numchan, obj.m_channels(i) = channels{i}; end
      for i=1:obj.m_numchan, obj.m_lineHandles{i} = plot(obj.m_axisHandle,NaN); end
       
      obj.m_dataBuffer = repmat(struct('x',[],'y',[]),obj.m_numchan,1);
      obj.m_indx = ones(obj.m_numchan,1);      

      for i=1:obj.m_numchan, obj.m_downSampler{i} = downsampler(); end
      obj.m_firstScreen = true;

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

      % set the time scale

      obj.m_axisHandle.XLim = [0 nsec];

    end

    %% initUpdate

    function endReached = initUpdate(obj)
    
      % the method <initUpdate> checks if the end of the screen is reached for all
      % channels in the display and take action depending on the display mode
      %
      %     syntax : endReached = initUpdate
      %
      % with <endReached> true if the end of the screen is reached, else false

      endReached = all(obj.m_indx >= obj.m_pntsInGraph);
      
      if (endReached)
        obj.m_firstScreen = false; 
        obj.m_indx(:) = 1;
      end

    end

    %% finishUpdate
  
    function finishUpdate(obj)
    
      % this methods performs the actual plotting of the data in the channels. This is a
      % seperate method to avoid time delays between the different channels
      %
      %   syntax : finishUpdate

      for i=1:obj.m_numchan
        len = length(obj.m_dataBuffer(i).y);
        set(obj.m_lineHandles{i},xdata = obj.m_dataBuffer(i).x(1:len),ydata = obj.m_dataBuffer(i).y);
      end
    end

  end
  
end

