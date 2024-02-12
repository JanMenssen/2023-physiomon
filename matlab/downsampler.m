%
% downsampler
%
%     this class downsamples the signal so MAX_POINTS_IN_GRAPH is not exceeded. In Matlab
%     this is a seperate file because it is not allowed to have 2 classes in one file
%
% modifications
%     06-feb-2024   JM    initial version
%     12-feb-2024   JM    derivated from class handle (pointer logic)

classdef downsampler < handle

  properties
  
    m_decimateFactor = [];          % reducing factor
    m_buffer = []                   % tempory buffer contains not processed samples
    
  end


  methods 

    %% constructor

    function obj = downsampler()

      % the constructor initialise the variables, allocate space for the buffer and set
      % positions in this buffer to 1
      %
      %     syntax : obj = downsampler()

      obj.m_buffer = [];

    end

    %% setRate

    function setRate(obj,rate)

      % the method <setRate> sets the decimation rate. Every <rate> samples a new output
      % sample is obtained
      %
      %     syntax : setRate(obj,rate)
      %
      % with <rate> the decimation factor
    
      obj.m_decimateFactor = rate;

    end

    %% getData

    function outData = getData(obj,inData)
    
      % decimates the number of input samples with a factor that is set in <setRate> so
      % the number of samples to the graphs are reduced
      %
      %     syntax outData = getData(obj,inData)
      %
      % with <inData> the input data and <outData> the downsampled data


      if (obj.m_decimateFactor > 1)

        obj.m_buffer = [obj.m_buffer inData];
        outData = inData(1:obj.m_decimateFactor:end);
        
        samplesToRemove = obj.m_decimateFactor * length(outData);
        if samplesToRemove > length(obj.m_buffer), samplesToRemove = length(obj.m_buffer); end
        obj.m_buffer(1:samplesToRemove) = [];
      
      else
  
        outData = inData;

      end

    end

  end

end