%
% physiomon_store
%
%   this class handles the storage of the data. TDMS files are used and storage is done
%   in groups
%
% modifications
%     15-mar-2024   JM  initial version

classdef physiomon_store < handle

  properties (Access = private)

    m_groupInfo = [];
    m_storage = [];
  
  end

  methods

    %% constructor

    function obj = physiomon_store(filename)

      obj.m_storage = false;

    end

    %% isStorageOn

    function onoff = isStorageOn(obj)

      onoff = obj.m_storage;
    end

    %% setStorage

    function setStorage(obj,onoff)
    end

    %% configure

    function configure(obj,settings,channels)

      % configures the storage engine using the information from the *.INI file and the 
      % channels class is used to get the samplerate
      %
      %     syntax : configure(obj,settings,channels)
      %
      % with <settings> the information from the *.INi file read by <phsyiomon_settings>
      % and <channels> instances of the channels class

      numstore = length(settings.m_store);
      obj.m_groupInfo = repmat(struct("name",[],"samplerate",[],"chanlist",cell([])),numstore,1);

      % first add the groupname to the groupInfo

      for i=1:numstore, obj.m_groupInfo(i).name = settings.m_store(i).groupname; end

      % loop over all channels for the storage engine

      istore = ones(numstore,1);
      nchannels = length(settings.m_channels);

      for ichan = 1:nchannels
        usedStore = settings.m_channels(ichan).store;
        if usedStore > 0
          obj.m_groupInfo(usedStore).chanlist{istore(usedStore)} = ichan;
          istore(usedStore) = istore(usedStore) + 1;
        end
      end
    
      % get the samplerate, this is currently done for the first channel, but in the
      % future there should be a check this samplerate is the same for all channels in a
      % group

      for i=1:numstore, obj.m_groupInfo(i).sampleRate = channels.getSamplerate(i); end
    
    end

    %% write

    function write(obj,groupNr)
    end

  end

  methods (Access = private)

    %% prepareWrite

  end

end
