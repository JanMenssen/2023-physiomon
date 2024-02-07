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
    m_first = [];
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
      % channcels that should be plotted in this chart

      obj = obj@basechart(axisHandle,channels);

      obj.m_first = ones(length(channels),1,'logical');

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

    end

    %% update

    function obj = update(obj,nchan,data)

      % <update> updates the graph for channel <ichan> with the data from <data>. Old
      % points are removed on left the graph is shifted and the new data points are added
      % to the right
      %
      %     syntax : obj = update(obj,ichan,data)
      %
      % with <ichan> the channel that should be updated and <data> the new data that is
      % added to the graph
      
      maxIndx = obj.m_pntsInGraph(nchan);

      % at the end of the display, reset curIndx and set first to false (not first
      % display)

      if (obj.m_first(nchan)) && (length(obj.m_buffer{nchan}) >= maxIndx)
        obj.m_pntsInGraph(nchan) = length(obj.m_buffer{nchan});
        obj.m_first(nchan) = false;
      end

      % downsample

      [obj.m_downSampler{nchan},data] = obj.m_downSampler{nchan}.getData(data);
      
      if (obj.m_first(nchan))
      
        % first screen is adding points 

        obj.m_buffer{nchan} = [obj.m_buffer{nchan} data];

      else

        % shift

        nPoints = length(data);
        obj.m_buffer{nchan} = [obj.m_buffer{nchan}((nPoints+1):end) data];
      
      end

      lenData = length(obj.m_buffer{nchan});
      xdata = obj.m_deltaT(nchan) * (1:lenData);
      plot(obj.m_handle,xdata,obj.m_buffer{nchan});

    end

  end

end
