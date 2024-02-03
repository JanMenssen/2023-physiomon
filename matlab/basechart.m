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

classdef basechart

  properties(Access = private)
  
    m_channels = []               % list with channels that should be plotted in the display
    m_handle = []                 % handle to the axis 
    m_downSampler = [];           % downsample class
    m_buffer = []                 % contains the data points (cell array
    m_pntsInGraph = [];           % number of points in the graph
    m_sampleRate = [500 500 500]; % sampleRate (Hz)
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
      
      obj.m_handle = axisHandle;
      obj.m_channels = channels;

    end

    %% setYaxis

    function setYaxis(obj,ymin,ymax)

      % setYaxis sets the limit of the y-axis
      %
      %     syntax : setAxis(obj,ymin,ymax)
      %
      % with <ymin> the lower boundary and <ymax> the upper boundary of the y-axis

      obj.m_handle.YLim = [ymin ymax];

    end

    %% setTimeAxis

    function obj = setTimeAxis(obj,nsec)

      % set the time scale

      obj.m_handle.XLim = [0 nsec];
      
      % calculate the number of points in the graph

      for ichan =1:length(obj.m_channels)
      end
      
      % set the points for the x-axis, these can be calculated and plot NaN's for the
      % yaxis and plot

    end

    %% finishUpdate

    function finishUpdate(~)
    end

  end

end
