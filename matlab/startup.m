%
% startup
%
%   this is the startup file for the physiomon project. It sets the correct paths
%
% modifications
%     30-jan-2024   JM    initial version

  if ~isdeployed
    
    if (ispc)
      addpath('C:\Users\z558043\OneDrive - Radboudumc\my matlab')
    end

    if (ismac)
      addpath('/Users/jan/Library/CloudStorage/OneDrive-Radboudumc/my matlab');
      addpath('/Users/jan/Library/CloudStorage/OneDrive-Personal/my projects/2024 physiomon');
    end
  
  end
