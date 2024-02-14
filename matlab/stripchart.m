%
% stripchart
%
%     this is the implementation of stripchart, a routine to plot signals like it is done
%     on a traditional paper recorder. Old signals are removed from the left of the screen
%     and new signals are added to the right while the screen is shifted
%
% modifications
%     03-feb-2024   JM    initial version

classdef stripchart < basechart

  properties
    m_firstScreen = [];
  end

  methods

    %% constructor

    function obj = stripchart(axisHandle,channels)

      % in the constructor the constructor of the parent class is called and some
      % variables are initialised
      %
      %     syntax : obj = stripchart(axisHandle,channels)
      %
      % with <axixHandle> a handle to the axis of the chart and <channels> a list of
      % channels that should be plotted in this chart

      obj = obj@basechart(axisHandle,channels);
      obj.m_firstScreen = true;

    end


    %% update

    function update(obj,ichan,data)

      % <update> updates the graph for channel <ichan> with the data from <data>. Old
      % points are removed on left the graph is shifted and the new data points are added
      % to the right
      %
      %     syntax : update(obj,ichan,data)
      %
      % with <ichan> the channel that should be updated and <data> the new data that is
      % added to the graph
      
      % downsample

      data = obj.m_downSampler{ichan}.getData(data);
      nPoints = length(data);
      
      % in the first screen points are added, to an empty buffer, later they are shifted
      
      if (obj.m_firstScreen)
        obj.m_dataBuffer(ichan).y = [obj.m_dataBuffer(ichan).y data];
      else    
        obj.m_dataBuffer(ichan).y = [obj.m_dataBuffer(ichan).y((nPoints+1):end) data];
      end
      
      % and draw the lines 

      lenY = length(obj.m_dataBuffer(ichan).y);
      set(obj.m_lineHandles{ichan}, xdata = obj.m_dataBuffer(ichan).x(1:lenY), ydata = obj.m_dataBuffer(ichan).y);


    end

    %% initUpdate

    function initUpdate(obj)

      % this method checks for all lines in the graph if the end of the screen is reached
      % and performs action (shift instead of add)
      %
      %     syntax : initUpdate()
 
      endReached = true;
      for i=1:obj.m_numchan, endReached = (endReached && (length(obj.m_dataBuffer(i).y) >= obj.m_pntsInGraph(i))); end
      if (endReached), obj.m_firstScreen = false; end

    end

  end

end
