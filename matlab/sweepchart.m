%
% sweepchart
%
%     this is the implementation of sweepchart, a routine to plot signals like it is done
%     on a oscilloscope. After the end of the display is reached on the right, the screen
%     is cleared and new signals are plotted on the left of the sccreen

% modifications
%     03-feb-2024   JM    initial version
%     28-feb-2024   JM    now derived from graphchart

classdef sweepchart < graphchart

  methods

    %% constructor

    function obj = sweepchart(axisHandle,channels)

      % in the constructor the constructor of the parent class is called and some
      % variables are initialised
      %
      %     syntax : sweephart(axisHandle,channels)
      %
      % with <axixHandle> a handle to the axis of the chart and <channels> a list of
      % channcels that should be plotted in this chart

      obj@graphchart(axisHandle,channels);

    end

    %% updatePlot

    function updatePlot(obj,ichan,data)

      % <update> updates the graph for channel <ichan> with the data from <data>. Point are 
      % added to the graph until the then of the screen is reached on the right. Then the
      % screen is cleared an new points are plotted and added to the left
      %
      %     syntax : updatePlot(ichan,data)
      %
      % with <ichan> the channel that should be updated and <data> the new data that is
      % added to the graph
      
      % downsample and add to buffer

      indx = obj.m_indx(ichan);
      maxindx = obj.m_pntsInGraph(ichan);

      data = obj.m_downSampler{ichan}.getData(data);
      nsamples = length(data);

      if ((indx + nsamples) > maxindx)
        obj.m_dataBuffer(ichan).y = [obj.m_dataBuffer(ichan).y data(1:(maxindx - indx))];
      else
        obj.m_dataBuffer(ichan).y = [obj.m_dataBuffer(ichan).y data];
      end

      % done, update index 

      obj.m_indx(ichan) = length(obj.m_dataBuffer(ichan).y);

    end

    %% initUpdatePlot

    function endReached = initUpdatePlot(obj)

      % clears the screen at the beginning of a new screen
      %
      %     syntax : endReached = initUpdatePlot
      %
      % with <endReached> is true if the end of the screen is reached, else false

      endReached = initUpdatePlot@graphchart(obj);
      
      if (endReached)
        for i = 1:obj.m_numchan 
          set(obj.m_lineHandles(i),xdata = [], ydata = []); 
          obj.m_dataBuffer(i).y = [];
        end
      end

    end

  end
end
