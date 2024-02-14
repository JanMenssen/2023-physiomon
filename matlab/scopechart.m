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
    m_firstScreen = [];
    m_posHandle = [];
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

      obj@basechart(axisHandle,channels);

      obj.m_curIndx = ones(size(channels));
      obj.m_firstScreen = true;

      % create a new position handle to show the current position

      obj.m_posHandle = plot(obj.m_axisHandle,NaN);

    end

    %% update

    function update(obj,ichan,data)

      % <update> updates the graph for channel <ichan> with the data from <data>. New points
      % are added to the right until the end is reached. The following points are overwrite
      % exsiting points on the left
      %
      %     syntax : update(ichan,data)
      %
      % with <ichan> the channel that should be updated and <data> the new data that is
      % added to the graph
       
      % downsample

      data = obj.m_downSampler{ichan}.getData(data);
      nsamples = length(data);

      % in the first screen is plotted, points are appended to the data buffer, later the points
      % are replaced in the data buffer

      if obj.m_firstScreen
        obj.m_dataBuffer(ichan).y = [obj.m_dataBuffer(ichan).y data];
      else
        obj.m_dataBuffer(ichan).y((obj.m_curIndx(ichan)):(obj.m_curIndx(ichan)+nsamples-1)) = data;
      end

      obj.m_curIndx(ichan) = obj.m_curIndx(ichan) + nsamples;
      len = length(obj.m_dataBuffer(ichan).y);
      set(obj.m_lineHandles{ichan},'xdata',obj.m_dataBuffer(ichan).x(1:len),'ydata',obj.m_dataBuffer(ichan).y);   
    end

    %% initUpdate

    function initUpdate(obj)

      % check if the end of the screen is reached for all lines (channels) in the plot
      % and take action on it (resetting indices). It also plots a red vertical line on
      % the screen indicating the current position
      %
      %     syntax : initUpdate

      % plot redline after first screen

      if ~obj.m_firstScreen
        xpos = obj.m_dataBuffer(1).x(obj.m_curIndx(1));
        set(obj.m_posHandle, xdata = [xpos xpos],ydata = obj.m_axisHandle.YLim,color = 'r')
      end

      % check the end of the screen is reached. add extra points to avoid checks in the
      % update loop

      if all(obj.m_curIndx >= obj.m_pntsInGraph)
        obj.m_curIndx(:) = 1;
        if obj.m_firstScreen, obj.addExtraPoints(0.2); end
        obj.m_firstScreen = false;
      end
    
    end



  end

  methods (Access = private)

    %% addExtraPoints

    function addExtraPoints(obj,nsec)

      % addExtraPoints adds extra datapoints to the y buffer to avoid checking in the main
      % update routine. This takes time an this routine should be faster
      %
      %   syntax : addExtraPoints(nsec)
      %
      % with <nsec> the time that should be aded (sec)

      for i = 1:obj.m_numchan
        nPoints = ceil(nsec / (obj.m_dataBuffer(i).x(2) - obj.m_dataBuffer(i).x(1)));
        obj.m_dataBuffer(i).x = [obj.m_dataBuffer(i).x(1:obj.m_pntsInGraph(i)) NaN * ones(1,nPoints)]; 
        obj.m_dataBuffer(i).y = [obj.m_dataBuffer(i).y(1:obj.m_pntsInGraph(i)) NaN * ones(1,nPoints)]; 
      end

    end
  
  end

end
