%
% testSpeed
%
%   script to test teh update speed of a graph (stripchart
%
%

  buffer = zeros(25000,1)';

  for i=1:25000, buffer(i) = sin(2 * pi * i /10000); end

  plot(buffer);
  
  haxis = get(gcf,'children');
  hline = get(haxis,"children");


  
  tic;
  for i=1:2500
    tmp = buffer(1:50);
    buffer(1:24950) = buffer(51:end);
    buffer(24951:end) = tmp;
    set(hline,'YData',buffer);
    drawnow limitrate;
  end
  elapsed_time = toc/2500
