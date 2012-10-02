%%
%% iscissor.m
%%
%% Computational Photography Assignment 1
%%
%% John Novatnack
%% jmn27@cs.drexel.edu
%%
%% Adapted from skeleton code by:
%%
%% 	Konstantinos Bitsakos
%% 	Department of Computer Science 
%% 	University of Maryland, College Park
%% 	kbits@cs.umd.edu
%%
%% Further reference on Intelligent Scissors:
%%	"Intelligent Scissors for Image Composition", E. Mortensen and W. Barret
%%	SIGGRAPH 1995.
%%
%%
%% Given a NxM image computes mask using Intelligent Scissors
%%
%% INPUT
%%	1) img		- N x M x 3 image
%% 
%% OUTPUT
%%	1) mask		- N x M mask
%%
function [mask] = iscissor(img)
  [rows,columns,c] = size(img);


  %%
  %% Compute the link costs for each pixel
  %%
  disp('Computing the cost matrix');
  COST_MAT = compute_cost(img);


  %%
  %% Compute the wire mask iteratively
  %% 
  iterations = double(1);
  wire_mask = zeros(rows, columns);

  
  %%
  %% Get the initial seed point
  %%
  close all;
  figure(1), imshow(img);

  disp('Click the seed point');
  [s_x, s_y] = ginput(1);
  s_x=round(s_x); s_y=round(s_y);

  figure(1); hold on;
  plot(s_x, s_y, 'rx');

  pixelpairs(1,1)=s_x;
  pixelpairs(2,1)=s_y;  

  %%
  %%
  %% Loop until the user has closed the loop
  %%
  %%
  while 1
    user_entry = menu('Choose a function', 'Select a new point', 'Undo last point','Close wire', 'Print current wire','Exit');

    switch user_entry

	%%
	%%
	%% Adding a new point to the wire 
	%%
	%%
	case 1
	  disp('Click the new point')
	  figure(1);	  

	  [e_x, e_y] = ginput(1);
	  e_x=round(e_x); e_y=round(e_y);
	  figure(1); hold on;
	  plot(e_x,e_y, 'bo');

	  pixelpairs(3,iterations)=e_x;
	  pixelpairs(4,iterations)=e_y;
	  pixelpairs(1,iterations+1)=e_x;
	  pixelpairs(2,iterations+1)=e_y;

	  disp('Finding new wire segment');


          wiremask(:,:,iterations)=create_cut(img,COST_MAT,pixelpairs(1,iterations),pixelpairs(2,iterations),pixelpairs(3,iterations),pixelpairs(4,iterations));
          iterations=iterations+1;

	%%
	%%
	%% Undoing last point
	%%
	%%
	case 2
	  disp('Undo');
	  if iterations > 1

            iterations=iterations-1;
            % Mark the point green
            figure(1); hold on;
            plot(pixelpairs(3,iterations),pixelpairs(4,iterations), 'go');
	    
	  end


	%%
	%%
	%% Closing the wire
	%%
	%%
	case 3
	  disp('Finishing wire');

            pixelpairs(3,iterations)=pixelpairs(1,1);
            pixelpairs(4,iterations)=pixelpairs(2,1);

            wiremask(:,:,iterations)=create_cut(img,COST_MAT,pixelpairs(1,iterations),pixelpairs(2,iterations),pixelpairs(3,iterations),pixelpairs(4,iterations));
            iterations = iterations+1;


	%%
	%%
	%% Printing the current wire
	%%
	%%
	case 4	

          wire=zeros(rows,columns);
          
          for i=1:iterations-1
            wire(:,:) =wire(:,:) | wiremask(:,:,i);
          end

          if length(size(img)) == 3
            imbw = double(rgb2gray(img));
          else
            imbw = double(img);
          end

          maxval = max(imbw(:));
          minval = min(imbw(:));
          wirethick = imfilter(wire, fspecial('average', 3)) > 0;
          W = double(wirethick).*maxval + double(~wirethick).*minval;
          Wcomplement =  double(wirethick).*minval + double(~wirethick).*maxval;
          imwire = (cat(3, max(W,imbw), min(Wcomplement,imbw), min(Wcomplement,imbw))-minval)./maxval; 
          
          figure(2), imagesc(imwire);
          axis equal;
          axis off;          


	%%
	%%
	%% Exiting
	%%
	%%
	case 5
	  break
      end
end


%%
%% Compiling the wires
%%
for i=1:iterations-1
    wire(:,:) =wire(:,:) | wiremask(:,:,i);
end

mask=wire;
mask=imfill(mask);
return;
	  


    
  
  

  

