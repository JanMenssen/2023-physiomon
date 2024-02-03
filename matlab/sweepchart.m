%
% sweepchart
%
%     this is the implementation of sweepchart, a routine to plot signals like it is done
%     on a oscilloscope. After the end of the display is reached on the right, the screen
%     is cleared and new signals are plotted on the left of the sccreen

% modifications
%     03-feb-2024   JM    initial version

classdef sweepchart < basechart

  properties
    m_curIndx = [];
  end

  methods

    %% constructor

    function obj = sweepchart(axisHandle,channels)

      % in the constructor the constructor of the parent class is called and some
      % variables are initialised
      %
      %     syntax : obj = sweephart(axisHandle,channels)
      %
      % with <axixHandle> a handle to the axis of the chart and <channels> a list of
      % channcels that should be plotted in this chart

      obj = obj@basechart(axisHandle,channels);

      obj.m_curIndx = ones(size(channels));

    end

    %% setTimeAxis

    function obj = setTimeAxis(obj,nsec)
      
      % in the method <setTimeAxis> the time scale is set to the graph and 
      % some variablea are initialised
      %
      %       syntax : obj = setTimeAxis(obj,nsec)
      %
      % with <nsec> the length of the time axis

      obj = obj.setTimeAxis@basechart(nsec);
      
      obj.m_curIndx = 0;

    end



    %% update

    function obj = update(obj,ichan,data)

      % <update> updates the graph for channel <ichan> with the data from <data>. Point are 
      % added to the graph until the then of the screen is reached on the right. Then the
      % screen is cleared an new points are plotted and added to the left
      %
      %     syntax : obj = update(obj,ichan,data)
      %
      % with <ichan> the channel that should be updated and <data> the new data that is
      % added to the graph
      
    end

  end

end
