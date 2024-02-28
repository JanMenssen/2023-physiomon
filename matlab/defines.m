%
% defines
%
%     this class contains all constants that are used in the application
%
% modifications
%     14-feb-2024   JM    initial value

classdef defines

  properties (Constant)
  
    % the maximum number of events

    MAX_EVENTS = 10;
    
    % we have different types of signals, these are defined here

    TYPE_ANALOG_IN = 1;
    TYPE_NUMERIC = 2;

    % the modes of displaying a signal

    DISPLAY_MODE_STRIP = 1;
    DISPLAY_MODE_SWEEP = 2;
    DISPLAY_MODE_SCOPE = 3;
    DISPLAY_MODE_NUMERIC = 4;
  
  end

end
