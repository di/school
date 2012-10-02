%%
%% barycentric.m
%%
%% Computational Photography Project 2
%%
%%
%% Determines the barycentric coordinates of a point in a triangle
%%
%% INPUT
%%	1) triangle_x		- 1 x 3 row vector containing the x coordinates of the triangle
%%				   points				   
%%	2) triangle_y		- 1 x 3 row vector containing the y coordinates of the triangle
%%				   points				
%%	3,4) x,y   		- x,y coordinates of the point that we want to compute the
%%				  barycentric coordinates of 
function [bary_coord] = barycentric(triangle_x, triangle_y, x, y)

% Compute the barycentric coordinates

    a(1,1) = triangle_x(2) - triangle_x(1);
    a(1,2) = triangle_x(3) - triangle_x(1);
    a(1,3) = x - triangle_x(1);

    a(2,1) = triangle_y(2) - triangle_y(1);
    a(2,2) = triangle_y(3) - triangle_y(1);
    a(2,3) = y - triangle_y(1);
  
    dims = 2;
    
    for j = 1 : dims
    %
    %  Choose a pivot row IPIVOT.
    %
        ipivot = j;
        apivot = a(j,j);

        for i = j+1 : dims
            if ( abs ( apivot ) < abs ( a(i,j) ) )
                apivot = a(i,j);
                ipivot = i;
            end
        end
    %
    %  Interchange.
    %
        temp = a(ipivot,1:dims+1);
        a(ipivot,1:dims+1) = a(j,1:dims+1);
        a(j,1:dims+1) = temp;
    %
    %  A(J,J) becomes 1.
    %
        a(j,j) = 1.0;
        a(j,j+1:dims+1) = a(j,j+1:dims+1) / apivot;
    %
    %  A(I,J) becomes 0.
    %
        for i = 1 : dims

            if ( i ~= j )

            factor = a(i,j);
            a(i,j) = 0.0;
            a(i,j+1:dims+1) = a(i,j+1:dims+1) - factor * a(j,j+1:dims+1);

            end

        end

    end

    bary_coord(1) = a(1,3);
    bary_coord(2) = a(2,3);
    bary_coord(3) = 1.0 - bary_coord(1) - bary_coord(2);
    
    return

  