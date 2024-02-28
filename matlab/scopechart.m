%
% scopechart
%
%     this is the implementation of scopechart, a routine to plot signals like it is done
%     on a traditional oscilloscope. When the end of the screen is reached on the right, new
%     points overwrite old points on the left.
%
% modifications
%     03-feb-2024   JM    initial version
%     28-feb-2024   JM    now derived from graphchart

classdef scopechart < graphchart

  properties
    m_posLineHandle = [];
    m_yLimits = [];
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

      obj@graphchart(axisHandle,channels);

      % create a new position handle to show the current position

      obj.m_posLineHandle = plot(obj.m_axisHandle,NaN);

    end

    %% setYaxis

    function setYaxis(obj,ymin,ymax)

      % this nethod sets the scaling for the y-axis
      %
      %     syntax ; setYaxis(ymin,ymax)
      %
      % with <ymin> the lower value adn <ymax> the upper value.

        setYaxis@graphchart(obj,ymin,ymax);
        obj.m_yLimits = [ymin ymax];

    end

    %% updatePlot

    function updatePlot(obj,ichan,data)

      % <update> updates the graph for channel <ichan> with the data from <data>. New points
      % are added to the right until the end is reached. The following points are overwrite
      % exsiting points on the left
      %
      %     syntax : update(ichan,data)
      %
      % with <ichan> the channel that should be updated and <data> the new data that is
      % added to the graph
       
      indx = obj.m_indx(ichan);
      maxindx = obj.m_pntsInGraph(ichan);

      % downsample

      data = obj.m_downSampler{ichan}.getData(data);
      nsamples = length(data);
  
      % check if the number of samples exceeds the number of points in the buffer and take
      % action

      if (indx + nsamples > maxindx)
        nsamples = maxindx - indx;
        data = data(1:nsamples);
      end
      
      % in the first screen is plotted, points are appended to the data buffer, later the points
      % are replaced in the data buffer

      if obj.m_firstScreen         
        obj.m_dataBuffer(ichan).y = [obj.m_dataBuffer(ichan).y data];
      else   
        obj.m_dataBuffer(ichan).y(indx:(indx+nsamples-1)) = data;
      end

      % done, save current position

      obj.m_indx(ichan) = indx + nsamples; 
    end
  
    %% finishUpdatePlot

    function finishUpdatePlot(obj)

      %
      %     this method draws a red vertical position line on the screen (after the first
      %     screen is plotted)
      %
      %         syntax : finishUpdatePlot
     
      finishUpdatePlot@graphchart(obj);
     
      if (~obj.m_firstScreen)
        atX = obj.m_dataBuffer(1).x(obj.m_indx(1));
        set(obj.m_posLineHandle,xdata = [atX atX], ydata = obj.m_yLimits, color = 'r');
      end
    end

  end

end
