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
      %     syntax : sweephart(axisHandle,channels)
      %
      % with <axixHandle> a handle to the axis of the chart and <channels> a list of
      % channcels that should be plotted in this chart

      obj@basechart(axisHandle,channels);
      obj.m_curIndx = ones(size(channels));

    end

    %% update

    function update(obj,ichan,data)

      % <update> updates the graph for channel <ichan> with the data from <data>. Point are 
      % added to the graph until the then of the screen is reached on the right. Then the
      % screen is cleared an new points are plotted and added to the left
      %
      %     syntax : update(ichan,data)
      %
      % with <ichan> the channel that should be updated and <data> the new data that is
      % added to the graph
      
      % downsample and add to buffer

      data = obj.m_downSampler{ichan}.getData(data);

      obj.m_dataBuffer(ichan).y = [obj.m_dataBuffer(ichan).y data];
      obj.m_curIndx(ichan) = length(obj.m_dataBuffer(ichan).y);
  
      % and plot

      set(obj.m_lineHandles{ichan},xdata = obj.m_dataBuffer(ichan).x(1:obj.m_curIndx(ichan)), ydata = obj.m_dataBuffer(ichan).y);
  
      % done

    end

    %% finishUpdate
    
    function initUpdate(obj)
    
      % called before the real update is done. It checks if end of the screen is reached
      % and takes action (clear buffers and start on the left on the screen again)
      %
      %     syntax : initUpdate()

      if all(obj.m_curIndx >= obj.m_pntsInGraph)

        obj.m_curIndx = 1;

        for ichan=1:obj.m_numchan 
          set(obj.m_lineHandles{ichan},xdata = [], ydata = []); 
          obj.m_dataBuffer(ichan).y = [];
        end
      
      end
    end


  end

end
