%
% displays
%
%     a class which is responsible for the displaying of the acquired data
%
% modifications
%   02-feb-2024   JM    initial version

classdef displays

  properties (Access = private)
  end

  methods

    %% constructor

    function obj = displays()
    
      % constructor of the class, members are initialised
      %
      %     syntax : obj = displays()

    end

    %% initialise

    function obj = initialise(obj)
    
      % this is a stub method, nothing is done in this method
      %
      %     syntax : obj = initialise(obj)

    end

    %% configure
   
    function obj = configure(obj,mySettings)
    
      % in configure, the displays are configured using the information from an instance
      % of the <physiomon_settings> class. The number of displays are placed on the canvas
      % on the desired place and scaling is done. 
      %
      %     syntax : obj = configure(obj,mySettings)
      %
      % with <mySettings> a "filled" instance of the <phsyiomon_settings> class

    end

    %% plot

    function myChannels = plot(obj,myChannels)
    
      % using the new information from the buffers in the instance of the <physiomon_channels> 
      % class (written by the read method of the instance of <measuredevice>, this method plots
      % this new data on the charts, using the method thas is selected (strip, scope,
      % sweep or numeric)
      %
      %     syntax : myChannels = plot(obj,myChannels)
      %
      % with <myChannels> and instance of the <physiomon_channels> 
      
    end

  end

end
