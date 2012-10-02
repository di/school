%%
%% project1.m
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
%% 
%% Usage:
%%	project1('iscissor','pupp.jpg');
%%	project1('composite','pupp.jpg','cow.jpg','cowdog.jpg',0.9,220,55);
%%	See below for details
%%
function project1(operation,img_p,target_img_p,out_img_p,scale_factor,t_x,t_y)

  %%
  %%
  if(nargin < 2) 
    disp(sprintf('Usage: project1(operation,img_p,target_img_p,out_img_p,scale_factor,t_x,t_y)'));
    disp(sprintf(' Operations:'));
    disp(sprintf('   iscissor - img_p: filename of the image to cut out a region from\n'));
    disp(sprintf('   composite - img_p: filename of the image to extract a region from using the corresponding mask'));
    disp(sprintf('               target_img_p: filename of the image you want to superimpose a region into'));
    disp(sprintf('               out_img_p: output (composited) filename'));
    disp(sprintf('               scale_factor: [0-1] scaling to be applied to the region'));
    disp(sprintf('               t_x: X trasnlation to be applied to the region'));
    disp(sprintf('               t_y: Y translation to be applied to the region'));


  %%
  %% Intelligent Scissors
  %%
  elseif(strcmp(operation,'iscissor'))
		if(nargin ~= 2)
			disp(sprintf('Incorrect arguments'));
			return;
		else
			%%
			%% Load the image and execute Intelligent Scissors
			%%
			img_to_cut = imread(img_p);
			cut_mask = iscissor(img_to_cut);
			%%
			%% Save the mask as <image filename>.mask
			%%
			save(sprintf('%s.mask',img_p),'cut_mask');
		end

	%% 
	%%	Composite
	%%
	elseif(strcmp(operation,'composite'))
		if(nargin ~= 7)
			disp(sprintf('Incorrect arguments'));
			return;
		else
			%% 
			%% Load the target image, the image to be cut out and its
			%% corresponding mask
			%%
			img_to_cut = imread(img_p);
			load('-mat',sprintf('%s.mask',img_p));
			if exist('cut_mask') ~= 1,
				disp(sprintf('Cannot find the mask for %s. Make sure there is a file named %s.mask.',img_p,img_p));
				return;
			end
			target_img = imread(target_img_p);
	
			%%
			%% Create the composite and write it out
			%%
			out_img = composite(target_img,img_to_cut,cut_mask,scale_factor,t_x,t_y);
			imwrite(uint8(out_img),out_img_p);
		end

	%%
	else
		disp(sprintf('Invalid operation'));
	
	end
