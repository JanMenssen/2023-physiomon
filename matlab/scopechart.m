%
% scopechart
%
%     this is the implementation of scopechart, a routine to plot signals like it is done
%     on a traditional oscilloscope. When the end of the screen is reached on the right, new
%     points overwrite old points on the left.
%
% modifications
%     03-feb-2024   JM    initial version

classdef scopechart < basechart

  properties
    m_curIndx = [];
    m_first = [];
  end

  methods

    %% constructor

    function obj = scopechart(axisHandle,channels)

      % in the constructor the constructor of the parent class is called and some
      % variables are initialised
      %
      %     syntax : obj = scopechart(axisHandle,channels)
      %
      % with <axixHandle> a handle to the axis of the chart and <channels> a list of
      % channcels that should be plotted in this chart

      obj = obj@basechart(axisHandle,channels);

      obj.m_curIndx = ones(size(channels));
      obj.m_first = ones(size(channels),'logical');

    end

    %% setTimeAxis

    function obj = setTimeAxis(obj,nsec)
      
      % in the method <setTimeAxis> the time scale is set to the graph and 
      % some variablea are initialised
      %
      %       syntax : obj = setTimeAxis(obj,nsec)
      %
      % with <nsec> the lenght of the time axis

      obj = obj.setTimeAxis@basechart(nsec);
      
      obj.m_first = true;
      obj.m_curIndx = 0;

    end



    %% update

    function obj = update(obj,ichan,data)

      % <update> updates the graph for channel <ichan> with the data from <data>. New points
      % are added to the right until the end is reached. The following points are overwrite
      % exsiting points on the left
      %
      %     syntax : obj = update(obj,ichan,data)
      %
      % with <ichan> the channel that should be updated and <data> the new data that is
      % added to the graph
      
    end

  end

end
