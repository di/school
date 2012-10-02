% Image Scissors
%
% Usage:  wire = scissor(im,s_x,s_y,e_x,e_y)
%
% Arguments:   
%            im      - image to be processed.
%            s_x,s_y - coordinates of the seed point (double)
%            e_x,e_y - coordinates of the end point (double)
%
% Returns:
%            wire    - wire mask of the image
%
% References: 
% Eric Mortensen, William Barrett, "Intelligent Scissors for Image
% Composition", Siggraph 1995
% Web page: http://www.cs.washington.edu/education/courses/455/04wi/projects/project1/web/project1.html
%
% Author: 
% Konstantinos Bitsakos
% Department of Computer Science 
% University of Maryland, College Park
% kbits@cs.umd.edu
%
% February 2004

% You really need to write this whole function.  We have included little
% snippets of code just to demonstrate some functions and declarations
% you might need.

function wire = scissor(im,s_x,s_y,e_x,e_y)
  
    [Size_y,Size_x,Size_z]=size(im);

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %Create CORRELATION kernels for the 8 links %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%%%%%%
    % TODO  The kernels below are filled with zeros.  You need
    % to fill them with the correct values.
    %%%%%%%%

    %LINK 1
    ker(:,:,1)=[0 0 0; 0 0 0 ; 0 0 0];
    
    %LINK 2
    ker(:,:,2)=[0 0 0; 0 0 0; 0 0 0];

    %LINK 3
    ker(:,:,3)=[0 0 0; 0 0 0; 0 0 0];
    
    %LINK 4
    ker(:,:,4)=[0 0 0; 0 0 0; 0 0 0];
    
    %LINK 5
    ker(:,:,5)=[0 0 0; 0 0 0; 0 0 0];
   
    %LINK 6
    ker(:,:,6)=[0 0 0; 0 0 0; 0 0 0];
    
    %LINK 7
    ker(:,:,7)=[0 0 0; 0 0 0; 0 0 0];
    
    %LINK 8
    ker(:,:,8)=[0 0 0; 0 0 0; 0 0 0];
    
    %%%%%%%%
    % TODO Likewise with the lengths.%
    %%%%%%%%
    %Define a 1x8 array with the length of each link
    length=[0 0 0 0 0 0 0 0];
    
    %%%%%%%%%%%%%%%%%%%%
    % PREPROCESS IMAGE %
    %%%%%%%%%%%%%%%%%%%%
    
    for i=1:8
        % TODO  compute the magnitude of the gradient crossing each link, using the kernels you
        % have defined above.  You could, for example, put these magnitudes
        % in matrix whose first two dimensions are the size of the image,
        % and whose third dimension is 8.
        D(:,:,i)= 0;
    end


    %Compute the cost for each link using the formula
    % linkcost(link)=(maxD-D(link))*length(link)
    maxD=max(D(:));

    linkcost=zeros(Size_y,Size_x,1);
    for i=1:8
        linkcost(:,:,i)=0; % TODO %
    end
    
    %%%%%%%%%%%%%%%%%%%%%%%%
    % INITIALIZE VARIABLES %
    %%%%%%%%%%%%%%%%%%%%%%%%
   
    
    global NodeState
    NodeState=zeros(Size_y,Size_x); % Each node will experience three states: INITIAL=0, ACTIVE=1, EXPANDED=2
    % Defining this variable as global will allow you to access it in any
    % subroutines you write, though this may not be necessary.
    
    global Pointers
    % Create an array of pointers and initialize it to Infinity
    Pointers=ones(Size_y,Size_x);
    % Defining this variable as global will allow you to access it in any
    % subroutines you write, though this may not be necessary.
    
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Minimum Cost Path Algorithm %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    %Initialize the priority queue
    % pq is an array with 3 rows: First row contains the x coordinate, the
    % second row the y coordinate and the third row the value for a given
    % point
    global pq
    pq=zeros(3,0); 
    % pq must be defined as a global variable for the routines insert and
    % extractmin to work.
    
    %Set the total cost of seed to be zero    
% TODO %
    
    %insert seed into pq
% TODO %
    
    %Extract the minimum cost point from the priority queue
    [q_x,q_y,q_cost]=extractmin;
    
    
% TODO %
% Now find the shortest path.  See Pseudocode in problem set. 
    
    % Create wire mask
    wire=logical(zeros(Size_y,Size_x));
 
    % Trace back your solution.  The result should be in the matrix wire.
    
    %%%%%%%
    %% TO DO
    %%%%%%%%%
    
    