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
    m_dataBuffer = []             % buffer containing xData points

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
      
      for i=1:obj.m_numchan, obj.m_downSampler{i} = downsampler(); end

    end

    %% initPlot

    function initPlot(obj,sampleRate)
      
      % configures the x-data using <sampleRate and the downsampler. For 100 ms (the timer
      % interval extra points are added to be sure all new samples are plotted
      %
      %     syntax : initPlot(obj,sampleRate)
      %
      % with <sampleRate> a vector with the sampleRate for each channel

      % get the time on the X-axis and calculate the number of points in the graph

      nsec = obj.m_axisHandle.XLim(2);

      rate = round((nsec .* sampleRate) ./ obj.MAX_POINTS_IN_GRAPH);
      rate(rate == 0) = 1;
      obj.m_pntsInGraph = round(nsec * sampleRate) ./ rate;
    
      % add for 100 ms extra points 

      extraPoints = 0.1 .* sampleRate ./ rate;
      for i=1:obj.m_numchan, obj.m_dataBuffer(i).x = rate(i)/sampleRate(i) * (1:(obj.m_pntsInGraph(i) + extraPoints(i))); end
      for i = 1:obj.m_numchan, obj.m_downSampler{i}.setRate(rate(i)); end

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

  end

end

