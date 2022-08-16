/*
 *  **************************************************************************
 *
 *  rmsd.c 
 *  (c) 2005 Bosco K Ho
 * 
 *  Implementation of the Kabsch algorithm to find the least-squares
 *  rotation matrix for a superposition between two sets of vectors.
 *  The jacobi transform of the diagonalization of a symmetric matrix
 *  is taken from Numerical Recipes. This piece of code is 
 *  self-contained and *does not require* another library.
 *
 *  **************************************************************************
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published
 *  by the Free Software Foundation; either version 2.1 of the License, or (at
 *  your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,  but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details. 
 *  
 *  You should have received a copy of the GNU Lesser General Public License 
 *  along with this program; if not, write to the Free Software Foundation, 
 *  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *  **************************************************************************
 * 
 */

#ifndef RMSD_H_
#define RMSD_H_

#include "rmsd.h"

#include <stdio.h>
#include <math.h>



/* vector functions using c arrays */

void normalize(float a[3]);



float dot(float a[3], float b[3]);



static void cross(float a[3], float b[3], float c[3]);



/*
 * setup_rotation() 
 *
 *      given two lists of x,y,z coordinates, constructs
 * the correlation R matrix and the E value needed to calculate the
 * least-squares rotation matrix.
 */
void setup_rotation(float **ref_xlist,
                    float **mov_xlist, 
                    int n_list,
                    float mov_com[3],
                    float mov_to_ref[3],
                    float R[3][3],
                    float* E0);


#define ROTATE(a,i,j,k,l) { g = a[i][j]; \
h = a[k][l]; \
a[i][j] = g-s*(h+g*tau); \
a[k][l] = h+s*(g-h*tau); }
/*   
 * jacobi3
 *
 *    computes eigenval and eigen_vec of a real 3x3
 * symmetric matrix. On output, elements of a that are above 
 * the diagonal are destroyed. d[1..3] returns the 
 * eigenval of a. v[1..3][1..3] is a matrix whose 
 * columns contain, on output, the normalized eigen_vec of
 * a. n_rot returns the number of Jacobi rotations that were required.
 */
int jacobi3(float a[3][3], float d[3], float v[3][3], int* n_rot);


/* 
 * diagonalize_symmetric 
 *
 *    Diagonalize a 3x3 matrix & sort eigenval by size
 */
int diagonalize_symmetric(float matrix[3][3], 
                          float eigen_vec[3][3], 
                          float eigenval[3]);


/*
 * calculate_rotation_matrix() 
 *
 *   calculates the rotation matrix U and the
 * rmsd from the R matrix and E0:
 */
int calculate_rotation_matrix(float R[3][3],
                              float U[3][3], 
                              float E0,
                              float* residual);


void calculate_rotation_rmsd(float **ref_xlist,
                             float **mov_xlist, 
                             int n_list,
                             float mov_com[3],
                             float mov_to_ref[3],
                             float U[3][3],
                             float* rmsd);


/*
 * Fast calculation of rmsd w/o calculating a rotation matrix.
 *
 *   Chris Saunders 11/2002 - Fast rmsd calculation by the method of 
 * Kabsch 1978, where the required eigenvalues are found by an 
 * analytical, rather than iterative, method to save time. 
 * The cubic factorization used to accomplish this only produces 
 * stable eigenvalues for the transpose(R]*R matrix of a typical 
 * protein after the whole matrix has been normalized. Note that 
 * the normalization process used here is completely empirical 
 * and that, at the present time, there are **no checks** or 
 * warnings on the quality of the (potentially unstable) cubic 
 * factorization. 
 *
 */
#define PI 3.14159265358979323846
void fast_rmsd(float **ref_xlist,
               float **mov_xlist, 
               int n_list,
               float* rmsd);

#endif