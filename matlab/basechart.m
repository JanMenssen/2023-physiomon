%
% basechart
%
%     this is an abstract class for handling the displays. Children of this class are
%
%         - stripchart (via graphchart)
%         - scopechart (via graphchart)
%         - sweepchart (via graphchart)
%         - numericchart
%
%
% modifications
%     28-feb-2024  JM initial version

% some defines

classdef basechart < handle

  properties (Constant)

    MAX_POINTS_IN_GRAPH = 2500;
  end

  properties
  
    m_numchan = [];               % number of channels in graphs (used to speed up things) 
    m_channels = []               % list with channels that should be plotted in the display
    m_axisHandle = []             % handle to the axis 

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
       
    end

  end
  
end

