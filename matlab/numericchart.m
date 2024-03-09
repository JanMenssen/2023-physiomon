%
% numericchart
%
%    this class contains methods and properties to display numerics on the screen. 
%
% modifications
%     28-feb-2024   JM  initial version

classdef numericchart < basechart

  properties (Access = private)

    m_labelTxt = [];            % contains the text for the labels
    m_valuePos = [];            % positions on the screen where to plot the values
    m_labelPos = [];            % positions on the screen where to plot the labels
    m_valueHandle = [];         % handle to value text

    m_scaleFactor = [];         % ratio between fontsize numbers and labels
    m_fontSize = 12;            % size of the font of the labels

    m_precision = [];           % number of digits after decimal to display
    m_value = [];               % stores the calculated numeric value
    m_usedColors = [];          % colors used
    
  end

  methods
  
    %% constructor

    function obj = numericchart(axisHandle,chanlist)
    
      % the constructor set the current axis handle which is used in the plotting and a
      % list with channels that should be shown on the chart
      %
      %     syntax : obj = graphchart(axisHandle,channels)
      %
      % with <axisHandle> a handle that is created and channels a list of channels that
      % should be plotted

      obj@basechart(axisHandle,chanlist);

      % hide the axis

      obj.m_axisHandle.Visible = 'off';

      % initialise variables

      obj.m_labelTxt = cell(obj.m_numchan,1);
      obj.m_valueHandle = cell(obj.m_numchan,1);

      obj.m_valuePos = repmat(struct('x',[],'y',[]),obj.m_numchan,1);
      obj.m_labelPos = repmat(struct('x',[],'y',[]),obj.m_numchan,1);  

      obj.m_scaleFactor = 1.0;

      obj.m_precision = ones(obj.m_numchan,1);
      obj.m_value = zeros(obj.m_numchan,1);

    end

    %% initPlot

    function obj = initPlot(obj,~)
    
            
      % initialises the numeric chart. positions where to store the values and the text belonging to the values
      % (the labels) are calculated. The labels are already shown on the chart
      %
      %     syntax : initPlot(obj,allChannels)
      %
      % with <channels> an the channels structure obtained from reading the *.INI file

      obj.m_labelPos = obj.calcLabelPositions();
      obj.m_valuePos = obj.calcValuePositions();

      % calculate the scale factor, the ratio between the size of fontsize for the values
      % and the labels

      obj.m_scaleFactor = obj.calcScaleFactor();

      % and place the labels on the screen

      for i=1:obj.m_numchan, obj.plotLabel(i,obj.m_labelTxt{i}); end

    end

    %% initUpdatePlot

    function endReached = initUpdatePlot(obj)
    
      % the method <initUpdate> is called every update sequence for all channels in the
      % plot. It is used for repositioning of labels and values 
      %
      %     syntax : endReached = initUpdatePlot
      %
      % with <endReached> an stub variable that is needed to be compatible with the graph
      % charts. It is always false

      endReached = false;
      obj.m_scaleFactor = obj.calcScaleFactor();
      
    end

    %% updatePlot

    function updatePlot(obj,ichan,data)

      % <update> updates the graph for channel <ichan> with the data from <data>. This
      % data is averaged if the number of samples > 1.
      %
      %     syntax : updatePlot(obj,ichan,data)
      %
      % with <ichan> the channel that should be updated and <data> the new data that is
      % added to the graph

      nsamples = length(data);
      if nsamples > 0, obj.m_value(ichan) = mean(data); end

      formatStr = sprintf("%%.%df",obj.m_precision(ichan));
      valueTxt = num2str(obj.m_value(ichan),formatStr);
      
      pos = obj.m_valuePos(ichan);
      fontsize = round(obj.m_scaleFactor * obj.m_fontSize);
      
      if ishandle(obj.m_valueHandle{ichan}), delete(obj.m_valueHandle{ichan}); end
      obj.m_valueHandle{ichan} = text(obj.m_axisHandle,pos.x,pos.y,valueTxt,'HorizontalAlignment','center', ...
        'VerticalAlignment','middle','fontSize',fontsize,'Color',obj.m_usedColors{ichan});
       
    end
    
    %% finishUpdatePlot
  
    function finishUpdatePlot(~)
    
      % this methods is called after updating all seperate channels every update loop. It
      % the numeric chart it is a stub method
      %
      %   syntax : finishUpdatePlot

    end

    %% setLabels

    function setLabels(obj,allChannels)
    
      % given the structure with the channel information, this methods finds the names of
      % the channels that are in this graph. The method <initPlot> is used to place these
      % names (labels) on the screen
      %
      %   syntax : setLabels(allChannels)
      %
      % with <allChannels> the channels structure

      for ichan = 1:obj.m_numchan
        curchan = obj.m_channels(ichan);
        obj.m_labelTxt{ichan} = allChannels(curchan).name;
      end

    end
   
    %% setColors

    function setColors(obj,allChannels)
    
      % given the structure with the channel information, this methods finds the colors for
      % the channels that are selected for the graph
      %
      %     syntax : setColors(allChannels)
      %
      % with <allChannels>< the channel structure
  
      obj.m_usedColors = cell(obj.m_numchan);
      for ichan=1:obj.m_numchan
      
        curchan = obj.m_channels(ichan);
        switch (allChannels(curchan).color)
  
          case obj.defs.COLOR_RED
            obj.m_usedColors{ichan} = [1,0,0];
          case obj.defs.COLOR_GREEN
            obj.m_usedColors{ichan} = [0,1,0];
          case obj.defs.COLOR_BLUE
            obj.m_usedColors{ichan} = [0,0,1];
          case obj.defs.COLOR_CYAN
            obj.m_usedColors{ichan} = [0,1,1];
          case obj.defs.COLOR_MAGENTA
            obj.m_usedColors{ichan} = [1,0,1];
          case obj.defs.COLOR_YELLOW
            obj.m_usedColors{ichan} = [1,1,0];
          case obj.defs.COLOR_BLACK
            obj.m_usedColors{ichan} = [0,0,0];
          case obj.defs.COLOR_WHITE
            obj.m_usedColors{ichan} = [1,1,1];

        end     
      end
    end

    %% setPrecsion

    function obj = setPrecision(obj,allChannels)
    
      % the method <setPrecision> sets the number of digits after the decimal. This is
      % read by the *.INI file and stored in the <settings.m_channels> structure
      %
      %    syntax  ; setPrecision(allChannels)
      %
      % with <allChannels> a <settings.m_channels> structure

      for ichan = 1:obj.m_numchan
        curchan = obj.m_channels(ichan);
        obj.m_precision(ichan) = allChannels(curchan).precision;
      end

    end

  end

  methods (Access = private)
  
    %% calcLabelPositions

    function pos = calcLabelPositions(obj)

      % the methods <calcLabelPositions> calculates the position of the label on the
      % chart. This is done in the chart coordinates system
      %
      %     syntax : pos = calcLabelPositions();
      %
      % with <pos> a structure of length <m_numchan> with an x and y field
    
      % first check vertical or horizontal mode (are the numeric below each other or on
      % the side of each other)

      increment = 1 / (obj.m_numchan + 1);
      
      position = obj.m_axisHandle.InnerPosition;
      if position(3) > position(4)
        xpos = 0:increment:1;
        ypos = repmat(0.8,obj_m_num_chan + 2,1);
      else
        ypos = (1:-increment:0) + 0.11;
        xpos = repmat(0.5,obj.m_numchan + 2,1);
      end
      
      pos = repmat(struct('x',[],'y',[]),obj.m_numchan,1);
      for i=1:obj.m_numchan 
        pos(i).x = xpos(i+1);
        pos(i).y = ypos(i+1);
      end

    end

    %% calcValuePositions

    function pos = calcValuePositions(obj)
    
      % the methods <calcValuePositions> calculates the position of the values on the
      % chart. This is done in the chart coordinates system
      %
      %     syntax : pos = calcValuePositions();
      %
      % with <pos> a structure of length <m_numchan> with an x and y field

      increment = 1 / (obj.m_numchan + 1);
      
      position = obj.m_axisHandle.InnerPosition;
      if position(3) > position(4)
        xpos = 0:increment:1;
        ypos = repmat(0.5,obj_m_num_chan + 2,1);
      else
        ypos = 1:-increment:0;
        xpos = repmat(0.5,obj.m_numchan + 2,1);
      end
      
      pos = repmat(struct('x',[],'y',[]),obj.m_numchan,1);
      for i=1:obj.m_numchan 
        pos(i).x = xpos(i+1);
        pos(i).y = ypos(i+1);
      end

    end

    %% plotLabels

    function plotLabel(obj,ichan,label)
    
      % method <plotLabel> plots the label/legend of channel <ichan> on the screen
      %
      %   syntax : plotLabel(ichan,label)
      %
      % wth <ichan> the channel number in the display and <label> the text to show on the
      % screen

      pos = obj.m_labelPos(ichan);
      text(obj.m_axisHandle,pos.x,pos.y,label,HorizontalAlignment = 'center',VerticalAlignment='middle',fontSize = obj.m_fontSize);

    end

    %% calcScaleFactor

    function scale = calcScaleFactor(obj)
    
      % the function <calcScaleFactor> calculates the ratio between the fontsize of the
      % values and the labels
      %
      %     syntax : scale = calcScaleFactor()
      %
      % with <scale> the ratio

      position = get(obj.m_axisHandle,'InnerPosition');
      
      labelPosInPixel = obj.m_labelPos(1).y * position(4);
      valuePosInPixel = obj.m_valuePos(1).y * position(4);

      scale = abs(labelPosInPixel - valuePosInPixel) / 12.5;

    end

  end



end
