%%
%% get_correspondences.m
%%
%% Computational Photography Project 2
%%
%% John Novatnack
%% jmn27@cs.drexel.edu
%%
%% Returns two Nx2 matrices that stores the N image correspondences
%%
%% INPUT
%%	1) im1			- N1 x M1 x 3 image
%%	2) im2 			- N1 x M1 x 3 image
%%
%% OUTPUT
%%	1) im1pts		- N x 2 (x,y) list of points from im1
%%	2) im2pts		- N x 2 (x,y) list of points from im2
%%
function [im1pts, im2pts] = get_correspondences(im1, im2)
  [rows,columns,c] = size(im1);

  %%
  %% Create two empty matrices for im1pts and im2pts
  %%
  im1pts = [];
  im2pts = []; 


  %%
  %% Add four corners to the lists
  %%
  im1pts = [1 1; 1 rows; columns 1; columns rows];
  im2pts = [1 1; 1 rows; columns 1; columns rows];


  %%
  %% Display both images for the user
  %% 
  figure(1), imshow(im1);
  figure(2), imshow(im2);

  

  %%
  %% Loop until the user has inputted all of the desired correspondences
  %%
  while 1
    user_entry = menu('Choose an action','Add a point','Exit');

    switch user_entry

	
      %%
      %% Add a new point
      %%
      case 1




	  %%
	  %% Get the point in image 1
	  %%
	  disp('Click on the point in image 1');
	  figure(1);
	  [p1_x,p1_y] =  ginput(1);
	  figure(1); hold on;
	  plot(p1_x,p1_y,'bo');



	  %%
	  %% Get the point in image 2
	  %%
	  disp('Click on the point in image 2');
	  figure(2);
	  [p2_x,p2_y] =  ginput(1);
	  figure(2); hold on;
	  plot(p2_x,p2_y,'bo');

	  
	  %%
	  %% Add the points to the lists
	  %%
	  im1pts = [im1pts; p1_x p1_y];
	  im2pts = [im2pts; p2_x p2_y];



	  %%
	  %% Color the points red 
	  %%
	  figure(1); hold on;
	  plot(p1_x,p1_y,'ro');

	  figure(2); hold on;
	  plot(p2_x,p2_y,'ro');


      %%
      %% Exit
      %%
      case 2	    
	break;
	

    end	  
  end

  

