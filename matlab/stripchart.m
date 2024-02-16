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
      
      indx = obj.m_indx(ichan);
      maxindx = obj.m_pntsInGraph(ichan);
      
      % downsample

      data = obj.m_downSampler{ichan}.getData(data);
      nsamples = length(data);
      
      % in the first screen points are added, to an empty buffer, later they are shifted
      
      if (obj.m_firstScreen)

        shift = indx + nsamples -maxindx;
        if shift > 0
          obj.m_dataBuffer(ichan).y = [obj.m_dataBuffer(ichan).y((shift+1):end) data];
        else
          obj.m_dataBuffer(ichan).y = [obj.m_dataBuffer(ichan).y data];
        end

      else    
        obj.m_dataBuffer(ichan).y = [obj.m_dataBuffer(ichan).y((nsamples+1):end) data];
      end
      
      % done, store current position

      obj.m_indx(ichan) = length(obj.m_dataBuffer(ichan).y);

    end

  end
end
